#include <string>
#include <set>
#include <iostream>
#include <algorithm>

#include <chrono>

//
// Generate all permutations then compare
//
void GeneratePermutation(const std::string permutation, const std::string source, std::set<std::string> &out)
{
	const size_t length = source.length();
	if (length == 0) {
		out.insert(permutation);
		return;
	}

	for (size_t i = 0; i != length; i++) {
		std::string nextSource(source);
		nextSource.erase(i, 1);
		GeneratePermutation((permutation + source[i]), nextSource, out);
	}
}

bool CheckPermutation(const std::string &str1, const std::string &str2)
{
	// Strings must have same length to be permutation of each other
	if (str1.length() != str2.length()) {
		return false;
	}

	// Generate all permutations of str1
	std::set<std::string> permutations;
	GeneratePermutation("", str1, permutations);

	// Check if any permutation matches str2
	for (auto elem : permutations) {
		if (elem == str2) {
			return true;
		}
	}

	return false;
}

//
// Generate and compare all permutations immediately
//
bool GenerateAndComparePermutation(const std::string permutation, const std::string source, const std::string other)
{
	const size_t length = source.length();
	if (length == 0) {
		// Immediatly compare permutation to target instead of storing all permutations
		return permutation == other;
	}

	bool result = false;
	for (size_t i = 0; i != length; i++) {
		std::string nextSource(source);
		nextSource.erase(i, 1);
		result |= GenerateAndComparePermutation(permutation + source[i], nextSource, other);
	}
	return result;
}

bool CheckPermutation_Direct(const std::string& str1, const std::string& str2)
{
	// Strings must have same length to be permutation of each other
	if (str1.length() != str2.length()) {
		return false;
	}

	return GenerateAndComparePermutation("", str1, str2);
}

//
// Sort and compare
//
bool CheckPermutation_Sort(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) {
		return false;
	}

	std::string s1 = str1;
	std::string s2 = str2;

	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	return s1 == s2;
}

//
// Sort and compare
//
bool CheckPermutation_SortCustomCompare(const std::string& str1, const std::string& str2)
{
	const size_t length = str1.length();
	if (length != str2.length()) {
		return false;
	}

	std::string s1 = str1;
	std::string s2 = str2;

	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	// Compare sorted strings
	for (int i = 0; i < length; i++)
		if (s1[i] != s2[i])
			return false;

	return true;
}

//
// Count characters
//
bool CheckPermutation_CountChars(const std::string& str1, const std::string& str2)
{
	const size_t length = str1.length();
	if (length != str2.length()) {
		return false;
	}

	int count[256] = { 0 };
	for (size_t i = 0; i < length; i++) {
		int val = str1[i];
		count[val]++;
	}

	for (size_t i = 0; i < length; i++) {
		int val = str2[i];
		count[val]--;
		if (count[val] == -1)
			return false;
	}
	return true;
}


void TestFunc(bool (*func)(const std::string&, const std::string&))
{
	std::string str1 = "test";
	std::string str2 = "something longer";
	std::string str3 = "abcd";
	std::string str4 = "tets";

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	std::cout << func(str1, str2) << std::endl;
	std::cout << func(str1, str3) << std::endl;
	std::cout << func(str1, str4) << std::endl;
	std::cout << func(str1, str1) << std::endl;
	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[mus]" << std::endl;
}

int main()
{
	std::cout << "Generate all permutations then compare" << std::endl;
	TestFunc(CheckPermutation);

	std::cout << "Generate and compare permutations immedately" << std::endl;
	TestFunc(CheckPermutation_Direct);

	std::cout << "Sort strings" << std::endl;
	TestFunc(CheckPermutation_Sort);

	// THIS IS THE FASTEST!!
	std::cout << "Sort strings and custom compare" << std::endl;
	TestFunc(CheckPermutation_SortCustomCompare); 

	std::cout << "Count chars" << std::endl;
	TestFunc(CheckPermutation_CountChars);


	std::cin.get();
}