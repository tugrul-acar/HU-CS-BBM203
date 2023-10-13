#ifndef MODEL_H
#define MODEL_H
#include "order.h"
#include "cashier.h"
#include "barista.h"
#include "events.h"
#include "cashier_queue.h"
#include<vector>
#include "barista_queue.h"

using namespace std;


int empty_cashier( vector<cashier*> cashiers){ //this function returns id of empty cashier if there is no empty casiher then it returns -1
    for (int i = 0; i < cashiers.size(); ++i) {
        if(cashiers[i]->is_empty){
            return cashiers[i]->id;
        }
    }
    return -1;
}

int empty_barista( vector<barista*> baristas){//this function returns id of empty barista if there is no empty barista then it returns -1
    for (int i = 0; i < baristas.size(); ++i) {
        if(baristas[i]->is_empty){
            return baristas[i]->id;
        }
    }
    return -1;
}

void method1(ofstream &File,int n,queue_events events){ //this function runs the first method of the coffee shop
    cashier_queue* cashierQueue = new cashier_queue();  //initializing the barista and cashier queue
    barista_queue* baristaQueue = new barista_queue();
    vector<cashier*> cashiers;      //initializing n cashiers and n/3 baristas
    for (int i = 0; i < n; ++i) {
        cashier* temp_cashier = new cashier();
        temp_cashier->id = i;
        cashiers.push_back(temp_cashier);

    }
    vector<barista*> baristas;
    for (int i = 0; i < n/3; ++i) {
        barista* temp_barista = new barista();
        temp_barista->id = i;
        baristas.push_back(temp_barista);
    }

    while (events.head != nullptr){//if there is no event then all coffe are ready so process is finished

        event* event1 =events.dequeue_event(); //this returns next event
        if(event1->event_type == "order"){ //firstly check type of order
            int id = empty_cashier(cashiers);//if it is order then we need to check empty cashiers
            if(id != -1){   //if there is empty cashier then customer goes this cashier and make new event for making order from cashier
                cashiers[id]->order_ptr = event1->order1;
                cashiers[id]->utilization += event1->order1->o_time;
                cashiers[id]->is_empty = false;
                events.enqueue_event(event1->order1,"cashier",event1->order1->o_time);//
            }else{
                cashierQueue->enqueue_order(event1->order1);//if all cashiers busy then add this order to cashier queue
            }
        }
        else if(event1->event_type == "cashier"){//if it is cashier type then we need to find cashier id, because it takes new customer

            int id = 0;
            for (int i = 0; i < cashiers.size(); ++i) { //finds the cashier id
                if(cashiers[i]->order_ptr == event1->order1 ){
                    id = i;
                }
            }
            order* temp = cashiers[id]->order_ptr;
            if (cashierQueue->head == nullptr) { //if there is no cashier queue then this cashier become available
                cashiers[id]->is_empty = 1;
            }else{  //if there are orders in queue next one comes this cashier and make new event for making order from cashier
                order* temp_order = cashierQueue->dequeue_order();
                cashiers[id]->order_ptr = temp_order;
                cashiers[id]->utilization += temp_order->o_time;
                events.enqueue_event(temp_order,"cashier",temp_order->o_time);
            }
            int id2 = empty_barista(baristas);  //finds empty barista id
            if(id2 ==-1){   //if all baristas are busy then add order to barista queue
                baristaQueue->enqueue_order(temp);
            }else{
                baristas[id2]->utilization += temp->b_time;   //if there is empty barista then order comes this barista and make new event for making coffe in barista
                baristas[id2]->order_ptr = temp;
                baristas[id2]->is_empty = false;
                events.enqueue_event(temp,"barista",temp->b_time);
            }



        }

        else if(event1->event_type == "barista"){//if event type is barista then we need to find barista id and its order
            int id = 0;
            for (int i = 0; i < baristas.size(); ++i) {
                if(baristas[i]->order_ptr == event1->order1 ){
                    id = i;
                }
            }
            order* temp = baristas[id]->order_ptr;

            if (baristaQueue->head == nullptr) {//if barista queue is empty then this barista becomes available
                baristas[id]->is_empty = 1;
            }
            else{   //if not then takes next order in queue and make new event for this barista
                order* temp_order = baristaQueue->dequeue_order();
                baristas[id]->order_ptr = temp_order;
                baristas[id]->utilization += temp_order->b_time;
                events.enqueue_event(temp_order,"barista",temp_order->b_time);

            }
            temp->finish_time = events.time;//previous orders coffe is ready so this events time also ending time of this order

        }
        if(cashierQueue->length() > cashierQueue->max){
            cashierQueue->max = cashierQueue->length();
        }
        if(baristaQueue->length() > baristaQueue->max){
            baristaQueue->max = baristaQueue->length();
        }
    }

    float total = events.time;
    File <<total<<"\n";//this is total time
    File <<cashierQueue->max<<"\n"; //this is max length of cashier queue
    File <<baristaQueue->max<<"\n";//this is max length of barista queue


    for (int i = 0; i < n; ++i) {
        float a = cashiers[i]->utilization / total; //this is utilization ratio of every cashier
        File <<fixed <<setprecision(2)<<a<<"\n";
    }
    for (int i = 0; i < n / 3; ++i) {
        float a = baristas[i]->utilization/total; //this is utilization ratio of every barista
        File <<fixed <<setprecision(2)<<a<<"\n";
    }

}





