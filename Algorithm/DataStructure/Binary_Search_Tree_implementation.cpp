#include<iostream>
using namespace std;

#define MAX_SIZE 100

// BST의 각 node 정의
class node{
public:
    int key;
    node *left, *right;

    node() : key(0), left(NULL), right(NULL) {}; // 생성자
    node(int k) : key(k), left(NULL), right(NULL) {}; // 생성자 (초기값 설정)
    ~node() {}; // 소멸자
};

//BST class 정의
class BST{
private:
    node *root;
    int size;

public:
    BST() : root(NULL), size(0) {}; // 생성자
    ~BST() {}; // 소멸자

    // BST가 비었는지 확인
    bool isEmpty(){
        if(size == 0) return true;
        else return false;
    }

    // BST가 꽉 찼는지 확인
    bool isFull(){
        if(size == MAX_SIZE) return true;
        else return false;
    }
    
    // 탐색. 외부에서 root에 접근하지 않도록 함수 호출로 구현
    void traversal(){
        _traversal(root);
        cout << endl;
    }

    // in-order 탐색
    void _traversal(node *root){
        if(root == NULL) return ;
        
        _traversal(root->left);
        cout << root->key << " ";
        _traversal(root->right);
    }

    // BST가 비었을 경우 root에 삽입, 그렇지 않을 경우 재귀함수 호출
    void insert(int val){
        if(isFull()){
            cout << "BST is full." << endl;
            return ;
        }

        node *newNode = new node(val);
        if(root == NULL)
            root = newNode;
        else
            _insert(root, newNode);
        size++;
    }

    // 루트 노드보다 큰지 작은지 판단하며 노드 이동 후 데이터 삽입
    node* _insert(node *root, node *newNode){
        if(root == NULL) return newNode;

        if(newNode->key < root->key)
            root->left = _insert(root->left, newNode);
        else
            root->right = _insert(root->right, newNode);

        return root;
    }

    // 데이터 삭제
    bool erase(int val){

        if(isEmpty()){
            cout << "BST is empty." << endl;
            return -1;
        }

        bool chk = false;
        root = _erase(root, val, &chk);
        
        if(chk == true) size--; // 성공했을 경우에만 size 줄이기
        return chk;
    }

    // 노드 삭제
    node* _erase(node *root, int val, bool *chk){
        if(root == NULL) return root;
        
        // 탐색
        if(val < root->key)
            root->left = _erase(root->left, val, chk);
        else if(val > root->key)
            root->right = _erase(root->right, val, chk);
        else{  // 원하는 노드를 찾았을 경우
            node *ptr = root;
            // 해당 노드에 자식 노드가 없는 경우
            if(root->left == NULL && root->right == NULL){
                root = NULL;
                delete ptr;
            }
            // 해당 노드의 오른쪽에마나 자식 노드가 있는 경우
            else if(root->left == NULL){
                root = root->right;
                delete ptr;
            }
            // 해당 노드의 왼쪽에만 자식 노드가 있는 경우
            else if(root->right == NULL){
                root = root->left;
                delete ptr;
            }
            // 해당 노드의 양쪽에 자식 노드가 있는 경우
            else{
                // 오른쪽 서브트리에서 가장 작은 값 찾기
                ptr = root->right;
                while(ptr->left != NULL)
                    ptr = ptr->left;
                // 찾은 최소값을 루트에 저장 후 기존 노드 제거
                root->key = ptr->key;
                root->right = _erase(root->right, root->key, chk);
            }
            *chk = true;
        }

        return root;
    }
};

int main(){

    BST bst;

    bst.insert(16);
    bst.insert(10);
    bst.insert(36);
    bst.insert(42);
    bst.insert(6);
    bst.insert(8);
    bst.insert(22);
    bst.insert(1);
    bst.insert(40);
    bst.insert(20);

    bst.traversal(); // 1 6 8 10 16 22 36 40 42

    bst.erase(22);
    bst.erase(36);
    bst.erase(16);

    bst.traversal(); // 1 6 8 10 40 42

    return 0;
}