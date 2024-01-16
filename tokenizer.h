/**
 * Header file for the tokenizer project
 * @author Chalres Barth and Jimmy Thao
 * @version 3/24/2023
 */

/* Constants */
#define LINE 100
#define TSIZE 20
#define TRUE 1
#define FALSE 0
#define LINE_END '\0'
#define SEMI_COLON ';'
#define ADD '+'
#define SUB '-'
#define MULT '*'
#define DIV '/'
#define LEFT_PAREN '('
#define RIGHT_PAREN ')'
#define EXPON '^'
#define ASSIGN '='
#define NOT '!'
#define LESS '<'
#define GREATER '>'
#define LESS_EQUAL "<="
#define GREATER_EQUAL ">="
#define EQUAL "=="
#define NOT_EQUAL "!="
#define LEX_TYPE 30

/**
 * Create function prototypes for all functions in the source code
 */
void get_token(char *);
void print_lexeme(FILE *, char *, int);
void print_io_error(char *, char *);
void two_line_tokens(char *, char *);
void new_statement(FILE *, int, int *);
