#include <cstdio>
#include <cctype>
#include <iostream>
#include <stdio.h>	// printf
using namespace std;

#define DEBUG

/* Author:	Matt W. Martin, 4374851
 *		kaethis@tasmantis.net
 *
 * Project:	CS2010, Assignment #1
 *		        Dictionary I */ 
			
class Dictionary{

	typedef char lett;

	static const int WORD_MAX =  10; //NOTE: The implimentation of the Dictionary
	static const int LETT_MAX =  10; /*      allows for only a fixed number of
				  	  *      words and word length. Adjust these 
				  	  *      parameters by modifying WORD_MAX and
				  	  *      LETT_MAX. */
	
	lett words[WORD_MAX][LETT_MAX];
	int word_index, lett_index;	// (i.e., current word, current letter)
	int freq[WORD_MAX];		/* Represents the frequency of the word of
					 * the same index number. */
	public: 
	Dictionary(){
		word_index = 0;	// Represents the total number of words.
		lett_index = 0; /* Indicates the index of the final letter of the
				 * current word entry. */

	}

	int getLength(int word_indexF){
		/* This method returns the length of the corresponding word in this
		 * Dictionary, given the index of the word (word_indexF). */

		int lett_indexF = 0;

		while(this -> words[word_indexF][lett_indexF] != '\n')
			lett_indexF++;

		return lett_indexF;
	}
	
	int findExisting(){
		/* This method examines the current entry in the Dictionary with past
		 * entries. If the word already exists, its word_index is returned.
		 * If the word doesn't already exist, it returns -1. */
		
#ifdef DEBUG	/* -START--------------------------------------------------------- */
		cout << " findExisting ::: " << endl;
#endif		/* -----------------------------------------------------------END- */

		int word_indexF = 0;
		int lett_indexF = 0;
		int found_count;	// Increments every time a letter matches.
		int word_length;
		lett *wordp;		/* Points to the current entry in the
					 * Dictionary. */
		
		wordp = this -> words[this -> word_index];

		while(word_indexF < this -> word_index){

			found_count = 0;
				
			while(this -> words[word_indexF][lett_indexF] != '\n'){

				/* Every time a letter matches that in the current
				 * entry, found_count is incremented. */ 
				if(wordp[lett_indexF] == this -> words[word_indexF]
							       	      [lett_indexF])
					found_count++;
				
				/* If a letter doesn't match, then we can safely
				 * assume the word is different; therefore, we jump 
				 * to Next_Word so that we can increment word_indexF
				 * and set lett_indexF back to 0. */	
				else 
					goto Next_Word;

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << "                  ";
				cout << "[word_indexF: ";
				cout << (word_indexF);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF word_indexF
				
				cout << "                  ";
				cout << "[lett_indexF: ";
				cout << (lett_indexF);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF lett_indexF

				cout << "                  ";
				cout << "                   [wordp[lett_indexF]: ";
				if(wordp[lett_indexF] != '\n')
					cout << wordp[lett_indexF];
				else
					cout << "!";
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF wordp AT
					      // lett_indexF
				
				cout << "                  ";
				cout << "[this->words[word_indexF][lett_indexF]: ";
				cout << (this -> words[word_indexF][lett_indexF]);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this -> words
					      // AT word_indexF, lett_indexF

				cout << "                  ";
				cout <<  "[found_count: ";
				cout << (found_count);
				cout << " ] | LN:" << __LINE__;
				cout << endl << endl; // PRINTS found_count NUM
#endif		/* -----------------------------------------------------------END- */

				lett_indexF++;
			}

			// The length of the word at word_indexF is gotten:	
			word_length = this -> getLength(word_indexF);

			/* If the sum of the number of matching letters (found_count)
			 * and the length of the existing word (word_length) is equal
			 * to twice the length of the current entry, this word already
			 * exists in the Dictionary. */
			if((found_count + word_length)  == 
			   ((this -> lett_index) * 2)){
	
#ifdef DEBUG	/* -START -------------------------------------------------------- */
				cout << "                  " ;
				cout << "[this->lett_index: ";
				cout << (this -> lett_index) << "] | LN:";
				cout << __LINE__;
				cout << endl; // PRINTS CONT. OF this -> lett_index

				cout << "                  ";
				cout << "FOUND EXISTING ENTRY @ this -> words[";
				cout << (word_indexF) << "]" << endl;
				cout << "                  RETURNING word_indexF";
				cout << " | LN: " << __LINE__;
				cout << endl << endl; // ANN. IF EXISTING WORD FOUND
					      // AND PRINTS CONTENTS OF word_indexF
#endif		/* -----------------------------------------------------------END- */
				
				return word_indexF;

			} else{
			  Next_Word:

				/* If the word at word_indexF doesn't match the
				 * current entry, word_indexF is incremented, and
				 * lett_indexF is set back to 0. */
				word_indexF++;
				lett_indexF = 0;
			}
		}

#ifdef DEBUG	/* -START -------------------------------------------------------- */
		cout << "                  ";
		cout << "NO EXISTING ENTRIES FOUND!" << endl;
		cout << "                  RETURNING -1!";
		cout << " | LN: " << __LINE__;
		cout << endl << endl; // ANNOUNCES IF NO EXISTING WORD IS FOUND
#endif		/* -----------------------------------------------------------END- */

		return -1;
	}
	
