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
 * @param[out] length Length of the container list.
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
int get_container_names(char names[][], int & length);
