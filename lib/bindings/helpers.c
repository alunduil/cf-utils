/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <curl/curl.h>

#include "bindings/helpers.h"

http_response request(const http_request & req) {
	CURL *curl_handle;
	CURLcode result;

	int i = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl_handle = curl_easy_init();

	if (curl_handle) {
#ifndef NDEBUG
		curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1);
#endif

#if 0
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, NULL); /*!< size_t function( char *ptr, size_t size, size_t nmemb, void *userdata) */
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, NULL); /*!< FILE * */
#endif

#if 0
		curl_easy_setopt(curl_handle, CURLOPT_READFUNCTION, NULL); /*!< size_t function( void *ptr, size_t size, size_t nmemb, void *userdata) */
		curl_easy_setopt(curl_handle, CURLOPT_READDATA, NULL); /*!< FILE * */
#endif

		curl_easy_setopt(curl_handle, CURLOPT_URL, req.url);
	}
}
