/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/**
 * @brief Get an array of container names.
 *
 * @param[in,out] names Array of container names as char[][] which is allocated
 *                      by the call and freed by the caller.
 * @param[in,out] length Length of the container names array.  When used as
 *                       input, a non-zero value sets a limit on the number of
 *                       names to be returned.
 *
 * @todo Add marker and end_marker support into this function.
 *
 * @returns FALSE if an error occurs and sets errno; otherwise, equivalent to
 *          length.
 *
 * @warning If length is zero on return, names will be a null pointer!
 *
 * Example HTTP Request:
 *
 * GET /v1.0/jdoe HTTP/1.1
 * Host: storage.clouddrive.com
 * X-Auth-Token: eaaafd18-0fed-4b3a-81b4-663c99ec1cbb
 *
 * Example HTTP Response:
 *
 * HTTP/1.1 200 Ok
 * Date: Thu, 07 Jun 2007 18:57:07 GMT
 * Content-Type: text/plain; charset=UTF-8
 * Content-Length: 32
 *
 * images
 * movies
 * documents
 * backups
 *
 */
const unsigned long int get_container_names(char names[][], unsigned long int * length);

/**
 * @brief Details about a container.
 */
typedef struct {
	char name[255]; /*!< Name of the container. */
	unsigned long long int object_count; /*!< Number of objects in container. */
	unsigned long long int byte_count; /*!< Number of bytes in container. */
} container_details;

/**
 * @brief Get an array of container_details.
 *
 * @param[in,out] details Array of container_details which is allocated by the
 *                        call and freed by the caller.
 * @param[in,out] length Length of the container_details array.  When used as
 *                       input, a non-zero value sets a limit on the number of
 *                       names to be returned.
 *
 * @todo Add marker and end_marker support into this function.
 *
 * @returns FALSE if an error occurs and sets errno; otherwise, equivalent to
 *          length.
 *
 * @warning If length is zero on return, details will be a null pointer!
 *
 * Example HTTP Request (JSON):
 *
 * GET /v1.0/jdoe?format=json HTTP/1.1
 * Host: storage.clouddrive.com
 * Content-Length: 0
 * X-Storage-Token: 182f9x0af0e828cfe3281767d29d19f4
 *
 * Example HTTP Response (JSON):
 *
 * HTTP/1.1 200 OK
 * Date: Tue, 25 Nov 2008 19:39:13 GMT
 * Content-Type: application/json; charset=UTF-8
 *
 * [
 *   { "name": "test_container_1", "count": 2, "bytes": 78 },
 *   { "name": "test_container_2", "count": 1, "bytes": 17 }
 * ]
 *
 * Example HTTP Request (XML):
 *
 * GET /v1.0/jdoe?format=xml HTTP/1.1
 * Host: storage.clouddrive.com
 * Content-Length: 0
 * X-Storage-Token: 182f9x0af0e828cfe3281767d29d19f4
 *
 * Example HTTP Response (JSON):
 *
 * HTTP/1.1 200 OK
 * Date: Tue, 25 Nov 2008 19:42:35 GMT
 * Content-Type: application/xml; charset=UTF-8
 *
 * <?xml version="1.0" encoding="UTF-8"?>
 * <account name="MichaelBarton">
 *   <container>
 *     <name>test_container_1</name>
 *     <count>2</count>
 *     <bytes>78</bytes>
 *   </container>
 *   <container>
 *     <name>test_container_2</name>
 *     <count>1</count>
 *     <bytes>17</bytes>
 *   </container>
 * </account>
 */
const unsigned long int get_container_details(container_details details[], unsigned long int * length);
