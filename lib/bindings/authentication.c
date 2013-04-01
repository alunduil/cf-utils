/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <errno.h>

#include "bindings/helpers.h"

#include "bindings/authentication.h"

int authenticate(char *user_name, char *api_key) {
	http_request req;
	const http_response * resp;

	int url_index = 0;

	char * urls[2] = {
		"https://identity.api.rackspacecloud.com/v1.0",
		"https://lon.identity.api.rackspacecloud.com/v1.0"
	};

	add_header(&req, "X-Auth-User", user_name);
	add_header(&req, "X-Auth-Key", api_key);

	while (url_index++ < 2) {
		req.url = urls[url_index];
		resp = request(&req);

		switch (resp->status_code) {
			case 204:
				auth_data.management_url = (char *)get_header_from_response((const http_response *)&resp, "X-Storage-Url");
				auth_data.cdn_management_url = (char *)get_header_from_response((const http_response *)&resp, "X-CDN-Management-Url");
				auth_data.token = (char *)get_header_from_response((const http_response *)&resp, "X-Auth-Token");

				return 1;
			case 401:
#ifdef EACCESS
				/** @todo Make this work consistently. */
				errno = EACCESS;
#endif
				continue;
		}
	}

	return (long)NULL;
}
