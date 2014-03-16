/**
 * @author Alex Brandt
 * @copyright MIT
 * @date 2014
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>

#include "container.h"

Container* container_create() {
    Container * container = (Container *) malloc(sizeof(Container));

    strncpy(container->name, "", 1);

    return container;
}

void container_free(Container* container) {
    free(container);
}
