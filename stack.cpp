/**
@file stack.cpp
@author Julien Leider
@brief This file includes the definitions of the
methods push(), pop(), top(), and empty()
of the class Stack.
*/

/** Push an object on stack.
  * @param element Object to push on stack.
  */
template<typename T>
void Stack<T>::push(T element) {
	stack.push_back(element);
}

/** Pop an object off stack.
  * @throws StackException
  */
template<typename T>
void Stack<T>::pop() {
	if (empty()) {
		throw StackException("Attempting to pop an empty stack.");
	}
	stack.pop_back();
}

/** Return object on top of stack.
  * @return Object on top of stack.
  * @throws StackException
  */
template<typename T>
T Stack<T>::top() {
	if (empty()) {
		throw StackException("Attempting to top an empty stack.");
	}
	return *(stack.end()-1);
}

/** Determine if stack is empty. */
template<typename T>
bool Stack<T>::empty() {
	return stack.empty();
}
