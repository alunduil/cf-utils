/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <errno.h>

#include "bindings/authentication.h"
#include "bindings/helpers.h"

#include "bindings/account.h"

const unsigned long long int get_account_property(const PROPERTY_MAP property, const unsigned char use_cache) {
	http_request req = DEFAULT_HTTP_REQUEST;
	const http_response * resp;

	int cache[3] = { -1, -1, -1 };

	if (
		!use_cache ||
		cache[CONTAINER_COUNT] < 0 ||
		cache[OBJECT_COUNT] < 0 ||
		cache[BYTE_COUNT] < 0
	) {
		add_header(&req, "X-Auth-Token", auth_data.token);

		req.url = auth_data.management_url;
		req.method = "head";

		resp = request(&req);

		switch (resp->status_code) {
			case 204:
				cache[CONTAINER_COUNT] = (unsigned long long int)strtoll(get_header_from_response((const http_response *)&resp, "X-Account-Container-Count"), NULL, 10);
				cache[OBJECT_COUNT] = (unsigned long long int)strtoll(get_header_from_response((const http_response *)&resp, "X-Account-Object-Count"), NULL, 10);
				cache[BYTE_COUNT] = (unsigned long long int)strtoll(get_header_from_response((const http_response *)&resp, "X-Account-Bytes-Count"), NULL, 10);

				break;
		}
	}

	return cache[property];
}

const unsigned long long int get_account_container_count(const unsigned char use_cache) {
	return get_account_property(CONTAINER_COUNT, use_cache);
}

const unsigned long long int get_account_object_count(const unsigned char use_cache) {
	return get_account_property(OBJECT_COUNT, use_cache);
}

const unsigned long long int get_account_byte_count(const unsigned char use_cache) {
	return get_account_property(BYTE_COUNT, use_cache);
}
