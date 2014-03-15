/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "../uhttpc/request.h"
#include "../uhttpc/response.h"
#include "../uhttpc/actions.h"

#include "account.h"

Account* account_create() {
    Account * account = ( Account * ) malloc ( sizeof ( Account ) );

    account->name = NULL;
    account->api_key = NULL;

    account->management_url = NULL;
    account->cdn_management_url = NULL;
    account->token = NULL;

    account->_properties[_CONTAINER_COUNT] = ULLONG_MAX;
    account->_properties[_OBJECT_COUNT] = ULLONG_MAX;
    account->_properties[_BYTE_COUNT] = ULLONG_MAX;

    return account;
}

unsigned char account_free ( Account* account ) {
    free ( account->name );
    free ( account->api_key );

    free ( account->management_url );
    free ( account->cdn_management_url );
    free ( account->token );

    return 1;
}

/**
 * @todo Test the following in uhttpc…
 *
 * Example Request HTTP:
 *
 * GET /v1.0 HTTP/1.1
 * Host: identity.api.rackspacecloud.com
 * X-Auth-User: jdoe
 * X-Auth-Key: a86850deb2742ec3cb41518e26aa2d89
 *
 * Example Response HTTP:
 *
 * HTTP/1.1 204 No Content
 * Date: Mon, 12 Nov 2007 15:32:21 GMT
 * X-Storage-Url: https://storage.clouddrive.com/v1/CF_xer7_34
 * X-CDN-Management-Url: https://cdn.clouddrive.com/v1/CF_xer7_34
 * X-Auth-Token: eaaafd18-0fed-4b3a-81b4-663c99ec1cbb
 * Content-Length: 0
 * Content-Type: text/plain; charset=UTF-8
 *
 * The X-Storage-Url is the endpoint used for all other API calls after
 * successful authentication.
 */
Account * authenticate ( Account * account, const char user_name[], const char api_key[] ) {
    http_request * req = http_request_create();
    HTTPResponse * resp;

    Account * ret = NULL;

    unsigned char url_index = 0;

    char * urls[2];

    /**
     * Tries to request a login token from the authentication endpoint by first
     * trying the global endpoint URL, https://identity.api.rackspacecloud.com/v1.0.
     * If this URL doesn't let the user authenticate we try the London endpoint,
     * https://lon.identity.api.rackspacecloud.com/v1.0.  This code will be removed
     * when there is only one authentication endpoint.
     */

    urls[0] = malloc ( sizeof ( char ) * ( 44 + 1 ) );
    strncpy ( urls[0], "https://identity.api.rackspacecloud.com/v1.0", 45 );

    urls[1] = malloc ( sizeof ( char ) * ( 48 + 1 ) );
    strncpy ( urls[1], "https://lon.identity.api.rackspacecloud.com/v1.0", 49 );

    account->name = malloc ( sizeof ( char ) * ( strlen ( user_name ) + 1 ) );
    strcpy ( account->name, user_name );

    account->api_key = malloc ( sizeof ( char ) * ( strlen ( api_key ) + 1 ) );
    strcpy ( account->api_key, api_key );

    add_header_to_request ( req, "X-Auth-User", account->name );
    add_header_to_request ( req, "X-Auth-Key", account->api_key );

    do {
        req->url = urls[url_index];
        resp = http ( req );

        switch ( atoi ( resp->status_code ) ) {
        case 204:
            /** @todo Thread safety for the following assignment or let user handle? */
            account->management_url = get_header_from_response ( resp, "X-Storage-Url" );
            account->cdn_management_url = get_header_from_response ( resp, "X-CDN-Management-Url" );
            account->token = get_header_from_response ( resp, "X-Auth-Token" );

            ret = account;

            break;
        case 401:
            errno = EACCES;

            break;
        }
    } while ( !ret && url_index++ < 2 );

    free ( urls[0] );
    free ( urls[1] );

    http_request_free ( req );
    http_response_free ( resp );

    return ret;
}

/**
 * @todo Test the following in uhttpc …
 *
 * Example HTTP Request:
 *
 * HEAD /v1.0/jdoe HTTP/1.1
 * Host: storage.clouddrive.com
 * X-Auth-Token: eaaafd18-0fed-4b3a-81b4-663c99ec1cbb
 *
 * Example HTTP Response:
 *
 * HTTP/1.1 204 No Content
 * Content-Type: text/html; charset=UTF-8
 * X-Account-Object-Count: 12
 * X-Trans-Id: txc44b00fccb6a49318626d3cac1d2cdb6
 * Date: Tue, 06 Nov 2012 19:50:04 GMT
 * X-Account-Bytes-Used: 10373619
 * Content-Length: 0
 * X-Account-Container-Count: 5
 */
unsigned long int _get_account_property ( Account * account, const _PROPERTY_MAP property, const unsigned char use_cache ) {
    http_request * req = http_request_create();
    HTTPResponse * resp;

    if ( !use_cache ) {
        add_header_to_request ( req, "X-Auth-Token", account->token ); /*!< @todo Wrap token in thread-save function. */

        req->url = account->management_url; /*!< @todo Wrap URL in thread-safe function. */
        req->method = "head";

        resp = http ( req );

        switch ( atoi ( resp->status_code ) ) {
        case 204:
            account->_properties[_CONTAINER_COUNT] = strtoull ( get_header_from_response ( resp, "X-Account-Container-Count" ), NULL, 10 );
            account->_properties[_OBJECT_COUNT] = strtoull ( get_header_from_response ( resp, "X-Account-Object-Count" ), NULL, 10 );
            account->_properties[_BYTE_COUNT] = strtoull ( get_header_from_response ( resp, "X-Account-Bytes-Count" ), NULL, 10 );

            break;
        }
    }

    http_request_free ( req );
    http_response_free ( resp );

    return account->_properties[property];
}

unsigned long int get_account_container_count ( Account * account, const unsigned char use_cache ) {
    return _get_account_property ( account, _CONTAINER_COUNT, use_cache );
}

unsigned long int get_account_object_count ( Account * account, const unsigned char use_cache ) {
    return _get_account_property ( account, _OBJECT_COUNT, use_cache );
}

unsigned long int get_account_byte_count ( Account * account, const unsigned char use_cache ) {
    return _get_account_property ( account, _BYTE_COUNT, use_cache );
}
