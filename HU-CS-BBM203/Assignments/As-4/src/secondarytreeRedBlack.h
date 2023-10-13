#ifndef SECONDARYTREEREDBLACK_H
#define SECONDARYTREEREDBLACK_H
#include <iostream>
#include <queue>
using namespace std;

bool RED = true;
bool BLACK = false;

class secondarynodeRB{ //this is node of red black tree
public:
    string key;
    int data;
    secondarynodeRB* left;
    secondarynodeRB* right;
    secondarynodeRB* parent;
    bool color;

    secondarynodeRB(int data,string key,bool color){
        this->data = data;
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        this->color = color;
    }
};

bool isRed(secondarynodeRB* x)  //this is returns the whether is red or not
{
    if (x == nullptr) {
        return false;
    }
    return x->color == RED;
}
secondarynodeRB* rotateLeftRB(secondarynodeRB* node) //this function makes left rotation
{
    secondarynodeRB* x = node->right;
    node->right = x->left;
    x->left = node;
    x->color = node->color;
    node->color = RED;
    return x;
}
secondarynodeRB* rotateRightRB(secondarynodeRB* node)//this function makes right rotation
{
    secondarynodeRB* x = node->left;
    node->left = x->right;
    x->right = node;
    x->color = node->color;
    node->color = RED;
    return x;
}
void flipColors(secondarynodeRB* node) //this function flip colors
{
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}

secondarynodeRB* insertsecondaryRB(secondarynodeRB* root,int data,string key){//this is insertion for red black tree
    if(root == nullptr) {
        return new secondarynodeRB(data, key, RED);
    }
    if(root->key > key){
        root->left = insertsecondaryRB(root->left,data,key);
    }else{
        root->right = insertsecondaryRB(root->right,data,key);
    }
    if (isRed(root->right) && !isRed(root->left)) {
        root = rotateLeftRB(root);
    }
    if (isRed(root->left) && isRed(root->left->left)) {
        root = rotateRightRB(root);
    }
    if (isRed(root->left) && isRed(root->right)) {
        flipColors(root);
    }

    return root;

}


secondarynodeRB* searchRB(secondarynodeRB* root,string key)//this function returns the node with required key
{
    if (root == nullptr || root->key == key)
        return root;
    if (root->key < key)
        return searchRB(root->right, key);
    return searchRB(root->left, key);
}

void printiemsRB(ofstream &File,secondarynodeRB* node){//this function print the tree level by level
    if (!node){
        File<<"{}"<<"\n";
        return;
    }
    File<<"\n";

    queue<secondarynodeRB*> q;
    q.push(node);

    while (!q.empty()){
        int x = q.size();
        bool line = true;

        while (x > 0){
            secondarynodeRB* temp = q.front();
            q.pop();
            if(x == 1){
                if(line){
                    File<<"\t";
                }
                File<<"\""<<temp->key<<"\""<<":"<<"\""<<temp->data<<"\"";
            }if(x != 1){
                if(line){
                    File<<"\t";
                }
                File<<"\""<<temp->key<<"\""<<":"<<"\""<<temp->data<<"\""<<",";
            }
            if(temp->left != nullptr){
                q.push(temp->left);
            }
            if(temp->right != nullptr){
                q.push(temp->right);
            }
            x--;
            line = false;
        }
        File<<"\n";

    }

}
secondarynodeRB* moveRedLeft(secondarynodeRB* h)
{
    h->color = BLACK;
    h->left->color = RED;
    if (isRed(h->right->left))
    {
        h->right = rotateRightRB(h->right);
        h = rotateRightRB(h);
    }
    else h->right->color = RED;
    return h;
}
secondarynodeRB* moveRedRight(secondarynodeRB* h)
{
    h->color = BLACK;
    h->right->color = RED;
    if (isRed(h->left->left))
    {
        h = rotateRightRB(h);
        h->color = RED;
        h->left->color = BLACK;
    }
    else h->left->color = RED;
    return h;
}

secondarynodeRB* findMin(secondarynodeRB* pNode) //find the inorder successor of the node
{
    while (NULL != pNode->left) {
        pNode = pNode->left;
    }
    return pNode;
}
secondarynodeRB* deleteMin(secondarynodeRB* h) //delete the inorder successor
{
    if (h->left == nullptr)
        return nullptr;
    if (!isRed(h->left) && !isRed(h->left->left))
        h = moveRedLeft(h);
    h->left = deleteMin(h->left);
    if (isRed(h->right))
        h = rotateLeftRB(h);
    return h;
}
secondarynodeRB* deleteRB(secondarynodeRB* h, string key)//this funtion deletes the item and make rotaions again
{
    if (key < h->key){
        if (!isRed(h->left) && !isRed(h->left->left))
            h = moveRedLeft(h);
        h->left = deleteRB(h->left, key);
    }
    else{
        if (isRed(h->left)) h = rotateRightRB(h);
        if (key == h->key && (h->right == nullptr))
            return nullptr;
        if (!isRed(h->right) && !isRed(h->right->left))
            h = moveRedRight(h);
        if (key == h->key){
            h->key = findMin(h->right)->key;
            h->right = deleteMin(h->right);
        }
        else h->right = deleteRB(h->right, key);
    }
    if (isRed(h->right)) h = rotateLeftRB(h);
    return h;
}







#endif //SECONDARYTREEREDBLACK_H
