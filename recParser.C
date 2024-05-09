
/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "RecParser.h"
#include "parser.h"
static int error();
/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

/******************************************************/
/* main driver */

//argc and argv are used to pass the command line so that we can choose the file path for the file we are opening.
int main(int argc, char *argv[])
{

    /* Open the input data file and process its contents */
    //"DCooke.in"
    //File path is chosen in the command line.
    if ((in_fp = fopen(argv[1], "r")) == NULL) {
        //Error for if name is entered but file is not found
        if(argv[1]!= NULL)
        {
            printf("ERROR - file not found \n");
            exit(3);
        }
        else
        {
            printf("ERROR - enter a file name \n");
            exit(2);
        }
    }
    else {
        getChar();
        do {
            lex();
            P();
        } while (nextToken != EOF);
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the
 * token */
static int lookup(char ch) {

    /* For 2char lexemes: Adds the char, gets the next char and checks the next token for two char lexemes.
     * If the second char does not match the second char needed to match the lexeme, it sets the first value to its value,
     * or unknown if there are no matches.
     */
    switch (ch) {
        case '<':
            addChar();
            nextToken = LESSER_OP;
            getChar();
            if(nextChar == '=')
            {
                addChar();
                nextToken = LEQUAL_OP;
                getChar();
            }
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
            getChar();
            if(nextChar == '=')
            {
                addChar();
                nextToken = GEQUAL_OP;
                getChar();
            }
            break;
        case '!':
            addChar();
            nextToken = UNKNOWN;
            getChar();
            if(nextChar == '=')
            {
                addChar();
                nextToken = NEQUAL_OP;
                getChar();
            }
            break;

        case ':':
            addChar();
            nextToken = UNKNOWN;
            getChar();
            if (nextChar == '=')
            {   addChar();
                nextToken = ASSIGN_OP;
                getChar();
            }
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            getChar();
            if(nextChar == '+')
            {
                addChar();
                nextToken = INC_OP;
                getChar();
            }
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            getChar();
            if(nextChar == '-')
            {
                addChar();
                nextToken = DEC_OP;
                getChar();
            }
            break;
        /*single char lexemes are added, checked and then set to the value in the corresponding switch statement if they match,
         * then it gets the next char to find the token for the next lexeme.
         */
        case'=':
            addChar();
            nextToken = EQUAL_OP;
            getChar();
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            getChar();
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            getChar();
            break;

        case '*':
            addChar();
            nextToken = MULT_OP;
            getChar();
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            getChar();
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            getChar();
            break;

        //The token is set to UNKNOWN if none of the other switch statements match the lexeme
        default:
            addChar();
            nextToken = UNKNOWN;
            getChar();
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its
 * character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */

        case LETTER:
            addChar();
            getChar();
            //original is while (charClass == LETTER || charClass == DIGIT) took out digit since ident V shouldnt need digit.
            while (charClass == LETTER) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            //compares the lexeme string to the following keywords using strcmp
            if ((strcmp(lexeme,"od")) == 0)
                nextToken = KEY_OD;
            if (strcmp(lexeme, "read" ) == 0)
                nextToken = KEY_READ;
            if ((strcmp(lexeme,"write")) == 0)
                nextToken = KEY_WRITE;
            if ((strcmp(lexeme,"while")) == 0)
                nextToken = KEY_WHILE;
            if ((strcmp(lexeme,"do")) == 0)
                nextToken = KEY_DO;

            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */


// switch statement to convert the token ID's to their actual names.
    switch (nextToken) {
        case 10:
        {
            printf("%s\tINT_LIT\n", lexeme);
            break;
        }
        case 11:
        {
            printf("%s\tIDENT\n", lexeme);
            break;
        }
        case 20:
        {
            printf("%s\tASSIGN_OP\n", lexeme);
            break;
        }
        case 21:
        {
            printf("%s\tADD_OP\n", lexeme);
            break;
        }
        case 22:
        {
            printf("%s\tSUB_OP\n", lexeme);
            break;
        }
        case 23:
        {
            printf("%s\tMULT_OP\n", lexeme);
            break;
        }
        case 24:
        {
            printf("%s\tDIV_OP\n", lexeme);
            break;
        }
        case 25:
        {
            printf("%s\tLEFT_PAREN\n", lexeme);
            break;
        }
        case 26:
        {
            printf("%s\tRIGHT_PAREN\n", lexeme);
            break;
        }
        case 27:
        {
            printf("%s\tEQUAL_OP\n", lexeme);
            break;
        }
        case 30:
        {
            printf("%s\tKEY_READ\n", lexeme);
            break;
        }
        case 31:
        {
            printf("%s\tINC_OP\n", lexeme);
            break;
        }
        case 32:
        {
            printf("%s\tDEC_OP\n", lexeme);
            break;
        }
        case 33:
        {
            printf("%s\tKEY_WRITE\n", lexeme);
            break;
        }
        case 34:
        {
            printf("%s\tLESSER_OP\n", lexeme);
            break;
        }
        case 35:
        {
            printf("%s\tGREATER_OP\n", lexeme);
            break;
        }
        case 36:
        {
            printf("%s\tNEQUAL_OP\n", lexeme);
            break;
        }
        case 37:
        {
            printf("%s\tLEQUAL_OP\n", lexeme);
            break;
        }
        case 38:
        {
            printf("%s\tGEQUAL_OP\n", lexeme);
            break;
        }
        case 39:
        {
            printf("%s\tSEMICOLON\n", lexeme);
            break;
        }
        case 40:
        {
            printf("%s\tKEY_WHILE\n", lexeme);
            break;
        }
        case 41:
        {
            printf("%s\tKEY_DO\n", lexeme);
            break;
        }
        case 42:
        {
            printf("%s\tKEY_OD\n", lexeme);
            break;
        }
        case 99:
        {
            printf("%s\tUNKNOWN\n", lexeme);
            break;
        }

    }
    return nextToken;
} /* End of function lex */






/*P()
 * Parses strings in the language generated by the rule:
 * P::= S
 */
int P()
{
    //Starts from the top and runs s()
    S();
    //prevents the Case of S()S() without a semicolon
    if(nextToken != EOF)
        error();
    printf("\nSyntax Validated");
    exit(0);
}

/*SS()
 * Parses strings in the language generated by the rule:
 * S'::= ;S
 */
void SS()
{
    printf("\nEnter <S'>");
    if(nextToken == SEMICOLON)
    {   lex();
        //if a semicolon is the last token to be processed then it's invalid
        if(nextToken == EOF)
        {
            //changes next token to semicolon to print correct error token.
         nextToken = SEMICOLON;
         error();
        }
            S();
    }
    printf("\nExit <S'>");
}

/*S()
 * Parses strings in the language generated by the rule:
 * S::= V:=ES' | read(V)S' | write(V)S' | while (C) do S odS' | OS' |
 */
void S() {
    printf("\nenter <s>");
    if (nextToken == IDENT) {
        V();
        if (nextToken == ASSIGN_OP) {
            lex();
            E();
            SS();
        }
        else
            error();
    }
    else if (nextToken == DEC_OP || nextToken == INC_OP)
    {
        O();
        SS();
    }
    else if (nextToken == KEY_READ)
    {
        lex();
        if(nextToken == LEFT_PAREN)
        {
            lex();
            V();
            if(nextToken == RIGHT_PAREN)
            {
                lex();
                SS();
            }
            else
                error();
        }
        else
            error();
    }
    else if (nextToken == KEY_WRITE)
    {
        lex();
        if(nextToken == LEFT_PAREN)
        {
            lex();
            V();
            if(nextToken == RIGHT_PAREN)
            {
                lex();
                SS();
            }
            else
                error();
        }
        else
            error();
    }
    else if(nextToken == KEY_WHILE)
    {   lex();
        if(nextToken == LEFT_PAREN)
        {
            lex();
            C();
            if(nextToken == RIGHT_PAREN)
            {
                lex();
                if(nextToken == KEY_DO)
                {
                    lex();
                    S();
                    if(nextToken == KEY_OD)
                    {
                        lex();
                        SS();
                    }
                    else
                        error();
                }
                else
                    error();
            }
            else
                error();
        }
        else
            error();
    }
    //prevents an error if next token is EOF. Terminates with syntax validated.
    else if(nextToken == EOF)
    {   printf("\nSyntax Validated");
        exit(0);
    }
    else
        error();
    printf("\nExit <S>");
}


/*C()
 * Parses strings in the language generated by the rule:
 * C::= E < E | E > E | E = E | E != E | E <= E | E >= E
 */
void C()
{   printf("\nEnter <C>");
    E();
    if(nextToken == LESSER_OP || nextToken == GREATER_OP || nextToken == EQUAL_OP || nextToken == NEQUAL_OP ||
       nextToken == LEQUAL_OP || nextToken == GEQUAL_OP)
    {
        lex();
        E();
    }
    else
        error();

    printf("\nExit <C>");
}

/*E()
 * Parses strings in the language generated by the rule:
 * E' ::= +TE'|-TE'|
 */
void EE()
{   printf("\nEnter <E'>");
    if(nextToken == ADD_OP || nextToken == SUB_OP)
    {   lex();
        T();
        EE();
    }
    printf("\nExit <E'>");
}
/*E()
 * Parses strings in the language generated by the rule:
 * E ::= TE'
 */
void E()
{
    printf("\nEnter <E>");
    T();
    EE();
    printf("\n<Exit E>");
}

/*TT()
 * Parses strings in the language generated by the rule:
 * T ::= *FT'|/FT'
 */
void TT()
{
    printf("\nEnter <T'>");
    if(nextToken == MULT_OP || nextToken == DIV_OP)
    {   lex();
        F();
        TT();
    }
    printf("\nExit <T'>");
}

/*T()
 * Parses strings in the language generated by the rule:
 * T ::= FT'
 */
void T()
{   printf("\nEnter <T>");
    F();
    TT();
    printf("\nExit <T>");
}

/*F()
 * Parses strings in the language generated by the rule:
 * F ::= (E) | O | N | V
 */
void F()
{   printf("\nEnter <F>");

    if(nextToken == LEFT_PAREN)
    {
        lex();
        E();
        if(nextToken == RIGHT_PAREN)
            lex();
        else
            error();
    }
    else if(nextToken == IDENT)
    {
        V();
    }
    else if(nextToken == INT_LIT)
    {
        N();
    }
    else
        O();
    printf("\nExit <F>");
}



/*O()
 * Parses strings in the language generated by the rule:
 * O ::=  ++V | --V
 */
void O()
{
    printf("\nEnter <O>");
    if(nextToken == INC_OP || nextToken == DEC_OP)
    {
        lex();
        V();
    }
    else
        error();


    printf("\nExit <O>");
}

/*N()
 * Parses strings in the language generated by the rule:
 * N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N
 */
void N()
{
    printf("\nEnter <N>");
    if(nextToken == INT_LIT)
    {
        lex();
    }
    else
        error();
    printf("\nExit <N>");

}


/*V()
 * Parses strings in the language generated by the rule:
 * V::= a | b | … | y | z | aV | bV | … | yV | zV
 */
void V()
{
    printf("\nEnter <V>");
    //If the nextToken is IDENT OR LETTER it calls lex().
    if( nextToken == IDENT)
    {
        lex();
    }
    else
        error();
    printf("\nExit <V>");
}


//if syntax is invalid error prints the lexeme and token that caused the error and exits with code 1
static int error()
{
    // switch statement to convert the token ID's to their actual names.
    switch (nextToken) {
        case 10:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: INT_LIT\n", lexeme);
            break;
        }
        case 11:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: IDENT\n", lexeme);
            break;
        }
        case 20:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: ASSIGN_OP\n", lexeme);
            break;
        }
        case 21:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: ADD_OP\n", lexeme);
            break;
        }
        case 22:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: SUB_OP\n", lexeme);
            break;
        }
        case 23:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: MULT_OP\n", lexeme);
            break;
        }
        case 24:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: DIV_OP\n", lexeme);
            break;
        }
        case 25:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: LEFT_PAREN\n", lexeme);
            break;
        }
        case 26:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: RIGHT_PAREN\n", lexeme);
            break;
        }
        case 27:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: EQUAL_OP\n", lexeme);
            break;
        }
        case 30:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: KEY_READ\n", lexeme);
            break;
        }
        case 31:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: INC_OP\n", lexeme);
            break;
        }
        case 32:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: DEC_OP\n", lexeme);
            break;
        }
        case 33:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: KEY_WRITE\n", lexeme);
            break;
        }
        case 34:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: LESSER_OP\n", lexeme);
            break;
        }
        case 35:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: GREATER_OP\n", lexeme);
            break;
        }
        case 36:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: NEQUAL_OP\n", lexeme);
            break;
        }
        case 37:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: LEQUAL_OP\n", lexeme);
            break;
        }
        case 38:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: GEQUAL_OP\n", lexeme);
            break;
        }
        case 39:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: SEMICOLON\n", lexeme);
            break;
        }
        case 40:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: KEY_WHILE\n", lexeme);
            break;
        }
        case 41:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: KEY_DO\n", lexeme);
            break;
        }
        case 42:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: KEY_OD\n", lexeme);
            break;
        }
        case 99:
        {
            printf("Error encounter: the next lexeme was: %s and next token was: UNKNOWN\n", lexeme);
            break;
        }
    }
    exit(1);
}
