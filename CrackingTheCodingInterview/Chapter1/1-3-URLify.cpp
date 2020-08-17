#include <iostream>
#include <string>

const char* URLify(const char* string, const int length)
{
	const int newLength = strlen(string);
	// Add one char for null terminator \0
	char* result = new char[newLength + 1];

	unsigned int resultIndex = 0;
	for (unsigned int i = 0; i != length; i++) {
		if (string[i] == ' ') {
			result[resultIndex] = '%';
			result[resultIndex + 1] = '2';
			result[resultIndex + 2] = '0';
			resultIndex += 3;
		}
		else {
			result[resultIndex] = string[i];
			resultIndex++;
		}
	}
	// Add null terminatore
	result[newLength] = '\0';

	return result;
}

void URLifyInplace(char* string, const int length)
{
	const int newLength = strlen(string);
	// Iterate backwards through string to replace only covered characters
	unsigned int resultIndex = newLength - 1;
	for (unsigned int i = length - 1; i != -1; i--) {
		if (string[i] == ' ') {
			string[resultIndex    ] = '0';
			string[resultIndex - 1] = '2';
			string[resultIndex - 2] = '%';
			resultIndex -= 3;
		}
		else {
			string[resultIndex] = string[i];
			resultIndex--;
		}
	}
}

bool equal(const char* str1, const char* str2)
{
	const int length = strlen(str1);
	if (length != strlen(str2))
		return false;

	for (unsigned int i = 0; i != length; i++) {
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}


int main()
{
	// Replace all strings with '%20'
	// Strings have suffcient space
	// Length is given
	// use char*

	const char* result = URLify("Mr John Smith    ", 13);
	
	if (equal("Mr%20John%20Smith", result)) {
		std::cout << "Passed!" << std::endl;
	}
	else {
		std::cout << "Failed! result was " << result << std::endl;
	}

	char string[] = "Mr John Smith    ";
	URLifyInplace(string, 13);

	if (equal("Mr%20John%20Smith", string)) {
		std::cout << "Passed!" << std::endl;
	}
	else {
		std::cout << "Failed! result was " << string << std::endl;
	}

	delete result;

	return  0;
}