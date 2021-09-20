#include<iostream>
using namespace std;

#define MAX_SIZE 6

template <typename T>
class Queue{
private:
    T queue[MAX_SIZE + 2];
    int front, rear;

public:
    Queue() : front(0), rear(0) {}; // 생성자
    ~Queue() {}; // 소멸자

    // Queue가 비었으면 true, 그렇지 않으면 false 반환
    bool IsEmpty(){
        if(front == rear) return true;
        else return false;
    }

    // Queue가 꽉 찼으면 true, 그렇지 않으면 false 반환
    bool IsFull(){
        if((rear+1) % MAX_SIZE == front) return true;
        else return false;
    }

    // rear를 한 칸 늘리고 데이터 저장
    void enqueue(T val){
        if(IsFull()){
            cout << "Queue is Full." << endl;
            return ;
        }
        rear = (rear+1) % MAX_SIZE;
        queue[rear] = val;
    }

    // front를 한 칸 늘리고 기존 front 값 반환
    T dequeue(){
        if(IsEmpty()){
            cout << "Queue is Empty." << endl;
            return 0;
        }
        T tmp = queue[front];
        front = (front+1) % MAX_SIZE;
        return tmp;
    }

    // Queue에 저장한 값 출력
    void show(){
        if(IsEmpty()){
            cout << "Queue is Empty." << endl;
            return ;
        }

        int cur;
        for(int i=0; i<MAX_SIZE; i++){
            cur = (front+i+1) % MAX_SIZE;
            cout << queue[cur] << " ";
            if(cur == rear) break;
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

}