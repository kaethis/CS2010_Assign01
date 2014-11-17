#include <cstdio>
#include <cctype>
#include <iostream>
#include <stdio.h>	// printf
using namespace std;

/* Author:	Matt W. Martin, 4374851
 *		kaethis@tasmantis.net
 *
 * Project:	CS2010, Assignment #1
 *		        Dictionary I */ 

class Dictionary{

	typedef char lett;
	
	/* NOTE: The implementation of this Dictionary class allows for only a fixed
	 *	 number of words and word-length.  Adjust the parameters below to
	 *	 modify the size of the Dictionary to suit your needs.
	 *
	 * NOTE 2: The value of LETT_MAX also includes its null-byte.  In other words,
	 *	   the actual word-length is (LETT_MAX - 1). */

	static const int WORD_MAX =  165;
	static const int LETT_MAX =  12;
	
	lett words[WORD_MAX][LETT_MAX];	// Array implementation of Dictionary.
	int word_index, lett_index;	// (i.e., current word, current letter.)

	int freq[WORD_MAX];		/* Represents the frequency of the word of the
					 * same index number. */
	bool overflow[WORD_MAX];	/* If true, the corresponding word of the same
					 * index number was too long to be captured in
					 * its entirety. */
	public: 
	Dictionary(){word_index = 0;	lett_index = 0;}

	int getLength(int word_indexF);	/* Returns the length of the corresponding
					 * word in the dictionary. */

	int findExisting();	/* Compares the current entry in a Dictionary with
				 * past entries to see if the word already exists. */
	
	void addWords();	/* Collects a series of characters and interprets them
				 * as words to be added to a Dictionary. */

	void dumpWords();	/* Provides an easy way of checking the contents of a
				 * dictionary; best suited for diagnostic purposes. */

	void printWords();	/* Prints the contents of a Dictionary in a manner
				 * that's clean, simple, and easy to look at. */
};

int Dictionary::getLength(int word_indexF){
	/* This method returns the length of the corresponding word in the Dictionary,
	 * given the index of the word (word_indexF). */

	int lett_indexF = 0;

	while(this -> words[word_indexF][lett_indexF] != '\n')
		lett_indexF++;

	return lett_indexF;
}

int Dictionary::findExisting(){
	/* This method compares the current entry in the Dictionary with past entries.
	 * If the word already exists, its word_index is returned.  If the word
	 * doesn't already exist, it returns -1. */
	
	int word_indexF = 0;
	int lett_indexF = 0;
	int found_count;	// Increments every time a letter matches.
	int word_length;
	lett *wordp;		// Points to the current entry in the Dictionary. */
	
	wordp = this -> words[this -> word_index];

	while(word_indexF < this -> word_index){

		found_count = 0;

		while(this -> words[word_indexF][lett_indexF] != '\n'){

			/* Every time a letter matches that in the current entry,
			 * found_count is incremented. */ 
			if(wordp[lett_indexF] == this -> words[word_indexF]
						       	      [lett_indexF])
				found_count++;
			
			/* If a letter doesn't match, then we can safely assume the
			 * rest of the word is different; therefore, the program jumps
			 * to the Next_Word label so that we can increment word_indexF
			 * and set lett_indexF back to 0. */	
			else 
				goto Next_Word;

			lett_indexF++;
		}

		// The length of the word at word_indexF is gotten:	
		word_length = this -> getLength(word_indexF);

		/* If the sum of the number of matching letters (found_count) and the
		 * length of the existing word (word_length) is equal to twice the
		 * length of the current entry, this word already exists in the
		 * Dictionary. */
		if((found_count + word_length)  == (this -> lett_index * 2))
			return word_indexF;	// THE WORD EXISTS IN THE DICTIONARY.

		else{
		  Next_Word:

			/* If the word at word_indexF doesn't match the current entry,
			 * word_indexF is incremented, and lett_indexF is set back to
			 * 0. */
			word_indexF++;
			lett_indexF = 0;
		}
	}

	return -1;			// THE WORD DOES NOT EXIST IN THE DICTIONARY.
}

