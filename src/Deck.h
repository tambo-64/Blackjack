#include "Card.h"

#include <iostream>
#include <string>

using namespace std;

class Deck{
	
	private:
		Card* head;
		
	public:
	
		Deck(); // constructor
		
		int countCards() const; // returns the number of cards in the deck
		void clearDeck(); // clears deck
		string toString() const; // returns a string of the hand
		string toStringDealer() const; // returns a string of the hand with a card hidden
		void addCard(Card cc); // adds a card to the hand
		void addCard(Card* cp); // adds a card to the hand
		void addCard(string number=0, string suit="Joker"); // adds a card to the hand
		int getTotal() const; // returns sum of all cards in hand
		friend ostream& operator << (ostream& os, Deck hand); // returns a string of all cards in the deck
		Card* retHead() const; // returns head of the deck
		void newHead(); // removes head of the deck and sets the next card as the current head
	
};
