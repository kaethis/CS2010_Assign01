#include <cstdio>
#include <cctype>
#include <iostream>
#include <stdio.h>	// printf
using namespace std;

#define DEBUG0
#define DEBUG1
#define DEBUG2

/* Author:	Matt W. Martin, 4374851
 *		kaethis@tasmantis.net
 *
 * Project:	CS2010, Assignment #1
 *		        Dictionary I */ 

const int WORD_MAX = 128;	// NOTE: The implimentation of the Dictionary class
const int LETT_MAX = 128;	/*       allows for only a fixed number of words and
				 *       word length. Adjust the size of the class by
				 *       modifying WORD_MAX and LETT_MAX. */
				
class Dictionary{

	int word_index, lett_index;
	char words[WORD_MAX][LETT_MAX];
	int freq[WORD_MAX];
	
	public: 
	Dictionary(){
		word_index = 0;	// Represents the total number of words.
		lett_index = 0;
		 
	}

	bool isApplicable(char ch){

		if((isalpha(ch)))
			return true;
		else
			return false;
	}

	int findExisting(){
		/* This method examines the current entry in the Dictionary with past
		 * entries. If the word already exists, its word_index is returned.
		 * If the word doesn't already exist, the method returns -1. */

		int word_indexF = 0;
		int lett_indexF = 0;
		char word[LETT_MAX];
		int found_count;

		
		// Adds the contents of the current entry into word[]:
		for(int i = 0; i < (this -> lett_index); i++){
			word[i] = (this -> words[this -> word_index][i]);

#ifdef DEBUG0	/* -START--------------------------------------------------------- */
			if(isApplicable(word[i]))
				cout << word[i];  // PRINTS THE CHAR AT LOCATION i
						  // IF NOT NULL-BYTE OR SOMETHING
			else
				cout << "!";	  // CAPTURED SOMETHING SUPERFLUOUS 
#endif		/* -----------------------------------------------------------END- */
		
		}

#ifdef DEBUG0	/* -START--------------------------------------------------------- */
		cout << endl; 
#endif		/* -----------------------------------------------------------END- */

		while(word_indexF < ((this -> word_index) -1)){

			found_count = 0;
			
			while(this -> words[word_indexF][lett_indexF] != '\n'){

				/* Every time a letter matches that in word[],
				 * found_count is incremented. */
				if(word[lett_indexF] == 
				  (this -> words[word_indexF][lett_indexF])){
					found_count++;

				}

				/* If the number of matching letters equals the
				 * Dictionary's current lett_index, the index of
				 * that word is returned. 
				 * -1 indicates the word doesn't already exist. */
				if(found_count == this -> lett_index){
					return word_indexF;
				}
				lett_indexF++;
			}
			word_indexF++;
			lett_indexF = 0;
		}
		return -1;
	}
	
	void addWords(){
		
		char ch;
		bool char_flag;		// Indicates if a char was last placed.
		int found;

		while(cin.good()){
			
			ch = cin.get();
			
			if(isApplicable(ch)){

				this -> words[this -> word_index]
					     [this -> lett_index] = tolower(ch);

#ifdef DEBUG1	/* -START--------------------------------------------------------- */
				cout << "[this -> word_index: ";
				cout << (this -> word_index) << " ] | LN:";
				cout << __LINE__;
				cout << endl; // PRINTS CONTENTS OF word_index
				
				cout << "[this -> lett_index: ";
				cout << (this -> lett_index) << " ] | LN:";
				cout << __LINE__;
				cout << endl; // PRINTS CONTENTS OF lett_index

				cout <<"[this -> words[][]:  ";
				cout << (this -> words[this -> word_index]
						      [this -> lett_index]);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this -> words
#endif		/* -----------------------------------------------------------END- */

				(this -> lett_index)++;
				char_flag = true;

			} else if(char_flag){
				
				/* If ch is invalid and the previous ch was valid, a
				 * null-byte is placed at the final letter index. */
				this -> words[this -> word_index]
					     [this -> lett_index] = '\n';

#ifdef DEBUG1	/* -START--------------------------------------------------------- */
				cout << "[this -> word_index: ";
				cout << (this -> word_index) << " ] | LN:";
				cout << __LINE__;
				cout << endl; // PRINTS CONTENTS OF word_index
				
				cout << "[this -> lett_index: ";
				cout << (this -> lett_index) << " ] | LN:";
				cout << __LINE__;
				cout << endl; // PRINTS CONTENTS OF lett_index
#endif		/* -----------------------------------------------------------END- */
			
				found = this -> findExisting();
				
				/* If the value of found is an index, its frequency
				 * is incremented. */
				if(found >= 0)
					this -> freq[found]++;
				else{
				/* Otherwise, the frequency count of the current word
				 * is set to 1, and the Dictionary's word_index is
				 * incremented. */
					this -> freq[this -> word_index] = 1;
					this -> word_index++;
				}

				this -> lett_index = 0;
				char_flag = false;

			} else if(ch == '=')
				break;
		}
	}
		
	void printWords(){

		char ch;
		bool char_flag;
		int word_indexP = 0;
		int lett_indexP = 0;
	
		while(word_indexP < (this -> word_index)){	
			if((this -> words[word_indexP][lett_indexP]) != '\n'){
				cout << this -> words[word_indexP][lett_indexP++];
				char_flag = true;

			} else if(char_flag){
				cout << " [FREQ: " << this -> freq[word_indexP];
				cout << "] " << endl;
				word_indexP++;
				lett_indexP = 0;
				char_flag = false;
			}
		}
	}
};


int main(){

	Dictionary test;
	
	test.addWords();
	test.printWords();
}
