// Given a string s, find the length of the longest substring without repeating characters.

#include "solution.h"

#include <iostream>

using namespace std;

int main() {
	Solution solution1;
	string example1 = "abcabcbb";
	int result1 = solution1.lengthOfLongestSubstring(example1);
	cout << result1 << "\n";
	if (result1 == 3) { // Explanation: The answer is "abc", with the length of 3.
		cout << "Test case passed\n";
	}

	Solution solution2;
	string example2 = "bbbbb";
	int result2 = solution2.lengthOfLongestSubstring(example2);
	cout << result2 << "\n";
	if (result2 == 1) { // Explanation: The answer is "b", with the length of 1.
		cout << "Test case passed\n";
	}

	Solution solution3;
	string example3 = "pwwkew";
	int result3 = solution3.lengthOfLongestSubstring(example1);
	cout << result3 << "\n";
	if (result3 == 3) { // Explanation: The answer is "wke", with the length of 3.
						// Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
		cout << "Test case passed\n";
	}

	return 0;
}
