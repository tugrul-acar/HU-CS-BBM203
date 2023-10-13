#include <vector>
#include <iostream>
#include "apartment.h"
#include <sstream>

void create_list(apart* &apartment_head,apart* &apartment_tail,apart* node){ //if linked list empty this appends first node
    apartment_head = node;
    node->next = node;
    apartment_tail = apartment_head;
}

void insert(apart* &apartment_head,apart* &apartment_tail,string where,apart* node,string name){//if linked list is not  empty this appends to the linked list
    if(where == "before"){ //this if else  checks commands contains before or after
        apart* temp = apartment_head;
        while (temp->next->name != name){
            temp = temp->next; //if before function finds the before of the given node and append next of them
        }
        if(temp->next == apartment_head){
            apartment_head = node;
        }
        node->next = temp->next;
        temp->next = node;
    }
    if(where == "after"){
        apart* temp = apartment_head;
        while (temp->name != name){
            temp = temp->next;  //if after function finds the after of the given node and append next of them
        }
        if(temp == apartment_tail){
            apartment_tail = node;
        }
        node->next = temp->next;
        temp->next = node;
    }

}

void add_flat(apart* &apartment_head,apart* apartment_tail,string apart_name,int id,int bandwitdh,int index){  //this function add flat to the apartment
    apart* temp = apartment_head;
    while (temp->name != apart_name){       //finds apartment by name
        temp = temp->next;
    }
    if(temp->flat_list == 0){ //if flatlist empty then make a falt list to this apartment
        if(temp->max_bandwidth < bandwitdh){
            temp->flat_list = new flat_list1(temp->max_bandwidth,new flat(id,temp->max_bandwidth));
        }
        else{
            temp->flat_list = new flat_list1(temp->max_bandwidth,new flat(id,bandwitdh));
        }

    }
    else{//if flatlist is not empty then insert the node to the linked list
        flat_list1* temp_flat_list = temp->flat_list;
        if(temp->max_bandwidth < temp_flat_list->total_band+bandwitdh){
            int band = temp->max_bandwidth - temp->flat_list->total_band;
            temp->flat_list->insert_flat(index,new flat(id,band));
        }else{
            temp->flat_list->insert_flat(index,new flat(id,bandwitdh));
        }
    }
}


apart* remove_apart(apart* &apartment_head,apart* apartment_tail,string name) {
    if(name == apartment_head->name && apartment_head == apartment_tail){ //if there is only one apartment delete this aparmtent and flat list
        apart* temp = apartment_head;
        apartment_head = 0;
        apartment_tail = 0;
        if(temp->flat_list != 0){
            flat* del_flat =  temp->flat_list->flat_head;
            while (del_flat->next != 0){
                flat* del_apart_next = del_flat->next;
                delete del_flat;
                del_flat = del_apart_next;
            }
            delete del_flat;
        }
        delete temp->flat_list;
        delete temp;

    }
    else{ //if there is more than one apartment this is running
        if(name == apartment_head->name){ //if head will be deleted head becomes next node of head
            apartment_head = apartment_head->next;
        }
        else if(name == apartment_tail->name){ //if tail will be  deleted then tail becomes previous node of tail
            apart* temp1 = apartment_head;
            while (temp1->next->name != name){
                temp1 = temp1->next;
            }
            apartment_tail = temp1;
        }


        apart* temp = apartment_head;

        while (temp->next->name != name){ //this finds previous of deleting node
            temp = temp->next;
        }
        apart* del_apart  = temp->next; //this is deleting apartment



        temp->next = temp->next->next;



        if(del_apart->flat_list != 0){  //if flat list is not null then firsly delete flats
            flat* del_flat =  del_apart->flat_list->flat_head;
            while (del_flat->next != 0){
                flat* del_apart_next = del_flat->next;
                delete del_flat;
                del_flat = del_apart_next;
            }
            delete del_flat;
        }

        delete del_apart->flat_list;
        delete del_apart;
    }

    return apartment_head;

}


void make_flat_empty(apart* &apartment_head,apart* apartment_tail,string name,int flat_id){ //this funcion make empty a flat of apartment
    apart* temp = apartment_head;
    while (temp->name != name){
        temp = temp->next;
    }
    flat*flat_temp = temp->flat_list->flat_head;
    while (flat_temp->id !=flat_id){
        flat_temp = flat_temp->next;
    }
    flat_temp->is_empty = 1;
    flat_temp->initial_bandwidth = 0;
}

int find_sum_of_max_bandwidth(apart* &apartment_head,apart* apartment_tail,vector<string> &output){
    int sum = 0;
    apart* temp = apartment_head;

    while (temp->next != apartment_head){
        sum += temp->max_bandwidth;
        temp = temp->next;
    }
    if(temp != 0){
        sum += temp->max_bandwidth;
    }
    stringstream s1;
    s1<<"sum of bandwidth: "<<sum<<"\n";
    string out = s1.str();
    output.push_back(out);
    return sum;
}


