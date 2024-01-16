/**
 * tokenizer.c - A simple token recognizer.
 *
 * NOTE: The terms 'token' and 'lexeme' are used interchangeably in this
 *       program.
 *
 * @author Charles Barth and Jimmy Thao
 * @version 3/24/2023
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokenizer.h"

// global variables
char *line; // Global pointer to line of input

/**
 * This is the entry point to the program. It takes in two command line arguments:
 * the name of the input file and the name of the output file.
 * It opens the files for reading and writing and passes off any errors that occur
 * to the aapropirate helper function. It then reads in each line of the input file
 * and calls the get_token function to tokenize each line. It then prints the
 * tokens to the output file.
 *
 * @param argc the number of command line arguments
 * @param argv the array of command line arguments
 *
 * @return 0 if the program exits successfully
 */
int main(int argc, char *argv[])
{
  char token[TSIZE];     /* Spot to hold a token, fixed size */
  char input_line[LINE]; /* Line of input, fixed size        */
  FILE *in_file = NULL;  /* File pointer                     */
  FILE *out_file = NULL;
  int statement_count, /* Number of statements read             */
      start,           /* is this the start of a new statement? */
      count;           /* count of tokens                  */

  if (argc < 3)
  {
    printf("Usage: tokenizer inputFile outputFile\n");
    exit(1);
  }

  in_file = fopen(argv[1], "r");
  if (in_file == NULL)
    print_io_error("reading", argv[1]);

  out_file = fopen(argv[2], "w");
  if (out_file == NULL)
    print_io_error("writing", argv[2]);

  statement_count = 0, start = TRUE, count = 0;

  while (fgets(input_line, LINE, in_file) != NULL)
  {
    line = input_line; // Sets a global pointer to the memory location
                       // where the input line resides.

    while (*line != LINE_END && *line != '\n')
    {
      if (start)
        new_statement(out_file, ++statement_count, &count);

      get_token(token);
      count++;

      start = *token == SEMI_COLON ? TRUE : FALSE;
      print_lexeme(out_file, token, count);
    }

    bzero(input_line, LINE);
  }

  fclose(in_file);
  fclose(out_file);
  return 0;
}

/**
 * This function finds the next token in the input line and stores it in the token pointer.
 *
 * @param token_ptr a pointer for where to store the token
 */
void get_token(char *token_ptr)
{
  while (isspace((unsigned char)*line))
    line++;

  int i = 0;
  while (isdigit((unsigned char)line[i]))
    i++;

  if ((*line == ASSIGN || *line == NOT || *line == LESS ||
       *line == GREATER) &&
      line[1] == ASSIGN)
    i = 2;
  else
    i = i == 0 ? 1 : i;

  char *temp_token = (char *)malloc(i * sizeof(char));
  strncpy(temp_token, line, i);
  strncpy(token_ptr, temp_token, TSIZE);

  line += i;
}

/**
 * This is responsible for printing errors to stderr when either the input file
 * or output file cannot be opened.
 *
 * @param read_write a string that indicates whether the error occurred
 * while trying to read or write to a file
 * @param file_name the name of the file that could not be opened
 */
void print_io_error(char *read_wrtie, char *file_name)
{
  fprintf(stderr, "ERROR: could not open %s for %s\n", file_name, read_wrtie);
  exit(1);
}

/**
 * This function prints the current lexeme and its type.
 *
 * @param output_file the file to print to
 * @param token_ptr a pointer to the current token
 * @param count the current token count
 */
void print_lexeme(FILE *output_file, char *token_ptr, int count)
{
  char lexeme_type[LEX_TYPE];
  strcpy(lexeme_type, "ERROR");

  if (*token_ptr == '\0')
    strcpy(lexeme_type, "SKIP");
  else if (isdigit((unsigned char)*token_ptr))
    strcpy(lexeme_type, "an INT_LITERAL");
  else if (*token_ptr == ADD)
    strcpy(lexeme_type, "an ADD_OP");
  else if (*token_ptr == SUB)
    strcpy(lexeme_type, "a SUB_OP");
  else if (*token_ptr == MULT)
    strcpy(lexeme_type, "a MULT_OP");
  else if (*token_ptr == DIV)
    strcpy(lexeme_type, "a DIV_OP");
  else if (*token_ptr == LEFT_PAREN)
    strcpy(lexeme_type, "a LEFT_PAREN");
  else if (*token_ptr == RIGHT_PAREN)
    strcpy(lexeme_type, "a RIGHT_PAREN");
  else if (*token_ptr == EXPON)
    strcpy(lexeme_type, "an EXPON_OP");
  else if (token_ptr[1] == ASSIGN)
    two_line_tokens(token_ptr, lexeme_type);
  else if (*token_ptr == ASSIGN)
    strcpy(lexeme_type, "an ASSIGN_OP");
  else if (*token_ptr == NOT)
    strcpy(lexeme_type, "a NOT_OP");
  else if (*token_ptr == LESS)
    strcpy(lexeme_type, "a LESS_THAN_OP");
  else if (*token_ptr == GREATER)
    strcpy(lexeme_type, "a GREAT_THAN_OP");
  else if (*token_ptr == SEMI_COLON)
    strcpy(lexeme_type, "a SEMI_COLON");

  if (*lexeme_type == 'E')
    fprintf(output_file, "===> \'%s\'\nLexical error: not a lexeme\n", token_ptr);
  else if (*lexeme_type != 'S')
    fprintf(output_file, "Lexeme %d is %s and is %s\n", count, token_ptr, lexeme_type);
}

/**
 * This function determines the lexeme type for two character tokens.
 *
 * @param token_ptr the token pointer
 * @param lexeme_type_ptr a pointer to the lexeme type
 */
void two_line_tokens(char *token_ptr, char *lexeme_type_ptr)
{
  if (*token_ptr == LESS)
    strcpy(lexeme_type_ptr, "a LESS_THAN_OR_EQUAL_OP");
  else if (*token_ptr == GREATER)
    strcpy(lexeme_type_ptr, "a GREATER_THAN_OR_EQUAL_OP");
  else if (*token_ptr == ASSIGN)
    strcpy(lexeme_type_ptr, "an EQUAL_OP");
  else if (*token_ptr == NOT)
    strcpy(lexeme_type_ptr, "a NOT_EQUALS_OP");
}

/**
 * This function prints the statement number and a line of dashes to the output file.
 *
 * @param out_file the output file
 * @param statement_count the number of statements found
 * @param count the current number of tokens in the statement
 */
void new_statement(FILE *out_file, int statement_count, int *count)
{
  *count = 0;

  if (statement_count > 1)
    fprintf(out_file, "---------------------------------------------------------\n");
  fprintf(out_file, "Statement #%d\n", statement_count);
}