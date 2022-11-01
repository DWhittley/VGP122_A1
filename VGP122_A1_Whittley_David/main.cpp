#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int credits = 1000; // player initial credits 1000
void init();
int deck[52];
int shuffleDeck[52];

int main()
{
	void init();


	return 0;
}

void init()
{
	int tempCard = 0;
	int* ptr = 0;

	for (int i = 0; i < 13; ++i) // populate a playing deck with 4 of each card (A,J,Q,K represented by 1,11,12,13)
	{
		for (int j = 0; j < 4; ++j)
		{
			deck[(i + j)] = (i + 1);
			cout << "deck location " << &deck[(i + j)] << "holds the value " << deck[(i + j)] << endl; //initial build checking
		}
	}

	for (int i = 0; i < 52; ++i) // initialize shuffleDeck array with 0's
		shuffleDeck[i] = 0;

	for (int i = 0; i < 52; ++i) // move 52 values from deck array (random location) to shuffleDeck array and replace with 0 in deck location
	{
		srand(time(0));
		*ptr = (&deck[(rand() % 52)] * sizeof(int)); // randomly select array cell location in deck incremented by int size (4 bytes)
		tempCard = ptr; // temporarily store the value at that array location

		if (tempCard == 0) // if there is a zero at that location then the value has already been pulled, so ignore the selection
			--i; // pre-reduce i so that next iteration has the same i value, thus we get a total of 52 cards in the shuffleDeck array
		else if (tempCard >= 1 && tempCard <= 52) // make sure only valid data is stored in shuffleDeck
		{
			shuffleDeck[(sizeof(shuffleDeck))] = tempCard; // Store the card value in tempCard in first available location in shuffleDeck
			deck[*ptr] = 0; // store a 0 in the deck location that we pulled the card value from
			cout << "The shuffled deck location" << i << "has the value " << shuffleDeck[i] << endl;  //initial build checking
		}

	}
}