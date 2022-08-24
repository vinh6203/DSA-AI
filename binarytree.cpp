#include <iostream>
using namespace std;

struct node
{
    int data;
    node* left;
    node* right;
    node* parent;
};

node* new_node(int data, node* parent = NULL)
{
    node* temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = parent;
    return temp;
}

void traversal_order(struct node* node)
{
    if (node == NULL)
    {
        return;
    }
    //cout << node->data << " ";  //preorder then print first
    traversal_order(node->left);
    cout << node->data << " ";    //inorder, print betwwen 2 recursion
    traversal_order(node->right);  
    //cout << node->data << " ";  //postorder then print after
}

node* find(node* root, int data)
{
    //cout << root->data << endl; //turn on if want to check the search path
    if (root->data == data)
    {
        return root;
    }
    else if ( (data < root->data && root->left == NULL) || (data > root->data && root->right == NULL) ) 
    {   //if the current node.data != data and its children is NULL (or it is a leaf) return item not in tree
        return nullptr;
    }
    else if (data > root->data)
    {
        //root = root->right; //recurse on the right subtree if data > root.data
        return find(root->right, data);
    }
    else
    {
        //root = root->left; //recurse on the left subtree if data =< root.data
        return find(root->left, data);
    }
}


node* insert(node* root, int data, node* parent = NULL)
{
    if (root == NULL)
    {
        root = new_node(data, parent);
        return root;
    }
    if (data < root->data)
    {
        root->left = insert(root->left, data, root);
    }
    else
    {
        root->right = insert(root->right, data, root);
    }
    return root;
}

node* deletion(node* root, int data)
{
    if (root == NULL)
    {
        cout << "Cannot delete, tree does not have such item" << endl;
        return NULL;
    }
    else if (data < root->data)
    {
        root->left = deletion(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deletion(root->right, data);
    }
    else
    {
        if (root->left == NULL && root->right == NULL) //the deleted node is a leaf
        {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL) //left child is NULL
        {
            node* temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL) //right child is NULL
        {
            node* temp = root;
            root = root->left;
            delete temp;
        }
        else //2 children
        {       
            node* temp = root->right; //move to the next larger element in right subtree
                                      //leftmost element in right subtree of "the node we want to delete"
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            root->data = temp->data;  //copy the leftmost node in right subtree of "the node we want to delete" 
                                      //to "the node we want to delete"
            root->right = deletion(root->right, temp->data);  //recurse on the right to find and delete leftmost node
        } 
    }
    return root;
}

int node_value_sum(node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->data + node_value_sum(root->left) + node_value_sum(root->right);
}

int k = 0;

void depth(node* root, int h)
{
    if (root == NULL)
    {
        if (h < k)
        {
            k = h;
        }
        h--;
        return;
    }
    depth(root->left, h+1);
    depth(root->right, h+1);
}

int main()
{
    struct node* root = NULL;
    root = insert(root, 5);
    root = insert(root, 0);
    root = insert(root, 10);
    root = insert(root, 9);
    root = insert(root, 8);
    root = insert(root, -5);
    root = insert(root, 2);
    traversal_order(root);
    deletion(root, 0);
    cout << endl;
    traversal_order(root);
}
