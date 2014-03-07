/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "request.h"

http_request* http_request_create() {
    int index = 0;

    http_request* req = ( http_request* ) malloc ( sizeof ( http_request ) );

    req->method = "get";
    req->url = NULL;
    strncpy ( req->http_version, "HTTP/1.1", 9 );

    req->query_count = 0;

    req->header_count = 0;

    while ( index++ < 90 )
        req->headers[index] = NULL;

    req->body = NULL;

    return req;
}

unsigned char http_request_free ( http_request* req ) {
    int index = 0;

    free ( req->method );
    free ( req->url );

    while ( index++ < 90 )
        free ( req->headers[index] );

    free ( req->body );

    return 1;
}

unsigned char add_query_parameter_to_request ( http_request * req, const char query_key[], const char query_value[] ) {
    char prefix[2] = "&";

    if ( req->query_count > 0 )
        strncpy ( prefix, "?", 2 );

    req->url = realloc ( req->url, sizeof ( char ) * ( strlen ( req->url ) + strlen ( query_key ) + strlen ( query_value ) + 2 ) );

    strcat ( req->url, prefix );
    strcat ( req->url, query_key );
    strcat ( req->url, "=" );
    strcat ( req->url, query_value );

    return 1;
}

unsigned char add_header_to_request ( http_request * req, const char header_name[], const char header_value[] ) {
    if ( req->header_count + 1 >= 90 ) {
        errno = ENOSPC;
        return 0;
    }

    req->headers[req->header_count] = malloc ( sizeof ( char ) *strlen ( header_name ) + sizeof ( char ) *strlen ( header_value ) + 2 );
    req->headers[req->header_count][0] = 0;

    strcat ( req->headers[req->header_count], header_name );
    strcat ( req->headers[req->header_count], ":" );
    strcat ( req->headers[req->header_count], header_value );

    ++req->header_count;

    return 1;
}

const char * get_header_from_request ( const http_request * req, const char header_name[] ) {
    unsigned char index = 0;

    do {
        if ( strcmp ( req->headers[index], header_name ) == 0 )
            return req->headers[index];
    } while ( ++index < req->header_count );

    return NULL;
}
