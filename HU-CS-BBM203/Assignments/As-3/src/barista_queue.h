#ifndef BARISTA_QUEUE_H
#define BARISTA_QUEUE_H
#include "barista.h"
class barista_queue{
public:
    int max = 0;
    order* head = nullptr;

    void enqueue_order(order* order1){ //this method add orders by looking its price
        if(head == nullptr){
            head = order1;
        }
        else{
            if(order1->price > head->price){
                order1->next = head;
                head = order1;
            }else{
                order* order_temp = head;
                while (order_temp->next != nullptr && order_temp->next->price > order1->price){
                    order_temp= order_temp->next;
                }
                order1->next = order_temp->next;
                order_temp->next = order1;

            }


        }
    }

    order* dequeue_order(){//this is returns next order in queue
        order* order_temp = head;
        head = head->next;
        return order_temp;
    }

    int length(){   //this is returns the legnth of queue
        order* order_temp = head;
        int i = 0;
        if(order_temp == nullptr){
            return 0;
        }
        i = 1;
        while (order_temp->next != nullptr){
            order_temp= order_temp->next;
            i++;
        }
        return i;

    }

};

#endif //BARISTA_QUEUE_H
