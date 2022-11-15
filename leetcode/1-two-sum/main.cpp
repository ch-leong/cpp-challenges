// Given an array of integers nums and an integer target,
// return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution,
// and you may not use the same element twice.
// You can return the answer in any order.

#include "solution.h"

#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "{";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last) 
            out << ", ";
    }
    out << "}\n";
    return out;
}

int main() {
	Solution solution1;
	vector<int> example1{ 2, 7, 11, 15 };
	vector<int> correct1{ 0, 1 }; // Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
	vector<int> result1 = solution1.twoSum(example1, 9);
	cout << result1;
	if (equal(result1.begin(), result1.end(), correct1.begin())) {
		cout << "Test case passed\n";
	}

	Solution solution2;
	vector<int> example2{ 3, 2, 4 };
	vector<int> correct2{ 1, 2 };
	vector<int> result2 = solution2.twoSum(example2, 6);
	cout << result2;
	if (equal(result2.begin(), result2.end(), correct2.begin())) {
		cout << "Test case passed\n";
	}

	Solution solution3;
	vector<int> example3{ 3, 3 };
	vector<int> correct3{ 0, 1 };
	vector<int> result3 = solution3.twoSum(example3, 6);
	cout << result3;
	if (equal(result3.begin(), result3.end(), correct3.begin())) {
		cout << "Test case passed\n";
	}

	return 0;
}