void Dictionary::addWords(){
	/* This method collects a series of characters and interprets them as words to
	 * be added to the Dictionary. The frequency of each occuring word is
	 * calculated as well. */

	lett letter;			// Input character.
	int word_found;	
	bool lett_flag = false;
	bool apostrophe_flag = false;
	bool hyphen_flag = false;
	bool overflow_flag = false;

	while((cin.good()) && (this -> word_index < WORD_MAX)){

		letter = cin.get();
	
		/* If the overflow_flag's been set, and it enounters a character that
		 *  isn't a letter, set the overflow_flag FALSE, and proceed.  Until
		 * then, it will ignore all subsequent letters. */
		if((!isalpha(letter)) && overflow_flag)
			overflow_flag = false;

		/* If letter is an alphabetic character, and the overflow_flag is
		 * FALSE, then proceed to add letters to the dictionary. */
		if(isalpha(letter) && (!overflow_flag)){

			/* If the word already exceeds the length of LETT_MAX, the
			 * overflow_flag is set, its overflow bool is set to TRUE, and
			 * the program jumps to the End_Word label. */
			if(this -> lett_index == (LETT_MAX - 1)){
				overflow_flag = true;
				this -> overflow[this -> word_index] = true;
				goto End_Word;
			}
			
			/* If an apostrophe is passed following a letter, an
			 * apostrophe is placed before placing the new letter
			 * (assuming there is enough room). */
			if((apostrophe_flag) && 
			   (this -> lett_index < (LETT_MAX - 2))){

				this -> words[this -> word_index]
					     [this -> lett_index] = 39;

				this -> lett_index++;

			/* Alternatively, if a hyphen is passed following a letter, a
			 * hyphen is placed before placing the new letter (assuming 
			 * there is enough room). */
			} else if((hyphen_flag) && 
			          (this -> lett_index < (LETT_MAX - 2))){

				this -> words[this -> word_index]
					     [this -> lett_index] = 45;

				this -> lett_index++;
			}

			/* The lowercase of letter is inserted in the current 
			 * word_index at the current lett_index. */
			this -> words[this -> word_index]
				     [this -> lett_index] = tolower(letter);

			this -> lett_index++;

			lett_flag = true;
			apostrophe_flag = false;
			hyphen_flag = false;
	
		/* If an apostrophe is immediately after a letter, the apostrophe_flag
		 * is set. */
		} else if((lett_flag) && (!apostrophe_flag) && 
			  (letter == 39)){ 
				
			/* NOTE: A word is only considered a contraction if there
			 *	 exists a letter on both sides of the  apostrophe.
			 * 
			 *	 FOR EXAMPLE:	[ENTRY]       [OUTCOME] 
			 *			you've   ---->  you've
			 *			you'     ---->     you
			 *			've      ---->      ve   
			 *       (THIS PROGRAM MAKES NO DISTINCTION BETWEEN
			 *        THE POSESSIVE 's AND THE CONTRACTION OF A
			 *        NOUN & 's [i.e., "Matt's tablet", vs.
			 *	  "Matt's late for class."]) */

			apostrophe_flag = true;
			hyphen_flag = false;


		// If a hyphen is immediately after a letter, the hyphen_flag is set.
		} else if((lett_flag) && (!hyphen_flag) && 
			  (letter == 45)){ 
				
			/* NOTE: A word is only considered hyphenated if there exists
			 *	 a letter on both sides of the hyphen.
			 *
			 *	 FOR EXAMPLE:	[ENTRY]          [OUTCOME] 
			 *		    one-hundred  ----> one-hundred
			 *			   one-  ---->         one
			 *		       -hundred  ---->     hundred */

			hyphen_flag = true;
			apostrophe_flag = false;

		} else if(lett_flag){

			/* If the program arrives here under normal circumstances,
			 * the limit of LETT_MAX has not been reached. Therefore, the
			 * overflow bool is FALSE. */
			this -> overflow[this -> word_index] = false;

		  End_Word:

			this -> words[this -> word_index]
				     [this -> lett_index] = '\n';

			/* The current entry is compared to existing words in the
			 * Dictionary to determine whether or not the word already
			 * exists. */
			word_found = this -> findExisting();
			
			/* If the value of word_found indicates a word index, that
			 * means the word already exists: the freqency of that word is
			 * incremented. */
			if(word_found >= 0)
				this -> freq[word_found]++;

			/* Otherwise, the frequency count of the  current word is set
			 * to 1, and the Dictionary's word_index is incremented. */
			else{

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
}

void Dictionary::dumpWords(){
	/* This method provides a quick-and-easy way of checking the contents of the
	 * Dictionary at any given time.  Not very pretty to look at, though, so I
	 * suggest you use this method for diagnostic purposes only. */

	int word_indexD = 0;
	int lett_indexD = 0;
	bool lett_flag;

	while(word_indexD < this -> word_index){	
		
		cout << "[WORD_INDEX: " << word_indexD << "]";
		cout << "[LETT_INDEX: " << lett_indexD << "] ";

		if((this -> words[word_indexD][lett_indexD]) != '\n'){

			cout << this -> words[word_indexD][lett_indexD++];
			lett_flag = true;

		} else if(lett_flag){
		
			cout << "!";	// End of word was reached, indicated by "!".

			// Frequency of the word is printed:
			cout << " [FREQ: " << this -> freq[word_indexD] << "] ";

			/* If a word was too long to be entered in the Dictionary in
			 * its entirety (meaning its Overflow bool was set to TRUE),
			 * this will let you knowr: */
			if(this -> overflow[word_indexD])
				cout << "[OVERFLOW]";

			cout << endl;

			word_indexD++;
			lett_indexD = 0;
			lett_flag = false;
		}

		cout << endl;
	}
}

void Dictionary::printWords(){
	/* This method prints the contents of the Dictionary in a manner that's clean,
	 * simple, and and easy to look at.
	 *
	 * NOTE: If the length of a word is more than 38 characters (REMEMBER, the
	 *	 value of LETT_MAX includes the null-byte!), printWords may not
	 *	 display correctly.  In this case, it's highly recommended you use
	 *	 the dumpWords method instead. */

	int word_indexP = 0;
	int lett_indexP = 0;
	bool lett_flag;

	int FREQ_BEGINS = 42;	// Frequency count begins in the 43rd column.
	int spaceCount;

	cout << " ____  _      _   _                              " << endl;
	cout << "|  _ \\(_) ___| |_(_) ___  _ __   __ _ _ __ _   _ " << endl;
	cout << "| | | | |/ __| __| |/ _ \\| '_ \\ / _` | '__| | | |" << endl;
	cout << "| |_| | | (__| |_| | (_) | | | | (_| | |  | |_| |" << endl;
	cout << "|____/|_|\\___|\\__|_|\\___/|_| |_|\\__,_|_|   \\__, |" << endl;
	cout << " F I X E D - A R R A Y   E D I T I O N !   |___/ " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << " [WORD]                                   [FREQ] " << endl;
	cout << endl << " ";

	while(word_indexP < this -> word_index){	
	
		if((this -> words[word_indexP][lett_indexP]) != '\n'){

			cout << this -> words[word_indexP][lett_indexP++];
			lett_flag = true;

		} else if(lett_flag){

			/* An ellipsis indicates a word was not captured in its
			 * entirety due to LETT_MAX limitations. */
			if(this -> overflow[word_indexP]){
				cout << "...";
				// (To account for the size of the ellipsis...)
				lett_indexP += 3;
			}

			/* I want the frequency to be printed starting from the column
			 * number stored in FREQ_BEGINS.  Because the length of each
			 * word varies, the number of blankspaces required to get to
			 * that column will also vary.  By subtracting the word's
			 * length (lett_indexP) from FREQ_BEGINS, we can determine the
			 * number of blankspaces we need. */
			spaceCount = (FREQ_BEGINS - lett_indexP);
		
			// This fills-in the space between the word and freq. count:
			for(int i = 0; i < spaceCount; i++)
				cout << " ";

			printf("%5d", (this -> freq[word_indexP]));

			/* This makes sure a blank-space isn't accidentally inserted
			 * into the beginning of the footer. */
			if(word_indexP < (this -> word_index - 1))
				cout << endl << " ";

			word_indexP++;
			lett_indexP = 0;
			lett_flag = false;
		}
	}

	cout << endl;
	cout << "-------------------------------------------------";
	cout << endl;

	cout << " [NUM. OF WORDS IN DICTIONARY: ";
	/* This prints out the number of UNIQUE words that were entered into the
	 * Dictionary.  If the Dictionary reached its full potential, the sum  will
	 * literally read "MAX". */
	if(this -> word_index == WORD_MAX)
		printf("%16s]", "MAX");
	
	// Otherwise, the numerical value gets printed.
	else
		printf("%16d]", word_indexP);

	cout << endl;
	cout << "-------------------------------------------------";
	cout << endl;
}


int main(){

	Dictionary dict;
	
	dict.addWords();
	dict.printWords();
}
