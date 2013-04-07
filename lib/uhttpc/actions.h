/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_UHTTPC_ACTION_H
#define CF_UHTTPC_ACTION_H

#include "request.h"
#include "response.h"

/**
 * @brief Fill the request passed and return a filled response.
 *
 * @param[in] req http_request with desired parameters
 *
 * @returns http_response with server's response
 */
http_response * request(const http_request * req);

#endif
