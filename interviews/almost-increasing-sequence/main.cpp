// Given a sequence of integers as an array, determine whether it is
// possible to obtain a strictly increasing sequence by removing no more
// than one element from the array.

#include <iostream>
#include <vector>

using namespace std;

bool solution(vector<int> sequence) {
	int prev = sequence[0], removedCount = 0;
	for (int i = 1; i < sequence.size(); ++i) {
		// Strictly increasing, so equal and decreasing is out.
		if (sequence[i] <= prev) {
			if (removedCount > 0) {
				// Already required to remove more than 1, stop here.
				return false;
			}
			++removedCount;
			// Check left and right is also strictly increasing without middle.
			if (i == 1 || (i - 2 > 0 && sequence[i] > sequence[i - 2])) {
				prev = sequence[i];
			}
		} else {
			prev = sequence[i];
		}
	}
	return true;
	/*for (int i = 0; i < sequence.size(); ++i) {
		bool isIncreasing = true;
		for (int j = 0; j < sequence.size() - 1; ++j) {
			if (j + 1 == i && j + 2 < sequence.size()) {
				if (sequence[j] >= sequence[j + 2]) {
					isIncreasing = false;
					break;
				}
			} else if (j == i) {
				continue;
			} else if (j + 1 != i) {
				if (sequence[j] >= sequence[j + 1]) {
					isIncreasing = false;
					break;
				}
			}
		}
		if (isIncreasing) {
			return true;
		}
	}
	return false;*/
}

int main()
{
	vector<int> sequence1 = {1, 3, 2, 1};
	if (solution(sequence1) == false) {
		cout << "Test case passed\n";
	}

	vector<int> sequence2 = {1, 3, 2};
	if (solution(sequence2) == true) {
		cout << "Test case passed\n";
	}

	return 0;
}
