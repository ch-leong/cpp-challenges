#include "solution.h"

#include <cstring>

int Solution::lengthOfLongestSubstring(std::string s) {
	// A vector of boolean to check if char exist. Since signed char has size of 128, this size is same.
	char exist[128];
	int length = 0, longestLength = 0;
	memset(exist, 0, 128);
	for (int i = 0; i < s.size(); ++i) {
		exist[s[i]] = 1;
		++length;
		for (int j = i + 1; j < s.size(); ++j) {
			// Check using value as index.
			if (exist[s[j]] != 0) {
				// Exists, so we stopped here.
				break;
			}
			exist[s[j]] = 1;
			++length;
		}
		if (longestLength < length) {
			longestLength = length;
		}
		memset(exist, 0, 128);
		length = 0;
	}
	return longestLength;
}
