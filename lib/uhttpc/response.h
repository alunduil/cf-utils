/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_UHTTPC_RESPONSE_H
#define CF_UHTTPC_RESPONSE_H

/**
 * @brief Model of an HTTP response.
 * @note Default values are provided by DEFAULT_HTTP_RESPONSE.
 */
typedef struct {
    char http_version[9]; /*!< HTTP Version. */
    char status_code[4]; /*!< HTTP Status Code. */
    char * reason_phrase; /*!< HTTP Reason Phrase. */

    char * headers[90]; /*!< Array of Headers in the form: HEADER:VALUE. */

    char * body; /*!< Optional Body */
} http_response;

/**
 * @brief Allocate an http_response and initialize parameters to defaults.
 *
 * @returns An initialized http_response pointer.
 */
http_response * http_response_create();

/**
 * @brief Properly free an http_response.
 *
 * @param[in] resp The response to free.
 *
 * @returns 0 if an error occurs (also sets errno); otherwise, 1.
 */
const unsigned char http_response_free ( http_response * resp );

/**
 * @brief Add a header to an HTTP response.
 *
 * @param[in,out] req HTTP Response
 * @param[in] header_name HTTP Header Name
 * @param[in] header_value HTTP Header Value
 *
 * @returns 0 if an error and sets errno; otherwise, 1
 *
 * @see http_response
 */
const unsigned char add_header_to_response ( http_response * resp, const char header_name[], const char header_value[] );

/**
 * @brief Get a particular header's value from an HTTP response.
 *
 * @param[in] resp HTTP Response
 * @param[in] header_name HTTP Header Name
 *
 * @see http_response
 *
 * @returns Header's Value.
 */
const char * get_header_from_response ( const http_response * resp, const char header_name[] );

#endif
