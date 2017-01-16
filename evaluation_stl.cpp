// infix expression evaluation
// implemented with STL vector
// evalues expression with multiple digit numbers, * / + - and {} [] () paratheis
// http://en.wikipedia.org/wiki/Shunting_yard_algorithm
// assume the expression is well formatted with balanced braces. 

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <string>
#include <cassert>
using namespace std;

//----------------------------------------------------------------
// Returns true if the string contains only digit characters
bool isNumber(string str)
{
    for(int i=0; i<str.length(); i++)
    {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------
// Returns true if op1 has higher precedence than op2. For the
// purpose of the shunting-yard algorithm, brace characters
// are treated as being of lowest priority.
bool isHigherPrecedence(string op1, string op2)
{
    if( (op1 == "*" || op1 == "/") && (op2 != "/" && op2 != "*"))
        return true;
    else if( op2 == "(" || op2 == "[" || op2 == "{" )
        return true;
    else return false;
}

//----------------------------------------------------------------
// Given a digit character ch and a stringstream ss of characters
// that follow it, returns the largest string from ss that
// contains only digits
string completeNumberToken(char ch, stringstream &ss)
{
    stringstream convert;
    
    convert << ch;
    while (isdigit(ss.peek()))
    {
        ss.get(ch);
        convert << ch;
    }
    return convert.str();
}

//----------------------------------------------------------------
// Returns the open-brace equivalent for ')', '>', '}', or ']'
char openBraceFor(char closeBrace)
{
    if (closeBrace == ')')
        return '(';
    else
        return closeBrace - 2;
}

//----------------------------------------------------------------
// Generates a stack of string tokens representing postfix
// notation for the input line
void generateRPN(string line, stack<string> &postfix)
{
    stack<string> opStack;
    stringstream ss(line);
    stringstream convert;  // for converting to string token
    string token, temp;
    
    char ch;  // placeholder char
    char openBraceChar;

    while (ss.get(ch))
    {
        // If space, continue
        if (isspace(ch))
            continue;

        // clean up convert buffer
        convert.str("");
        convert.clear();

        // If number;
        // construct the number by looking one char ahead into the stream
        if (isdigit(ch))
        {
            postfix.push(completeNumberToken(ch, ss));
            continue;
        }

        // non numbers
        else
        {
            convert << ch;
            token = convert.str();

            switch (ch)
            {
                case '(': case '[': case '{':
                    opStack.push(token);
                    break;

                case ')': case ']': case '}':
                    openBraceChar = openBraceFor(ch);
                    while (!opStack.empty() && (temp = opStack.top())[0] != openBraceChar)
                    {
                        if ( (temp == "*") || (temp == "/") || (temp == "+") || (temp == "-") )
                        {
                            postfix.push(temp);
                            opStack.pop();
                        }
                    }
                    opStack.pop(); // pop open brace
                    break;

                case '*': case '/': case '+': case '-':
                    while( !opStack.empty() )
                    {
                        temp = opStack.top();
                        if ( !isHigherPrecedence(token, temp) )
                        {
                            postfix.push(temp);
                            opStack.pop();
                        }
                        else
                            break;
                    }
                    opStack.push(token);
                    break;
            }
        }
    }
    // for remaining operators
    while (!opStack.empty())
    {
        postfix.push( opStack.top() );
        opStack.pop();
    }
}

//----------------------------------------------------------------
// Returns a the result of evaluating the passed postfix token
// stack as a decimal string
string evaluateRPN(stack<string> &postfix)
{
    stringstream convert;  // for converting to string token
    string temp;
    stack<string> tempStack;
    stack<string> testStack;
    stack<string> postfixForward;

    // put postfix stack in correct order for evaluation
    while(!postfix.empty())
    {
        temp = postfix.top();
        //cout << temp << " ";
        postfix.pop();
        postfixForward.push(temp);
        testStack.push(temp);
    }

    int ans, op1, op2;
    string answer;
    while(!postfixForward.empty())
    {
        temp = postfixForward.top();
        postfixForward.pop();

        // is number
        if( isNumber(temp) ) {
            tempStack.push(temp);
        } else {   // is operator
            op1 = atoi( tempStack.top().c_str() );
            tempStack.pop();
            op2 = atoi( tempStack.top().c_str() );
            tempStack.pop();

            switch(temp[0])
            {
            case '+': ans = op1 + op2; break;
            case '-': ans = op2 - op1; break;
            case '*': ans = op1 * op2; break;
            case '/': ans = op2 / op1; break;
            default: break;
            }
            convert.str("");
            convert.clear();
            convert << ans;
            answer = convert.str();
            tempStack.push(answer);
        }
    }

    answer = tempStack.top();
    tempStack.pop();
    assert(tempStack.empty());
    return answer;
}
