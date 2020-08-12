#include <string>
#include <iostream>
#include <set>

#include <chrono>

bool IsUnique(const std::string& str)
{
	int length = str.length();
	for (int i = 0; i < length; i++) {
		for (int j = i+1; j < length; j++) {
			if (i != j && str[i] == str[j]) {
				return false;
			}
		}
	}
	return true;
}

bool IsUniqueSet(const std::string& str)
{
	// possible improvement: use bitset with one bit per char to reduce memory size
	std::set<char> found;
	std::set<char>::iterator it;

	int length = str.length();
	for (int i = 0; i < length; i++) {
		if (found.count(str[i]) == 0) {
			found.insert(str[i]);
		}
		else {
			return false;
		}
	}

	return true;
}


int main()
{
	std::string posTest = "abcde";
	std::string negTest = "abcda";
	std::string emptyTest = "";

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	std::cout << IsUnique(posTest) << std::endl;
	std::cout << IsUnique(negTest) << std::endl;
	std::cout << IsUnique(emptyTest) << std::endl;
	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[mus]" << std::endl;

	begin = std::chrono::steady_clock::now();
	std::cout << IsUniqueSet(posTest) << std::endl;
	std::cout << IsUniqueSet(negTest) << std::endl;
	std::cout << IsUnique(emptyTest) << std::endl;
	end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[mus]" << std::endl;

}