/*
 * issn_test.c
 * Test suite function for Journal.
 *
 *  Created on: Oct 3, 2017
 *  Author: esandar
 */
#include <stdio.h>
#include <stdlib.h>
#include "journal.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * Test Journal functions for local allocation.
 */
static void test_journal_local(void) {
	Publisher publisher = {
			.name = "Institute of Food Technologists"
	};
	Journal journal = {
				.name = "Journal of Food Science",
				.issn = 221147,
				.publisher = &publisher
	};

	Journal j1, j2;
	// create local instance of journal
	Journal *jou1 = createJournal(journal.issn, journal.name, journal.publisher, &j1);
	CU_ASSERT_PTR_NOT_NULL_FATAL(jou1);
	CU_ASSERT_PTR_EQUAL(jou1, &j1);
	CU_ASSERT_STRING_EQUAL(jou1->name, journal.name);

	// create second instance of journal
	Journal *jou2 = createJournal(journal.issn, journal.name, journal.publisher, &j2);
	CU_ASSERT_PTR_NOT_NULL_FATAL(jou2);
	CU_ASSERT_PTR_EQUAL(jou2, &j2);
	CU_ASSERT_STRING_EQUAL(jou2->name, journal.name);

	// verify they are different
	CU_ASSERT_PTR_NOT_EQUAL(jou1, jou2);
}

/**
 * Test Journal functions for dynamic allocation.
 */
static void test_journal_dynamic(void) {
	Publisher publisher = {
			.name = "Institute of Food Technologists"
	};
	Journal journal = {
				.name = "Journal of Food Science",
				.issn = 221147,
				.publisher = &publisher
	};

	// create local instance of journal
	Journal *jou1 = createJournal(journal.issn, journal.name, &publisher, NULL);
	CU_ASSERT_PTR_NOT_NULL_FATAL(jou1);
	CU_ASSERT_STRING_EQUAL(jou1->name, journal.name);

	// create second instance of journal
	Journal *jou2 = createJournal(journal.issn, journal.name, &publisher, NULL);
	CU_ASSERT_PTR_NOT_NULL_FATAL(jou2);
	CU_ASSERT_STRING_EQUAL(jou2->name, journal.name);

	// verify they are same instance
	CU_ASSERT_PTR_EQUAL(jou1, jou1);
}

/**
 * Add suite for Journal unit tests
 */
void journal_test(void) {
	// add a suite to the registry with no init or cleanup
	CU_pSuite pSuite = CU_add_suite("journal_test", NULL, NULL);

	// add the tests to the suite
	CU_add_test(pSuite, "test_journal_local", test_journal_local);
	CU_add_test(pSuite, "test_journal_dynamic", test_journal_dynamic);
}
