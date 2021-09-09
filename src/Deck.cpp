#include "Deck.h"
		
Deck::Deck(){
	this->head = nullptr;
}

void Deck::addCard(Card cc){
	if(this->head == nullptr)
		this->head = &cc;
	else{
		Card* cursor = this->head;
		while(cursor->nextCard != nullptr)
			cursor = cursor->nextCard;
		cursor->nextCard = &cc;
	}
}

void Deck::addCard(Card* cp){
	if(this->head == nullptr)
		this->head = cp;
	else{
		Card* cursor = this->head;
		while(cursor->nextCard != nullptr)
			cursor = cursor->nextCard;
		cursor->nextCard = cp;
	}
}
void Deck::addCard(string number, string suit){
	
	Card* cc = new Card(number, suit);
	
	if(this->head == nullptr)
		this->head = cc;
	else{
		Card* cursor = this->head;
		while(cursor->nextCard != nullptr)
			cursor = cursor->nextCard;
		cursor->nextCard = cc;
	}
}

int Deck::getTotal() const{
	int sum = 0;
	Card* cursor = this->head;
	while(cursor != nullptr){
		sum += cursor->retValue();
		cursor = cursor->nextCard;
	}
	return sum;
}

Card* Deck::retHead() const{
	return this->head;
}

ostream& operator << (ostream& os, Deck hand){
	Card* cursor = hand.retHead();
	while(cursor != nullptr){
		os << *cursor << endl;
		cursor = cursor->nextCard;
	}
	return os;
}

string Deck::toString() const{
	Card* cursor = this->head;
	string s;
	while(cursor != nullptr){
		s += cursor->toString() + " | ";
		cursor = cursor->nextCard;
	}
	return s;
}

int Deck::countCards() const{
	Card* cursor = this->head;
	int counter = 0;
	while(cursor != nullptr){
		++counter;
		cursor = cursor->nextCard;
	}
	
	return counter;
}

string Deck::toStringDealer() const{
	Card* cursor = this->head;
	string s;
	while(cursor != nullptr){
		if(cursor->nextCard == nullptr)
			s += "X of XXXXXX | ";
		else
			s += cursor->toString() + " | ";
		cursor = cursor->nextCard;
	}
	return s;
}

void Deck::newHead(){
	head = head->nextCard;
}

void Deck::clearDeck(){
	while(this->head != nullptr){
		Card* shreder = this->head;
		this->head = this->head->nextCard;
		delete(shreder);
	}
}