void method2(ofstream &File,int n,queue_events events){
    cashier_queue* cashierQueue = new cashier_queue();//initializing the barista and cashier queue

    barista_queue* baristaQueue[n/3];
    for (int i = 0; i < n / 3; ++i) {
        baristaQueue[i] = new barista_queue();
    }
    vector<cashier*> cashiers;  //initializing n cashiers and n/3 baristas
    for (int i = 0; i < n; ++i) {
        cashier* temp_cashier = new cashier();
        temp_cashier->id = i;
        cashiers.push_back(temp_cashier);

    }
    vector<barista*> baristas;
    for (int i = 0; i < n/3; ++i) {
        barista* temp_barista = new barista();
        temp_barista->id = i;
        baristas.push_back(temp_barista);
    }

    while (events.head != nullptr){//if there is no event then all coffe are ready so process is finished
        event* event1 =events.dequeue_event();//this returns next event
        if(event1->event_type == "order"){//firstly chech type of order
            int id = empty_cashier(cashiers);//if it is order then we need to check empty cashiers
            if(id != -1){//if there is empty cashier then customer goes this cashier and make new event for making order from cashier
                cashiers[id]->order_ptr = event1->order1;
                cashiers[id]->utilization += event1->order1->o_time;
                cashiers[id]->is_empty = false;
                events.enqueue_event(event1->order1,"cashier",event1->order1->o_time);
            }else{
                cashierQueue->enqueue_order(event1->order1);//if all cashiers busy then add this order to cashier queue
            }
        }
        else if(event1->event_type == "cashier"){//if it is cashier type then we need to find cashier id, because it takes new customer

            int id = 0;
            for (int i = 0; i < cashiers.size(); ++i) {//finds cashier id
                if(cashiers[i]->order_ptr == event1->order1 ){
                    id = i;
                }
            }
            order* temp = cashiers[id]->order_ptr;
            if (cashierQueue->head == nullptr) {//if there is no cashier queue then this cashier become available
                cashiers[id]->is_empty = 1;
            }else{//if there are orders in queue next one comes this cashier and make new event for making order from cashier
                order* temp_order = cashierQueue->dequeue_order();
                cashiers[id]->order_ptr = temp_order;
                cashiers[id]->utilization += temp_order->o_time;
                events.enqueue_event(temp_order,"cashier",temp_order->o_time);
            }
            int barista_id_for_cashier = id/3;//finds the id of barista for this cashier

            if(!baristas[barista_id_for_cashier]->is_empty){//if this barista empty then this barista takes this order
                baristaQueue[barista_id_for_cashier]->enqueue_order(temp);
            }
            else{//if not then add this order to the barista queue
                baristas[barista_id_for_cashier]->utilization += temp->b_time;
                baristas[barista_id_for_cashier]->order_ptr = temp;
                baristas[barista_id_for_cashier]->is_empty = false;
                events.enqueue_event(temp,"barista",temp->b_time);
            }
        }

        else if(event1->event_type == "barista"){//if event type is barista then we need to find barista id and its order

            int id = 0;
            for (int i = 0; i < baristas.size(); ++i) {
                if(baristas[i]->order_ptr == event1->order1 ){
                    id = i;
                }
            }
            order* temp = baristas[id]->order_ptr;

            if (baristaQueue[id]->head == nullptr) {//if barista queue is empty then this barista becomes available
                baristas[id]->is_empty = 1;
            }
            else{ //if not then takes next order in queue and make new event for this barista
                order* temp_order = baristaQueue[id]->dequeue_order();
                baristas[id]->order_ptr= temp_order;
                baristas[id]->utilization += temp_order->b_time;
                events.enqueue_event(temp_order,"barista",temp_order->b_time);

            }
            temp->finish_time = events.time;//previous orders coffe is ready so this events time also ending time of this order

        }

        if(cashierQueue->length() > cashierQueue->max){
            cashierQueue->max = cashierQueue->length();//this is utilization ratio of every cashier
        }
        for (int i = 0; i < n / 3; ++i) {
            if(baristaQueue[i]->length() > baristaQueue[i]->max){
                baristaQueue[i]->max = baristaQueue[i]->length();//this is utilization ratio of every barista
            }
        }




    }
    float total = events.time;
    File <<total<<"\n";//this is total time
    File <<cashierQueue->max<<"\n";//this is max length of cashier queue
    for (int i = 0; i < n / 3; ++i) {//this is max length of every barista queue
        File <<baristaQueue[i]->max<<"\n";
    }
    for (int i = 0; i < n; ++i) {
        float a = cashiers[i]->utilization / total;//this is utilization ratio of every cashier
        File <<fixed <<setprecision(2)<<a<<"\n";
    }
    for (int i = 0; i < n / 3; ++i) {
        float a = baristas[i]->utilization/total;//this is utilization ratio of every barista
        File <<fixed <<setprecision(2)<<a<<"\n";
    }
}


#endif //MODEL_H
