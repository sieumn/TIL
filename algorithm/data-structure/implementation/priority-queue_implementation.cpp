#include<iostream>
using namespace std;

#define MAX_SIZE 100

class PQ{
private:
    int maxheap[MAX_SIZE + 1];
    int size;

public:
    PQ() : size(0) {};
    ~PQ() {};

    // heap이 비어있으면 true, 그렇지 않으면 false 반환
    bool isEmpty(){
        if(size == 0) return true;
        else return false;
    }

    // heap이 꽉 찼으면 true, 그렇지 않으면 false 반환
    bool isFull(){
        if(size == MAX_SIZE) return true;
        else return false;
    }

    // 데이터 삽입. 가장 마지막 노드에 새로운 데이터를 입력하고 위로 올리며 자리를 찾는다.
    void push(int val){
        if(isFull()){
            cout << "PQ is full." << endl;
            return ;
        }

        int child = ++size;
        int parent = child / 2;

        while(parent >= 1){
            if(maxheap[parent] < val){
                maxheap[child] = maxheap[parent];
                child = parent;
                parent = child / 2;
            }
            else break;
        }
        maxheap[child] = val;
    }

    // 최댓값은 항상 root에 위치
    int top(){
        if(isEmpty()){
            cout << "PQ is empty." << endl;
            return -1;
        }
        return maxheap[1];
    }

    // 데이터 삭제. 가장 마지막 노드를 root에 두고 아래로 내리며 자리를 찾는다.
    int pop(){
        if(isEmpty()){
            cout << "PQ is empty." << endl;
            return -1;
        }
        int top = maxheap[1];
        int val = maxheap[size--];

        int parent = 1;
        int child = parent * 2;

        while(child <= size){
            if(child < size && maxheap[child] < maxheap[child+1])
                child++;
            
            if(val < maxheap[child]){
                maxheap[parent] = maxheap[child];
                parent = child;
                child = parent * 2;
            }
            else break;
        }
        maxheap[parent] = val;

        return top;
    }

    // heap 배열에 있는 모든 원소 출력
    void show(){
        if(isEmpty()){
            cout << "PQ is empty." << endl;
            return ;
        }
        for(int i = 1; i <= size; i++)
            cout << maxheap[i] << " ";
        cout << endl;

        return ;
    }
};

int main(){

    PQ pq;
    pq.push(1);
    pq.show(); // 1

    pq.push(4);
    pq.show(); // 4 1
    
    pq.push(7);
    pq.show(); // 7 1 4
    
    pq.push(5);
    pq.show(); // 7 5 4 1
    
    pq.push(2);
    pq.show(); // 7 5 4 1 2
    
    pq.push(6);
    pq.show(); // 7 5 6 1 2 4
    
    pq.push(9);
    pq.show(); // 9 5 7 1 2 4 6

    pq.pop();
    pq.show(); // 7 5 6 1 2 4

    pq.pop();
    pq.show(); // 6 5 4 1 2

    pq.pop();
    pq.show(); // 5 2 4 1

    pq.pop();
    pq.show(); // 4 2 1

    return 0;
}