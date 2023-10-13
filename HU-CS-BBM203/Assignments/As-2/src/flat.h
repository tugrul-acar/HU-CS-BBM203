#ifndef FLAT_H
#define FLAT_H
using namespace std;

class flat{     //this is flat that contains id, bandwith is empty next and prev
public:
    int id;
    int initial_bandwidth;
    int is_empty;
    flat* next;
    flat* prev;
    flat(int id,int initial_bandwidth){
        this->id = id;
        this->initial_bandwidth = initial_bandwidth;
        this->is_empty = 0;
        this->next = 0;
        this->prev = 0;
    }

};


class flat_list1{   //this is representing flat linked list of a apartment
public:
    flat* flat_head;    //this class has flat head total band and insert flat operation
    int max;
    int total_band;

    flat_list1(int max,flat* node){
        this->max = max;
        this->flat_head = node;
        this->total_band = 0;
        this->total_band += node->initial_bandwidth;
    }

    void insert_flat(int index,flat* node){
        int ind = 1;
        flat* temp = flat_head;

        while (ind < index){
            temp = temp->next;
            ind++;
        }


        if(index ==0){
            node->next = flat_head;
            flat_head = node;
            flat_head->next->prev = flat_head;
            total_band += node->initial_bandwidth;
        }else{
            flat* temp_next = temp->next;
            temp->next = node;
            node->next = temp_next;
            if(temp_next != 0){
                temp_next->prev = node;
            }

            node->prev = temp;
            total_band += node->initial_bandwidth;
        }



    }



};

#endif //FLAT_H
