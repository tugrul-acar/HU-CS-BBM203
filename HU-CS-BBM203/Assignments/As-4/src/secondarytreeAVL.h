//
// Created by Tugrul on 12/23/2022.
//
#ifndef AS4_SECONDARYTREEAVL_H
#define AS4_SECONDARYTREEAVL_H
#include <iostream>
#include <queue>
using namespace std;
class secondarynode{ //this is node of avl tree
public:
    string key;
    int data;
    secondarynode* left;
    secondarynode* right;
    int height;

    secondarynode(int data,string key){
        this->data = data;
        this->key = key;
        left = nullptr;
        right = nullptr;
        height = 0;

    }
};

int height(secondarynode* root) { //this function returns the height of the noode
    int h = 0;
    if (root != nullptr) {
        int l_height = height(root->left);
        int r_height = height(root->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int Balance(secondarynode *node) //this function returns the balance of node
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
secondarynode* r_rotate(secondarynode *node)//this function makes right rotate
{
    secondarynode *node1 = node->left;
    secondarynode *temp = node1->right;
    node1->right = node;
    node->left = temp;
    node->height = max(height(node->left),height(node->right)) + 1;
    node1->height = max(height(node1->left),height(node1->right)) + 1;
    return node1;
}

secondarynode* l_rotate(secondarynode *root)//this function makes left rotate
{
    secondarynode *node1 = root->right;
    secondarynode *temp = node1->left;
    node1->left = root;
    root->right = temp;
    root->height = max(height(root->left),height(root->right)) + 1;
    node1->height = max(height(node1->left),height(node1->right)) + 1;
    return node1;
}

secondarynode* insert1(secondarynode* root, int data,string key)//by using this function we make insertion
{
    if (root == nullptr){ //firsly check the root is null or not
        return(new secondarynode(data,key)); //if null then return new pointer
    }
    if (key < root->key){//if less then ,root then check its left again
        root->left = insert1(root->left, data,key);
    }
    else if (key > root->key){//if grater then, root then check its right again
        root->right = insert1(root->right, data,key);
    }
    else{
        return root;
    }

    root->height = 1 + max(height(root->left),height(root->right));//then updates the height of node

    int balance = Balance(root);

    if (balance > 1 && key < root->left->key){//check the balance and make rotate if it necessary
        return r_rotate(root);
    }
    if (balance < -1 && key > root->right->key){
        return l_rotate(root);
    }
    if (balance > 1 && key > root->left->key)
    {
        root->left = l_rotate(root->left);
        return r_rotate(root);
    }
    if (balance < -1 && key < root->right->key)
    {
        root->right = r_rotate(root->right);
        return l_rotate(root);
    }
    return root;
}


void levelorder(ofstream &File,secondarynode* node, int lvl) {//traverse by using level ordering
    if (!node)
        return;
    if (lvl == 0) {
        File<<"\""<<node->key<<"\""<<":"<<"\""<<node->data<<"\""<<",";
    }
    else {
        levelorder(File,node->left, lvl - 1);
        levelorder(File,node->right, lvl - 1);
    }

}
void printiemsAVL(ofstream &File,secondarynode* node) {//prints the avl tree level by level
    if (!node){
        File<<"{}"<<endl;
        return;
    }
    File<<endl;
    int node_height = height(node);
    for (int i=0; i<node_height; i++) {
        File<<"\t";
        levelorder(File,node, i);
        File<<endl;
    }
}
secondarynode* minchild(secondarynode* node)//returns the in order successor of node
{
    secondarynode* temp = node;
    while (temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}

secondarynode* deleteAVL(secondarynode* root, string key)//this function is used for deleting
{

    if(root != nullptr && root->right == nullptr && root->left == nullptr){//if there is only root then delete  root and return null ptr
        root = nullptr;
    }
    if (root == nullptr){
        return root;
    }
    if ( key < root->key ){ //if key is smaller, then check left subtree
        root->left = deleteAVL(root->left, key);

    }
    else if( key > root->key ){//if key is greater ,then check right subtree
        root->right = deleteAVL(root->right, key);
    }

    else//if it equals
    {
        if((root->left == nullptr) || (root->right == nullptr))//then  check right and left child and if one of them is null
        {


            secondarynode* temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
        }
        else
        {
            secondarynode* temp = minchild(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right,temp->key);
        }
    }

    if (root == nullptr)//if root is null then return root
        return root;

    root->height = 1 + max(height(root->left),height(root->right));//check height of root

    int balance = Balance(root);//check the balance

    if (balance > 1 && Balance(root->left) >= 0)//if balance greater then 1 ,then make right rotate
        return r_rotate(root);

    if (balance > 1 && Balance(root->left) < 0)//if balance greater then 1 and its childs balance less then 0  ,then make left rotate and right rotate
    {
        root->left = l_rotate(root->left);
        return r_rotate(root);
    }
    if (balance < -1 && Balance(root->right) <= 0)//if balance less then -1 and its childs balance less then 0 ,then make left rotate
        return l_rotate(root);

    if (balance < -1 && Balance(root->right) > 0)//if balance less then -1  and its childs balance greater then 0  ,then make right rotate and left rotate
    {
        root->right = r_rotate(root->right);
        return l_rotate(root);
    }

    return root;
}

secondarynode* searchAVL(secondarynode* root,string key)//returns the node of required key
{
    if (root == nullptr || root->key == key)
        return root;
    if (root->key < key)
        return searchAVL(root->right, key);
    return searchAVL(root->left, key);
}

#endif //AS4_SECONDARYTREEAVL_H
