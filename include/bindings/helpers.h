/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>

/**
 * @brief Model of an HTTP request.
 * @note Default values are provided by DEFAULT_HTTP_REQUEST.
 */
typedef struct {
	char * method; /*!< HTTP method used for request. */
	char * url; /*!< URL being requested. */
	float http_version; /*!< HTTP version string (i.e. 1.1 for HTTP/1.1). */

	char * body; /*!< Optional Body of the request. */

	/**
	 * @brief Number of headers passed in this request.
	 * @note The upstream API limits us to 90 headers thus we only need space
	 * for one byte of integer.
	 */
	unsigned char headers_length;
	char ** headers; /*!< Array of Headers as Strings of the form: HEADER:VALUE. */
} http_request;

const http_request DEFAULT_HTTP_REQUEST = {
	.method = "get",
	.http_version = 1.1,
	.headers_length = 0,
	.body = NULL
};

/**
 * @brief Model of an HTTP response.
 * @note Default values are provided by DEFAULT_HTTP_RESPONSE.
 */
typedef struct {
	float http_version; /*!< @see http_request::http_version */
	unsigned short int status_code; /*!< HTTP Status Code returned. */
	char * reason_phrase; /*!< HTTP Reason Phrase returned. */

	char * body; /*!< @see http_request::body */

	unsigned char headers_length; /*!< @see http_request::headers_length */
	char ** headers; /*!< @see http_request::headers */
} http_response;

const http_response DEFAULT_HTTP_RESPONSE = {
	.http_version = 1.1,
	.headers_length = 0,
	.body = NULL
};

/**
 * @brief Check request meets cloud files request limits.
 *
 * @param[in] req HTTP Request
 *
 * @see http_request
 *
 * @returns 1 if valid; otherwise NULL.
 */
short int check_request(const http_request * req);

/**
 * @brief Add a header to an HTTP request.
 *
 * @param[in,out] req HTTP Request
 * @param[in] header_name HTTP Header Name
 * @param[in] header_value HTTP Header Value
 *
 * @see http_request
 */
void add_header(http_request * req, const char * header_name, const char * header_value);

/**
 * @brief Get a particular header's value from an HTTP request.
 *
 * @param[in] req HTTP Request
 * @param[in] header_name HTTP Header Name
 *
 * @see http_request
 *
 * @returns Header's Value (char *).
 */
const char * get_header_from_request(const http_request * req, const char * header_name);

/**
 * @brief Get a particular header's value from an HTTP response.
 *
 * @param[in] resp HTTP Response
 * @param[in] header_name HTTP Header Name
 *
 * @see http_response
 *
 * @returns Header's Value (char *)
 */
const char * get_header_from_response(const http_response * resp, const char * header_name);

/**
 * @brief Perform an HTTP request given the passed parameters.
 *
 * @param[in] req HTTP Request
 * @see http_request
 *
 * @returns An http_resposne.
 * @see http_response
 */
const http_response * request(const http_request * req);