	void addWords(){
		/* This method collects a series of characters and interprets them
		 * as words to be added to this Dictionary. The frequency of each
		 * occuring word is calculated as well. */

		lett letter;		// Input character.
		int word_found;	
		bool lett_flag = false;
		bool apostrophe_flag = false;
		bool hyphen_flag = false;
		bool overflow_flag = false;

		while((cin.good()) && ((this -> word_index) < WORD_MAX)){

			letter = cin.get();

			if(isalpha(letter) && ((this -> lett_index < LETT_MAX))){

#ifdef DEBUG	/* -START--------------------------------------------------------- */
			cout << " addWords ::: " << endl;
#endif		/* -----------------------------------------------------------END- */

				/* If the apostrophe_flag is set to true before
p
				 * placing a new letter, an apostrophe is placed
				 * before placing the new letter. */

				if(apostrophe_flag &&
				   ((this -> lett_index) < (LETT_MAX - 1))){

					this -> words[this -> word_index]
						     [this -> lett_index] = 39;

#ifdef DEBUG	/* -START--------------------------------------------------------- */
					cout << "              ";
					cout << "APPOSTROPHE PLACED! ";
					cout << "[apostrophe_flag is now FALSE "; 
					cout << " ] | LN:" << __LINE__;
					cout << endl; // ANN. IF APPOSTROPHE PLACED

					cout << "              ";
					cout << "[this->word_index: ";
					cout << (this -> word_index);
					cout << " ] | LN:" << __LINE__;
					cout << endl; // PRINTS this->word_index

					cout << "              ";
					cout << "[this->lett_index: ";
					cout << (this -> lett_index);
					cout << " ] | LN:" << __LINE__;
					cout << endl; // PRINTS this->lett_index

					cout << "              ";
					cout << "[this->words[this->word_index]";
					cout << endl << "              ";
					cout << "            [this->lett_index]: ";
					cout << (this -> words[this -> word_index]
							      [this -> lett_index]);
					cout << " ] | LN:" << __LINE__;
					cout << endl << endl; // PRINTS this->words

#endif		/* -----------------------------------------------------------END- */

					(this -> lett_index)++;

				} else if(apostrophe_flag &&
					  ((this -> lett_index) >= (LETT_MAX - 1)))
					/* If there isn't enough room to place both
					 * the letter and the apostrophe, jump to
					 * End_Word. */
					goto End_Word;

				/* Alternatively, if a hyphen is passed following a 
				 * letter, a hyphen is placed before placing the new
				 * letter. */
				if(hyphen_flag &&
				   ((this -> lett_index) < (LETT_MAX - 1))){

					this -> words[this -> word_index]
						     [this -> lett_index] = 45;

#ifdef DEBUG	/* -START--------------------------------------------------------- */
					cout << "              ";
					cout << "HYPHEN PLACED! ";
					cout << "[hyphen_flag is now FALSE "; 
					cout << " ] | LN:" << __LINE__;
					cout << endl; // ANN. IF HYPHEN PLACED

					cout << "              ";
					cout << "[this->word_index: ";
					cout << (this -> word_index);
					cout << " ] | LN:" << __LINE__;
					cout << endl; // PRINTS this->word_index
				
					cout << "              ";
					cout << "[this->lett_index: ";
					cout << (this -> lett_index);
					cout << " ] | LN:" << __LINE__;
					cout << endl; // PRINTS this->lett_index

					cout << "              ";
					cout << "[this->words[this->word_index]";
					cout << endl << "              ";
					cout << "            [this->lett_index]: ";
					cout << (this -> words[this -> word_index]
							      [this -> lett_index]);
					cout << " ] | LN:" << __LINE__;
					cout << endl << endl; // PRINTS this->words

#endif		/* -----------------------------------------------------------END- */

					(this -> lett_index)++;

				} else if(hyphen_flag &&
					  ((this -> lett_index) >= (LETT_MAX - 1)))

					/* If there isn't enough room to place both
					 * the letter and the hyphen, jump to
					 * End_Word. */
					goto End_Word;

				/* The lowercase of letter is inserted in the current
				 * word_index at the current lett_index. */
				this -> words[this -> word_index]
					     [this -> lett_index] = tolower(letter);

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << "              ";
				cout << "[this->word_index: ";
				cout << (this -> word_index);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this->word_index
				
				cout << "              ";
				cout << "[this->lett_index: ";
				cout << (this -> lett_index);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this->lett_index

				cout << "              ";
				cout << "[this->words[this->word_index]" << endl;
				cout << "              ";
				cout << "            [this->lett_index]: ";
				cout << (this -> words[this -> word_index]
						      [this -> lett_index]);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this->words
#endif		/* -----------------------------------------------------------END- */

				(this -> lett_index)++;

				lett_flag = true;
				apostrophe_flag = false;
				hyphen_flag = false;

			} else if((lett_flag) && (!apostrophe_flag) && 
				  (letter == 39)){
					
				/* NOTE: A word is only considered a contraction if
				 *       there exists a letter on both sides of the
				 *       apostrophe. 
				 *	 FOR EXAMPLE:	[ENTRY]       [OUTCOME] 
				 *			you've   ---->  you've
				 *			you'     ---->     you
				 *			've      ---->      ve   
				 *       (THIS PROGRAM MAKES NO DISTINCTION BETWEEN
				 *        THE POSESSIVE 's AND THE CONTRACTION OF A
				 *        NOUN AND "is" [i.e., "Matt's tablet", vs.
				 *	  "Matt's late for class."]) */

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << " addWords ::: " << endl;
#endif		/* -----------------------------------------------------------END- */
				
				/* If an apostrophe is placed immediately after a
				 * letter, the apostrophe_flag is set to true.*/
				apostrophe_flag = true;

				/* A hyphen cannot appear after an apostrophe; to
				 * make sure this doesn't happen, hyphen_flag is set
				 * to false. */
				hyphen_flag = false;

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << "              ";
				cout << "APOSTROPHE PASSED! ";
				cout << "[apostrophe_flag is TRUE "; 
				cout << " ] | LN:" << __LINE__;
				cout << endl; // ANN. IF APPOSTROPHE WAS PASSED
#endif		/* -----------------------------------------------------------END- */

			} else if((lett_flag) && (!hyphen_flag) && 
				  (letter == 45)){
					
				/* NOTE: A word is only considered hyphenated if
				 *       there exists a letter on both sides of the
				 *       hyphen. 
				 *	 FOR EXAMPLE:	[ENTRY]           [OUTCOME] 
				 *		   one-hundred	 ----> one-hundred
				 *		   one-          ---->         one
				 *		   -hundred      ---->     hundred */

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << " addWords ::: " << endl;
#endif		/* -----------------------------------------------------------END- */
				
				/* If a hyphen is placed immediately after a letter,
				 * the hyphen_flag is set to true.*/
				hyphen_flag = true;

				/* An apostrophie cannot appear after a hyphen; to
				 * make sure this doesn't happen, apostrophie_flag is
				 * set to false. */
				apostrophe_flag = false;

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << "              ";
				cout << "HYPHEN PASSED! ";
				cout << "[hyphen_flag is TRUE "; 
				cout << " ] | LN:" << __LINE__;
				cout << endl; // ANN. IF APPOSTROPHE WAS PASSED
#endif		/* -----------------------------------------------------------END- */
				
			} else if(lett_flag){
			  End_Word:

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << " addWords ::: " << endl;
#endif		/* -----------------------------------------------------------END- */
			
				/* If the character was considered invalid following
				 * a letter, a null-byte is placed at the final 
				 * lett_index, indicating the end of a word.. */
				this -> words[this -> word_index]
					     [this -> lett_index] = '\n';

#ifdef DEBUG	/* -START--------------------------------------------------------- */
				cout << "              ";
				cout << "[this->word_index: ";
				cout << (this -> word_index);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this->word_index
				
				cout << "              ";
				cout <<  "[this->lett_index: ";
				cout << (this -> lett_index);
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS CONTENTS OF this->lett_index

				cout << "              ";
				cout << "[this->words[this->word_index]" << endl;
				cout << "              ";
				cout << "            [this->lett_index]: ";
				if((this -> words[this -> word_index]
						 [this -> lett_index]) == '\n')
					cout << "!";
				cout << " ] | LN:" << __LINE__;
				cout << endl; // PRINTS ! IF CONTENTS OF WORDS[][]
					      // IS NULL-BYTE, INDICATING END OF WORD
#endif		/* -----------------------------------------------------------END- */
				
				/* The current entry is compared to existing words in
				 * the Dictionary to determine whether or not the
				 * wordalready exists. */
				word_found = this -> findExisting();
				
				if(word_found >= 0){

#ifdef DEBUG	/* -START--------------------------------------------------------- */
					cout << " addWords ::: " << endl;
#endif		/* -----------------------------------------------------------END- */

					/* If the value of word_found indicates a 
					 * word index, the freqency of that index is
					 * incremented. */
					this -> freq[word_found]++;

#ifdef DEBUG	/* -START--------------------------------------------------------- */
					cout << "              ";
					cout << "[this->freq[";
					cout << (word_found) << "]: ";
					cout << this -> freq[word_found];
					cout << " ] | LN:" << __LINE__;
					cout << endl; // PRINTS CONTENTS OF WORD FREQ
						      // IF FREQ GETS INCREMENTED

					cout << "              ";
					cout << "WORD FREQUENCY INCREASED!";
					cout << endl; // ANNOUNCES WORD FREQ INC.
#endif          /* -----------------------------------------------------------END- */

				} else{

					/* Otherwise, the frequency count of the 
					 * current word is set to 1,  and the
					 * Dictionary's word_index is incremented. */
					this -> freq[this -> word_index] = 1;
					this -> word_index++;
				}

				this -> lett_index = 0;

				lett_flag = false;
				apostrophe_flag = false;
				hyphen_flag = false;

			} else if(letter == '\n')
				break;
		}
		if(this -> word_index == WORD_MAX)
			cout << "WORD MAXIMUM REACHED!" << endl;
	}
		
	void dumpWords(){

		int word_indexD = 0;
		int lett_indexD = 0;
		bool lett_flag;

		while(word_indexD < (this -> word_index)){	
			
			cout << "[WORD_INDEX: " << word_indexD << "]";
			cout << "[LETT_INDEX: " << lett_indexD << "] ";

			if((this -> words[word_indexD][lett_indexD]) != '\n'){

				cout << this -> words[word_indexD][lett_indexD++];
				lett_flag = true;

			} else if(lett_flag){
			
				cout << "!";	
				cout << " [FREQ: " << this -> freq[word_indexD];
				cout << "] " << endl;

				word_indexD++;
				lett_indexD = 0;
				lett_flag = false;
			}
		
			cout << endl;
		}
	}
};


int main(){

	Dictionary test;
	
	test.addWords();
	test.dumpWords();
}
