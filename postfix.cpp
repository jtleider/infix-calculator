/**
@file postfix.cpp
@author Julien Leider
@brief This file includes the definition of the
function evalPostfix() for evaluating
postfix expressions.
*/

#include <iostream>
#include <string>
#include <sstream>
#include "postfix.h"
#include "stack.h"
#include "operator.h"

using namespace std;

/** Evaluate a postfix expression.
  * @param postfix Postfix expression.
  * @return Value of postfix expression. If the expression
is malformed, print an error message to stderr and return 0.
  */
double evalPostfix(string postfix) {
	istringstream iss(postfix);
	Stack<double> valStack;
	Operator op;
	double valueLeft, valueRight;

	iss.exceptions(ios_base::failbit);
	while (iss.tellg() < iss.str().length() - 1) { // We read to the end of the expression.
		try { // Try to read this as a value.
			iss >> valueLeft;
			valStack.push(valueLeft);
		} catch (ios_base::failure) { // This is not a value, so try to read this as an operator.
			iss.clear();
			if (iss.tellg() != 0) {
				iss.unget(); // Put any '+' or '-' taken by the last extraction back in the stream.
			}
			try {
				iss >> op;
			} catch (OperatorException) {
				cerr << "Error at position " << iss.tellg() << ". Encountered input that is neither value nor operator." << endl
						<< "Unable to evaluate postfix expression \"" << postfix << "\"." << endl;
				return 0;
			}
			try { // Try to apply the operator.
				valueRight = valStack.top();
				valStack.pop();
				valueLeft = valStack.top();
				valStack.pop();
			} catch (StackException) {
				cerr << "Postfix expression \"" << postfix << "\" is malformed, "
						<< "as indicated by stack error at position " << iss.tellg() << " in string." << endl;
				return 0;
			}
			valStack.push(op(valueLeft, valueRight));
		}
	}

	try { // The result should be at the top of the stack, assuming a well-formed expression.
		return valStack.top();
	} catch (StackException) {
		cerr << "Postfix expression \"" << postfix << "\" is malformed, "
				<< "as indicated by stack error at position " << iss.tellg() << " in string." << endl;
		return 0;
	}

}
