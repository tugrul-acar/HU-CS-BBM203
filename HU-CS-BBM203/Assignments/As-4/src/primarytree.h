//
// Created by Tugrul on 12/23/2022.
//
#ifndef AS4_PRIMARYTREE_H
#define AS4_PRIMARYTREE_H
#include "secondarytreeAVL.h"
#include <iostream>
#include <queue>

using namespace std;

class primarynode{ //this is node of primary tree , this is used for avl implementation
public:
    string key;
    secondarynode* secondarytreeptr;
    primarynode* left;
    primarynode* right;
    primarynode(string key){
        left = nullptr;
        right = nullptr;
        secondarytreeptr = nullptr;
        this->key = key;
    }
};
primarynode* insert1(primarynode* node, string key) { //this function is used for inserting new element
        if (node == nullptr){
            return new primarynode(key);
        }
        if (key < node->key)
            node->left = insert1(node->left, key);
        else
            node->right = insert1(node->right, key);
        return node;
    }
primarynode* search1(primarynode* root,string key) //this function returns the node which has the required key value
    {
        if (root == nullptr || root->key == key)
            return root;
        if (root->key < key)
            return search1(root->right, key);
        return search1(root->left, key);
    }
void printitemsprimary1(ofstream &File,primarynode* node){ //by using this function it prints level by level
    if(node == nullptr){
        return;
    }
    queue<primarynode*> queuee;
    queuee.push(node);
    while (!queuee.empty()){ //by using queue we traverse level by level
        primarynode* temp = queuee.front();
        File<<"\""<<temp->key<<"\":";
        printiemsAVL(File,temp->secondarytreeptr);
        if(temp->left != nullptr){
            queuee.push(temp->left);
        }
        if(temp->right != nullptr){
            queuee.push(temp->right);
        }
        queuee.pop();
    }
}




#endif //AS4_PRIMARYTREE_H
