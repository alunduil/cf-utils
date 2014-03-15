/**
 * @copyright 2014
 * @author Alex Brandt
 *
 * cf-utils is freely distributable under the terms of an MIT-style license.
 * See COPYING or http://www.opensource.org/licenses/mit-license.php.
 */

#include <check.h>
#include <stdlib.h>

#include "../../../lib/cf-bindings/object.h"

/**
 * @test MAX_OBJECT_NAME_LENGTH 1024
 *
 * Following the spec, Object names cannot be longer than 1024 bytes after
 * URL-encoding.
 */
START_TEST(test_max_object_name_length)
{
    ck_assert_int_eq(MAX_OBJECT_NAME_LENGTH, 1024);
}
END_TEST

/**
 * @test MAX_OBJECT_METADATA_PAIRS_NUM 90
 *
 * Following the spec, Object metadata should not contain more than 90 pairs.
 */
START_TEST(test_max_object_metadata_pairs_num)
{
    ck_assert_int_eq(MAX_OBJECT_METADATA_PAIRS_NUM, 90);
}
END_TEST

/**
 * @test object_create—produces and prepares an Object.
 */
START_TEST(test_object_create)
{
    Object * object = object_create();
    ck_assert_str_eq(object->name, "");
    ck_assert(object->container == NULL);
    ck_assert(object->metadata == NULL);
    object_free(object);
}
END_TEST

/**
 * @test object_encode_name—encodes the object's name
 */
START_TEST(test_object_encode_name)
{
    /** @todo Add fixture support. */
    char name[MAX_OBJECT_NAME_LENGTH + 1];

    Object * object = object_create();
    strncpy(object->name, "C++final(v2).txt", MAX_OBJECT_NAME_LENGTH + 1);
    ck_assert_str_eq(object_encode_name(object, name), "C%2B%2Bfinal%28v2%29.txt");
}
END_TEST

/**
 * @test object_metadata_bytes—returns the number of bytes in the Object's
 *       metadata.
 *
 * @note The spec recommends that this does not exceed 4096.
 */
START_TEST(test_object_metadata_bytes)
{
    Object * object = object_create();
    ck_assert_int_eq(object_metadata_bytes(object), 0);
}
END_TEST

/** @todo Object Name Length must be less than 1024 after URL-encoding */
/** @todo Segmentation? */
/** @todo Metadata is limited to 90 key value pairs */
/** @todo Total size of metadata is 4096 bytes */

Suite * object_suite(void) {
    Suite * suite = suite_create("Test Object");

    TCase * tc = tcase_create("MAX_OBJECT_NAME_LENGTH");
    tcase_add_test(tc, test_max_object_name_length);
    suite_add_tcase(suite, tc);

    tc = tcase_create("MAX_OBJECT_METADATA_PAIRS_NUM");
    tcase_add_test(tc, test_max_object_metadata_pairs_num);
    suite_add_tcase(suite, tc);

    tc = tcase_create("Create");
    tcase_add_test(tc, test_object_create);
    suite_add_tcase(suite, tc);

    tc = tcase_create("Encode Name");
    tcase_add_test(tc, test_object_encode_name);
    suite_add_tcase(suite, tc);

    tc = tcase_create("Metadata Bytes");
    tcase_add_test(tc, test_object_metadata_bytes);
    suite_add_tcase(suite, tc);

    return suite;
}

int main() {
    int number_failed;

    Suite * suite = object_suite();
    SRunner * suite_runner = srunner_create(suite);

    srunner_run_all(suite_runner, CK_NORMAL);

    number_failed = srunner_ntests_failed(suite_runner);

    srunner_free(suite_runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
