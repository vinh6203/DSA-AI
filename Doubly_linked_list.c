#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* next;
    struct node* prev;
};

struct node* head;

struct node* get_new_node(int x)
{
    struct node* newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = x;     //(*newnode).data = x;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

int linked_list_length()
{
    struct node* temp = head;
    int length = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        length++;
    }
    return length;
}

void insert_at_head(int x)
{
    struct node* new_node;
    new_node = get_new_node(x);
    if (head == NULL)
    {
        head = new_node;
        return;
    } 
    head->prev = new_node;
    new_node->next = head;
    head = new_node;   
}

void insert_at_tail(int x)
{
    struct node* temp = head;
    struct node* new_node;
    new_node = get_new_node(x);
    if (head == NULL)
    {
        head = new_node;
        return;
    }
    while(temp->next != NULL) 
    {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->prev = temp;
}

void insert_at(int n, int x)
{
    struct node** temp = &head;
    struct node* temp_p = *temp;
    struct node* new_node = get_new_node(x);
    int length = linked_list_length();
    if (head == NULL)
    {
        head = new_node;
        return;
    }
    else if (n > length || n <= 0)
    {
        printf("Invalid Position!\n");
        return;
    }
    else if (n == length)
    {
        insert_at_tail(x);
        return;
    }
    else if (n == 1)
    {
        insert_at_head(x);
        return;
    }
    else
    {
        while (temp_p->prev != NULL)
        {
            temp_p = temp_p->prev;
        }
        for (int i = 1; i < n; i++)
        {
            temp_p = temp_p->next;
        }
        new_node->next = (temp_p->next)->prev;
        new_node->prev = temp_p->prev->next;
        temp_p->next->prev = new_node;
        temp_p->prev->next = new_node;
    }
}

void delete_at(int n)
{
    struct node* temp = head;
    int length = linked_list_length();
    if (n > length || n <= 0 || head == NULL)
    {
        printf("Invalid Position!\n");
        return;
    }
    while (temp->prev != NULL)
    {
        temp = temp->prev;
    }
    if (n == 1)
    {
        temp = temp->next;
        temp->prev = NULL;
        head = temp;
        return;
    }
    else if (n == length)
    {
        temp = temp->prev;
        temp->next = NULL;
        head = temp;
        return;
    }
    else
    {
        struct node** head_reference = &head;
        struct node* temp_p = *head_reference;
        for (int i = 1; i < n && temp_p != NULL; i++)
        {
            temp_p = temp_p->next;
        }
        temp_p->next->prev = temp_p->prev;
        temp_p->prev->next = temp_p->next;
    }
     
}

void print()
{
    struct node* temp = head;
    while (temp->prev != NULL)
    {
        temp = temp->prev;
    }
    while (temp != NULL)
    {
        printf("(%i)-", temp->data);
        temp = temp->next;
    }
}

void reversed_print()
{
    struct node* temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    while (temp != NULL)
    {
        printf("(%i)-", temp->data);
        temp = temp->prev;
    }
}


int main()
{
    head = NULL;
    insert_at_tail(1);
    insert_at_tail(2);
    insert_at_tail(3);
    insert_at_tail(4);
    insert_at_tail(5);
    insert_at_tail(6);
    delete_at(2);
    print();
}