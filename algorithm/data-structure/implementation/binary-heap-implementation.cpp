#include<iostream>
using namespace std;

#define MAX_SIZE 100

class MinHeap{
private:
    int heap[MAX_SIZE];
    int heap_size;

public:

    MinHeap() : heap_size(0) {};
    ~MinHeap() {};

    bool isEmpty(){
        if(heap_size == 0) return true;
        else return false;
    }

    bool isFull(){
        if(heap_size == MAX_SIZE) return true;
        else return false;
    }

    int findMin(){
        if(isEmpty()){
            cout << "Heap is Empty." << endl;
            return -1;
        }

        return heap[1];
    }

    void InsertHeap(int element){

        if(isFull()){
            cout << "Heap is full." << endl;
            return ;
        }

        int idx = ++heap_size;

        while(idx > 1 && heap[idx/2] > element){
            heap[idx] = heap[idx/2];
            idx /= 2;
        }
        heap[idx] = element;
    }

    int DeleteHeap(){

        if(isEmpty()){
            cout << "Heap is empty." << endl;
            return -1;
        }

        int min = heap[1];
        int tmp = heap[heap_size--];
        int parent = 1, child = 2;

        while(child <= heap_size){
            if(child + 1 <= heap_size && heap[child] > heap[child+1])
                child++;
            
            if(heap[child] > tmp) 
                break;

            heap[parent] = heap[child];
            parent = child;
            child = parent * 2;

        }
        heap[parent] = tmp;
        return min;
    }

};

int main(){
    MinHeap h;

    h.InsertHeap(9);
    h.InsertHeap(3);
    h.InsertHeap(7);
    h.InsertHeap(4);
    h.InsertHeap(5);

    cout << "min: " << h.findMin() << endl; // min: 3

    h.DeleteHeap();
    cout << "min: " << h.findMin() << endl; // min: 4

    h.DeleteHeap();
    cout << "min: " << h.findMin() << endl; // min: 5

    return 0;
}