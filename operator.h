/**
@file operator.h
@author Julien Leider
@brief This function defines the class Operator
and the class OperatorException.
*/

#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include <stdexcept>
#include <string>

/** Represent a binary arithmetical operator. */
class Operator {
public:
	/** No-parameter constructor. */
	Operator(): sym(' '), prec(-1) {}
	Operator(char sym);
	double operator()(double, double) const;
	/** Accessor method for private variable sym. */
	char getSym() const { return sym; }
	/** Accessor method for private variable prec,
	representing operator precedence. Value is -1 is
	operation has not been specified or the
	operator is a parenthesis. */
	int getPrec() const { return prec; }
private:
	char sym;
	int prec;
};

/** Represent an exception in using class Operator. */
class OperatorException: public std::runtime_error {
public:
	/** Constructor. */
	OperatorException(const std::string& msg = ""): std::runtime_error(msg) {}
};

std::istream& operator>>(std::istream&, Operator&);
std::ostream& operator<<(std::ostream&, const Operator&);

#endif
