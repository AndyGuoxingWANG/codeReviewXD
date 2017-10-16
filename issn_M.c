/*
 * issn.c
 * This file contains the definition of functions that
 * convert from Issn to string and string to Issn.
 *
 * Assignment 9
 * CS 5001, Fall 2017
 * Northeastern University Silicon Valley
 */

#include "issn.h"
#include <stdio.h>

/** Declaration of an invalid ISSN */
const Issn NO_ISSN = 0;

/**
 * Converts an Issn to a string.
 * @param issn an Issn
 * @param issnStr the result string of at least 10 characters.
 * @return a pointer to the result string representing the ISSN
 */
char *issnToString(Issn issn, char *issnStr) {
		int dgt, sum =0, copyIssn = issn;
		//calculate sum of digits * position
		for (int i = 0; i < 7; i++){
			dgt = issn%10;
			sum += dgt*(i+2);
			issn /= 10;
		}
		int rmd = 11, checksum;
		char lastChar;
		//get checksum
		rmd = sum % 11;
		checksum = 11 - rmd;
		// get the last character in the issn according to checksum
		if (rmd == 0) {
			lastChar = '0';
		}else if (checksum == 10){
			lastChar = 'X';
		}else {
			lastChar = checksum + '0';
		}
		//convert issn from int to string
		sprintf (issnStr, "%04d-%03d%c", copyIssn/1000, copyIssn%1000, lastChar);
		return issnStr;
	}

/**
 * Parses a string representing an ISSN and returns the
 * corresponding Issn.
 * @param issnStr the string representing an ISSN
 * @return an Issn or the constant NO_ISSN if the input
 *   does not represent a valid ISSN string.
 */
Issn parseIssn(const char *issnStr) {
	//check the format of issn; calculate first 7 digits of issn and sum
	Issn issn = 0;
	int sum = 0, j = 8;
	if (strlen(issnStr) != 9){
		return NO_ISSN;
	}
	for (int i = 0; i < 8; i++){
		if (i == 4){
			if (issnStr[4] != '-'){
				return NO_ISSN;
			}
		}else{
			if (issnStr[i] < '0' || issnStr[i] > '9'){
				return NO_ISSN;
			}
			issn = 10 * issn + (issnStr[i] - '0');
			sum += j * (issnStr[i] - '0');
			j--;
		}
	}
	if (issnStr[8] != 'X' && (issnStr[8] < '0' || issnStr[8] > '9')){
		return NO_ISSN;
	}
	//check the last digit of issn
	int rmd = sum % 11;
	int checksum = 11 - rmd;
	if (rmd == 0){
		if (issnStr[8] != '0'){
			return NO_ISSN;
		}
	}else if (checksum == 10){
		if (issnStr[8] != 'X'){
			return NO_ISSN;
		}
	}else {
		if (issnStr[8] != checksum + '0'){
			return NO_ISSN;
		}
	}
	return issn;
}


