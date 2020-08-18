/**
 * There are three types of edits that can be performed on strings: insert a character,
 * remove a character, or replace a character. Given two strings, write a function 
 * to check if they are one edit (or zero edits) away.
 * EXAMPLE
 * pale,  pIe   -> true
 * pales, pale  -> true
 * pale,  bale  -> true
 * pale,  bake  -> false 
 *
 * Hints: #23, #97, #130 
 */
#include <string>
#include <iostream>

bool CheckDelete(const char*& str1, const char*& str2)
{
	size_t sLen1 = strlen(str1);
	size_t sLen2 = strlen(str2);

	int deletes = 0;
	bool deleteEdit = sLen1 == sLen2 + 1;
	if (deleteEdit) {
		for (size_t i = 0, j = 0; i < sLen1 && j < sLen2; i++, j++) {
			if (str1[i] != str2[j]) {
				deletes++;
				i++; // move to next index in str1
				if (deletes > 1) {
					deleteEdit = false;
					break;
				}
			}
		}
	}
	return deleteEdit;
}

bool IsOneEditAway(const char* str1, const char* str2)
{
	size_t sLen1 = strlen(str1);
	size_t sLen2 = strlen(str2);

	// Check replace
	int replace = 0;
	bool singleReplaceOrEqual = sLen1 == sLen2;
	if (singleReplaceOrEqual) {
		for (size_t i = 0; i < sLen1; i++) {
			if (str1[i] != str2[i]) {
				replace++;
				// string are same length and one or less replacements away
				if (replace > 1) {
					singleReplaceOrEqual = false;
					break;
				}
			}
		}
	}

	// Check delete
	bool singleDeleteEdit = CheckDelete(str1, str2);

	// Check insert (it's just a delete edit with str1 and str2 swapped)
	bool singleInsertEdit = CheckDelete(str2, str1);

	return singleReplaceOrEqual ^ singleDeleteEdit ^ singleInsertEdit;
}

bool IsOneEditAway_singlePass(const char* str1, const char* str2)
{
	size_t sLen1 = strlen(str1);
	size_t sLen2 = strlen(str2);

	// swap the longer string into s1
	const char*& s1 = sLen1 >= sLen2 ? str1 : str2;
	const char*& s2 = sLen1 < sLen2 ? str1 : str2;
	sLen1 = strlen(s1);
	sLen2 = strlen(s2);

	// String differ by more than 2 characters
	if (sLen1 - sLen2 > 1)
		return false;

	// Check replace
	int replace = 0;
	bool singleReplaceOrEqual = sLen1 == sLen2;
	bool singleDeleteEdit = sLen1 == sLen2 + 1;
	bool editFound = false;
	for (size_t i = 0, j = 0; i < sLen1 && j < sLen2; i++, j++) {
		if (s1[i] != s2[j]) {
			// It's the 2nd edit
			if (editFound)
				return false;

			editFound = true;

			if (sLen1 > sLen2) {
				j--;
			}
		}
	}

	return true;
}

int main()
{
	std::cout << IsOneEditAway("pale", "ple")   << std::endl;  // expect: true
	std::cout << IsOneEditAway("pale", "pales") << std::endl;  // expect: true
	std::cout << IsOneEditAway("pale", "pasle") << std::endl;  // expect: true
	std::cout << IsOneEditAway("pale", "bale")  << std::endl;  // expect: true
	std::cout << IsOneEditAway("pale", "pale") << std::endl;   // exptect: true
	std::cout << IsOneEditAway("pale", "bake")  << std::endl;  // expect: false
	std::cout << IsOneEditAway("pale", "palesy") << std::endl; // expected: false

	std::cout << IsOneEditAway_singlePass("pale", "ple") << std::endl;    // expect: true
	std::cout << IsOneEditAway_singlePass("pale", "pales") << std::endl;  // expect: true
	std::cout << IsOneEditAway_singlePass("pale", "pasle") << std::endl;  // expect: true
	std::cout << IsOneEditAway_singlePass("pale", "bale") << std::endl;   // expect: true
	std::cout << IsOneEditAway_singlePass("pale", "pale") << std::endl;   // exptect: true
	std::cout << IsOneEditAway_singlePass("pale", "bake") << std::endl;   // expect: false
	std::cout << IsOneEditAway_singlePass("pale", "palesy") << std::endl; // expected: false

	return 0;
}