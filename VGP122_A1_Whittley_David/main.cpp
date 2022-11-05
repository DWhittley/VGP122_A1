#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>
#include <ctime>

using namespace std;

enum card_suit
{
	S = 0,
	H = 1,
	D = 2,
	C = 3
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
void Split();
void Double();
void Half();
char PrintSuit();
void PrintCards(vector<card>);
void DealerPlay();
int HandValue(vector<card>);
void Clear(vector<card>&);
bool hasAce(vector<card>);
Card Hit();
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
		cout << "Vinny the loan shark pulls you aside and offers you 1000 credits..... we'll discuss terms after you win. Press (V) to accept." << endl;
	}
	cin >> USERiNPUT;
	USERiNPUT = tolower(USERiNPUT);
	// Ask player if they want to start a new game or continue
	if (USERiNPUT == 'v')
	{
		CRED += 1000;
		cout << "Vinny smiles." << endl;
		GamePlay();
	}
	else {
		cout << "Shame ... you had your chance." << endl;
	}

	if (CRED == 0){
		cout << "Would you like to (S)tart a new one?" << endl;
		cout << "Credits: " << CRED << endl;
	}
	else {
		cout << "Would you like to (C)ontinue your game or (S)tart a new one?" << endl;
		cout << "Credits: " << CRED << endl;
	}
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
	Clear(player.hand);
	Clear(dealer.hand);
	Clear(playerSplit.hand);
	player.bet = 0;
	isPlaying = true;
	// ask player what they want to bet on the hand

	while (!(player.bet >= 10 && player.bet <= CRED))
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

	cout << "Player's cards: ";
	PrintCards(player.hand);
	cout << " = " << HandValue(player.hand) << " ";
	cout << endl;
	cout << "Dealer's cards: ";
	PrintCards(dealer.hand);
	cout << " = " << dealer.hand[1].value << " ";
	cout << endl;
}
Card Hit() {
	return Deal();
}
void Split() {

}
void Double() {

}
void Half() {

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
	cout << "===================================" << endl;
	cout << "Player's cards: ";
	PrintCards(player.hand);
	cout << " = " << HandValue(player.hand) << " ";
	cout << endl;
	cout << "Dealer's cards: ";
	PrintCards(dealer.hand);
	cout << " = " << HandValue(dealer.hand) << " ";
	cout << endl;
	if (HandValue(player.hand) > 21) {
		cout << "You Lost this hand!" << endl;
		CRED -= player.bet;
		Game();
	}
	else if (HandValue(player.hand) == 21) {
		if (HandValue(dealer.hand) == 21) {
			cout << "Push!" << endl;
			Game();
		}
		else {
			cout << "You win!" << endl;
			CRED += player.bet;
			Game();
		}
	} else if ((HandValue(player.hand) > (HandValue(dealer.hand))) || (HandValue(dealer.hand) > 21)) {
		cout << "You win!" << endl;
		CRED += player.bet;
		Game();
	} else if ((HandValue(player.hand)) == (HandValue(dealer.hand))) {
		cout << "Push!" << endl;
		Game();
	} else {
		cout << "You Lost this hand!" << endl;
		CRED -= player.bet;
		Game();
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
		player.hand.push_back(Hit());
		cout << "Player's cards: ";
		PrintCards(player.hand);
		cout << " = " << HandValue(player.hand) << " ";
		cout << endl;
		break;
	case 's':
		dealer.hand[0].up = true;
		DealerPlay();
		isPlaying = false;
		break;
	case 'p':
		Split();
		break;
		// check that split is allowed
		// split existing cards to two hands
		// call Gameplay for each hand
	case 'd':
		Double();
		break;
		// check that double down is allowed
		// adjust bet
		// continue
	case 'x':
		Half();
		break;
		// half bet returned to player
		// new deal
	default:
		cout << USERiNPUT << endl;
		cout << "you didn't enter something valid you dumbass" << endl;
		break;
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

void DealerPlay() {
	while ((HandValue(dealer.hand) < 17) || (HandValue(dealer.hand) == 17 && hasAce(dealer.hand))) { //dealer hits at less than 17 and on soft 17
		dealer.hand.push_back(Hit()); //dealer gets a card
		cout << "Dealer's cards: "; 
		PrintCards(dealer.hand);
		cout << " = " << HandValue(dealer.hand) << " ";
		cout << endl;
	}
}

char PrintSuit(Card card) {
	switch (card.suit) {
	case 0:
		return 'S';
	case 1:
		return 'H';
	case 2:
		return 'D';
	case 3:
		return 'C';
	}
}
void PrintCards(vector<Card> hand) {
	const string CARD_VALUES[14] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "X" }; //makes it easier to print

	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].up) { //if the hand is face up we print this
			cout << CARD_VALUES[(hand[i].value - 1)] << PrintSuit(hand[i]) << " ";
		}
		else { //if it's face down we print XX
			cout << CARD_VALUES[13] << CARD_VALUES[13] << " ";
		}
	}
}