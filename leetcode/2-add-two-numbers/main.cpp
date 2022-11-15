// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each of their nodes contains a single digit.
// Add the two numbers and return the sum as a linked list.
// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

#include "solution.h"

#include <iostream>
#include <memory>

using namespace std;

ostream& operator<<(ostream& out, ListNode *ln) {
    out << "{ ";
	while (ln != nullptr) {
        out << ln->val;
        if (ln->next != nullptr) 
        	out << ", ";
		ln = ln->next;
	}
    out << " }\n";
    return out;
}

bool equal(ListNode *l, ListNode *r) {
	if (l == nullptr || r == nullptr) {
		return false;
	}
	while (l != nullptr || r != nullptr) {
		if (l->val != r->val) {
			return false;
		}
		l = l->next;
		r = r->next;
		if ((l == nullptr && r != nullptr) || (l != nullptr && r == nullptr)) {
			return false;
		}
	}
	return true;
}

int main() {
	Solution solution1;
	unique_ptr<ListNode> example1_l1{ new ListNode(2, new ListNode(4, new ListNode(3))) };
	unique_ptr<ListNode> example1_l2{ new ListNode(5, new ListNode(6, new ListNode(4))) };
	unique_ptr<ListNode> correct1{ new ListNode(7, new ListNode(0, new ListNode(8))) }; // Explanation: 342 + 465 = 807.
	unique_ptr<ListNode> result1{ solution1.addTwoNumbers(example1_l1.get(), example1_l2.get()) };
	cout << result1.get();
	if (equal(result1.get(), correct1.get())) {
		cout << "Test case passed\n";
	}

	Solution solution2;
	unique_ptr<ListNode> example2_l1{ new ListNode(0) };
	unique_ptr<ListNode> example2_l2{ new ListNode(0) };
	unique_ptr<ListNode> correct2{ new ListNode(0) };
	unique_ptr<ListNode> result2{ solution2.addTwoNumbers(example2_l1.get(), example2_l2.get()) };
	cout << result2.get();
	if (equal(result2.get(), correct2.get())) {
		cout << "Test case passed\n";
	}

	Solution solution3;
	unique_ptr<ListNode> example3_l1{ new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))))))) };
	unique_ptr<ListNode> example3_l2{ new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9)))) };
	unique_ptr<ListNode> correct3{ new ListNode(8, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(0, new ListNode(0, new ListNode(0, new ListNode(1)))))))) };
	unique_ptr<ListNode> result3{ solution3.addTwoNumbers(example3_l1.get(), example3_l2.get()) };
	cout << result3.get();
	if (equal(result3.get(), correct3.get())) {
		cout << "Test case passed\n";
	}

	return 0;
}
