// calculate hand type
// Complete the function f that computes the ranking of a poker hand. The input is consisted of five integers that represent different poker cards.
// Belows are the correspoding relationship between each interger(for better reading, the integer is shown in hexadecimal) and poker card:
//
// 0x102,0x103,0x104,0x105,0x106,0x107,0x108,0x109,0x10a,0x10b,0x10c,0x10d,0x10e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of diamond.
// 0x202,0x203,0x204,0x205,0x206,0x207,0x208,0x209,0x20a,0x20b,0x20c,0x20d,0x20e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of club.
// 0x302,0x303,0x304,0x305,0x306,0x307,0x308,0x309,0x30a,0x30b,0x30c,0x30d,0x30e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of heart.
// 0x402,0x403,0x404,0x405,0x406,0x407,0x408,0x409,0x40a,0x40b,0x40c,0x40d,0x40e correspond to 2,3,4,5,6,7,8,9,10,J,Q,K,A of spade.
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

bool isStraight(const vector<int>& values) {
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
	return false;
}

int flushType(const vector<int>& values) {
	if (values[8] == 1 && values[9] == 1 && values[10] == 1 && values[11] == 1 && values[12] == 1) {
		return RoyalFlush;
	} else if (isStraight(values)) {
		return StraightFlush;
	}
	return Flush;
}


int f(const std::vector<int>& input) {
	vector<int> types = vector<int>(TypeSize, 0);
	vector<int> values = vector<int>(ValueSize, 0);
	vector<int> sortedInput = input;
	sort(sortedInput.begin(), sortedInput.end());

	for (int i = 0; i < sortedInput.size(); ++i) {
		types[((sortedInput[i] & PositionTwoHex) >> ShiftTwoHex) - 1] += 1;
		values[(sortedInput[i] & PositionZeroHex) - 0x2] += 1;
	}

	for (int i = 0; i < types.size(); ++i) {
		if (types[i] == HandSize) {
			return flushType(values);
		}
	}

	for (int i = 0; i < values.size(); ++i) {
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

	return isStraight(values) ? Straight : HighCard;
}

} // namespace

/*
int main() {
	vector<int> royalFlush = { 0x10a, 0x10b, 0x10c, 0x10d, 0x10e };
	cout << "royalFlush: " << to_string(f(royalFlush)) << " (1)\n";
	vector<int> straightFlush = { 0x102, 0x103, 0x104, 0x105, 0x106 };
	cout << "straightFlush: " << to_string(f(straightFlush)) << " (2)\n";
	vector<int> fourOfAKind = { 0x102, 0x202, 0x302, 0x402, 0x103 };
	cout << "fourOfAKind: " << to_string(f(fourOfAKind)) << " (3)\n";
	vector<int> fullHouse = { 0x102, 0x202, 0x103, 0x203, 0x303 };
	cout << "fullHouse: " << to_string(f(fullHouse)) << " (4)\n";
	vector<int> flush = { 0x102, 0x103, 0x104, 0x105, 0x107 };
	cout << "flush: " << to_string(f(flush)) << " (5)\n";
	vector<int> straight = { 0x102, 0x203, 0x304, 0x405, 0x206 };
	cout << "straight: " << to_string(f(straight)) << " (6)\n";
	vector<int> threeOfAKind = { 0x102, 0x202, 0x302, 0x405, 0x206 };
	cout << "threeOfAKind: " << to_string(f(threeOfAKind)) << " (7)\n";
	vector<int> twoPair = { 0x102, 0x202, 0x304, 0x404, 0x305 };
	cout << "twoPair: " << to_string(f(twoPair)) << " (8)\n";
	vector<int> onePair = { 0x102, 0x202, 0x404, 0x405, 0x306 };
	cout << "onePair: " << to_string(f(onePair)) << " (9)\n";
	vector<int> highCard = { 0x102, 0x203, 0x30c, 0x405, 0x20b };
	cout << "highCard: " << to_string(f(highCard)) << " (10)\n";
	return 0;
}
*/
