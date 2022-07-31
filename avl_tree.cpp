#include <bits/stdc++.h>
using namespace std;

class node
{
    public:
        int data;
        int height;
        node* left;
        node* right;
};

node* new_node(int data)
{
    node* new_node = new node();
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

int height(node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->height;
}

int getBalance(node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->right) - height(node->left);
}

int max(int a, int b) //find the higher height
{
    return (a > b) ? a : b;
}

node* right_rotate(node* y)
{
    node* x = y->left;              /*       y                 x        */
    node* t2 = x->right;            /*      / \     right     / \       */
                                    /*     x   t3   --->     t1  y      */
    x->right = y;                   /*    / \       <---        / \     */
    y->left = t2;                   /*   t1 t2      left       t2 t3    */

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* left_rotate(node* x)
{
    node* y = x->right;             /*       y                 x        */
    node* t2 = y->left;             /*      / \     right     / \       */   
                                    /*     x   t3   --->     t1  y      */
    y->left = x;                    /*    / \       <---        / \     */
    x->right = t2;                  /*   t1 t2      left       t2 t3    */

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

node* insert(node* root, int data)
{
    if (root == NULL)
    {
        root = new_node(data);
        return root;
    }
    //find "perfect spot" for insertion (spot that doesn't change avl tree invariant after insertion)
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = getBalance(root); // how far our tree are from balance, balance if |balance| <= 1 (for every node)
                                    // |balance| = |root.right.height - root.left.height| <= 1
                                    // cout << balance << " root data: " << root->data << " data: " << data << endl;
    // Left Left Case
    if (balance < -1 && data < root->left->data) //left have higher height and data > current root.data, right rotate
    {
        return right_rotate(root);
    }
    // Right Right Case
    if (balance > 1 && data > root->right->data) //right have higher height and data > current root.data, left rotate
    {
        return left_rotate(root);   
    }
    // Left Right Case
    if (balance < -1 && data > root->left->data)
    {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    // Right Left Case
    if (balance > 1 && data < root->right->data)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    // if none of the 4 cases return unchanged root without rotation
    return root;
}

node* deletion(node* root, int data)
{
    if ((data < root->data && root->left == NULL) || (data > root->data && root->right == NULL))
    {
        cout << "Cannot delete, item not in tree!" << endl;
        return root;
    }
    else if (data < root->data)
    {
        root->left = deletion(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deletion(root->right, data);
    }

    return root;
}

void node_order(node* root)
{
    if (root != NULL)
    {
        node_order(root->left);
        cout << root->data << " ";
        node_order(root->right);
    }
}

int count_element(node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + count_element(root->left) + count_element(root->right);
    //int c = 1;
    //if (root == NULL)
    //{
    //    return 0;
    //}
    //else
    //{
    //    c += count_element(root->left);
    //    c += count_element(root->right);
    //    return c;
    //}
        
}

int find(node* root, int data)
{
    if (root->data == data)
    {
        cout << "Find the item" << endl;
        //cout << root->height << endl; //check the height to see if we have changed the height correctly
        return (root->left)->height; //return item position or "return data" for data
    }
    else if ( (data < root->data && root->left == NULL) || (data > root->data && root->right == NULL) ) 
    {   //if the current node.data != data and its children is NULL (or it is a leaf) return item not in tree
        cout << "Item not in tree" << endl;
        return -1;
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
    return -1;
}

int sum_element(node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->data + sum_element(root->left) + sum_element(root->right);
    
}

int max_element(node* root, int max_value) //  max_value = -1 at start
{
    if (root == NULL)
    {
        return max_value;
    }
    else
    {
        if (max_value < root->data) // > if for min
        {
            max_value = root->data;
        }
        return max(max_element(root->left, max_value), max_element(root->right, max_value));
    }
}

int main()
{
    node* root = NULL;
    root = insert(root, 1);
    root = insert(root, 9);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 4);
    //find(root, 1);
    //node_order(root);
    //cout << count_element(root);
    //cout << sum_element(root);
    //cout << max_element(root, -1);
}