/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_UHTTPC_RESPONSE_H
#define CF_UHTTPC_RESPONSE_H

#include "common.h"

typedef struct {
    char http_version[9]; /*!< HTTP Version. */
    char status_code[4]; /*!< HTTP Status Code. */
    char * reason_phrase; /*!< HTTP Reason Phrase. */

    HTTPHeader * headers; /*!< HTTP Headers */
    unsigned char header_count; /*!< HTTP Header Count */

    char * body; /*!< HTTP Body */
} HTTPResponse;

/**
 * @brief Allocate an HTTPResponse with sane defaults.
 *
 * @returns An initialized HTTPResponse pointer.
 */
HTTPResponse * http_response_create();

/**
 * @brief Properly free an http_response.
 *
 * @param[in] resp The response to free.
 */
void http_response_free(HTTPResponse * resp);

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
unsigned char add_header_to_response ( HTTPResponse * resp, const char header_name[], const char header_value[] );

/**
 * @brief Get a particular header's value from an HTTP response.
 *
 * @param[in] resp HTTP Response
 * @param[in] header_name HTTP Header Name
 *
 * @see http_response
 *
 * @todo Remove const declaration?
 *
 * @returns Header's Value.
 */
char * get_header_from_response ( const HTTPResponse * resp, const char header_name[] );

#endif
