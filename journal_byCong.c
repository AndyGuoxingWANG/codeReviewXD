/*
 * journal.c
 *
 *  Definition of a Journal
 *
 *  Created on: Oct 31, 2017
 *  Author: philip gust
 */

#include "journal.h"
#include <stdio.h>
#include <string.h>

/**  Size of allocated journals pointer array */
static size_t JOURNALS_SIZE = 0;

/** pointer to allocated journals pointer array */
static Journal **journals = NULL;

/**
  * Print a Journal
  * @param journal the journal to print
  */
void printJournal(const Journal *journal) {
	char issnChars[10];
	char* issnString = issnToString(journal->issn, issnChars);
	printf("Name: ’%s’\n", journal->name);
	printf("ISSN: %s\n", issnString);
	printPublisher(journal->publisher);  // journal publisher pointer field
}

/**
 * Initialize journals cache. Call from operations that access it
 */
static void initJournalsCache(void) {
	if (journals == NULL) {
		JOURNALS_SIZE = 4; // size of journals array
		journals = malloc(JOURNALS_SIZE * sizeof(Journal*));
		journals[0] = NULL; // null terminate array
	}
}

/**
  * Create a journal from its information
  * @param issn the journal Issn
  * @param name the journal name
  * @param pub the Publisher
  * @param journal pointer to space for returned Journal, or NULL to use saved journals array
  * @return pointer to journal struct, or to saved journal if journal is NULL
  * 	   (NULL if not defined)
  */
Journal* createJournal(Issn issn, const char* name, Publisher* pub, Journal* journal) {
	if (journal == NULL) {
		initJournalsCache();

		// find journal in array
		int jindex = 0;
		for ( ; journals[jindex] != NULL; jindex++) { // while not at sentinel entry
			if (journals[jindex]->issn == issn) {
				return journals[jindex]; // return matching journal
			}
		}

		// if journal not found, allocate new struct and add to array
		if (jindex + 1 >= JOURNALS_SIZE) {
			JOURNALS_SIZE *= 2; // double size of journals array
			journals = realloc(journals, JOURNALS_SIZE * sizeof(Journal*));
		}
		journal = malloc(sizeof(Journal)); // allocate storage for new journal
		journals[jindex] = journal; // add pointer to new Journal to array
		journals[++jindex] = NULL; // add null pointer after new one
	}
	strcpy(journal->name, name);
	journal->issn = issn;
	journal->publisher = pub;
	return journal;
}

/**
  * Get a journal from its issn from the journals array
  * @param issn the journal Issn
  * @return pointer to saved journal (NULL if not in journals array)
  */
Journal* getJournalByIssn(Issn issn) {
	initJournalsCache();

	//find journal in array
	int pindex = 0;
	for ( ; journals[pindex] != NULL; pindex++) { // while not at sentinel entry
		if (journals[pindex]->issn == issn) {
			return journals[pindex]; // return matching journal
		}
	}
	// if not found in journal array, return NULL
	return NULL;
}
