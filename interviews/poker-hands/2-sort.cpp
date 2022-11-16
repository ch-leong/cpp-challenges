// sort
// Complete the function f that sorts an integer array by ascending order.
// For example, given array 2 1, function f should output 1 2.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace Sort
{

std::string f(const std::vector<int>& input) {
	if (input.size() == 0) {
		return std::string();
	}
	std::vector<int> output = input;
	std::sort(output.begin(), output.end());

	std::string outputStr;
	for (int i = 0; i < output.size(); ++i) {
		outputStr += std::to_string(output[i]) + " ";
	}
	outputStr.pop_back();
	return outputStr;
}

} // namespace Sort

/*
int main() {
	using namespace Sort;

	std::vector<int> test = { 2, 1};
	std::cout << f(test);
	return 0;
}
*/
