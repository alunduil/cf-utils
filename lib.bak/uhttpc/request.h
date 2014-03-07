/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_UHTTPC_REQUEST_H
#define CF_UHTTPC_REQUEST_H

typedef struct {
    char method[7]; /*!< HTTP Method. */
    char * url; /*!< URL. */
    char http_version[9]; /*!< HTTP Version. */

    unsigned char query_count; /*!< Number of query parameters on URL. */

    char * headers; /*!< Array of Headers in the form: HEADER:VALUE. */

    char * body; /*!< Optional Body */
} HTTPRequest;

/**
 * @brief Allocate an http_request and initialize parameters to defaults.
 *
 * @returns An initialized http_request pointer.
 */
http_request * http_request_create();

/**
 * @brief Properly free an http_request.
 *
 * @param[in] req The request to free.
 *
 * @returns 0 if an error occurs (also sets errno); otherwise, 1.
 */
unsigned char http_request_free ( http_request * req );

/**
 * @brief Add query parameter to HTTP request.
 * @param[in,out] req HTTP Request
 * @param[in] query_key Query Parameter Name
 * @param[in] query_value Query Parameter Value
 *
 * @returns 0 if an error occurs (also sets errno); otherwise, 1
 *
 * @see http_request
 */
unsigned char add_query_parameter_to_request ( http_request * req, const char query_key[], const char query_value[] );

/**
 * @brief Add a header to an HTTP request.
 *
 * @param[in,out] req HTTP Request
 * @param[in] header_name HTTP Header Name
 * @param[in] header_value HTTP Header Value
 *
 * @note Maximum of 90 headers per request.
 * @note Maximum of 4096 bytes for all headers
 *
 * @returns 0 if an error and sets errno; otherwise, 1
 *
 * @see http_request
 */
unsigned char add_header_to_request ( http_request * req, const char header_name[], const char header_value[] );

/**
 * @brief Get a requested header's value from an HTTP request.
 *
 * @param[in] req HTTP Request
 * @param[in] header_name HTTP Header Name
 *
 * @see http_request
 *
 * @returns Header's Value.
 */
const char * get_header_from_request ( const http_request * req, const char header_name[] );

#endif
