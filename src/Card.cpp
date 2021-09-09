
#include "Card.h"

Card::Card(string number, string suit){
	this->number = number;
	this->suit = suit;
	this->nextCard = nullptr;
}

string Card::toString() const{
	return this->number + " of " + this->suit;
}

int Card::operator +(const int num) const{
	return this->retValue() + num;
}

int Card::operator +(const Card cc) const{
	return this->retValue() + cc.retValue();
}

int operator + (const int num, const Card cc){
	return num + cc.retValue();
}

int Card::retValue() const{
	
	if(this->number == "A")
		return 11;
	else if(this->number == "K" || this->number == "Q" || this->number == "J")
		return 10;
	else if(this->number == "a")
		return 1;
	else
		return stoi(this->number);
}

string Card::retSuit() const{
	return this->suit;
}

string Card::retCardName() const{
	return this->number;
}

ostream& operator << (ostream& os, const Card cc){
	os  << "" << cc.retCardName() << " of " << cc.retSuit();
	return os;
}

void Card::toLower(){
	this->number = "a";
}