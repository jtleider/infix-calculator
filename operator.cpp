/**
@file operator.cpp
@author Julien Leider
@brief This file includes the definitions
of the constructor Operator(char) and
the overloaded function call operator
for the class Operator. It also defines
the overloaded stream insertion and
extraction operators for Operator objects.
*/

#include <iostream>
#include <cctype>
#include <cmath>
#include "operator.h"

using namespace std;

/** Constructor taking the symbol of the operator.
  * @param sym Symbol of appropriate operator.
  * @throws OperatorException
  */
Operator::Operator(char sym): sym(sym) {
	switch(sym) {
	case '-':
		prec = 0;
		break;
	case '+':
		prec = 0;
		break;
	case '%':
		prec = 1;
		break;
	case '/':
		prec = 1;
		break;
	case '*':
		prec = 1;
		break;
	case '^':
		prec = 2;
		break;
	case '(':
	case ')':
		prec = -1; // We do not assign a precedence to parentheses.
		break;
	default:
		throw OperatorException(std::string("Unknown operator: ").append(1,sym));
		break;
	}
}

/** Overloaded function call operator.
  * @param left Left value for operation.
  * @param right Right value for operation.
  * @return Result of applying operation to given arguments.
  * @throws OperatorException
  */
double Operator::operator()(double left, double right) const {
	switch (getSym()) {
	case '-':
		return left - right;
		break;
	case '+':
		return left + right;
		break;
	case '%':
		if (right == 0) {
			throw OperatorException("Attempting to take remainder of division by zero.");
		}
		return fmod(left, right);
		break;
	case '/':
		if (right == 0) {
			throw OperatorException("Attempting to divide by zero.");
		}
		return left / right;
		break;
	case '*':
		return left * right;
		break;
	case '^':
		return std::pow(left, right);
		break;
	}
	throw OperatorException("Attempting to use uninitialized operator.");
	return 0;
}

/** Overloaded stream extraction for Operator objects. */
istream& operator>>(istream& is, Operator& op) {
	char sym;

	// Ignore whitespace before the operator.
	while (isspace(is.peek())) {
		is.ignore();
	}

	is >> sym;
	op = Operator(sym);

	return is;
}

/** Overloaded stream insertion operator for Operator objects. */
ostream& operator<<(ostream& os, const Operator& op) {
	os << op.getSym();
	return os;
}
