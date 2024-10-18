# include <iostream>
# include <stack>
using namespace std;

template <class T>
class StackExt {
	stack<T> values;
	stack<T> minimums;
public:
	StackExt() {};
	bool empty() const; 
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

//TODO
template <class T>
bool StackExt<T>::empty() const {
	return values.empty();
}

//TODO
template <class T> 
T& StackExt<T>::top() {
    return values.top();
}

//TODO
template <class T> 
void StackExt<T>::pop() {
    T val = values.top();
    values.pop();
    if (minimums.top() == val) {minimums.pop();}
}

//TODO
template <class T> 
void StackExt<T>::push(const T& val) {
    values.push(val);
    if (!minimums.empty()) {if (val <= minimums.top()) {minimums.push(val);}}
    else {minimums.push(val);}
}

//TODO
template <class T> 
T& StackExt<T>::findMin() {
    return minimums.top();
}

