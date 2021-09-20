#include<iostream>
using namespace std;

template <typename T>
struct Node{
    T Data;
    struct Node<T> *next = NULL;
    struct Node<T> *prev = NULL;
};

template <typename T>
class Stack{
private:
    Node<T> *top, *btm;
    int size = 0;

public:
    Stack() : top(NULL), btm(NULL) {};
    ~Stack() {};

    // Stack이 비었으면 true, 그렇지 않으면 false
    bool IsEmpty(){
        if(top == NULL) return true;
        else return false;
    }

    // Stack의 top에 val 추가
    void push(T val){
        // newNode 생성
        Node<T> *newNode = new Node<T>();
        newNode->Data = val;
        newNode->next = NULL;
        newNode->prev = top;

        // Stack이 비었다면 btm, top 모두 newNode 지정
        if(top==NULL){
            btm = newNode;
            top = newNode;
        }
        // Stack이 비어있지 않다면 top의 next에 newNode 지정
        else{
            top->next = newNode;
            top = newNode;
        }
        size++;
    }

    // Stack의 top 반환 및 제거
    T pop(){
        // Stack이 비었을 경우 메세지 출력
        if(IsEmpty()==true){
            cout << "Stack is Empty." << endl;
            return 0;
        }

        Node<T> *ptr = top;
        T tmp = top->Data;

        // 만약 Stack에 데이터가 1개라면 top에 NULL 저장
        if(top->prev == NULL){
            btm = NULL;
            top = NULL;
        }
        // 그렇지 않다면 top 직전 노드를 top으로 지정
        else{
            Node<T> *prev = new Node<T>();
            top = top->prev;
            top->next = NULL;
        }

        // 기존 top이 저장된 주소 메모리 해제
        delete ptr;
        size--;

        return tmp;
    }
    
    // Stack의 top 반환 
    T peek(){
        // Stack이 비었을 경우 메세지 출력
        if(IsEmpty()==true){
            cout << "Stack is Empty." << endl;
            return 0;
        }
        //top 데이터 반환
        return top->Data;
    }

    // Stack 전체 데이터 출력
    void show(){
         // Stack이 비었을 경우 메세지 출력       
        if(IsEmpty()==true){
            cout << "Stack is Empty." << endl;
            return;
        }
        //btm부터 top까지 탐색하며 데이터 출력
        Node<T> *ptr = btm;
        while(ptr!=NULL){
            cout << ptr->Data << " ";
            ptr = ptr->next;
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
    stack.show(); // 1, 2, 4, 5, 6

    stack.pop(); 
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop(); 
    stack.pop(); // Stack is Empty

    return 0;
}