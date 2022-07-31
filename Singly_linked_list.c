#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
}Node;

Node* newNode(int data);
Node* insertTail(Node* head, int value);
Node* insertHead(Node* head, int value);
Node* insert_at(Node* head, int value, int pos);
Node* delete_at(Node* head, int pos);
Node* deleteSingle(Node* head);
Node* rotate(Node* head, int k);
int linked_list_length(Node* head);

Node* newNode(int data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = data;
    new_node->next = NULL;
    return new_node;
}

Node* insertTail(Node* head, int value)
{
    Node* new_node = newNode(value);
    if (head == NULL)
    {
        return new_node;
    }
    head->next = insertTail(head->next, value);
    return head;
}

Node* insertHead(Node* head, int value)
{
    struct Node* new_node = newNode(value);
    if (head == NULL)
    {
        head = new_node;
        return head;
    }
    new_node->next = head;
    return new_node;
}

Node* insert_at(Node* head, int value, int pos)
{
    if (pos == 1)
    {
        Node* new_node = newNode(value);
        new_node->next = head;
        return new_node;
    }
    head->next = insert_at(head->next, value, pos-1);
    return head;
}

Node* delete_at(Node* head, int pos)
{
    if (pos == 0)
    {
        return head->next;
    }
    head->next = delete_at(head->next, pos-1);
    return head;
}

Node* deleteSingle(Node* head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    if (head->value != (head->next)->value)
    {
        return head->next;
    }
    Node* temp = head;
    while (temp->next != NULL && temp->next->value == head->value)
    {
        temp = temp->next;
    }
    temp->next = deleteSingle(temp->next);
    return head;
}

Node* rotate(Node* head, int k)
{
    if (head == NULL || head->next == NULL || k < 1)
    {
        return head;
    }
    Node* kth = head;
    Node* end = head;
    while (end->next != NULL)
    {
        end = end->next;
    }
    while (k > 1)
    {
        kth = kth->next;
        k--;
    }
    Node* temp = kth->next;
    end->next = head;
    kth->next = NULL;
    return temp;
}

int linked_list_length(Node* head)
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

void Print(Node* head)
{
    while (head != NULL)
    {
        printf("%i ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    Node* head = NULL;
    head = insertTail(head, 1);
    head = insertTail(head, 2);
    head = insertTail(head, 3);
    head = insertTail(head, 4);
    head = insertTail(head, 5);
    Print(head);
    //printf("length: %i", linked_list_length(head));
}