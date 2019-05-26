#include<iostream>
#include <iomanip>
#include<cstdlib>
#include<ctime>
#include <cstring>
#include<string>
#include <algorithm>

using namespace std;
//replace all '-' with the guess
void update_hidden(char guess, string &sofar, string &actual_word) {
	int pos = actual_word.find(guess);
	char convert_char_to_str[10];  //to convert string guesses to char
	while(pos != -1) {
		sofar[pos] = guess;
		pos = actual_word.find(guess, pos+1);
	}
}

//returns true if guess okay, otherwise false
bool check_guess(char userguess, string &actualword, string &hiddenword) {
	if(actualword.find(userguess) != -1) {
		update_hidden(userguess, hiddenword, actualword);
		return true;
	}
	//no match found
	return false;
}

void hangman(int &guesses) {
	cout << "\nYour state: " << endl;
	cout << "                     |" << endl;
	
	if(guesses >= 1) {
		cout << "                     O" << endl;
	}
	if(guesses == 2) {
		cout << "                     |" << endl;
	}
	else if(guesses == 3) {
		cout << "                    /|" << endl;
	}
	else if (guesses >=3) {  //minimum of 4 mistakes
		cout << "                    /|\\" << endl;
		if(guesses == 4) {
		    cout << "                    /" << endl;
		}
		else if(guesses == 5) {
			cout << "                    / \\" << endl;
			cout << "You have only 1 chance remaining" << endl;
		}
		else {  //6 mistakes made
			cout << "                    / \\" << endl;
		}
	}
}

void display(string word) {
	cout << "You have to guess====> " << word << endl;
}

int main() {
    string wordlist[12] = {"idiot", "monopoly", "game", "economy",
        "simple", "hard", "labyrinth", "fun", "easy", "hero", "loser", "kpop"};
    
	//choosing a random word from the list above
    srand(time(0)); 
    string word = wordlist[rand()%12];
	char cguess;
    int total_guesses = 0;  //keep track of incorrect guesses and matched characters
    
    //initialising the hidden word
    string display_word;
    for(int i = 0; i < word.length(); i++) {
    	display_word += "-";
	}
	while(total_guesses < 6 && display_word != word) {
		display(display_word);
		hangman(total_guesses);
		cout << "Guess: ";
		cin >>  cguess;
		//check if guess correct or not, true means the guess is correct
		if(check_guess(cguess, word, display_word)) {
			update_hidden(cguess, display_word, word);
		}
		else{
			++total_guesses;
		}
	}
	
	if(total_guesses < 6) {
		cout << "You have guessed " << word << " correctly.\nYou win! Congrats! :)" << endl;
	}
	else {
		cout << "Oops\nYour character died :(\nYou were unable to guess \"" << word << "\"";
		cout << "\nYou lose, but try again to see if you can guess it correctly!";
	}	
}

