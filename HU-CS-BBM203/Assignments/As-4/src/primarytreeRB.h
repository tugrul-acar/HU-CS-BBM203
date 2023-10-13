//
// Created by Tugrul on 12/24/2022.
//

#ifndef AS4_PRIMARYTREERB_H
#define AS4_PRIMARYTREERB_H
#include "secondarytreeRedBlack.h"
#include <iostream>
#include <queue>

using namespace std;

class primarynodeRB{//this is node of primary tree , this is used for red black implementation
public:
    string key;
    secondarynodeRB* secondarytreeptr;
    primarynodeRB* left;
    primarynodeRB* right;
    primarynodeRB(string key){
        left = nullptr;
        right = nullptr;
        secondarytreeptr = nullptr;
        this->key = key;
    }
};
primarynodeRB* insert2(primarynodeRB* node, string key) {//this function is used for inserting new element
    if (node == nullptr){
        return new primarynodeRB(key);
    }
    if (key < node->key)
        node->left = insert2(node->left, key);
    else
        node->right = insert2(node->right, key);
    return node;
}
primarynodeRB* search2(primarynodeRB* root,string key)//this function returns the node which has the required key value
{
    if (root == nullptr || root->key == key)
        return root;
    if (root->key < key)
        return search2(root->right, key);
    return search2(root->left, key);
}
void printitemsprimary2(ofstream &File,primarynodeRB* node){//by using this function it prints level by level
    if(node == nullptr){
        return;
    }
    queue<primarynodeRB*> queuee;
    queuee.push(node);

    while (!queuee.empty()){//by using queue we traverse level by level
        primarynodeRB* temp = queuee.front();

        File<<"\""<<temp->key<<"\":";
        printiemsRB(File,temp->secondarytreeptr);
        if(temp->left != nullptr){
            queuee.push(temp->left);
        }
        if(temp->right != nullptr){
            queuee.push(temp->right);
        }
        queuee.pop();
    }
}

#endif //AS4_PRIMARYTREERB_H
