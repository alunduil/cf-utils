/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#ifndef CF_CONTAINER_H
#define CF_CONTAINER_H

#define MAX_SIZE_CONTAINER_NAME 256

/**
 * @todo Container.name cannot contain '/'
 * @todo Cotnainer.name must be URL-encoded
 */

typedef struct container {
    char name[MAX_SIZE_CONTAINER_NAME + 1]; /*!< Container name */
} Container;

/**
 * @brief Allocate a Container.
 *
 * Allocates memory for a Container and returns a pointer to the structure.  The
 * memory should be deallocated by a matching call to container_free.
 *
 * @return Container *
 *
 * @see container_free
 */
Container * container_create();

/**
 * @brief Deallocate a Container.
 *
 * Frees all memory for a Container including property memory.
 *
 * @param[in,out] container Pointer to the Container being freed will be NULL
 *                          upon return.
 *
 * @see container_create
 */
void container_free(Container * container);

#endif
