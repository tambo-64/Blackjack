/*
 * Main source file for Blackjack
 * 
 * T. Johnny Tamborrino
 * 
 */
 
#include "deckMaker.h"
#include "repo/ncurses.h"
#include <iostream>
#include <string>

using namespace std;

void gameLoop(WINDOW* win);

void printCentered(WINDOW* win, int num, string s){
	int center = win->_maxx / 2;
	int half_length = s.length() / 2;
	int adjusted = center - half_length;
	mvwprintw(win, num, adjusted, s.c_str());
	wrefresh(win);
}

void displayTable(WINDOW* win, Deck& dealerHand, Deck& playerHand, int d){
	
	wmove(win, 2,1);
	
	if(d == 0){
		wprintw(win,"DEALER == X");
		wmove(win, 3,1);
		wprintw(win,"%s", dealerHand.toStringDealer().c_str());
	}else{
		wprintw(win,"DEALER == %d", dealerHand.getTotal());
		wmove(win, 3,1);
		wprintw(win,"%s", dealerHand.toString().c_str());
	}
	wmove(win, 11,1);
	wprintw(win,"PLAYER == %d", playerHand.getTotal());
	wmove(win, 12,1);
	wprintw(win,"%s", playerHand.toString().c_str());
	wrefresh(win);
}

void displayReset(WINDOW* win, Deck& dealerHand, Deck& playerHand, int round, int d){
	wclear(win);
	box(win, 0,0);
	wmove(win, 1,1);
	wprintw(win, "Round %d", round);
	displayTable(win, dealerHand, playerHand, d);
}

void displayInfo(WINDOW* win, string s, string c){
	
	printCentered(win,0,s);
	printCentered(win,1,c);
	wmove(win,13,1);
	wrefresh(win);
}

void displayInfo(WINDOW* win, string s){
	
	printCentered(win,0,s);
	wmove(win,13,1);
	wrefresh(win);
}

int main(){
	initscr();
	cbreak();
	
	WINDOW* win = newwin(15, 60, 5, 10);
	refresh();
	box(win, 0, 0);
	wrefresh(win);
	
	wmove(win, 1,1);
	wprintw(win, "Welcome to Blackjack!");
	wmove(win, 2, 1);
	wprintw(win, "Press any key to continue");
	wrefresh(win);
	
	getch();
	
	wclear(win);
	box(win, 0, 0);
	wmove(win, 1,1);
	
	gameLoop(win);
	endwin();
	return 0;
}

void gameLoop(WINDOW* win){
	
	Deck dealerHand = Deck();
	Deck playerHand = Deck();
	Deck mainDeck = Deck();
	int round = 1;
	
	makeDeck(mainDeck);
	
	refresh();
		
	while(1){
		
		char input = ' ';
		
		if(mainDeck.countCards() < 12)
			makeDeck(mainDeck);
		refresh();
		displayReset(win, dealerHand, playerHand, round, 0);
		
		giveCard(mainDeck, playerHand);
		giveCard(mainDeck, dealerHand);
		giveCard(mainDeck, playerHand);
		giveCard(mainDeck, dealerHand);
		
		refresh();
		wrefresh(win);
		
		displayTable(win, dealerHand, playerHand, 0);
		
		if(playerHand.getTotal() == 21){
			printCentered(win,0,"BLACKJACK!");
			printCentered(win,1,"Player wins!");
			displayTable(win, dealerHand, playerHand, 1);
			wmove(win,13,1);
			wrefresh(win);
			getch();
			playerHand.clearDeck();
			dealerHand.clearDeck();
			round += 1;
			continue;
		}
		
		if(dealerHand.getTotal() == 21){
			printCentered(win,0,"BLACKJACK!");
			printCentered(win,1,"Dealer wins!");
			displayTable(win, dealerHand, playerHand, 1);
			wmove(win,13,1);
			wrefresh(win);
			getch();
			playerHand.clearDeck();
			dealerHand.clearDeck();
			round += 1;
			continue;
		}
		
		//player move
		
		displayInfo(win, "Player's move", "[H] Hit | [S] Stand");
		
		while(input != 's' && input != 'S' && input != 'q' && input != 'Q' && playerHand.getTotal() < 21){
			
			//Display
			displayTable(win, dealerHand, playerHand, 0);
			input = wgetch(win);
			
			switch(input){
				case 'h':
				case 'H':
					giveCard(mainDeck, playerHand);
					printCentered(win, 6, "Hit!");
					break;
				case 's':
				case 'S':
					printCentered(win, 6, "Stand");
				case 'q':
				case 'Q':
				default:
					break;
			}
		}
		
		if(input == 'q' || input == 'Q') break;
		
		displayTable(win, dealerHand, playerHand, 0);
		
		if(playerHand.getTotal() > 21){
			printCentered(win, 7, "BUST! You lose...");
			printCentered(win, 8, "Press any key to continue");
			displayTable(win, dealerHand, playerHand, 1);
			wmove(win,13,1);
			wgetch(win);
			wclear(win);
			playerHand.clearDeck();
			dealerHand.clearDeck();
			round += 1;
			continue;
		}
		
		displayReset(win, dealerHand, playerHand, round, 1);
		
		//Dealer moves
		displayInfo(win, "Dealer's move");
		printCentered(win, 8, "Press any key to continue");
		wrefresh(win);
		
		while(dealerHand.getTotal() < 17){
			wgetch(win);
			giveCard(mainDeck, dealerHand);
			displayTable(win, dealerHand, playerHand, 1);
			wmove(win,13,1);
		}
		
		if(dealerHand.getTotal() > 21){
			printCentered(win, 7, "BUST! You win!");
			printCentered(win, 8, "Press any key to continue");
			wmove(win,13,1);
			wgetch(win);
			wclear(win);
			playerHand.clearDeck();
			dealerHand.clearDeck();
			round += 1;
			continue;
		}
		
		displayReset(win, dealerHand, playerHand, round, 1);
		displayInfo(win, "Results");
		
		if(playerHand.getTotal() > dealerHand.getTotal()){
			printCentered(win, 7, "You win!");
			printCentered(win, 8, "Press any key to continue");
			wmove(win,13,1);
		} else if(playerHand.getTotal() == dealerHand.getTotal()){
			printCentered(win, 7, "Push!");
			printCentered(win, 8, "Press any key to continue");
			wmove(win,13,1);
		} else{
			printCentered(win, 7, "You lose...");
			printCentered(win, 8, "Press any key to continue");
			wmove(win,13,1);
		}
		
		wrefresh(win);
		wgetch(win);
		
		playerHand.clearDeck();
		dealerHand.clearDeck();
		round += 1;
	}
	
	wclear(win);
	box(win,0,0);
	wmove(win,1,1);
	printCentered(win, 7, "Thanks for playing!");
	printCentered(win, 8, "Press any key to continue");
	wmove(win, 13,1);
	wrefresh(win);
	wgetch(win);
}
