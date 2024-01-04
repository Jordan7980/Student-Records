/*
Program Name: Student Records
Programmer Name: Jordan Forbes
Purpose: Implementation of courses.h file
Attempt Number: 1
Purpose for Update: n/a
Global Variable List: n/a
*/

#include "courses_dll.h"

namespace DS {
    //---===[ Constructors ]===---
    //Precondition: none
    //Postcondition: An empty list of courses is created
    courses::courses() : head(nullptr), tail(nullptr), used(0){
    }

    //Precondition: none
    //Postcondition: Deep copy of courses is done.
    courses::courses(const courses& source) : head(nullptr), tail(nullptr), used(0){
        operator=(source);
    }

    //Precondition: none
    //Postcondition: Free's all allocations on heap
    courses::~courses(){
        node * cursor;
        while(head != nullptr){
            cursor = head;
            head = cursor->next();
            delete cursor;
        }
        head = tail = nullptr;
    }

    //---===[ Modification Members / Mutator Methods ]===---
    //Precondition: No course already exists in collection with same subject and catalog number
    //Postcondition: Adds the course to the end of list of courses. Returns a reference to the newly added course.
    course& courses::add(const course& courseIn){
        if(head == nullptr){
            head = new node(courseIn);
            tail = head;
            used++;
            return head->data();
        }
        tail->next() = new node(courseIn, nullptr, tail);
        tail = tail->next();
        used++;
        return tail->data();
    }

    void courses::remove(const course& courseIn){
        node * cursor;
        if(courseIn.getSubject() == head->getData().getSubject() && courseIn.getCatalog() == head->getData().getCatalog()){
            cursor = head;
            head = head->next();
            head->prev() = nullptr;
            delete cursor;
            return;
        }

        if(courseIn.getSubject() == tail->getData().getSubject() && courseIn.getCatalog() == tail->getData().getCatalog()){
            cursor = tail;
            tail = cursor->prev();
            tail->next() = nullptr;
            delete cursor;
            return;
        }

        for(cursor = head; cursor != nullptr; cursor = cursor->next()){
            if(cursor->getData().getSubject() == courseIn.getSubject() && cursor->getData().getCatalog() && courseIn.getCatalog()){
                cursor->prev() = cursor->next();
                cursor->next()->prev() = cursor->prev();
            }
        }
    }

    courses& courses::operator=(const courses& source){
        if(this == &source) {
            return *this;
        }

        node * cursor;
        while(head != nullptr){
            cursor = head;
            head = cursor->next();
            delete cursor;
        }

        used = 0;
        head = tail = nullptr;

        cursor = source.head;

        while(cursor != nullptr){
            add(cursor->getData());
            cursor = cursor->next();
        }
        return *this;
    }

    const course * courses::find(const char* subject, unsigned short catalog) const{
        if(head->getData().getSubject() == subject && head->getData().getCatalog() == catalog){
            return &(head->data());
        }

        if(tail->getData().getSubject() == subject && tail->getData().getCatalog() == catalog){
            return &(tail->data());
        }

        for(node * cursor = head; cursor != nullptr; cursor = cursor->next()){
            if(cursor->getData().getSubject() == subject && cursor->getData().getCatalog() == catalog){
                return &(cursor->getData());
            }
        }
        return nullptr;
    }

}