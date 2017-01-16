# Expression_evaluator

write a simple expression evaluator to evaluate infix arithmetic expressions. In this
assignment, an expression is a sequence of tokens. A token can be one of the following:
- An operand, which is an integer number (without + or – sign).
- An operator: +, -, * or / (integer division),
- Parentheses which include three types of braces ( ), [ ] and { }.
Your program will repeatedly prompt the user to type in an expression from keyboard; the
result will be output to the screen until the user types “exit” or control-d to terminate the
input.
You can assume all tokens are valid, all numbers are integers and all braces are balanced.
Spaces are allowed in the expression. Although all operands are positive, the expression may
be evaluated to a negative result.
Below is a sample run from the command line prompt.
$ ./evaluation
Expression: 1+2
Answer: 3
Expression: 1* ( 2 + 3 )
Answer: 5
Expression: (6 - 2 )*10 + 2
Answer: 42
Expression: [(6 - 2)* 10 + 2 ]/( 4 + 2 )
Answer: 7
Expression: 10 - [(6 - 2) * 10 + 2 ] / ( 4 + 2 )
Answer: 3
Expression: 10 - [ ( 3 - 2 ) * 10 ] / 5
Answer: 8
Expression:  newline here
Expression: exit
Empty lines typed at the prompt are ignored.
Requirements:
1. You must evaluate the given infix expression by first converting it to a postfix expression,
and then evaluate the postfix expression. Here you will find an explanation of the
algorithm that converts infix to postfix:
http://en.wikipedia.org/wiki/Shunting_yard_algorithm
You will need to modify the algorithm in order to supports three types of braces. Once
you have the postfix expression equivalent to the input expression, its evaluation is
straightforward. The postfix evaluation algorithm is described here
http://en.wikipedia.org/wiki/Reverse_Polish_notation
2. You are allowed to use appropriate C++ STL containers in this class.
3. You may also use other libraries, such as <cctype> for alpha/digit check and
<cstdlib> for alpha to digit/float conversion.
Note: The input stream is not space-delimited, so you would need to read the user input one
character at a time. While this works fine for all single character tokens, it could fail when the
input number have multiple digits. The stream’s peek() method can be used on the input
stream to look one character ahead and thus help us determine when a number ends. 
