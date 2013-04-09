/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>

#include "response.h"

http_response* http_response_create() {
    int index = 0;

    http_response* resp = ( http_response* ) malloc ( sizeof ( http_response ) );

    strncpy ( resp->http_version, "HTTP/1.1", 9 );
    strncpy ( resp->status_code, "200", 4 );
    resp->reason_phrase = NULL;

    while ( index++ < 90 )
        resp->headers[index] = NULL;

    resp->body = NULL;
}

const unsigned char http_response_free ( http_response* resp ) {
    int index = 0;

    free ( resp->reason_phrase );

    while ( index++ < 90 )
        free ( resp->headers[index] );

    free ( resp->body );

    return 1;
}
