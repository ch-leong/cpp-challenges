// Given a list dots with 2-d coordinates (x, y), each pair represents a dot in the plane,
// and each dot has a corresponding integer score (could be either negative or positive integers).
// Take the origin as the center, inifinite number of rings(donuts) could be drawn.
// There will be a ring, which could give you the maximum summation of all scores within
// the ring area (dots at both the outer radius & inner radius), return the maxium summaton of scores.
// For Example, dots: (-1, 1, -10) (1, 0, 2) (-2, 2, 1) (-2, -2, 3) (2, -2, 20) (3, 2, 1000) (-4, 2, -10) (-1, -5, 4 )
// you can find an annulus, which gives you a maximum score of 1024.
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

bool isNearer(const vector<int>& lhs, const vector<int>& rhs) {
	return sqrt(lhs[0] * lhs[0] + lhs[1] * lhs[1]) < sqrt(rhs[0] * rhs[0] + rhs[1] * rhs[1]);
}

int main() {
	vector<vector<int>> coordinates = { { -1, 1, -10 }, { 1, 0, 2 }, { -2, 2, 1 }, { -2, -2, 3 }
		, { 2, -2, 20 }, { 3, 2, 1000 }, { -4, 2, -10 }, { -1, -5, 4 }};
	// Sort so that the vector contains coordinate from center to outer.
	sort(coordinates.begin(), coordinates.end(), isNearer);

	int biggestScore = coordinates[0][2];
	// We search from inner, increasing inner each time.
	for (int i = 0; i < coordinates.size(); ++i) {
		// We search from outer, increasing outer each time.
		for (int j = i + 1; j < coordinates.size(); ++j) {
			// If this inner-outer pair is bigger, we keep it.
			int score = 0;
			for (int k = i; k <= j; ++k) {
				score += coordinates[k][2];
			}
			if (score > biggestScore) {
				biggestScore = score;
			}
		}
	}
	cout << biggestScore;
	return 0;
}
