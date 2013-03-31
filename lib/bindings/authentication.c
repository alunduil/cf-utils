/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

/**
 * 
 * @brief Authenticate the Cloud Account.
 * 
 * @param[in] user_name Cloud Account user name used to authenticate.
 * @param[in] api_key Cloud Account API Key used to authenticate.
 * 
 * @returns Token provided by authentication.
 * 
 * X-Auth-User
 * X-Auth-Key
 * 
 * X-Auth-Token
 * 
 * https://identity.api.rackspacecloud.com/v1.0
 * https://lon.identity.api.rackspacecloud.com/v1.0
 * 
 * How do we allow this URI to be modified?
 * 
 */
char * authenticate(char *user_name, char *api_key)
{
}
