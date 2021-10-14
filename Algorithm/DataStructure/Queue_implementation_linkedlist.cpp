#include<iostream>
using namespace std;

#define MAX_SIZE 5

template <typename T>
struct Node{
    T Data;
    struct Node<T> *next = NULL;
};

template <typename T>
class Queue{
private:
    struct Node<T> *front, *rear;
    int size = 0;

public:
    Queue() : front(NULL), rear(NULL), size(0) {}; // 생성자
    ~Queue() {}; // 소멸자

    // Queue가 비었으면 true, 그렇지 않으면 false 반환
    bool IsEmpty(){
        if(rear == NULL) return true;
        else return false;
    }

    // Queue가 꽉 찼으면 true, 그렇지 않으면 false 반환
    bool IsFull(){
        if(size == MAX_SIZE) return true;
        else return false;
    }

    // rear를 한 칸 늘리고 데이터 저장
    void enqueue(T val){
        if(IsFull()){
            cout << "Queue is Full." << endl;
            return ;
        }

        Node<T> *newNode = new Node<T>();
        newNode->Data = val;
        newNode->next = NULL;

        if(IsEmpty()){
            front = newNode;
            rear = newNode;
        }
        else{
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // front를 한 칸 늘리고 기존 front 값 반환
    T dequeue(){
        if(IsEmpty()){
            cout << "Queue is Empty." << endl;
            return 0;
        }

        T tmp = front->Data;
        Node<T> *ptr = front;

        if(size == 1){
            front = NULL;
            rear = NULL;
        }
        else{
            front = front->next;
        }

        delete ptr;
        size--;

        return tmp;
    }

    // Queue에 저장한 값 출력
    void show(){
        if(IsEmpty()){
            cout << "Queue is Empty." << endl;
            return ;
        }

        Node<T> *ptr = front;
        while(ptr != NULL){
            cout << ptr->Data << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
};

int main(){

    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6); // Queue is Full
    queue.show(); // 1, 2, 3, 4, 5

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.show(); // 4, 5

    queue.enqueue(6);
    queue.enqueue(7);
    queue.enqueue(8);
    queue.enqueue(9); // Queue is Full
    queue.show(); // 4, 5, 6, 7, 8

    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue();
    queue.dequeue(); // Queue is Empty

}