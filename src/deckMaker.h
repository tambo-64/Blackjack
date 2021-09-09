#include "Deck.h"
#include <iostream>
#include <string>
#include <cstring>
#include <random>

const string SUITS[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string NUMBERS[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

void makeDeck(Deck& myDeck){
	
	bool checker[4][13];
	memset(checker, 0, sizeof checker);
	srand(unsigned(time(0)));
	
	for(int i = 0; i < 52; ++i){
		int s, n;
		
		do{
			s = rand() % 4;
			n = rand() % 13;
		}while(checker[s][n] == 1);
		
		myDeck.addCard(NUMBERS[n], SUITS[s]);
		checker[s][n] = 1;
	}
}

bool giveCard(Deck& mainDeck, Deck& myDeck){
	if(mainDeck.retHead() == nullptr)
		return 0;
	
	myDeck.addCard(mainDeck.retHead()->retCardName(), mainDeck.retHead()->retSuit());
	mainDeck.newHead();
	return 1;
}
