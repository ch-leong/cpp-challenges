#include "solution.h"

#include <unordered_map>

using namespace std;

vector<int> Solution::twoSum(vector<int> &nums, int target) {
	if (nums.size() == 2) {
		return vector<int>{0, 1};
	}

	// Adding into hash table the value and the position.
	unordered_map<int, int> map;
	int i = 0;
	for (const auto &num : nums) {
		map.insert(pair<int, int>(num, i));
		++i;
	}

	i = 0;
	int j = 0;
	for (const auto &num1 : nums) {
		// A + B = target, so B = target - A. Check if B exist in the hash table.
		if (map.find(target - num1) != map.end() && map[target - num1] != i) {
			return vector<int>{i, map[target - num1]};
		}
		// If not, continue find another B by using another A.
		++i;
	}
	return vector<int>();
}
