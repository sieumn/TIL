// Linked List 구현
// 2021.09.19

#include<iostream>
using namespace std;

template <typename T>
struct Node{
public:
    T data;
    struct Node<T> *next = NULL;
};

template <typename T>
class SingleLL{
private:
    Node<T> *head; //첫 번째 node
    Node<T> *tail; //마지막 node
    int size = 0; //list 크기

public:
    SingleLL() : head(NULL), tail(NULL) {}; //생성자
    ~SingleLL() {} //소멸자

    //탐색: List에서 특정 값 검색 후 index 반환 (없다면 -1 반환)
    int searchNode(T target){

		Node<T> *ptr = head;
        int index = 0;

        while(ptr != NULL){
            index++;
            if(ptr->data == target){
                return index;
            }
            ptr = ptr->next;
        }
        return -1;
    }

    //삽입: List의 head에 node 삽입
    bool addNodeAtHead(T newData){

        //새로운 node 생성
        Node<T> *newNode = new Node<T>();
        newNode->data = newData;
        newNode->next = NULL;
        size++;

        //데이터가 없을 경우 head, tail에 추가
        if(head == NULL){
            head = newNode;
            tail = newNode;
            return true;
        }
        //head에 추가
        else{
            newNode->next = head;
            head = newNode;
            return true;
        }
        
        return false;
    }

    //삽입: List의 tail에 node 삽입
    bool addNodeAtTail(T newData){
        
        //새로운 node 생성
        Node<T> *newNode = new Node<T>();
        newNode->data = newData;
        newNode->next = NULL;
        size++;

        //데이터가 없을 경우 head, tail에 추가
        if(head == NULL){
            head = newNode;
            tail = newNode;
            return true;
        }
        //tail에 추가
        else{
            tail->next = newNode;
            tail = newNode;
            return true;
        }

        return false;
    }
    
    //삽입: 특정 index 위치에 node 삽입
    bool addNode(int index, T newData){

        if(index < 0 || index > size) return false; //index 범위가 잘못된 경우 종료
        if(index==0) return addNodeAtHead(newData); //index가 0일 경우 head에 추가
        if(index==size) return addNodeAtTail(newData); //index가 마지막일 경우 tail에 추가

        Node<T> *ptr = head;

        //새로운 node 생성
        Node<T> *newNode = new Node<T>();
        newNode->data = newData;
        newNode->next = NULL;

        //index-1만큼 이동하여 원하는 위치 전 node까지 이동
        for(int i = 0; i < index-1; i++){
            ptr = ptr->next;
        }
        newNode->next = ptr->next;
        ptr->next = newNode;
        size++;

        return true;
    }

    //삭제: 첫 번째 node 삭제
    bool RemoveNodeAtHead(){
        
        if(size==0) return false;

        Node<T> *ptr = head;

        head = head->next;
        size--;
        delete ptr;        

        return true;
    }

    //삭제: 마지막 node 삭제
    bool RemoveNodeAtTail(){

        if(size==0) return false;
        
        Node<T> *ptr = head;
        Node<T> *prev = new Node<T>();
    
        while(ptr->next != NULL){
            prev = ptr;
            ptr = ptr->next;
        }

        tail = prev;
        tail->next = NULL;
        size--;
        delete ptr;

        return true;
    }

    //삭제: 특정 데아터 값을 갖는 node 삭제
    bool RemoveNode(T target){

        //target이 head나 tail이라면 해당 함수 호출
        if(size==0) return false;
        if(head->data == target) return RemoveNodeAtHead();
        if(tail->data == target) return RemoveNodeAtTail();

        Node<T> *ptr = head;
        Node<T> *prev = head;

        //target node와 target node의 prev node 모두 필요
        while(ptr->next != NULL){
            if(ptr->data == target){
                prev->next = ptr->next;
                size--;
                delete ptr;

                return true;
            }
            prev = ptr;
            ptr = ptr->next;
        }        

        return false;
    }

    // 전체 Linked List 동적 할당 제거
    void deleteList(){
        Node<T> *ptr = head;
        while(ptr != NULL){
            head = ptr->next;
            delete ptr;

            ptr = head;
        }
        delete head;
        size = 0;
    }

    //List의 size 반환
    int getsize(){
        return size;
    }

    //List 전체 요소 출력
    void print(){

        cout << "head: " << head->data << ", tail: " << tail->data << ", size: " << size << endl;
        Node<T> *ptr = head;
        while(ptr != NULL){
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << endl << "----------------------" << endl;
    }
};

int main(){

    SingleLL<int> List;

    List.addNodeAtHead(3);
    List.addNodeAtHead(2);
    List.addNodeAtHead(1);
    List.print();

    List.addNodeAtTail(4);
    List.addNodeAtTail(5);
    List.addNodeAtTail(6);
    List.print();

    List.addNode(2, 7);
    List.addNode(0, 8);
    List.addNode(8, 9);
    List.print();

    List.RemoveNode(8);
    List.RemoveNode(3);
    List.RemoveNode(9);
    List.print(); 

    List.RemoveNodeAtHead();
    List.print(); 

    List.RemoveNodeAtTail();
    List.print(); 

    List.deleteList();
    cout << List.getsize();

    return 0;
}