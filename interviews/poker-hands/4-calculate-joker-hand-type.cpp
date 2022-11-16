// calculate hand type
// Complete the function f that computes the ranking of a poker hand. The input is consisted of five integers that represent different poker cards.
// Belows are the correspoding relationship between each interger(for better reading, the integer is shown in hexadecimal) and poker card:
//
// 0x102,0x103,0x104,0x105,0x106,0x107,0x108,0x109,0x10a,0x10b,0x10c,0x10d,0x10e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of diamond.
// 0x202,0x203,0x204,0x205,0x206,0x207,0x208,0x209,0x20a,0x20b,0x20c,0x20d,0x20e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of club.
// 0x302,0x303,0x304,0x305,0x306,0x307,0x308,0x309,0x30a,0x30b,0x30c,0x30d,0x30e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of heart.
// 0x402,0x403,0x404,0x405,0x406,0x407,0x408,0x409,0x40a,0x40b,0x40c,0x40d,0x40e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of spade.
// 0x50f and 0x610 reprents two different wild cards.
//
// 1. Royal flush: A poker hand with the A, K, Q, K and 10 all in the same suit.
// 2. Straight flush: A poker hand with consecutive cards in the same suit.
// 3. Four of a kind: A poker hand with 4 cards with the same rank plus 1 arbitrary card.
// 4. Full house: A poker hand with 3 of a kind and a pair.
// 5. Flush: A poker hand with all 5 cards in the same suit.
// 6. Straight: A poker hand with 5 consecutive cards (regardless of suit).
// 7. Three of a kind: A poker hand with 3 cards with the same rank plus 2 cards in different rank.
// 8. Two pair: A poker hand with two pairs of similar-ranking cards plus 1 arbitrary card.
// 9. One pair: A poker hand with 2 cards in same rank plus 3 cards in different rank.
// 10. High card: A poker hand that do not make any of the poker hands given above.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace
{

#define HandSize 5
#define TypeSize 4
#define ValueSize 13

#define RoyalFlush 1
#define StraightFlush 2
#define FourOfAKind 3
#define FullHouse 4
#define Flush 5
#define Straight 6
#define ThreeOfAKind 7
#define TwoPair 8
#define OnePair 9
#define HighCard 10

#define ShiftTwoHex 8
#define PositionZeroHex 0xf
#define PositionTwoHex 0xf00

const int Joker1 = 0x50f;
const int Joker2 = 0x610;

bool isStraight(const vector<int>& values, int wilds) {
	if (wilds >= 1) {
		for (int i = 0; i < values.size() - 4; ++i) {
			if ((i > 4 && values[i - 4] + values[i - 3] + values[i - 2] + values[i - 1] + values[i] + wilds == 5)
				|| (i > 3 && values[i - 3] + values[i - 2] + values[i - 1] + values[i] + values[i + 1] + wilds == 5)
				|| (i > 2 && values[i - 2] + values[i - 1] + values[i] + values[i + 1] + values[i + 2] + wilds == 5)
				|| (i > 1 && values[i - 1] + values[i] + values[i + 1] + values[i + 2] + values[i + 3] + wilds == 5)
				|| (values[i] + values[i + 1] + values[i + 2] + values[i + 3] + values[i + 4] + wilds == 5)) {
				return true;
			}
		}
		return false;
	} else {
		for (int i = 0; i < values.size() - 4; ++i) {
			if (values[i] == 0) {
				continue;
			}
			if (values[i + 1] == 1 && values[i + 2] == 1 && values[i + 3] == 1 && values[i + 4] == 1) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

int flushType(const vector<int>& values, int wilds) {
	if (values[8] + values[9] + values[10] + values[11] + values[12] + wilds >= 5) {
		return RoyalFlush;
	} else if (isStraight(values, wilds)) {
		return StraightFlush;
	}
	return Flush;
}

int f(const std::vector<int>& input) {
	vector<int> types = vector<int>(TypeSize, 0);
	vector<int> values = vector<int>(ValueSize, 0);
	int wilds = 0;
	vector<int> sortedInput = input;
	sort(sortedInput.begin(), sortedInput.end());

	for (int i = 0; i < sortedInput.size(); ++i) {
		if (sortedInput[i] == Joker1 || sortedInput[i] == Joker2) {
			++wilds;
			continue;
		}
		types[((sortedInput[i] & PositionTwoHex) >> ShiftTwoHex) - 1] += 1;
		values[(sortedInput[i] & PositionZeroHex) - 0x2] += 1;
	}

	for (int i = 0; i < types.size(); ++i) {
		if (types[i] + wilds == HandSize) {
			return flushType(values, wilds);
		}
	}

	for (int i = 0; i < values.size(); ++i) {
		if (wilds == 2) {
			if (values[i] >= 2) {
				return FourOfAKind;
			} else if (values[i] == 1) {
				for (int j = i + 1; j < values.size(); ++j) {
					if (values[j] == 2) {
						return FourOfAKind;
					}
				}
				return isStraight(values, wilds) ? Straight : ThreeOfAKind;
			}
		} else if (wilds == 1) {
			if (values[i] >= 3) {
				return FourOfAKind;
			} else if (values[i] == 2) {
				for (int j = i + 1; j < values.size(); ++j) {
					if (values[j] == 2) {
						return FullHouse;
					}
				}
				return isStraight(values, wilds) ? Straight : ThreeOfAKind;
			} else if (values[i] == 1) {
				for (int j = i + 1; j < values.size(); ++j) {
					if (values[j] == 3) {
						return FullHouse;
					} else if (values[j] == 2) {
						return isStraight(values, wilds) ? Straight : TwoPair;
					}
				}
				return isStraight(values, wilds) ? Straight : OnePair;
			}
		} else {
			if (values[i] == 4) {
				return FourOfAKind;
			} else if (values[i] == 3) {
				for (int j = i + 1; j < values.size(); ++j) {
					if (values[j] == 2) {
						return FullHouse;
					}
				}
				return ThreeOfAKind;
			} else if (values[i] == 2) {
				for (int j = i + 1; j < values.size(); ++j) {
					if (values[j] == 3) {
						return FullHouse;
					} else if (values[j] == 2) {
						return TwoPair;
					}
				}
				return OnePair;
			}
		}
	}

	return isStraight(values, wilds) ? Straight : HighCard;
}

} // namespace

/*
int main() {
	vector<int> royalFlush1 = { 0x10a, 0x10b, 0x10c, 0x10d, 0x10e };
	cout << "royalFlush1: " << to_string(f(royalFlush1)) << " (1)\n";
	vector<int> royalFlush2 = { 0x10a, 0x10b, Joker1, 0x10d, 0x10e };
	cout << "royalFlush2: " << to_string(f(royalFlush2)) << " (1)\n";
	vector<int> royalFlush3 = { 0x10a, Joker1, 0x10c, Joker2, 0x10e };
	cout << "royalFlush3: " << to_string(f(royalFlush3)) << " (1)\n";

	vector<int> straightFlush1 = { 0x102, 0x103, 0x104, 0x105, 0x106 };
	cout << "straightFlush1: " << to_string(f(straightFlush1)) << " (2)\n";
	vector<int> straightFlush2 = { Joker1, 0x103, 0x104, 0x105, 0x106 };
	cout << "straightFlush2: " << to_string(f(straightFlush2)) << " (2)\n";
	vector<int> straightFlush3 = { 0x102, 0x103, 0x104, Joker2, 0x106 };
	cout << "straightFlush3: " << to_string(f(straightFlush3)) << " (2)\n";

	vector<int> fourOfAKind1 = { 0x102, 0x202, 0x302, 0x402, 0x103 };
	cout << "fourOfAKind1: " << to_string(f(fourOfAKind1)) << " (3)\n";
	vector<int> fourOfAKind2 = { Joker1, 0x202, 0x302, 0x402, 0x103 };
	cout << "fourOfAKind2: " << to_string(f(fourOfAKind2)) << " (3)\n";
	vector<int> fourOfAKind3 = { 0x102, 0x202, 0x302, Joker1, Joker2 };
	cout << "fourOfAKind3: " << to_string(f(fourOfAKind3)) << " (3)\n";

	vector<int> fullHouse1 = { 0x102, 0x202, 0x103, 0x203, 0x303 };
	cout << "fullHouse1: " << to_string(f(fullHouse1)) << " (4)\n";
	vector<int> fullHouse2 = { 0x102, 0x202, Joker1, 0x203, 0x303 };
	cout << "fullHouse2: " << to_string(f(fullHouse2)) << " (4)\n";
	vector<int> fullHouse3 = { 0x102, Joker1, 0x103, Joker2, 0x303 }; // Four of a kind is okay since it is higher.
	cout << "fullHouse3: " << to_string(f(fullHouse3)) << " (3)\n";

	vector<int> flush1 = { 0x102, 0x103, 0x104, 0x105, 0x107 };
	cout << "flush1: " << to_string(f(flush1)) << " (5)\n";
	vector<int> flush2 = { Joker1, 0x103, 0x104, 0x105, 0x10c };
	cout << "flush2: " << to_string(f(flush2)) << " (5)\n";
	vector<int> flush3 = { Joker1, Joker2, 0x107, 0x105, 0x10d };
	cout << "flush3: " << to_string(f(flush3)) << " (5)\n";

	vector<int> straight1 = { 0x102, 0x203, 0x304, 0x405, 0x206 };
	cout << "straight1: " << to_string(f(straight1)) << " (6)\n";
	vector<int> straight2 = { Joker1, 0x203, 0x304, 0x405, 0x206 };
	cout << "straight2: " << to_string(f(straight2)) << " (6)\n";
	vector<int> straight3 = { Joker1, 0x203, 0x304, Joker2, 0x406 };
	cout << "straight3: " << to_string(f(straight3)) << " (6)\n";

	vector<int> threeOfAKind1 = { 0x102, 0x202, 0x302, 0x405, 0x206 };
	cout << "threeOfAKind1: " << to_string(f(threeOfAKind1)) << " (7)\n";
	vector<int> threeOfAKind2 = { 0x102, Joker1, 0x302, 0x40a, 0x206 };
	cout << "threeOfAKind2: " << to_string(f(threeOfAKind2)) << " (7)\n";
	vector<int> threeOfAKind3 = { Joker1, 0x202, Joker2, 0x405, 0x20a };
	cout << "threeOfAKind3: " << to_string(f(threeOfAKind3)) << " (7)\n";

	vector<int> twoPair1 = { 0x102, 0x202, 0x304, 0x404, 0x305 };
	cout << "twoPair1: " << to_string(f(twoPair1)) << " (8)\n";
	vector<int> twoPair2 = { Joker1, 0x202, 0x304, 0x404, 0x30a };
	cout << "twoPair2: " << to_string(f(twoPair2)) << " (8)\n";
	vector<int> twoPair3 = { Joker1, 0x202, Joker2, 0x404, 0x30a }; // Three of a kind here is okay since it is higher.
	cout << "twoPair3: " << to_string(f(twoPair3)) << " (7)\n";

	vector<int> onePair1 = { 0x102, 0x202, 0x404, 0x405, 0x306 };
	cout << "onePair1: " << to_string(f(onePair1)) << " (9)\n";
	vector<int> onePair2 = { 0x10c, 0x202, Joker1, 0x405, 0x306 };
	cout << "onePair2: " << to_string(f(onePair2)) << " (9)\n";
	vector<int> onePair3 = { 0x102, Joker1, Joker2, 0x40a, 0x306 }; // Three of a kind here is okay since it is higher.
	cout << "onePair3: " << to_string(f(onePair3)) << " (7)\n";

	vector<int> highCard1 = { 0x102, 0x203, 0x30c, 0x405, 0x20b };
	cout << "highCard1: " << to_string(f(highCard1)) << " (10)\n";
	vector<int> highCard2 = { Joker1, 0x203, 0x30c, 0x405, 0x20b }; // Two of a kind here is okay since it is higher.
	cout << "highCard2: " << to_string(f(highCard2)) << " (9)\n";
	vector<int> highCard3 = { Joker1, 0x203, 0x30c, 0x405, Joker2 }; // Three of a kind here is okay since it is higher.
	cout << "highCard3: " << to_string(f(highCard3)) << " (7)\n";

	return 0;
}
*/
