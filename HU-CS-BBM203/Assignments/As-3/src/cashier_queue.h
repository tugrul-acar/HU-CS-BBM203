
#ifndef CASHIER_QUEUE_H
#define CASHIER_QUEUE_H
#include "order.h"
class cashier_queue{
public:
    int max = 0;
    order* head = nullptr;
    order* rear = nullptr;
    void enqueue_order(order* order1){//this method add orders to the end of queue
        if(head == nullptr && rear == nullptr){
            rear = head = order1;
        }
        else{
            rear->next = order1;
            rear = order1;
        }
    }

    order* dequeue_order(){//this is returns next order in queue
        order* order_temp = head;
        head = head->next;
        return order_temp;
    }
    int length(){//this is returns the legnth of queue
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
#endif //CASHIER_QUEUE_H
