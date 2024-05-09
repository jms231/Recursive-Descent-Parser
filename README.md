# Recursive-Descent-Parser
A recursive descent syntax parser in C that can validate the syntax of a source code file provided by the
user.
The source code file provided by the user will be written in a new programming language called “DCooke” and is
based upon the following grammar (in BNF):
Tested in Windows and Linux. 
Example execution with makefile: recParser test.txt.
Output: Prints syntax validation results.


Language Rules:
P ::= S
S ::= V:=E | read(V) | write(V) | while (C) do S od | O | S;S
C ::= E < E | E > E | E = E | E != E | E <= E | E >= E
E ::= T | E + T | E - T
T ::= F | T * F | T / F
F ::= (E) | O | N | V
O ::= ++V | --V
V ::= a | b | … | y | z | aV | bV | … | yV | zV
N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N
![recParser ex output](https://github.com/jms231/Recursive-Descent-Parser/assets/144720587/05ffe121-f099-4539-8fab-53314774ac96)
