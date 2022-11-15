#include "solution.h"

void Solution::addRest(ListNode* l) {
	while (l != nullptr) {
		val = l->val + overflow;
		// 10 or more has a carry over.
		if (val >= 10) {
			overflow = 1;
			val -= 10;
		}
		else {
			overflow = 0;
		}
		tail->next = new ListNode(val);
		tail = tail->next;
		l = l->next;
	}
}

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {
	while (l1 != nullptr && l2 != nullptr) {
		val = l1->val + l2->val + overflow;
		// 10 or more has a carry over.
		if (val >= 10) {
			overflow = 1;
			val -= 10;
		}
		else {
			overflow = 0;
		}
		// Creating the first node.
		if (head == nullptr) {
			head = new ListNode(val, nullptr);
			tail = head;
		}
		else { // We keep updating the tail.
			tail->next = new ListNode(val);
			tail = tail->next;
		}
		// Done with this index.
		l1 = l1->next;
		l2 = l2->next;
	}
	addRest(l1);
	addRest(l2);
	if (overflow > 0) {
		tail->next = new ListNode(overflow);
		tail = tail->next;
	}
	return head;
}
