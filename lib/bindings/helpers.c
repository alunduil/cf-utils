/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <curl/curl.h>

typedef struct {
	char * method;
	char * uri;
	float http_version;
	
	char * headers[];
	
	char * body;
} http_request;

typedef struct {
	float http_version;
	int status_code;
	char * reason_phrase;
	
	char * headers[];
	
	char * body;
} http_response;

/**
 * @brief Perform an HTTP request given the passed parameters.
 * 
 * @param[in] req HTTP Request
 * 
 * @returns HTTP Response
 */
http_response request(const http_request & req) {
	CURL *curl_handle;
	
	CURLcode result;
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
	
	curl = curl_easy_init();
	
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, req.uri);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, req.headers);
		
		
	}
}
