#include<iostream>

using namespace std;

struct ListNode{
    int data;
    ListNode *next;

    ListNode(int x) : data(x) , next(nullptr) {}
};

void printAll(ListNode* head){
    ListNode* current = head;

    while(current != nullptr){
        cout<< current->data <<" -> ";
        current = current->next;
    }
    cout<<"nullptr"<<endl;
}

ListNode* deleteNode(ListNode* head,int val){
    ListNode* dummy = new ListNode(01);
    dummy->next = head;

    ListNode* prev = dummy;
    ListNode* curr = head;

    while(curr != nullptr){
        if(curr->data == val){
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    ListNode* newHead = dummy->next;

    delete dummy;

    return newHead;
}
int main(){
    ListNode* node1 = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);

    node1->next = node2;
    node2->next = node3;

    ListNode* head = node1;

    printAll(head);

    ListNode* newNode = new ListNode(0);
    newNode->next = head;
    head = newNode;

    printAll(head);

    deleteNode(head,3);

    printAll(head);

    return 0;
}