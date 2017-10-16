/*
 * vcache_test.c
 *
 * This file contains a test suite of function for Vcache
 *
 *  Created on: Oct 12, 2017
 *  Author: mg
 */

#include <stdio.h>
#include <stdlib.h>
#include "vcache.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * Test Vcache functions
 */
static void test_vcache(void) {

	typedef struct Vcache {
		/** capacity of allocated cache array */
		size_t capacity;
		/** current size of allocated cache */
		size_t size;
		/** pointer to allocated cache pointer array */
		void **cache;
	} Vcache;

	//test createVcache
	Vcache *vc = createVcache();
	CU_ASSERT_PTR_NOT_NULL_FATAL (vc);
	CU_ASSERT (vc -> capacity == 4);
	CU_ASSERT (vc -> size == 0);
	CU_ASSERT_PTR_NOT_NULL (vc -> cache);
	Vcache *vc1 = createVcache();
	Vcache *vc2 = createVcache();
	CU_ASSERT_PTR_NOT_EQUAL (vc1, vc2);

	//test addVcacheItem
	const char* test[5] = {"Test0", "Test1", "Test2", "Test3", "Test4"};
	CU_ASSERT_FALSE (addVcacheItem (vc, NULL));
	for (int i = 0; i < 5; i++){
		CU_ASSERT_TRUE (addVcacheItem (vc, test[i]));
	}

	//test containsVcacheItem
	const char* hello = "HelloWorld";
	CU_ASSERT_FALSE (containsVcacheItem (vc, hello));
	for (int i = 0; i < 5; i++){
		CU_ASSERT_TRUE (containsVcacheItem (vc, test[i]));
	}

	//test getVcacheItem
	CU_ASSERT_PTR_NULL (getVcacheItemAt (vc, -1));
	CU_ASSERT_PTR_NULL (getVcacheItemAt (vc, 5));
	for (int i = 0; i < 5; i++){
		CU_ASSERT_PTR_EQUAL ((char*) getVcacheItemAt (vc, i), test[i]);
	}

	//test getVcacheSize
	CU_ASSERT (getVcacheSize(vc) == 5);
}

/**
 * Add suite for Vcache unit tests
 */
void vcache_test(void) {
	// add a suite to the registry with no init or cleanup
	CU_pSuite pSuite = CU_add_suite("vcache_test", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_vcache", test_vcache);
}
