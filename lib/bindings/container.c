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

int get_container_names(char ** names, unsigned int * length) {
	http_request req = DEFAULT_HTTP_REQUEST;
	const http_response * resp;

	char name[256];

	char question_mark = 0;
	char limit[16];

	add_header(&req, "X-Auth-Token", auth_data.token);

	req.url = auth_data.management_url;

	if (*length > 0) {
		if (question_mark) 
		sprintf(limit, "?limit=%u", *length);
		strcat(req.url, limit);
	}

	resp = request(&req);

	switch (resp->status_code) {
		case 204:
			length = 0;
			names = NULL;

			break;
		case 200:
			while (resp->body

			/** Containers present! */

			break;
	}

	return 1;
}
