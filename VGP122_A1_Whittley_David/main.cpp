#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int credits = 1000; // player initial credits 1000
void init();
int Deck [260] [260] = {0}; // standard 5 deck shoe in Vegas holds 260 cards.  this will hold card value and suit
char userInput;

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
	Shuffle();
}


void Shuffle()
{
	int rndCard;
	int rndSuit;

	for (int i = 0; i < 260; ++i) // typical vegas 5 deck shoe holds 260 cards
	{
		rndCard = (rand() + 1) % 13; // random card between Ace and King
		rndSuit = (rand() + 1) % 4; // random suit
		Deck[i][0] = rndCard;
		Deck[i][1] = rndSuit;
		cout << "the Deck array has :" << Deck[i][0] << Deck[i][1] << " stored at array location" << i << endl;
	}
}

void Game()
{

	// Ask player if they want to start a new game or continue
	cout << "Would you like to (C)ontinue your game or (S)tart a new one?" << endl;
	cin >> userInput;
	userInput = tolower(userInput);

	if (userInput == 's')
	{
		credits = 1000;
		GamePlay();
	}
	else if (userInput == 'c')
	{
		GamePlay();
	}
	else
	{
		Game();
	}
}

void GamePlay()
{
	int bet1 = 0;
	int betSplit = 0;
	card handP1[10] = { 0 }; // array to hold cards dealt to player in A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K format: note "T" for ten so that we can keep it to "char" array so smaller
	card handP1Split[10] = { 0 }; // array to hold cards dealt to player split hand if they choose split
	card handDlr[10] = { 0 }; // array to hold dealer's hand

	
	// ask player what they want to bet on the hand

	while (bet1 <= 0)
	{
		cout << "How much would you like to bet? (minimum 1):";
		cin >> bet1;
	}

	// deal initial cards for dealer and player

	InitDeal();


	// ask player action what they want to do
	cout << "What would you like to do? (Hit(H), Stand(S), Split(P), Double Down(D), Pass(X): ";
	
	cin >> userInput;
	
	switch (tolower(userInput))
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
	default:
		// go back to input

	}
	void InitDeal()
	{
		HandP1[0] = deal();
		HandDlr[0] = deal();
		HandDlr[0].up = false;
		HandP1[1] = deal();
		HandDlr[1] = deal();
	}
	card deal() 
	{
		card new_card; //card we will be returning

		new_card.value = 1 + rand() % 13; //makes sure the random number is between 1 and 13 for the value
		int suit = rand() % 4;
		switch (suit) { //makes sure the random number is between 1 and 4 for the suit
		case 0:
			new_card.suit = S;
			break;
		case 1:
			new_card.suit = H;
			break;
		case 2:
			new_card.suit = D;
			break;
		case 3:
			new_card.suit = C;
			break;
		}

		new_card.up = true; //we'll change it later if it's the dealers face down card

		return new_card; //returning the card
	}
}


