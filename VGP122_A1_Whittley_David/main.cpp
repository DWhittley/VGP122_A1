#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum card_suit
{
	S, H, D, C
};

int CRED = 1000; // player initial credits 1000
char USERiNPUT;

typedef struct card
{ //how the cards are stored
	int value; //value of the card
	card_suit suit; //suit of the card we have. Not really that important in this game but might as well have it
	bool up; //for the dealer since one card is face down
} Card;

typedef struct player
{
	int bet = 0;
	Card hand[10] = { 0 }; // array to hold cards dealt to player in A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K format: note "T" for ten so that we can keep it to "char" array so smaller
} Player;

void init();
void Game();
void GamePlay();
void InitDeal();
Card Deal();
Player player;
Player playerSplit;
Player dealer;

int main()
{
	void init();

	return 0;
}

void init()
{

}


void Game()
{
	// Ask player if they want to start a new game or continue
	cout << "Would you like to (C)ontinue your game or (S)tart a new one?" << endl;
	cin >> USERiNPUT;
	USERiNPUT = tolower(USERiNPUT);

	if (USERiNPUT == 's')
	{
		CRED = 1000;
		GamePlay();
	}
	else if (USERiNPUT == 'c')
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

	// ask player what they want to bet on the hand

	while (player.bet <= 0)
	{
		cout << "How much would you like to bet? (minimum 1):";
		cin >> player.bet;
	}

	// deal initial cards for dealer and player

	InitDeal();


	// ask player action what they want to do
	cout << "What would you like to do? (Hit(H), Stand(S), Split(P), Double Down(D), Pass(X): ";

	cin >> USERiNPUT;

	//switch (tolower(USERiNPUT))
	//{
	//case 'h':
	//	// deal method to deal a card (function that is targetable to player hand 1, player hand 2, dealer)
	//	// hand busted? then take bet and GamePlay()
	//	// ask player action
	//case 's':
	//	// proceed to dealer hand
	//case 'p':
	//	// check that split is allowed
	//	// split existing cards to two hands
	//	// call Gameplay for each hand
	//case 'd':
	//	// check that double down is allowed
	//	// adjust bet
	//	// continue
	//case 'x':
	//	// half bet returned to player
	//	// new deal
	//default:
	//	// go back to input
	//}
}

void InitDeal()
{
	player.hand[0] = Deal();
	dealer.hand[0] = Deal();
	dealer.hand[0].up = false;
	player.hand[1] = Deal();
	player.hand[1] = Deal();
}
Card Deal() 
{
	Card new_card; //card we will return

	new_card.value = 1 + rand() % 13; //make sure the random number is between 1 and 13 for the value
	int suit = rand() % 4;
	switch (suit) { //make sure the random number is between 1 and 4 for the suit
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

	new_card.up = true; //we change it to false for the dealers face down card

	return new_card; //returning the card
}


