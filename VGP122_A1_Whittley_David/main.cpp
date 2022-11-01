#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int credits = 1000; // player initial credits 1000
void init();
int deck[52];


enum card_suit 
{
	S, H, D, C
};
struct card 
{ //how the cards are stored
	int value; //value of the card
	card_suit suit; //suit of the card we have. Not really that important in this game but might as well have it
	bool up; //for the dealer since one card is face down
};

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

void Shuffle()
{
	Card* temp = nullptr;
	int rndIndex;

	for (int i = 0; i < MAXCARDS; ++i)
	{
		rndIndex = rand() % MAXCARDS;

		temp = cards[0];
		cards[0] = cards[rndIndex];
		cards[rndIndex] = temp;
	}
}

void GamePlay()
{
	char action = 0;
	
	// Ask player if they want to start a new game or continue


	// ask player what they want to bet on the hand


	// deal initial cards for dealer and player

	// ask player action what they want to do
	cout << "What would you like to do? (Hit(H), Stand(S), Split(P), Double Down(D), Pass(X): ";
	
	cin >> action;
	

	switch (tolower(action))
	{
	case 'h':
		// deal method to deal a card (function that is targetable to player hand 1, player hand 2, dealer)
		// hand busted? then take bet and GamePlay()
		// ask player action
	case 's':
		// proceed to dealer hand
	case 'p':
		// check that split is allowed
		// split existing cards to two hands
		// call Gameplay for each hand
	case 'd':
		// check that double down is allowed
		// adjust bet
		// continue
	case 'x':
		// half bet returned to player
		// new deal

	}

}