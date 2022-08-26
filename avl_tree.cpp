#include<iostream>
using namespace std;

class node
{
    public:
        int data;
        int height;
        node* left;
        node* right;
        node* parent;
};

node* new_node(int data, node* parent = NULL)
{
    node* new_node = new node();
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    new_node->parent = parent;
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

node* right_rotate(node* y)
{
                                    /*       |                 |        */
    node* x = y->left;              /*       y                 x        */
    node* t2 = x->right;            /*      / \     right     / \       */
                                    /*     x   t3   --->     t1  y      */
    x->right = y;                   /*    / \       <---        / \     */
    y->left = t2;                   /*   t1 t2      left       t2 t3    */
    if (t2 != nullptr)
    {
        t2->parent = y;
    }
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1; //update height

    x->parent = y->parent;
    if (y->parent != NULL) //set parent pointer to y (if not NIL)
    {
        if (y->parent->left == y)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }
    y->parent = x;
    return x;
}

node* left_rotate(node* x)
{                                   
    node* y = x->right;             /*       |                 |        */
    node* t2 = y->left;             /*       y                 x        */
                                    /*      / \     right     / \       */   
    y->left = x;                    /*     x   t3   --->     t1  y      */
    x->right = t2;                  /*    / \       <---        / \     */
                                    /*   t1 t2      left       t2 t3    */
    if (t2 != nullptr)
    {
        t2->parent = x;
    }

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1; //update height

    y->parent = x->parent;
    if (x->parent != NULL) //set parent pointer to y (if not NIL)
    {
        if (x->parent->left == x)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        
    }
    x->parent = y;
    return y;
}

node* insertion(node* root, int data, node* parent = NULL)
{
    if (root == NULL)
    {
        root = new_node(data, parent);
        return root;
    }
    //find "perfect spot" for insertion (spot that doesn't violate avl tree invariant after insertion)
    if (data < root->data)
    {
        root->left = insertion(root->left, data, root);
    }
    else
    {
        root->right = insertion(root->right, data, root);
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
    if (root == NULL)
    {
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
            root->data = temp->data;    //swap the leftmost node in right subtree of "the node we want to delete" 
                                        //to "the node we want to delete"
            root->right = deletion(root->right, temp->data);  //recurse on the right to find and delete leftmost node
        }
    }

    if (root == NULL)
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right)); //update height
    int balance = getBalance(root);
    //cout << root->data << " " << balance << endl;
    //Left Left Case
    if (balance > 1 && getBalance(root->right) >= 0)
    {
        return left_rotate(root);
    }
    //Right Left Case
    if (balance > 1 && getBalance(root->right) < 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    //Right Right Case
    if (balance < -1 && getBalance(root->left) <= 0)
    {
        return right_rotate(root);
    }
    //Left Right Case
    if (balance < -1 && getBalance(root->left) > 0)
    {
        root->left = left_rotate(root);
        return right_rotate(root);
    } 
    return root;
}

void print_tree(node* root)
{
    if (root != NULL)
    {
        print_tree(root->left);
        cout << root->data << " ";
        print_tree(root->right);
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

//return node if success, return nullptr if failed
node* find_node(node* root, int data)
{
    if (root->data == data)
    {
        //cout << root->height << endl; //check the height to see if we have changed the height correctly
        return root; //return correct node
    }
    else if ( (data < root->data && root->left == NULL) || (data > root->data && root->right == NULL) ) 
    {   //if the current node.data != data and its children is NULL (or it is a leaf) return item not in tree
        return nullptr;
    }
    else if (data > root->data)
    {
        //root = root->right; //recurse on the right subtree if data > root.data
        return find_node(root->right, data);
    }
    else
    {
        //root = root->left; //recurse on the left subtree if data =< root.data
        return find_node(root->left, data);
    }
}

int sum_element(node* root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->data + sum_element(root->left) + sum_element(root->right);
    
}

int main()
{
    node* root = NULL;
    root = insertion(root, 3);
    root = insertion(root, 10);
    root = insertion(root, 4);
    root = insertion(root, 6);
    root = insertion(root, 11);
    
    
    //cout << count_element(root);
    //cout << sum_element(root);
}
