#include<iostream>
using namespace std;

#define MAX_SIZE 5 // Stack 사이즈 정의

template <typename T>
class Stack{
private:
    T stack[MAX_SIZE + 2];
    int top = -1;

public:
    Stack() : top(-1) {};
    ~Stack() {};

    // Stack이 비었으면 true, 그렇지 않으면 false
    bool IsEmpty(){
        if(top == -1) return true;
        else return false;
    }

    // Stack이 MAX_SIZE까지 찼으면 true, 그렇지 않으면 false
    bool IsFull(){
        if(top == MAX_SIZE-1) return true;
        else return false;
    }

    // Stack의 top에 val 추가
    void push(T val){
        if(IsFull()==true){
            cout << "Stack is Full." << endl;
            return;
        }
        stack[++top] = val;
    }

    // Stack의 top 반환 및 제거
    T pop(){
        if(IsEmpty()==true){
            cout << "Stack is Empty." << endl;
            return 0;
        }
        return stack[top--];
    }

    // Stack의 top 반환 
    T peek(){
        if(IsEmpty()==true){
            cout << "Stack is Empty." << endl;
            return 0;
        }
        return stack[top];
    }

    // Stack 전체 데이터 출력
    void show(){
        if(IsEmpty()==true){
            cout << "Stack is Empty." << endl;
            return;
        }
        for(int i = 0; i < top+1; i++){
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

int main(){

    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.show(); // 1, 2, 3

    cout << "Peek: " << stack.peek() << endl;

    stack.pop();
    stack.show(); // 1, 2

    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7); // Stack is Full
    stack.show(); // 1, 2, 4, 5, 6

    stack.pop(); 
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop(); 
    stack.pop(); // Stack is Empty

    return 0;
}