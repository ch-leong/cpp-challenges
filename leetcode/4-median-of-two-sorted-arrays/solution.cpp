#include "solution.h"

#include <algorithm>

using namespace std;

double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	// Merge them both, O(n+m).
	nums1.insert(nums1.end(), nums2.begin(), nums2.end());
	// Sort whole thing, O( (n+m)log(n+m) ).
	sort(nums1.begin(), nums1.end());
	// Get median, if even, get average of left and right of middle.
	const int half = nums1.size() / 2;
	if (nums1.size() % 2 == 0) {
		return static_cast<double>(nums1[half - 1] + nums1[half]) / 2.0;
	}
	return static_cast<double>(nums1[half]);
}
