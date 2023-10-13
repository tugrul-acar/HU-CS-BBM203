//
// Created by Tugrul on 12/23/2022.
//

#ifndef AS4_PARTS_H
#define AS4_PARTS_H
#include "primarytree.h"
#include "primarytreeRB.h"
#include "secondarytreeRedBlack.h"
void part1(ofstream &File,vector<string> &file_commands){//this function makes operation for avl tree

    primarynode* root = nullptr;
    for (int i = 0; i < file_commands.size(); ++i) {
        vector<string> splitted = util::split(file_commands[i],'\t');
        if(splitted[0] == "insert"){
            primarynode* temp = search1(root,splitted[1]);
            if(temp == nullptr){
                root = insert1(root,splitted[1]);
            }
            temp = search1(root,splitted[1]);
            int data = stoi(splitted[3]) ;
            temp->secondarytreeptr = insert1(temp->secondarytreeptr, data,splitted[2]);
        }else if(splitted[0] == "printAllItems"){
            File<<"command:printAllItems"<<endl<<"{"<<endl;
            printitemsprimary1(File,root);
            File<<"}"<<endl;
        }else if(splitted[0] == "remove"){
            primarynode* temp = search1(root,splitted[1]);
            temp->secondarytreeptr = deleteAVL(temp->secondarytreeptr,splitted[2]);

        }else if(splitted[0] == "printAllItemsInCategory"){
            primarynode* temp = search1(root,splitted[1]);
            if(temp->secondarytreeptr == nullptr){
                File<<"command:printAllItemsInCategory\t"<<splitted[1]<<endl<<"{"<<endl<<"\""<<temp->key<<"\":{}"<<endl<<"}"<<endl;
            }
            else{
                File<<"command:printAllItemsInCategory\t"<<splitted[1]<<endl<<"{"<<endl<<"\""<<splitted[1]<<"\""<<":";
                printiemsAVL(File,temp->secondarytreeptr);
                File<<"}"<<endl;
            }
        }else if(splitted[0] == "printItem"){
            primarynode* temp = search1(root,splitted[1]);
            if(temp != nullptr){
                secondarynode* tempavl = searchAVL(temp->secondarytreeptr,splitted[2]);
                if(tempavl == nullptr){
                    File<<"command:printItem\t"<<splitted[1]<<"\t"<<splitted[2]<<endl<<"{}"<<endl;
                }
                else{
                    File<<"command:printItem"<<"\t"<<splitted[1]<<"\t"<<splitted[2]<<endl<<"{"<<endl<<"\""<<splitted[1]<<"\""<<":"<<endl;
                    File<<"\t\""<<tempavl->key<<"\":\""<<tempavl->data<<"\""<<endl<<"}"<<endl;
                }
            }else{
                File<<"command:printItem\t"<<splitted[1]<<"\t"<<splitted[2]<<endl<<"{}"<<endl;
            }

        }else if(splitted[0] == "find"){

            primarynode* temp = search1(root,splitted[1]);
            if(temp != nullptr){
                secondarynode* tempavl = searchAVL(temp->secondarytreeptr,splitted[2]);
                if(tempavl == nullptr){
                    File<<"command:find\t"<<splitted[1]<<"\t"<<splitted[2]<<endl<<"{}"<<endl;
                }
                else{
                    File<<"command:find"<<"\t"<<splitted[1]<<"\t"<<splitted[2]<<endl<<"{"<<endl<<"\""<<splitted[1]<<"\""<<":"<<endl;
                    File<<"\t\""<<tempavl->key<<"\":\""<<tempavl->data<<"\""<<endl<<"}"<<endl;
                }
            }else{
                File << "command:find\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{}" << "\n";
            }

        }else if(splitted[0] == "updateData"){
            primarynode* temp = search1(root,splitted[1]);
            secondarynode* tempavl = searchAVL(temp->secondarytreeptr,splitted[2]);
            int newdata = stoi(splitted[3]);
            tempavl->data = newdata;
        }

    }
    cout<<endl;

}



void part2(ofstream &File,vector<string> &file_commands) { //this function makes operation for red black tree
    primarynodeRB *root = nullptr;

    for (int i = 0; i < file_commands.size(); ++i) {
        vector<string> splitted = util::split(file_commands[i], '\t');
        if (splitted[0] == "insert") {
            primarynodeRB *temp = search2(root, splitted[1]);
            if (temp == nullptr) {
                root = insert2(root, splitted[1]);
            }
            temp = search2(root, splitted[1]);
            int data = stoi(splitted[3]);
            temp->secondarytreeptr = insertsecondaryRB(temp->secondarytreeptr, data, splitted[2]);
        } else if (splitted[0] == "printAllItems") {
            File << "command:printAllItems" << "\n" << "{" << "\n";
            printitemsprimary2(File, root);
            File << "}" << "\n";
        }else if(splitted[0] == "remove"){
            primarynodeRB* temp = search2(root,splitted[1]);
            temp->secondarytreeptr = deleteRB(temp->secondarytreeptr,splitted[2]);

        }else if (splitted[0] == "printAllItemsInCategory") {
            primarynodeRB *temp = search2(root, splitted[1]);
            if (temp->secondarytreeptr == nullptr) {
                File << "command:printAllItemsInCategory\t" << splitted[1] << "\n" << "{" << "\n" << "\"" << temp->key
                     << "\":{}" << "\n" << "}" << "\n";
            } else {
                File << "command:printAllItemsInCategory\t" << splitted[1] << "\n" << "{" << "\n" << "\"" << splitted[1]
                     << "\"" << ":";
                printiemsRB(File, temp->secondarytreeptr);
                File << "}" << "\n";
            }
        } else if (splitted[0] == "printItem") {
            primarynodeRB *temp = search2(root, splitted[1]);
            if(temp != nullptr){
                secondarynodeRB *temprb = searchRB(temp->secondarytreeptr, splitted[2]);
                if (temprb == nullptr) {
                    File << "command:printItem\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{}" << "\n";
                } else {
                    File << "command:printItem" << "\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{" << "\n" << "\""
                         << splitted[1] << "\"" << ":" << "\n";
                    File << "\t\"" << temprb->key << "\":\"" << temprb->data << "\"" << "\n" << "}" << "\n";
                }
            }else{
                File << "command:printItem\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{}" << "\n";
            }

        } else if (splitted[0] == "find") {

            primarynodeRB *temp = search2(root, splitted[1]);
            if(temp != nullptr){
                secondarynodeRB *temprb = searchRB(temp->secondarytreeptr, splitted[2]);
                if (temprb == nullptr) {
                    File << "command:find\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{}" << "\n";
                } else {
                    File << "command:find" << "\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{" << "\n" << "\""
                         << splitted[1] << "\"" << ":" << "\n";
                    File << "\t\"" << temprb->key << "\":\"" << temprb->data << "\"" << "\n" << "}" << "\n";
                }
            }else{
                File << "command:find\t" << splitted[1] << "\t" << splitted[2] << "\n" << "{}" << "\n";
            }

        } else if (splitted[0] == "updateData") {
            primarynodeRB *temp = search2(root, splitted[1]);
            secondarynodeRB *temprb = searchRB(temp->secondarytreeptr, splitted[2]);
            int newdata = stoi(splitted[3]);
            temprb->data = newdata;
        }
    }


}
#endif //AS4_PARTS_H
