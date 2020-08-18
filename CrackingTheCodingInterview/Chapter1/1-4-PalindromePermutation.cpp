#include <iostream>
#include <bitset>

bool IsPalinPermu(const char* str)
{
	std::bitset<256> charOdd(0);
	const size_t length = strlen(str);

	for (size_t i = 0; i != length; i++) {
		if (str[i] == ' ')
			continue;

		charOdd[str[i]] = ((charOdd[str[i]] + 1) % 2);
	}

	// The following argumentation ignores spaces for string length.
	// odd count must be 0 (string length is even)
	// or 1 (string length is odd); it is not possible that the string length is even and the odd count is 1
	return charOdd.count() <= 1;
}

void Assert(bool condition)
{
	if (condition)
		std::cout << "PASS" << std::endl;
	else
		std::cout << "FAIL" << std::endl;
}

int main()
{
	/**
	 * Given a string, write a function to check if it is a permutation of a palindrome. 
	 * A palindrome is a word or phrase that is the same forwards and backwards. 
	 * A permutation is a rearrangement of letters. 
	 * The palindrome does not need to be limited to just dictionary words. 
	 * 
	 * EXAMPLE
	 * Input:  Tact Coa
	 * Output: True (permutations: "taco cat", "atco cta",...)
	 * 
	 * Assumptions:
	 * - spaces are ignored ("taco cat" == "tacocat")
	 * - permutations can bridge words ("taco cat" can permute to "ttaa occ")
	 * - lower case characters are not equal upper case characters ("T" != "t")
	 */

	const char* testStr1 = "taco cat";
	const char* testStr2 = "taco ca";

	Assert(IsPalinPermu(testStr1) == true);
	Assert(IsPalinPermu(testStr2) == false);

	return 0;
}