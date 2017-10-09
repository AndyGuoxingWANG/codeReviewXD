/*
 * journal.c
 *
 *  Definition of a Journal
 *
 *  Created on: Oct 31, 2017
 *  Author: esandar
 */

#include "journal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**  Size of allocated journals pointer array */
static size_t JOURNALS_SIZE = 0;

/** pointer to allocated journals pointer array */
static Journal **journals = NULL;

/**
 * Initialize journal cache. Call from perations that access it
 */
static void initJournalsCache(void) {
	if (journals == NULL) {
		JOURNALS_SIZE = 4; //size of journal array
		journals = malloc(JOURNALS_SIZE * sizeof (Journal *));
		journals[0] = NULL; // null terminate array
	}

}
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
  * Create a journal from its information
  * @param issn the journal Issn
  * @param name the journal name
  * @param pub the Publisher
  * @param journal pointer to space for returned Journal, or NULL to use saved journals array
  * @return pointer to journal struct, or to saved journal if journal is NULL
  * 	   (NULL if not defined)
  */
Journal* createJournal(Issn issn, const char* name, Publisher *pub, Journal *journal) {
	if (journal == NULL) {
		initJournalsCache();

		//find journal in array
		int pindex = 0;
		for ( ; journals[pindex] != NULL; pindex++) { //while not as sentinel entry
			if (journal->issn == issn) {
				return journals[pindex];	// return matching journal
			}
		}

		//if journal not found, allocate new struct and add to array
		if (pindex + 1 >= JOURNALS_SIZE) {
			JOURNALS_SIZE *= 2; //double size of journals array
			journals = realloc (journals, JOURNALS_SIZE * sizeof (Journal*));

		}
		journal = malloc ( sizeof(Journal)); //allocate storage for new publisher
		journals[pindex] = journal;	//add pointer to new Publisher to array;
		journals[++pindex] = NULL;	//add null pointer after new one
	}
	journal->issn = issn;
	strcpy(journal->name, name);
	strcpy(journal->publisher->name,pub->name);
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
	for ( ; journals[pindex] != NULL; pindex++) {	//while not at sentinel entry
		if (journals[pindex]->issn == issn) {
			return journals[pindex];	//return matching journal
		}
	}
	return NULL;
}
