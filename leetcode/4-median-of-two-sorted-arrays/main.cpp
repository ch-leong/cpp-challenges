// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
// The overall run time complexity should be O(log (m+n)).
// Constraints:
//   nums1.length == m
//   nums2.length == n
//   0 <= m <= 1000
//   0 <= n <= 1000
//   1 <= m + n <= 2000
//   -106 <= nums1[i], nums2[i] <= 106

#include "solution.h"

#include <iostream>

using namespace std;

int main() {
	Solution solution1;
	vector<int> example1Nums1{ 1, 3 };
	vector<int> example1Nums2{ 2 };
	double correct1 = 2.0; // Explanation: merged array = [1,2,3] and median is 2.
	double result1 = solution1.findMedianSortedArrays(example1Nums1, example1Nums2);
	cout << result1 << "\n";
	if (correct1 == result1) {
		cout << "Test case passed\n";
	}

	Solution solution2;
	vector<int> example2Nums1{ 1, 2 };
	vector<int> example2Nums2{ 3, 4 };
	double correct2 = 2.5; // Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
	double result2 = solution1.findMedianSortedArrays(example2Nums1, example2Nums2);
	cout << result2 << "\n";
	if (correct2 == result2) {
		cout << "Test case passed\n";
	}

	return 0;
}
