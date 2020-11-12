# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
private:
	stack<T> stk;
	stack<T> mins;
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return stk.size() == 0;
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    *novo = stk.top();
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if(!stk.empty()){
        if(stk.top() == mins.top()){
            mins.pop();
        }
        stk.pop();
    }
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    if(mins.empty()){
       mins.push(val);
    }
    else if(val <= mins.top()){
        mins.push(val);
    }
    stk.push(val);
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    T *novo = new T();
    *novo = mins.top();
    return *novo;
}

