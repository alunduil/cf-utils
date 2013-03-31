/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include "bindings/authentication.h"
#include "bindings/helpers.h"

int get_container_names(char names[][], int & length) {
	http_request req;
	http_response * resp;

	add_header(req, "X-Auth-Token", auth_data.token);

	req.url = auth_data.management_url;

	resp = request(req);

	switch (resp->status_code) {
		case 204:
			length = 0;
			names = NULL;

			break;
		case 200:

			/** Containers present! */

			break;
	}

	return 1;
}
