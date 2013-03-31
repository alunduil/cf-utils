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
 *  :prefix: not used in account!
 */

/** @brief Map of properties that can be requested in an account. */
enum {
	CONTAINER_COUNT = 0, /*!< Count of containers in an account. */
	OBJECT_COUNT, /*!< Count of objects in an account. */
	BYTE_COUNT /*!< Total bytes used in account. */
} PROPERTY_MAP;

/**
 * @brief Get requested account property.
 *
 * @param[in] property Specifies which property's value to return.
 * @param[in] use_cache 1 → use cached values; 0 → use values from the API.
 *
 * @returns Requested property (int).
 *
 * @note Not intended for direct use.
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
 */
int get_account_property(PROPERTY_MAP property, int use_cache = 0);

/**
 * @brief Get account's container count.
 *
 * @param[in] use_cache 1 → use cached values; 0 → use values from the API.
 *
 * @returns The container count (int).
 */
int get_account_container_count(int use_cache = 0);

/**
 * @brief Get account's object count.
 *
 * @param[in] use_cache 1 → use cached values; 0 → use values from the API.
 *
 * @returns The object count (int).
 */
int get_account_object_count(int use_cache = 0);

/**
 * @brief Get account's byte count.
 *
 * @param[in] use_cache 1 → use cached values; 0 → use values from the API.
 *
 * @returns The byte count (int).
 */
int get_account_byte_count(int use_cache = 0);
