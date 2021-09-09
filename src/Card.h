
#include <iostream>
#include <string>
using namespace std;

class Card{
	
	private:
		string number;
		string suit;
	public:
		Card* nextCard;
		
		Card(string number="0", string suit="Joker"); //constructor
	
		string toString() const; // returns a string of the card
		string retCardName() const; // returns string name of card number
		int operator +(const int num) const; // returns sum of card and number
		int operator +(const Card cc) const; // returns sum of 2 cards;
		friend int operator + (const int num, const Card cc); // returns sum of number and card
		int retValue() const; // returns value of card
		string retSuit() const; // returns value of suit
		friend ostream& operator << (ostream& os, const Card cc); //returns card in string format
		void toLower(); //changes Ace from 11 value to 1 value ( A -> a ) -- ONLY USE WITH ACES
	
};
