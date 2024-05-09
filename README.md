# Recursive-Descent-Parser
A recursive descent syntax parser in C that can validate the syntax of a source code file provided by the
user.<br>
The source code file provided by the user will be written in a new programming language called “DCooke” and is
based upon the following grammar (in BNF):<br>
Tested in Windows and Linux. <br>
Example execution with makefile: recParser test.txt.<br>
Output: Prints syntax validation results.<br>


Language Rules:<br>
P ::= S<br>
S ::= V:=E | read(V) | write(V) | while (C) do S od | O | S;S<br>
C ::= E < E | E > E | E = E | E != E | E <= E | E >= E<br>
E ::= T | E + T | E - T<br>
T ::= F | T * F | T / F<br>
F ::= (E) | O | N | V<br>
O ::= ++V | --V<br>
V ::= a | b | … | y | z | aV | bV | … | yV | zV<br>
N ::= 0 | 1 | … | 8 | 9 | 0N | 1N | … | 8N | 9N<br>
![recParser ex output](https://github.com/jms231/Recursive-Descent-Parser/assets/144720587/05ffe121-f099-4539-8fab-53314774ac96)
