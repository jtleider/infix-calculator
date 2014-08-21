/**
@file infix.cpp
@author Julien Leider
@brief This file includes the definition of the
function infixToostfix(), for converting
an infix expression to a postfix expression.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "infix.h"
#include "stack.h"
#include "operator.h"

using namespace std;

/** Convert an infix expression to a postfix expression.
  * We assume the infix expression is formatted with exactly
  * one space on the side of each operator and no space after
  * a unary minus, and that there is no trailing whitespace,
  * as would be the case if the input had been
  * processed by processInfix(). No systematic attempt is made
  * to validate the input; in general, the result of converting
  * a malformed infix expression will be a malformed postfix
  * expression, and the program may not warn about this.
  * @param infix Infix expression.
  */
string infixToPostfix(string infix) {
	ostringstream pf;
	istringstream iss(infix);
	Stack<Operator> opStack;
	Operator op;
	double value;

	iss.exceptions(ios_base::failbit);
	while (!(iss.tellg() == iss.str().length())) {
		try { // Try to extract a value.
			iss >> value;
			if (value >= 0) {
				pf << value << ' ';
			} else {
				pf << "0 " << -value << " - ";
			}
		} catch (ios_base::failure) { // This is not a value, so try to extract an operator.
			iss.clear();
			if (iss.tellg() != 0) {
				iss.unget(); // Get back any '+' or '-' that the previous extraction may have taken.
			}
			try {
				iss >> op;
			} catch (OperatorException) {
				cerr << "Error at position " << iss.tellg() << ". Encountered input that is neither value nor operator." << endl
						<< "Unable to convert infix expression \"" << infix << "\" to postfix." << endl;
				return "";
			}
			if (op.getSym() == '(') { // opening parenthesis
				opStack.push(op);
				continue;
			} else if (op.getSym() == ')') { // closing parenthesis
				while (!opStack.empty()) {
					if (opStack.top().getSym() == '(') {
						opStack.pop();
						break;
					} else {
						pf << opStack.top().getSym() << ' ';
						opStack.pop();
					}
				}
			} else { // standard operator
				while (!opStack.empty() && ((op.getPrec() < opStack.top().getPrec()) ||
						(op.getPrec() == opStack.top().getPrec() && op.getSym() != '^'))) {
					pf << opStack.top().getSym() << ' ';
					opStack.pop();
				}
				opStack.push(op);
			}
		}
	}

	while (!opStack.empty()) {
		pf << ' ' << opStack.top().getSym() << ' ';
		opStack.pop();
	}

	return pf.str();
}

