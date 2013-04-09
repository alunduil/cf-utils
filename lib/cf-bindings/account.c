/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/**
 * Query Parameters:
 *  :limit: Number of results to return.
 *  :marker: Return container names greater than passed UTF-8 string.
 *  :end_marker: Return container names less than passed UTF-8 string.
 *  :format: json or xml to get the requested format.
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

    account->properties[_CONTAINER_COUNT] = ULLONG_MAX;
    account->properties[_OBJECT_COUNT] = ULLONG_MAX;
    account->properties[_BYTE_COUNT] = ULLONG_MAX;

    return account;
}

const unsigned char account_free ( Account* account ) {
    free ( account->name );
    free ( account->api_key );

    free ( account->management_url );
    free ( account->cdn_management_url );
    free ( account->token );

    return 1;
}

/**
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
const unsigned char authenticate ( Account * account, const char user_name[], const char api_key[] ) {
    http_request * req = http_request_create();
    const http_response * resp;

    unsigned char url_index = 0;

    char * urls[2];

	urls[0] = malloc ( sizeof ( char ) * 44 + 1);
	strncpy( urls[0], "https://identity.api.rackspacecloud.com/v1.0", 45);

	urls[1] = malloc ( sizeof ( char ) * 48 + 1);
	strncpy( urls[1], "https://lon.identity.api.rackspacecloud.com/v1.0", 49);

    account->name = malloc ( sizeof ( char ) *strlen ( user_name ) + 1 );
    strcpy ( account->name, user_name );

    account->api_key = malloc ( sizeof ( char ) *strlen ( api_key ) + 1 );
    strcpy ( account->api_key, api_key );

    add_header_to_request ( req, "X-Auth-User", account->name );
    add_header_to_request ( req, "X-Auth-Key", account->api_key );

    do {
        req->url = urls[url_index];
        resp = request ( req );

        switch ( atoi ( resp->status_code ) ) {
        case 204:
            /** @todo Thread safety for the following assignment. */
            account->management_url = ( char * ) get_header_from_response ( ( const http_response * ) &resp, "X-Storage-Url" );
            account->cdn_management_url = ( char * ) get_header_from_response ( ( const http_response * ) &resp, "X-CDN-Management-Url" );
            account->token = ( char * ) get_header_from_response ( ( const http_response * ) &resp, "X-Auth-Token" );

            return 1;
        case 401:

#ifdef EACCESS /*!< @todo Make this work consistently. */
            errno = EACCESS;
#endif

            break;
        }
    } while ( url_index++ < 2 );

    return 0;
}

/*
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
const unsigned long long int _get_account_property ( Account * account, const _PROPERTY_MAP property, const unsigned char use_cache ) {
    http_request * req = http_request_create();
    const http_response * resp;

    if ( !use_cache ) {
        add_header_to_request ( req, "X-Auth-Token", account->token ); /*!< @todo Wrap token in thread-save function. */

        req->url = account->management_url; /*!< @todo Wrap URL in thread-safe function. */
        req->method = "head";

        resp = request ( req );

        switch ( atoi ( resp->status_code ) ) {
        case 204:
            account->properties[_CONTAINER_COUNT] = ( unsigned long long int ) strtoll ( get_header_from_response ( ( const http_response * ) &resp, "X-Account-Container-Count" ), NULL, 10 );
            account->properties[_OBJECT_COUNT] = ( unsigned long long int ) strtoll ( get_header_from_response ( ( const http_response * ) &resp, "X-Account-Object-Count" ), NULL, 10 );
            account->properties[_BYTE_COUNT] = ( unsigned long long int ) strtoll ( get_header_from_response ( ( const http_response * ) &resp, "X-Account-Bytes-Count" ), NULL, 10 );

            break;
        }
    }

    http_response_free ( ( void * ) resp );

    return account->properties[property];
}

const unsigned long long int get_account_container_count ( Account * account, const unsigned char use_cache ) {
    return _get_account_property ( account, _CONTAINER_COUNT, use_cache );
}

const unsigned long long int get_account_object_count ( Account * account, const unsigned char use_cache ) {
    return _get_account_property ( account, _OBJECT_COUNT, use_cache );
}

const unsigned long long int get_account_byte_count ( Account * account, const unsigned char use_cache ) {
    return _get_account_property ( account, _BYTE_COUNT, use_cache );
}
