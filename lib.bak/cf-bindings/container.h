/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_BINDINGS_CONTAINER
#define CF_BINDINGS_CONTAINER

#define MAX_CONTAINER_NUM 500000
#define MAX_CONTAINER_NAME_LENGTH 256

/**
 * Upstream container property notes:
 *
 * @note Maximum of 500,000 containers.
 * @note No / in container names.
 * @note Less than 256 bytes in length.
 * @note Container name length is after URL encoding.
 */

/**
 * @brief Container data structure.
 */
typedef struct {
    char name[MAX_CONTAINER_NAME_LENGTH + 1]; /*!< Container Name. */

    unsigned short int cdn_enabled; /*!< CDN Enabled? */
    char * cdn_url; /*!< CDN URL */
    unsigned int cdn_ttl; /*!< CDN TTL */

    unsigned long int object_count; /*!< Number of objects in container. */
    unsigned long int byte_count; /*!< Number of bytes in container. */
} Container;

/**
 * @brief Initialize a new container structure.
 *
 * @returns Container struct allocated by this call.
 */
Container * container_create();

/**
 * @brief Free a container structure.
 *
 * @param[in] container Container struct to be de-allocated.
 *
 * @return 0 on error and sets errno; otherwise, 1.
 */
void container_free ( Container * container );

/**
 * @brief URL-encode the container's name and return the result.
 *
 * Container names in Cloud Files must be URL-encoded.  We encode any special
 * characters and check for the presence of any '/' characters—deemed illegal by
 * upstream.
 *
 * @warn '/' is an illegal character and will cause an error!
 *
 * @param[in]     container Container whose name we are URL-encoding.
 * @param[in,out] name      The resulting name after encoding or as much
 *                          encoding as was performed if an error occurred.
 *
 * @return A pointer to the encoded string or NULL if an error occurred.
 */
char * container_encode_name(Container * container, char * name);

#if 0
/**
 * @brief Get an array of container names.
 *
 * @param[in] account Account for which to get containers' names.
 * @param[in,out] containers Array of Containers that will be allocated if NULL;
 *                           otherwise, names will be merged (duplicates removed
 *                           and others concatenated) with existing entries.
 * @param[in,out] length Length of the Container array.  When used as input, a
 *                       non-zero value sets a limit on the number of names to
 *                       be returned.
 *
 * @todo Add marker and end_marker support into this function.
 *
 * @returns 0 if an error occurs and sets errno; otherwise, length.
 *
 * @warning If length is zero on return, containers will be a null pointer!
 */
unsigned long int get_container_names ( const Account * account, Container containers[], unsigned long int * length );

/**
 * @brief Determine if a name is already in a list of containers.
 *
 * @param[in] name The name to search for in the array of containers.
 * @param[in] containers The array of Containers to search for the name.
 * @param[in] length The length of the container array.
 *
 * @returns The count of that name in the array (should be 0 or 1).
 *
 * @warning Not meant for typical consumption but this function has not side
 *          effects so feel free.
 */
unsigned char _is_name_element_of_containers ( const char name[], const Container containers[], const unsigned long int length );

/**
 * @brief Get or populate an array of Containers.
 *
 * @param[in] account The account for which to get containers' details.
 * @param[in,out] containers Array of Containers that will be allocated if NULL;
 *                           otherwise, details for the existing entries will be
 *                           added to the passed array.
 * @param[in,out] length Length of the container_details array.  When used as
 *                       input, a non-zero value sets a limit on the number of
 *                       names to be returned.
 *
 * @todo Add marker and end_marker support into this function.
 *
 * @returns 0 if an error occurs and sets errno; otherwise, 1
 *
 * @warning If length is zero on return, details will be a null pointer!
 */
unsigned long int get_container_details ( const Account * account, Container containers[], unsigned long int * length );

#endif
#endif
