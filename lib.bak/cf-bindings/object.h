/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_BINDINGS_OBJECT
#define CF_BINDINGS_OBJECT

#include "container.h"

#define MAX_OBJECT_NAME_LENGTH 1024
#define MAX_OBJECT_METADATA_PAIRS_NUM 90

typedef struct {
    char * key; /*!< MetaData Key */
    char * value; /*!< MetaData Value */
} MetaDataItem;

#define MAX_OBJECT_NAME_SIZE 1024 /*!< Maximum size of Object->name */

/**
 * @brief Object Structure
 *
 * The following are upstream limitations on Objects:
 *   * strlen(name) < 1024 after URL-encoding
 *   * 90 metadata items (key-value) per object
 *   * total size of metadata cannot exceed 4096 bytes
 *   * 5 GB maximum in data
 */
typedef struct {
    char name[MAX_OBJECT_NAME_SIZE + 1]; /*!< Object Name */
    MetaDataItem metadata[90]; /*!< Object Metadata */
    Container * container; /*!< Object's Container */
    char * data; /*!< Object Data */
} Object;

/**
 * @brief Allocate and initialize a blank Object.
 *
 * This function allocates memory for an Object and provides sane default values
 * for its members.
 *
 * @post Memory for an Object has been allocated.
 *
 * @returns Object *
 *
 * @warn If object_create is called and object_free is not, memory will leak
 *
 * @since 1.0.0
 * @see object_free
 */
Object * object_create();

/**
 * @brief Deallocate an Object.
 *
 * This function deallocates memory for an Object.
 *
 * @post Memory for an Object has been deallocated.
 *
 * @since 1.0.0
 * @see object_create
 */
void object_free(Object * object);

/**
 * @brief URL-encode the object's name and return the result.
 *
 * Object names in Cloud Files must be URL-encoded.  We encode any special
 * characters.
 *
 * @param[in]     object Object whose name we are URL-encoding.
 * @param[in,out] name   The resulting name after encoding or as much encoding
 *                       as was performed if an error occurred.
 *
 * @return A pointer to the encoded string or NULL if an error occurred.
 */
char * object_encode_name(Object * object, char * name);

/**
 * @brief Determine byte size of Object's metadata.
 *
 * The Object's metadata cannot be larger than 4096 bytes.  This means we should
 * have some mechanism for checking the size of the metadata.
 *
 * @param[in] object Object whose metadata we are sizing.
 *
 * @return An integer number of bytes contained in the object's metadata.
 */
unsigned short int object_metadata_bytes(Object * object);

#endif
