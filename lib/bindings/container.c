/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdio.h>
#include <string.h>

#include "bindings/authentication.h"
#include "bindings/helpers.h"

#include "bindings/container.h"

/**
 * @todo URL Encode Names
 * @todo UTF-8 Encode Names
 * @todo 256 Bytes in Name after URL encoding
 * @todo CDN URI
 * @todo Expires
 * @todo Cache-Control
 */

const unsigned long int get_container_names(char * names[], unsigned long int * length) {
	http_request req = DEFAULT_HTTP_REQUEST;
	const http_response * resp;

	char name[256] = "";
	unsigned short int body_index = 0;
	unsigned int body_length = 0;

	char tmp[10];

	add_header_to_request(&req, "X-Auth-Token", auth_data.token);

	sprintf(tmp, "%lu", *length);
	add_query_parameter_to_request(&req, "limit", tmp);

	req.url = auth_data.management_url;

	resp = request(&req);

	switch (resp->status_code) {
		case 204:
			length = 0;
			names = NULL;

			break;
		case 200:
			body_length = strlen(resp->body);
			for (body_index = 0; body_index < body_length; ++body_index) {
				if (resp->body[body_index] == '\n') {
					names = realloc(names, (++(*length)) * sizeof(name));
					names[*length] = strncpy(names[*length], name, 256);
					name[0] = 0;
				} else
					strncat(name, (const char *)resp->body[body_index], 1); /*!< @todo Use strtok instead. */
			}

			break;
	}

	free_response((void *)resp);

	return TRUE;
}

const unsigned long int get_container_details(container_details details[], unsigned long int * length) {
	http_request req = DEFAULT_HTTP_REQUEST;
	const http_response * resp;


}
