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
 * @brief An account structure that is populated with management information.
 */
typedef struct {
	char * user_name; /*!< Account Username (Name) */
	char * name; /*!< Alias to username. */

	char * api_key; /*!< API key (@todo remove this from memory?). */

	char * management_url; /*!< URL for Cloud Files Management. */
	char * cdn_management_url; /*!< URL for CDN Management. */
	char * token; /*!< Token. */
} Account;

/**
 * @brief Initialize a new account structure.
 *
 * @returns Account struct allocated by this call.
 */
Account * account_create();

/**
 * @brief Free an account structure.
 *
 * @param[in] account Account struct to be de-allocated.
 *
 * @return FALSE on error and sets errno; otherwise, TRUE.
 */
const unsigned char account_free(Account * account);

/**
 * @brief Authenticate the Cloud Account.
 *
 * @param[in,out] account Account structure storing persistent information.
 * @param[in] user_name Cloud Account user name used to authenticate.
 * @param[in] api_key Cloud Account API Key used to authenticate.
 *
 * @returns FALSE on error and sets errno; otherwise, TRUE.
 *
 * Tries to request a login token from the authentication endpoint by first
 * trying the global endpoint URL, https://identity.api.rackspacecloud.com/v1.0.
 * If this URL doesn't let the user authenticate we try the London endpoint,
 * https://lon.identity.api.rackspacecloud.com/v1.0.  This code will be removed
 * when there is only one authentication endpoint.
 *
 * Example Request HTTP:
 *
 * GET /v1.0 HTTP/1.1
 * Host: identity.api.rackspacecloud.com
 * X-Auth-User: jdoe
 * X-Auth-Key: a86850deb2742ec3cb41518e26aa2d89
 *
 * Example Response HTTP:
 *
 * HTTP/1.1 204 No Content
 * Date: Mon, 12 Nov 2007 15:32:21 GMT
 * X-Storage-Url: https://storage.clouddrive.com/v1/CF_xer7_34
 * X-CDN-Management-Url: https://cdn.clouddrive.com/v1/CF_xer7_34
 * X-Auth-Token: eaaafd18-0fed-4b3a-81b4-663c99ec1cbb
 * Content-Length: 0
 * Content-Type: text/plain; charset=UTF-8
 *
 * The X-Storage-Url is the endpoint used for all other API calls after
 * successful authentication.
 */
const unsigned char authenticate(Account * account, char user_name[], char api_key[]);

/**
 * @brief Map of properties that can be requested in an account.
 */
typedef enum {
	_CONTAINER_COUNT = 0, /*!< Count of containers in an account. */
	_OBJECT_COUNT, /*!< Count of objects in an account. */
	_BYTE_COUNT /*!< Total bytes used in account. */
} _PROPERTY_MAP;

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
 * @todo Check return type for appropriate sizing for responses.
 *
 */
const unsigned long long int _get_account_property(const _PROPERTY_MAP property, const unsigned char use_cache);

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
