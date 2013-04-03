/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/**
 * @brief List container names.
 *
 * @param[in,out] names Names of containers.  Will be allocated by the call.
 * @param[in,out] length Length of the container list.  Non-zero sets a limit on the number of returned names.
 *
 * @returns 1 → success; NULL → error (errno will be set).
 *
 * @warning If length is zero, names will be a null pointer!
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
short int get_container_names(char ** names, unsigned long int * length);

typedef struct {
	char * name; /*!< Name of the container. */
	unsigned long long int object_count; /*!< Number of objects in container. */
	unsigned long long int byte_count; /*!< Number of bytes in container. */
} container_details;

/**
 * @brief List container names with object count and byte count.
 *
 * @param[in,out] details Container name, object count, and byte count.  Allocated by the call.
 * @param[out] length Length of the container_details list.
 *
 * @returns 1 → success; NULL → error (errno will be set).
 *
 * @warning If length is zero, container_details will be a null pointer!
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
short int get_container_details(container_details * details, unsigned long int length);
