/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../uhttpc/request.h"
#include "../uhttpc/response.h"
#include "../uhttpc/actions.h"

#include "container.h"

/**
 * @todo URL Encode Names
 * @todo UTF-8 Encode Names
 * @todo 256 Bytes in Name after URL encoding
 * @todo CDN URI
 * @todo Expires
 * @todo Cache-Control
 */

const unsigned long int get_container_names ( const Account * account, char * names[], unsigned long int * length ) {
    http_request * req = http_request_create();
    const http_response * resp;

    char name[256] = "";
    unsigned short int body_index = 0;
    unsigned int body_length = 0;

    char name_length[10];

    add_header_to_request ( req, "X-Auth-Token", account->token );

    sprintf ( name_length, "%lu", *length );
    add_query_parameter_to_request ( req, "limit", name_length );

    req->url = account->management_url;

    resp = request ( req );

    *length = 0;

    switch ( atoi ( resp->status_code ) ) {
    case 204:
        names = NULL;

        break;
    case 200:
        body_length = strlen ( resp->body );
        do {
            if ( resp->body[body_index] == '\n' ) {
                names = realloc ( names, ( ++ ( *length ) ) * sizeof ( name ) );
                strncpy ( names[*length], name, 256 );
                name[0] = 0;
            } else
                strncat ( name, &resp->body[body_index], 1 );
        } while ( body_index < body_index++ );

        break;
    }

    http_request_free ( ( void * ) req );
    http_response_free ( ( void * ) resp );

    return * length;
}

const unsigned long int get_container_details ( const Account * account, container_details details[], unsigned long int * length ) {
    http_request * req = http_request_create();
    const http_response * resp;


}
