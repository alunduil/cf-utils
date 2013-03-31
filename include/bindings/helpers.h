/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/** @brief Model of an HTTP request. */
typedef struct {
	char * method; /*!< HTTP method used for request. */
	char * url; /*!< URL being requested. */
	float http_versioni = 1.1; /*!< HTTP version string (i.e. 1.1 for HTTP/1.1). */

	int headers_length = 0; /*!< Number of Headers being passed in this request. */
	char * headers[]; /*!< Array of Headers as Strings of the form:
	HEADER:VALUE. */

	char * body = NULL; /*!< Optional Body of the request. */
} http_request;

/** @brief Model of an HTTP response. */
typedef struct {
	float http_version = 1.1; /*!< @see http_request::http_version */
	int status_code; /*!< HTTP Status Code returned. */
	char * reason_phrase; /*!< HTTP Reason Phrase returned. */

	int headers_length = 0; /*!< @see http_request::headers_length */
	char * headers[]; /*!< @see http_request::headers */

	char * body = NULL; /*!< @see http_request::body */
} http_response;

/**
 * @brief Check request meets cloud files request limits.
 *
 * @param[in] req HTTP Request
 *
 * @see http_request
 *
 * @returns 1 if valid; otherwise NULL.
 */
int check_request(const http_request & req);

/**
 * @brief Add a header to an HTTP request.
 *
 * @param[in,out] req HTTP Request
 * @param[in] header_name HTTP Header Name
 * @param[in] header_value HTTP Header Value
 *
 * @see http_request
 */
void add_header(http_request & req, const char * header_name, const char * header_value);

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
const char & get_header(const http_request & req, const char * header_name);

/**
 * @brief Perform an HTTP request given the passed parameters.
 *
 * @param[in] req HTTP Request
 * @see http_request
 *
 * @returns An http_resposne.
 * @see http_response
 */
http_response request(const http_request & req);
