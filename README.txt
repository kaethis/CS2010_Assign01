----------------------------------------
    _            _              ___  _ 
   / \   ___ ___(_) __ _ _ __  / _ \/ |
  / _ \ / __/ __| |/ _` | '_ \| | | | |
 / ___ \\__ \__ \ | (_| | | | | |_| | |
/_/   \_\___/___/_|\__, |_| |_|\___/|_|
                   |___/               
----------------------------------------
Author: 	Matt W. Martin, 4374851
		kaethis@tasmantis.net

Project:	CS2010, Assignment 01
		Dictionary (Fixed-Array Implementation)

Date Issued:	29-Sept-2014
Date Archived:	[REDACTED]

Comments:	This lab consists of just one program: dict 

		- dict: This program will read either a text file or input and build a
			"Dictionary" of words based on that file or user input. This
			Dictionary will contain not only each word, but also the
			occurance of each unique word.

			NOTE: By default, the Dictionary can store a maximum of 165
			      words, each containing up to 11 chararacters.

		To read from a file, execute like so:		$  ./dict < TEXT.txt
		(Where "TEXT" is the name of your file.)

		Otherwise, the program will request input from the user as soon as
		the program executes: it will interpret the each word from the input
		and add them to the Dictionary before printing its contents on the
		screen.

MAKE:		./dict		Creates the dict program described above.
		./clean		Removes dict program.
		./archive	Creates a .tar in parent-directory (../).
		
GIT Repository:			https://github.com/kaethis/CS2010_Assign01.git

Notes (Optional):	- To test reading from a file, I've included an excerpt from
			  Jaron Lanier's "You Are Not A Gadget: A Manifesto". 
