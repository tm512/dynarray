#include <stdio.h>
#include "minunit.h"
#include "dynarray.h"
 
int tests_run = 0;
int tests_failed = 0;

typedef struct
{
    int a;
    int b;
} test_t;

static char * test_create_and_delete() {
    dynarray_t *arr = dynarray_create(4, sizeof(test_t), 1);
    mu_assert("allocation failed", arr != NULL);
    dynarray_delete(&arr);
    mu_assert("deletion failed", arr == NULL);
    return NULL;
}

static char * test_push_fixed_size() {
    dynarray_t *arr = dynarray_create(2, sizeof(test_t), 0);
    mu_assert("wrong size", arr->e_max == 2);
    test_t t;
    mu_assert("push failed", dynarray_push(arr, &t) != NULL);
    mu_assert("push failed", dynarray_push(arr, &t) != NULL);
    /* one too many, resize is disabled */
    mu_assert("push should have failed", dynarray_push(arr, &t) == NULL);
    dynarray_delete(&arr);
    return NULL;
}

static char * test_push_growable() {
    dynarray_t *arr = dynarray_create(2, sizeof(test_t), 2);
    mu_assert("wrong size", arr->e_max == 2);
    test_t t;
    mu_assert("push failed", dynarray_push(arr, &t) != NULL);
    mu_assert("push failed", dynarray_push(arr, &t) != NULL);
    /* one too many, should resize */
    test_t* third = dynarray_push(arr, &t);
    mu_assert("push failed", third != NULL);
    mu_assert("dynarray length should have grown by 2", arr->e_max == 4);
    mu_assert("third item should be third item", third == arr->index[2]);
    dynarray_delete(&arr);
    return NULL;
}

static char * all_tests() {
    mu_run_test(test_create_and_delete);
    mu_run_test(test_push_fixed_size);
    mu_run_test(test_push_growable);
    return NULL;
} 

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("FAILURE: %s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    printf("Tests failed: %d\n", tests_failed);

    return result != 0;
 }
