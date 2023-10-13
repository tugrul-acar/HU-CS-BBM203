#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include "order.h"
#include "event.h"
using namespace std;

class queue_events{
public:
    float time = 0;
    event* head = nullptr;

    void enqueue_event(order* order,string event_type,float time){//this funstion add new event to thw queue by looking its ending time
        event* event_ptr = new event(event_type,order,this->time+time);
        if(head == nullptr){
            head = event_ptr;
        }
        else{
            float endingtime = this->time+time;
            if(head->ending_time > endingtime){
                event_ptr->next = head;
                head = event_ptr;
            }else{
                float endingtime = this->time+time;
                event* event_temp = head;
                while (event_temp->next != nullptr && event_temp->next->ending_time < endingtime){
                    event_temp = event_temp->next;
                }
                event* next = event_temp->next;
                event_temp->next = event_ptr;
                event_ptr->next = next;
            }

        }
    }
    event* dequeue_event(){//this returns next event in the queue
        event* temp = head;
        head = head->next;
        time = temp->ending_time;
        return temp;
    }

};


#endif //EVENTS_H
