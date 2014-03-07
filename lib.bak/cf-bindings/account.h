/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_BINDINGS_ACCOUNT
#define CF_BINDINGS_ACCOUNT

#include "container.h"

/**
 * @brief An account structure that is populated with management information.
 */
typedef struct {
    char * name; /*!< Account Username (Name) */
    char * api_key; /*!< API key (@todo remove this from memory?). */

    Container * containers; /*!< Account's containers. */

    char * management_url; /*!< URL for Cloud Files Management. */
    char * cdn_management_url; /*!< URL for CDN Management. */
    char * token; /*!< Token. */

    unsigned long int _properties[3]; /*!< Property Cache */
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
 * @return 0 on error and sets errno; otherwise, 1.
 */
unsigned char account_free ( Account * account );

/**
 * @brief Authenticate the Cloud Account.
 *
 * @param[in,out] account Account structure storing persistent information.
 * @param[in] user_name Cloud Account user name used to authenticate.
 * @param[in] api_key Cloud Account API Key used to authenticate.
 *
 * @returns 0 on error and sets errno; otherwise, 1.
 */
Account * authenticate ( Account * account, const char user_name[], const char api_key[] );

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
 */
unsigned long int _get_account_property ( Account * account, const _PROPERTY_MAP property, const unsigned char use_cache );

/**
 * @brief Get account's container count.
 *
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @note Maximum of 500,000 containers.
 *
 * @returns The account's container count.
 */
unsigned long int get_account_container_count ( Account * account, const unsigned char use_cache );

/**
 * @brief Get account's object count.
 *
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @returns The account's object count.
 */
unsigned long int get_account_object_count ( Account * account, const unsigned char use_cache );

/**
 * @brief Get account's byte count.
 *
 * @param[in] use_cache Use cached values if present and this parameter is TRUE;
 *                      otherwise, query the API for fresh values.
 *
 * @returns The account's byte count.
 */
unsigned long int get_account_byte_count ( Account * account, const unsigned char use_cache );

#endif
