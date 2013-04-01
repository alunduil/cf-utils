/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>

/**
 * @brief Global variable for authentication data.
 *
 * @todo Consider moving this to a static variable in a function call?
 */
struct {
	char * management_url; /*!< Endpoint URL for cloud files. */
	char * cdn_management_url; /*!< Endpoint URL for CDN Management of cloud files. */
	char * account_name; /*!< @todo Remove if already present in management URLs. */
	char * token; /*!< Token for further request authentication. */
} auth_data = {
	.management_url = NULL,
	.cdn_management_url = NULL,
	.account_name = NULL,
	.token = NULL
};

/**
 * @brief Authenticate the Cloud Account.
 *
 * @param[in] user_name Cloud Account user name used to authenticate.
 * @param[in] api_key Cloud Account API Key used to authenticate.
 *
 * @returns 1 for success and NULL on error (also sets errno).
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
int authenticate(char *user_name, char *api_key);
