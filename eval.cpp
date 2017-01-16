// infix expression evaluation
// implemented with STL vector
// evalues expression with multiple digit numbers, * / + - and {} [] () paratheis
// http://en.wikipedia.org/wiki/Shunting_yard_algorithm
// assume the expression is well formatted with balanced braces. 

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "stack.h"
#include <queue>
#include <string>
#include <cassert>
using namespace std;

void generateRPN(string line, stack &postfix);
string evaluateRPN(stack &postfix);

//----------------------------------------------------------------
int main(int argc, char ** argv)
{
    string line;
    cout << "Expression: ";
    while ( getline(cin, line) )
    {
        // skip empty line
        if (line.length() == 0)
            continue;

        stack postfix;

        generateRPN(line, postfix);
        
        cout << "Answer: " << evaluateRPN(postfix) << endl;
        line.clear();
        cout << "Expression: ";
    }
    return 0;
}
