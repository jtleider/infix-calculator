/**
@file main.cpp
@author Julien Leider
@brief This program
allows the user to enter infix expressions, for which
the program displays equivalent postfix expressions
as well as the evaluations of the postfix expressions. The
function main() and the helper function processInfix() are
defined here.
*/

#include <iostream>
#include <sstream>
#include <cstring>
#include "infix.h"
#include "postfix.h"
#include "stack.h"
#include "operator.h"

using namespace std;

void processInfix(string&);

/** Direct program flow. */
int main() {
	string infix, postfix;

	while (true) {
		cout << "Enter infix expression (Ctrl-C to quit): ";
		getline(cin, infix, '\n');
		processInfix(infix);
		cout << "Infix expression after preprocessing: " << infix << endl;
		postfix = infixToPostfix(infix);
		cout << "Equivalent postfix expression: " << postfix << endl;
		cout << "This expression evaluates to " << evalPostfix(postfix) << "." << endl;
	}

	return 0;
}

/** Process infix expression to ensure correct format. The
  * resulting expression may be malformed if the input is malformed;
  * otherwise, it will be suitable as input for infixToostfix().
  * @param infix Infix expression to process.
  */
void processInfix(string& infix) {
	istringstream iss(infix);
	stringstream oss;
	Operator op; double value;
	bool opLast = true; // Did we last read an operator (rather than a value)?

	iss.exceptions(ios_base::failbit);
	while (!(iss.tellg() == iss.str().length())) {
		// We go through whitespace manually so we can handle '+' and '-'.
		while (isspace(iss.peek())) {
			iss.ignore();
			if (iss.tellg() == iss.str().length()) {
				break;
			}
		}
		// Since cin could read '+' or '-' as part of a number, rather than
		// as operators, we handle them as a special case.
		if (iss.peek() == '+' || (iss.peek() == '-' && !opLast)) {
			iss >> op;
			oss << op << ' ';
			opLast = true;
			if (iss.tellg() == iss.str().length()){
				break;
			}
		}
		try { // Try to read a value.
			iss >> value;
			oss << value << ' ';
			opLast = false;
		} catch (ios_base::failure) { // This is not a value, so try to read an operator.
			iss.clear();
			try {
				iss >> op;
				oss << op << ' ';
			} catch (OperatorException) {
				cerr << op.getSym() << " at position " << iss.tellg() << " in string is not a digit and is not a recognized operator." << endl
						<< "Unable to process infix expression \"" << infix << "\"." << endl;
				return;
			}
			if (op.getSym() == ')') {
				opLast = false;
			} else {
				opLast = true;
			}
		}
	}

	infix = oss.str().substr(0, oss.str().length() - 1);
}
