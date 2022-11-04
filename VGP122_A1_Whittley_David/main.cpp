#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>
#include <ctime>

using namespace std;

enum card_suit
{
	S, H, D, C
};

int CRED = 1000; // player initial credits 1000
char USERiNPUT;
bool isPlaying = true;

typedef struct card
{ //how the cards are stored
	int value; //value of the card
	card_suit suit; //suit of the card we have. Not really that important in this game but might as well have it
	bool up; //for the dealer since one card is face down
} Card;

typedef struct player
{
	int bet = 0;
	vector<Card> hand; // vector to hold cards dealt to player in A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K format: note "T" for ten so that we can keep it to "char" array so smaller
} Player;

void init();
void Game();
void GamePlay();
void InitDeal();
void Evaluate();
void PlayerChoice();
void Hit();
void DealerPlay(Player);
int HandValue(vector<card>);
void Clear(vector<card>&);
bool hasAce(vector<card>);
Card Deal();
Player player;
Player playerSplit;
Player dealer;

void main()
{
	init();
};

void init()
{
	unsigned int time_seed = time(0);
	srand(time_seed);
	Game();
}


void Game()
{
	if (CRED <= 0) {
		cout << "You have 0 credits, Vinny the loan shark pulls you aside and offers you 1000 credits... (y) to accept (n) to decline" << endl;
	}
	// Ask player if they want to start a new game or continue
	cout << "Would you like to (C)ontinue your game or (S)tart a new one?" << endl;
	cout << "Credits: " << CRED << endl;
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
	else if (USERiNPUT == 'v') {
		CRED += 1000;
		cout << "Vinnie the poo poo ..." << endl;
		GamePlay();
	}
	else
	{
		Game();
	}
}

void GamePlay()
{
	Clear(player.hand);
	Clear(dealer.hand);
	Clear(playerSplit.hand);
	// ask player what they want to bet on the hand

	while (player.bet <= 0)
	{
		cout << "How much would you like to bet? (minimum 1):";
		cin >> player.bet;
	}

	// deal initial cards for dealer and player

	InitDeal();


	// ask player action what they want to do
	while (isPlaying) {
		PlayerChoice();
	}
	
	Evaluate();
}

void InitDeal()
{
	player.hand.push_back(Deal());
	dealer.hand.push_back(Deal());
	dealer.hand[0].up = false;
	player.hand.push_back(Deal());
	dealer.hand.push_back(Deal());

	cout << "Player has: " << HandValue(player.hand) << setw(10) << endl;
	cout << "Dealer has a: " << dealer.hand[1].value << setw(10) << endl;
}
void Hit() {
	player.hand.push_back(Deal());
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
void Evaluate() {
	cout << "Player has: " << HandValue(player.hand) << setw(10) << endl;
	cout << "Dealer has a: " << HandValue(dealer.hand) << setw(10) << endl;
	if (HandValue(player.hand) > 21) {
		cout << "You Lost this hand!";
		CRED -= player.bet;
	}
	else if (HandValue(player.hand) == 21) {
		DealerPlay(dealer);
		if (HandValue(dealer.hand) == 21) {
			cout << "Push!";
			GamePlay();
		}
		else {
			cout << "You win!";
			CRED += player.bet;
			GamePlay();
		}
	}
}
void PlayerChoice() {

	if (HandValue(player.hand) > 21) { // Player bust
		isPlaying = false;
		cout << "You busted with: " << HandValue(player.hand) << "!";
		CRED -= player.bet;
		Game();
	}
	// ask player action what they want to do
	cout << "What would you like to do? (Hit(H), Stand(S), Split(P), Double Down(D), Pass(X): ";

	cin >> USERiNPUT;

	switch (tolower(USERiNPUT))
	{
	case 'h':
		Hit();
		cout << player.hand.back().value << (card_suit)player.hand.back().suit << endl;
		break;
	case 's':
		DealerPlay(dealer);
		isPlaying = false;
		break;
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
		cout << USERiNPUT << endl;
		cout << "you didn't enter something valid you dumbass" << endl;
	}
}

int HandValue(vector<Card> hand) {
	int total = 0; //setting up the total value
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].value >= 10) { //if it's 10, J, Q, or K
			total += 10; //adds 10 to the toal
		}
		else {
			total += hand[i].value; //adds the value to the total 
		}
	}

	if (hasAce(hand) && total <= 11) { //if the hand has an ace and we won't bust
		total += 10; //add 10
	}

	return total; //return the total
}

void Clear(vector<card>& hand) {
	hand.clear();
}

bool hasAce(vector<card> hand) {
	bool has_ace = false; //For now we say there is no ace in the hand
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].value == 1) { //we have an ace
			has_ace = true; //so we set this to true
		}
	}
	return has_ace;
}

void DealerPlay(Player dealer) {
	if ((HandValue(dealer.hand) < 17) || (HandValue(dealer.hand) == 17 && hasAce(dealer.hand))) { //dealer hits at less than 17 and on soft 17
		dealer.hand.push_back(Deal()); //dealer gets a card
	}
}