apart* merge_apart(apart* &apartment_head,apart* &apartment_tail,string name1 ,string name2){//this function merge two apartments

    apart* temp = apartment_head;

    while (temp->next->name != name1){
        temp = temp->next;
    }
    apart* merge1  = temp->next; //this finds first apartment
    if(name1 == apartment_tail->name){
        apartment_tail = temp;
    }
    temp->next = temp->next->next;  //deleting from linked list


    temp = apartment_head;
    while (temp->name != name2){
        temp = temp->next;
    }
    apart* merge2  = temp; //this finds second apartment

    merge2->max_bandwidth += merge1->max_bandwidth; //add maxbandwidth to the second apartment


    if(merge1->flat_list != 0 && merge2->flat_list ==0){ //second apartment does not have flat list then link from first apartment
        merge2->flat_list = merge1->flat_list;
    }else if(merge1->flat_list != 0 && merge2->flat_list !=0) { //second apartment have flat list then link from first apartment to the second apartment linked list
        flat* temp = merge2->flat_list->flat_head;
        while (temp->next != 0){
            temp = temp->next;
        }
        temp->next = merge1->flat_list->flat_head;
        merge1->flat_list->flat_head->prev = temp;
    }

    delete merge1->flat_list;
    delete merge1;


    if(name1 == apartment_head->name){
        apartment_head = apartment_head->next;
    }
    return apartment_head;
}


void relocate_flats(apart* &apartment_head,apart* &apartment_tail,string name,int id,vector<string> flats){//this function relocate the apartments by commands
    flat* temp_list_head = 0;
    int add_bandwith = 0;
    for (int i = 0; i < flats.size(); ++i) {
        apart* apart = apartment_head;
        int id;
        stringstream stringstream1(flats[i]);
        stringstream1>>id;
        // firslty traverse all linked list and finds flats then make a link between them and connect to the apartment flat linked list
        while (apart->next != apartment_head ){  //firstly we are traverse every item in linked list
            flat* temp = apart->flat_list->flat_head; //temp holds flat head of flat list
            while (temp != 0 ){
                if(temp->id == id){ //if id equals then break loop
                    break;
                }
                temp = temp->next;
            }
            if(temp != 0 && id == temp->id){
                apart->max_bandwidth -= temp->initial_bandwidth;
                add_bandwith += temp->initial_bandwidth;
                if(temp_list_head == 0){ //if it is first flat to relocate then make it  head node of temporary flat list
                    if(temp == apart->flat_list->flat_head){
                        apart->flat_list->flat_head = apart->flat_list->flat_head->next;
                        apart->flat_list->flat_head->prev = 0;
                    }else{
                        flat* prev = temp->prev;
                        prev->next = prev->next->next;
                        if(prev->next != 0){
                            prev->next->prev = prev;
                        }
                        temp->prev = 0;
                        temp->next = 0;
                    }
                    temp_list_head = temp;
                }else{//if it is not first flat to relocate then insert it end of temporary flat list
                    if(temp == apart->flat_list->flat_head){
                        apart->flat_list->flat_head = apart->flat_list->flat_head->next;
                        apart->flat_list->flat_head->prev = 0;
                    }else{
                        flat* prev = temp->prev;
                        prev->next = prev->next->next;
                        prev->next->prev = prev;
                        temp->prev = 0;
                        temp->next = 0;
                    }
                    flat* flat_temp = temp_list_head;
                    while (flat_temp->next != 0){
                        flat_temp = flat_temp->next;
                    }
                    flat_temp->next = temp;
                    temp->prev = flat_temp;
                }
                break;
            }
            apart = apart->next;
        }

    }
    apart* temp_apart = apartment_head;
    while (temp_apart->name != name){
        temp_apart = temp_apart->next;
    }
    temp_apart->max_bandwidth += add_bandwith;

    flat* temp_flat = temp_apart->flat_list->flat_head;
    if(id ==  temp_flat->id){//this is linking to the flat list of target apartment
        flat* temp_flat2 = temp_list_head;
        while (temp_flat2->next != 0){
            temp_flat2 = temp_flat2->next;
        }
        temp_flat2->next = temp_flat;
        temp_flat->prev = temp_flat2;
        temp_apart->flat_list->flat_head = temp_list_head;
    }
}


void list_apartments(apart* &apartment_head,apart* &apartment_tail,vector<string> &output){//this function list every apartment and its flats
    apart* apart = apartment_head;

    while (apart->next != apartment_head ){
        stringstream s1;
        s1<<apart->name<<"("<<apart->max_bandwidth<<")"<<"\t";
        if(apart->flat_list != 0){
            flat* temp = apart->flat_list->flat_head;
            while (temp != 0){
                s1<<"Flat"<<temp->id<<"("<<temp->initial_bandwidth<<")"<<"\t";
                temp = temp->next;
            }
        }
        string out = s1.str();
        output.push_back(out);
        apart = apart->next;
    }
    stringstream s1;
    s1<<apart->name<<"("<<apart->max_bandwidth<<")"<<"\t";
    if(apart->flat_list != 0){
        flat* temp = apart->flat_list->flat_head;
        while (temp != 0){
            s1<<"Flat"<<temp->id<<"("<<temp->initial_bandwidth<<")"<<"\t";
            temp = temp->next;
        }

    }
    s1<<"\n";
    string out = s1.str();
    output.push_back(out);

}