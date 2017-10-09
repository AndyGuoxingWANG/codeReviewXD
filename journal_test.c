/*
 * issn_test.c
 * Test suite function for Journal.
 *
 *  Created on: Oct 3, 2017
 *  Author: philip gust
 */

#include <stdlib.h>
#include "journal.h"
#include "publisher.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * Test Journal functions for local allocation.
 */
static void test_journal_local(void) {
	// names of test journals
	const char* journalNames[5] = {
	"National Geography", "Times", "Science", "Sunset", "Life"};

	// issns of test journals
	Issn issn[5] = {
	12345678, 13572468, 98764321, 10101010, 5201314};

	// publishers of test journals
	Publisher* pubs[5];
	pubs[0] = createPublisher("National Geographic Society", NULL);
	pubs[1] = createPublisher("Time", NULL);
	pubs[2] = createPublisher("Science Service", NULL);
	pubs[3] = createPublisher("Sunset", NULL);
	pubs[4] = createPublisher("Life", NULL);

	//test local journal
	for (int i = 0; i < 5; i++) {
		Journal j1, j2;

		// create local instance of journal
		Journal *journal1 = createJournal(issn[i], journalNames[i], pubs[i], &j1);
		CU_ASSERT_PTR_NOT_NULL_FATAL(journal1);
		CU_ASSERT_PTR_EQUAL(journal1, &j1);
		CU_ASSERT(journal1->issn == issn[i]);
		CU_ASSERT_STRING_EQUAL(journal1->name, journalNames[i]);
		CU_ASSERT_PTR_EQUAL(journal1->publisher, pubs[i]);

		// create second instance of journal
		Journal *journal2 = createJournal(issn[i], journalNames[i], pubs[i], &j2);
		CU_ASSERT_PTR_NOT_NULL_FATAL(journal2);
		CU_ASSERT_PTR_EQUAL(journal2, &j2);
		CU_ASSERT(journal2->issn = issn[i]);
		CU_ASSERT_STRING_EQUAL(journal2->name, journalNames[i]);
		CU_ASSERT_PTR_EQUAL(journal2->publisher, pubs[i]);

		// verify the two return pointers are different
		CU_ASSERT_PTR_NOT_EQUAL(journal1, journal2);
	}
}

/**
 * Test Journal functions for dynamic allocation.
 */
static void test_journal_dynamic(void) {
	// names of test journals
	const char* journalNames[5] = {
	"National Geography", "Times", "Science", "Sunset", "Life"};

	// issns of test journals
	Issn issn[5] = {
	12345678, 13572468, 98764321, 10101010, 5201314};

	// publishers of test journals
	Publisher* pubs[5];
	pubs[0] = createPublisher("National Geographic Society", NULL);
	pubs[1] = createPublisher("Time", NULL);
	pubs[2] = createPublisher("Science Service", NULL);
	pubs[3] = createPublisher("Sunset", NULL);
	pubs[4] = createPublisher("Life", NULL);

	// test dynamic journal
	for (int i = 0; i < 5; i++) {
		// create instance of journal
		Journal *journal1 = createJournal(issn[i], journalNames[i], pubs[i], NULL);
		CU_ASSERT_PTR_NOT_NULL_FATAL(journal1);
		CU_ASSERT(journal1->issn = issn[i]);
		CU_ASSERT_STRING_EQUAL(journal1->name, journalNames[i]);
		CU_ASSERT_PTR_EQUAL(journal1->publisher, pubs[i]);

		// create second instance of journal
		Journal *journal2 = createJournal(issn[i], journalNames[i], pubs[i], NULL);
		CU_ASSERT_PTR_NOT_NULL_FATAL(journal2);
		CU_ASSERT(journal2->issn = issn[i]);
		CU_ASSERT_STRING_EQUAL(journal2->name, journalNames[i]);
		CU_ASSERT_PTR_EQUAL(journal2->publisher, pubs[i]);

		// verify the two return pointers are different
		CU_ASSERT_PTR_EQUAL(journal1, journal2);
	}
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
