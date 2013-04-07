/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/**
 * Query Parameters:
 *  :limit: Number of results to return.
 *  :marker: Return container names greater than passed UTF-8 string.
 *  :end_marker: Return container names less than passed UTF-8 string.
 *  :format: json or xml to get the requested format.
 */

#include <errno.h>
#include <limits.h>

#include "../uhttpc/request.h"
#include "../uhttpc/response.h"

#include "account.h"

/*
 * Example HTTP Request:
 *
 * HEAD /v1.0/jdoe HTTP/1.1
 * Host: storage.clouddrive.com
 * X-Auth-Token: eaaafd18-0fed-4b3a-81b4-663c99ec1cbb
 *
 * Example HTTP Response:
 *
 * HTTP/1.1 204 No Content
 * Content-Type: text/html; charset=UTF-8
 * X-Account-Object-Count: 12
 * X-Trans-Id: txc44b00fccb6a49318626d3cac1d2cdb6
 * Date: Tue, 06 Nov 2012 19:50:04 GMT
 * X-Account-Bytes-Used: 10373619
 * Content-Length: 0
 * X-Account-Container-Count: 5
 */
const unsigned long long int get_account_property(Account * account, const _PROPERTY_MAP property, const unsigned char use_cache) {
	http_request * req = http_reqeust_create();
	const http_response * resp;

	/**
	 * @brief property cache.
	 *
	 * The size of an unsigned long long int should be so ridiculous that it's
	 * never hit … we'll see how long that lasts.
	 */
	static unsigned long long int cache[3] = {
		ULLONG_MAX,
		ULLONG_MAX,
		ULLONG_MAX
	};

	if (
		!use_cache ||
		cache[_CONTAINER_COUNT] == ULLONG_MAX ||
		cache[_OBJECT_COUNT] == ULLONG_MAX ||
		cache[_BYTE_COUNT] == ULLONG_MAX
	) {
		add_header_to_request(&req, "X-Auth-Token", auth_data.token); /*!< @todo Wrap token in thread-save function. */

		req.url = auth_data.management_url; /*!< @todo Wrap URL in thread-safe function. */
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

	free_response((void *)resp);

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

const unsigned char authenticate(const char * user_name, const char *api_key) {
	http_request req = DEFAULT_HTTP_REQUEST;
	const http_response * resp;

	unsigned char url_index = 0;

	char * urls[2] = {
		"https://identity.api.rackspacecloud.com/v1.0",
		"https://lon.identity.api.rackspacecloud.com/v1.0"
	};

	add_header_to_request(&req, "X-Auth-User", user_name);
	add_header_to_request(&req, "X-Auth-Key", api_key);

	while (url_index++ < 2) {
		req.url = urls[url_index];
		resp = request(&req);

		switch (resp->status_code) {
			case 204:
				/** @todo Thread safety for the following assignment. */
				auth_data.management_url = (char *)get_header_from_response((const http_response *)&resp, "X-Storage-Url");
				auth_data.cdn_management_url = (char *)get_header_from_response((const http_response *)&resp, "X-CDN-Management-Url");
				auth_data.token = (char *)get_header_from_response((const http_response *)&resp, "X-Auth-Token");

				return TRUE;
			case 401:

				#ifdef EACCESS /*!< @todo Make this work consistently. */
				errno = EACCESS;
				#endif

				break;
		}
	}

	return FALSE;
}
