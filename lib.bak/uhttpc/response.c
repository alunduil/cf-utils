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

HTTPResponse * http_response_create() {
    HTTPResponse * resp = (HTTPResponse *) malloc(sizeof(HTTPResponse));

    strncpy(resp->http_version, "HTTP/1.1", 9);
    strncpy(resp->status_code, "200", 4);
    resp->reason_phrase = NULL;

    resp->headers = NULL;

    resp->body = NULL;

    return resp;
}

void http_response_free(HTTPResponse * resp) {
    free(resp->reason_phrase);

    free(resp->headers);

    free(resp->body);
}

char* get_header_from_response(const HTTPResponse* resp, const char header_name[])
{
	HTTPHeader * iter = resp->headers;
	char * result = NULL;

	while (iter != NULL) {
		if (strncmp(iter->name, header_name, strlen(iter->name)) == 0) {
			result = iter->value;
		}
	}

	return result;
}
