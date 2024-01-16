Authors : Charles Barth & Jimmy Thao
Date : March 24th, 2023

How to use:
To run this program, you must type in this format into the command line argument:

./tokenizer <input_file> <output_file>

The arguments should be paths to either the input or output file. If there is a 
missing arguement, the program will display a message showing how to properly format the 
command line arguement.

Description of Program:
The purpose of the project is to find statements and determine the lexemes within. The program
will first check to see if there are enough command line arguments. If so, the input file is 
read and each line is read and split into individual lexemes as they're found. All of the lexemes that are traversed 
through are displayed with a statement signifying what the lexeme is. The lexemes are determined
by from a preselected pool of characters and categories. If there is an unknown symbol, the 
symbol will be displayed with a message stating there is a lexical error. After each semicolon,
a new statement is started and the steps stated above are repeated. This process is repeated until
all lines and statements have been read. The output information is sent to the output file for
viewing.