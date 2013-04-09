/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>

#include "request.h"

http_request* http_reqeust_create() {
    int index = 0;

    http_request* req = ( http_request* ) malloc ( sizeof ( http_request ) );

    req->method = "get";
    req->url = NULL;
    strncpy ( req->http_version, "HTTP/1.1", 9 );

    while ( index++ < 90 )
        req->headers[index] = NULL;

    req->headers[0] = NULL;

    req->body = NULL;
}

const unsigned char http_request_free ( http_request* req ) {
    int index = 0;

    free ( req->method );
    free ( req->url );

    while ( index++ < 90 )
        free ( req->headers[index] );

    free ( req->body );

    return 1;
}
