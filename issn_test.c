/*
 * vcache_test.c
 *
 * This file contains a test suite of function for Issn
 *
 * Assignment 9
 * CS 5001, Fall 2017
 * Northeastern University Silicon Valley
 */

#include <stdio.h>
#include <stdlib.h>
#include "issn.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * test issnToString and parseIssn functions
 */
static void test_issn(void) {
	char str[20];
	char *s;
	//convert Issn to string
	Issn issn0 = 378595;
	s = issnToString (issn0, str);
	CU_ASSERT_STRING_EQUAL (s, "0378-5955");
	//parse string to Issn
	Issn issn_0 = parseIssn (s);
	CU_ASSERT_EQUAL (issn0, issn_0);

	//convert Issn to string
	Issn issn1 = 1542773;
	s = issnToString (issn1, str);
	CU_ASSERT_STRING_EQUAL (s, "1542-7730");
	//parse string to Issn
	Issn issn_1 = parseIssn(s);
	CU_ASSERT_EQUAL (issn1, issn_1);

	//convert Issn to string
	Issn issn2 = 1078;
	s = issnToString (issn2, str);
	CU_ASSERT_STRING_EQUAL (s, "0001-0782");
	//parse string to Issn
	Issn issn_2 = parseIssn(s);
	CU_ASSERT_EQUAL (issn2, issn_2);

	//convert Issn to string
	Issn issn3 = 18923;
	s = issnToString (issn3, str);
	CU_ASSERT_STRING_EQUAL (s, "0018-9235");
	//parse string to Issn
	Issn issn_3 = parseIssn (s);
	CU_ASSERT_EQUAL (issn3, issn_3);

	//convert Issn to string
	Issn issn4 = 2434561;
	s = issnToString (issn4, str);
	CU_ASSERT_STRING_EQUAL (s, "2434-561X");
	//parse string to Issn
	Issn issn_4 = parseIssn(s);
	CU_ASSERT_EQUAL (issn4, issn_4);

	//convert Issn to string
	Issn issn5 = 2049363;
	s = issnToString (issn5, str);
	CU_ASSERT_STRING_EQUAL (s, "2049-3630");
	//parse string to Issn
	Issn issn_5 = parseIssn(s);
	CU_ASSERT_EQUAL (issn5, issn_5);

	//convert Issn to string
	Issn issn6 = 2348795;
	s = issnToString (issn6, str);
	CU_ASSERT_STRING_EQUAL (s, "2348-795X");
	//parse string to Issn
	Issn issn_6 = parseIssn(s);
	CU_ASSERT_EQUAL (issn6, issn_6);

	//parse string to Issn
	s = "2049-3631";
	Issn issn_7 = parseIssn(s);
	CU_ASSERT_EQUAL (0, issn_7);

	//parse string to Issn
	s = "204-93630";
	Issn issn_8 = parseIssn(s);
	CU_ASSERT_EQUAL (0, issn_8);

	//parse string to Issn
	s = "2049-363";
	Issn issn_9 = parseIssn(s);
	CU_ASSERT_EQUAL (0, issn_9);
}

/**
 * Add suite for Vcache unit tests
 */
void issn_test(void) {
	// add a suite to the registry with no init or cleanup
	CU_pSuite pSuite = CU_add_suite("issn_test", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_issn", test_issn);
}
