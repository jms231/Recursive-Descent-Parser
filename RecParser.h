#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define EQUAL_OP 27
#define KEY_READ 30
#define INC_OP 31
#define DEC_OP 32
#define KEY_WRITE 33
#define LESSER_OP 34
#define GREATER_OP 35
#define NEQUAL_OP 36
#define LEQUAL_OP 37
#define GEQUAL_OP 38
#define SEMICOLON 39
#define KEY_WHILE 40
#define KEY_DO 41
#define KEY_OD 42





int lex();

#endif
