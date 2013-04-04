/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_UTILS_BINDINGS_ACCOUNT
#define CF_UTILS_BINDINGS_ACCOUNT

/**
 * @brief Map of properties that can be requested in an account.
 */
typedef enum {
	CONTAINER_COUNT = 0, /*!< Count of containers in an account. */
	OBJECT_COUNT, /*!< Count of objects in an account. */
	BYTE_COUNT /*!< Total bytes used in account. */
} PROPERTY_MAP;

/**
 * Query Parameters:
 *  :limit: Number of results to return.
 *  :marker: Return container names greater than passed UTF-8 string.
 *  :end_marker: Return container names less than passed UTF-8 string.
 *  :format: json or xml to get the requested format.
 *  :prefix: not used in account!
 */

/**
 * @brief Get requested account property.
 *
 * @param[in] property Specifies which property's value to return.
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @returns Requested account property.
 *
 * @note Not intended for direct use.  Please, use on of the referenced
 *       functions instead.
 *
 * @see get_account_byte_count
 * @see get_account_container_count
 * @see get_account_object_count
 *
 * This is intended as a helper function to cache values for the properties of
 * an account (byte count, container count, and object count).  This function
 * returns a particular int and behaves quite similarly to an union.  The reason
 * a union is not used instead is the state we can provide with the function
 * through the static cache variable.
 *
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
 *
 * @todo Check return type for appropriate sizing for responses.
 *
 */
const unsigned long long int get_account_property(const PROPERTY_MAP property, const unsigned char use_cache);

/**
 * @brief Get account's container count.
 *
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @returns The account's container count.
 */
const unsigned long long int get_account_container_count(const unsigned char use_cache);

/**
 * @brief Get account's object count.
 *
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @returns The account's object count.
 */
const unsigned long long int get_account_object_count(const unsigned char use_cache);

/**
 * @brief Get account's byte count.
 *
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @returns The account's byte count.
 */
const unsigned long long int get_account_byte_count(const unsigned char use_cache);

#endif
