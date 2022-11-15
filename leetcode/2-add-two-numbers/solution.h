struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
	~ListNode() { if (next != nullptr) delete next; }
};

class Solution {
	ListNode *head = nullptr, *tail = nullptr;
    int overflow = 0;
    int val = 0;
    void addRest(ListNode* l);
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
};
