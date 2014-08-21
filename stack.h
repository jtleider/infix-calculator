/**
@file stack.h
@author Julien Leider
@brief This file includes the definition of the
class Stack and the class StackException.
*/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>
#include <vector>
#include <string>

/** A simple templated stack. */
template<typename T>
class Stack {
public:
	void push(T);
	void pop();
	T top();
	bool empty();
private:
	std::vector<T> stack;
};

/** Represent an exception in the use of the class Stack. */
class StackException: public std::runtime_error {
public:
	/** Constructor. */
	StackException(const std::string& msg = ""): runtime_error(msg) {}
};

#include "stack.cpp"

#endif
