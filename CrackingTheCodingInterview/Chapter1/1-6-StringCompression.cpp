/**
 * Implement a method to perform basic string compression using the counts
 * of repeated characters. For example, the string aabcccccaaa would become a2b1c5a3. If the
 * "compressed" string would not become smaller than the original string, your method should return
 * the original string. You can assume the string has only uppercase and lowercase letters (a - z). 
 */

#include <string>
#include <iostream>

std::string CompressString(const std::string& str)
{
	size_t length = str.length();
	if (length < 2) {
		return str;
	}
	char c = str[0];
	int cCount = 1;

	std::string result;
	// prevent allocation during loop by reserving enough memory
	result.reserve(str.length());

	// start with 2nd char
	for (size_t i = 1; i < length; i++) {
		if (c != str[i]) {
			result += c + std::to_string(cCount);
			c = str[i];
			cCount = 1;
		}
		else {
			cCount++;
		}

		// early return if results gets to long
		if (result.length() >= length) {
			return std::string(str);
		}
	}
	if (c != 0) {
		result += c + std::to_string(cCount);;
	}
	if (result.length() >= length) {
		return std::string(str);
	}

	return result;
}

int main()
{
	std::string testStr1 = "aabcccccaaa";
	std::string testStr1Result = "a2b1c5a3";
	std::string testStr2 = "SomeOtherString";
	std::string testStr2Result = testStr2;

	std::cout << testStr1 << " -> " << CompressString(testStr1) << std::endl;
	std::cout << (CompressString(testStr1) == testStr1Result ? "PASS" : "FAIL") << std::endl;
	std::cout << testStr2 << " -> " << CompressString(testStr2) << std::endl;
	std::cout << (CompressString(testStr2) == testStr2Result ? "PASS" : "FAIL") << std::endl;

	return 0;
}