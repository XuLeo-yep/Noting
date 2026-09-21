#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

struct ListNode{
    int data;
    ListNode* next;

    ListNode(int x ) : data(x) , next(nullptr){}
};

class SortedSinglyLinkedList {
private :
    ListNode* head;

public :
    SortedSinglyLinkedList() : head (nullptr) {};

    void insertSorted( int num){
        ListNode* newNode = new ListNode(num);

        if(head == nullptr){
            head = newNode;
            return;
        }

        if(num < head->data){
            newNode->next = head;
            head = newNode;
            return;
        }

        ListNode* current = head;
        while(current->next != nullptr && current->next->data < num){
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void traversePrint() {
        ListNode* current = head;
        while(current != nullptr){
            cout <<current->data<<" ";
            current = current->next;
        }
        cout <<endl;
    }

    void clear(){
        ListNode* current = head;
        while(current != nullptr){
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

int main(){
    srand((unsigned int)time(NULL));

    SortedSinglyLinkedList list;
    int randomNums[10];

    cout<<"Original random numbers:"<<endl;
    for(int i = 0 ; i < 10; i++){
        randomNums[i] = rand() % 100;
        cout<<randomNums[i]<<" ";
    }
    cout <<endl;

    for(int x : randomNums){
        list.insertSorted(x);
    }

    cout<<"Sorted linked list:"<<endl;
    list.traversePrint();

    list.clear();

    return 0;

}
