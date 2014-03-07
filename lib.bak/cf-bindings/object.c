/**
 * @copyright 2013
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <stdlib.h>
#include <string.h>

#include "object.h"

Object* object_create()
{
	Object * object = (Object *) malloc(sizeof(Object));
	return object;
}

void object_free(Object* object)
{
	free(object);
}

char* object_encode_name(Object* object, char* name)
{
	name = object->name;
	return name;
}

short unsigned int object_metadata_bytes(Object* object)
{
	MetaDataItem * iterator = object->metadata;
	short unsigned int size = 0;

	while (iterator != NULL) {
		size += strlen(iterator->key) + 1 + strlen(iterator->value);
	}

	return size;
}
