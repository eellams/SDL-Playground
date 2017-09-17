#include <stdlib.h>

#include "config.h"
#include <check.h>

#include "../src/map.h"

/* Test: test_map_create
 * ---------------------
 * covers: map_create
 *         map_get_width
 *         map_get_height
 */
START_TEST (test_map_create)
{
    unsigned int width;
    unsigned int height;
    struct t_map *computed;
    unsigned int i;
    unsigned int j;

    computed = NULL;
    width = 10u;
    height = 10u;

    /* create a new map */
    computed = map_create(width, height);

    ck_assert_ptr_ne(computed, NULL);

    ck_assert_uint_eq(computed->width, 10);

    /* check computed */
    ck_assert_uint_eq(map_get_width(computed), width);
    ck_assert_uint_eq(map_get_height(computed), height);


    /* check the tiles */
    for (i=0; i<width*height; i++)
    {
        /* check ID is correct */
        ck_assert_uint_eq(computed->tiles[i].id, i);

        /* check weight is 0
            this should be ck_assert_float_eq but causes errors on Ubuntu 16.04 */
        ck_assert(computed->tiles[i].weight == 0.0f);

        for (j=0; j<SUBTILE_WIDTH_PER_TILE*SUBTILE_HEIGHT_PER_TILE; j++)
        {
            /* check ID */
            ck_assert_uint_eq(computed->tiles[i].subtiles[j].id, j);

            /* check state is initialised to empty */
            ck_assert(computed->tiles[i].subtiles[j].occupied == SUBTILE_OCCUPIED);
        }
    }
}
END_TEST

/* Test: test_map_destroy
 * ---------------------
 * covers: map_destroy
 */
START_TEST (test_map_destroy)
{
    unsigned int width;
    unsigned int height;
    struct t_map *computed;

    width = 10u;
    height = 10u;

    computed = NULL;
    computed = map_create(width, height);

    /* check the pointer has been set correctly */
    ck_assert_ptr_ne(computed, NULL);

    ck_assert_int_eq(map_destroy(computed), 0);

    /* this destroy should fail (return non zero) */
    ck_assert_int_ne(map_destroy(NULL), 0);
}
END_TEST

Suite* map_suite (void)
{
    Suite *s = suite_create("map_suite");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_map_create);
    tcase_add_test(tc, test_map_destroy);

    suite_add_tcase(s, tc);
    return s;
}

int map_suite_free(Suite* s)
{
    if (s != NULL)
    {
        free(s);
        return 0;
    }
    return 1;
}

int main()
{
    int nf;
    Suite *s = map_suite();

    SRunner *sr = srunner_create(s);
    srunner_set_log(sr, "check_map.log");
    srunner_run_all(sr, CK_VERBOSE);

    nf = srunner_ntests_failed(sr);

    srunner_free(sr);
    map_suite_free(s);

    return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

