/*
Program Name: Project1
Programmer Name: S. Miller
Purpose: Defines the courses class as a doubly linked list
Version: 20230318
Purpose for Update: Updated pre/post of add
Global Variable List: n/a
*/


#ifndef PROJ_GRADES_COURSES_DLL_H
#define PROJ_GRADES_COURSES_DLL_H

#include <utility>
#include <cassert>
#include <string>
#include <iostream>
#include <iterator>

#include "course.h"
#include "node_dll_iterator.h"

namespace DS {

/*
Class courses

Class to store a collection of courses.

Value Semantics declaration:
    It safe to use the copy constructor and the assignment operator

Dynamic Memory Usage declaration:
    Each course is stored on the heap, all storage is managed by this class.

Invariant declaration:
    Once object is created, the values are immutable. No verification performed to ensure the values make sense.
*/

    class courses {
    public:
        typedef DSDLLI17::node<course> node;
        typedef node::iterator iterator;
        typedef node::const_iterator const_iterator;
        typedef node::reverse_iterator reverse_iterator;
        typedef node::const_reverse_iterator const_reverse_iterator;
        //---===[ Constructors ]===---
        //Precondition: none
        //Postcondition: An empty list of courses is created
        courses();

        //Precondition: none
        //Postcondition: Deep copy of courses is done.
        courses(const courses&);

        ~courses();
        //Precondition: none
        //Postcondition: Free's all allocations on heap

        //---===[ Modification Members / Mutator Methods ]===---
        course& add(const course& courseIn);
        //Precondition: No course already exists in collection with same subject and catalog number
        //Postcondition: Adds the course to the end of list of courses. Returns a reference to the newly added course.

        course& add(const std::string& subject, unsigned short catalog, const std::string& courseName, unsigned short credits) {
            return add(course(subject, catalog, courseName, credits));
        }
        //Precondition: No course already exists in collection with same subject and catalog number
        //Postcondition: Same as add(const course& courseIn)

        void remove(const course& courseIn);
        //Precondition: At most one course matches the passed subject and catalog number. No external references
        //      exist to the course.
        //Postcondition: Removes the course from the container that matches the passed subject and catalog number.

        void remove(const std::string& subject, unsigned short catalog) {
            return remove(course(subject, catalog, "", 0));
        }
        //Precondition: Same as remove(const course& courseIn)
        //Postcondition: Same as remove(const course& courseIn)

        courses& operator=(const courses&);
        //Precondition: none
        //Postcondition: Any heap allocated by object is reclaimed and new allocation created for incoming courses.
        //      Deep copy of courses is done.

        const course * find(const char* subject, unsigned short catalog) const;
        //Precondition: None
        //Postcondition: locates the course with passed subject and catalog number and returns a pointer to it.
        //      Returns nullptr if not existing.

        size_t size() const { return used; }
        //Precondition: none
        //Postcondition: returns the number of courses stored

        //Iterators
        iterator begin( ) { return {head}; }
        iterator end( )	{ return { }; } // Uses default constructor
        const_iterator begin( ) const { return {head}; }
        const_iterator end( ) const	{ return { }; } // Uses default constructor
        const_iterator cbegin( ) const { return {head}; }
        const_iterator cend ( ) const { return { }; } // Uses default constructor end( )
        reverse_iterator rbegin() { return {tail}; }
        reverse_iterator rend() { return {}; }
        const_reverse_iterator rbegin() const { return {tail}; }
        const_reverse_iterator rend() const { return {}; }
        const_reverse_iterator crbegin() const { return {tail}; }
        const_reverse_iterator crend() const { return {}; }

    private:
        size_t used;        //Number of courses stored in the linked list
        node * head;        //Pointer to the start of the courses linked list
        node * tail;        //Pointer to the last node of the courses linked list
    };

    std::ostream &operator<<(std::ostream &os, const courses &courses);
    //Precondition: none
    //Postcondition: Outputs each of the courses stored with a newline after each course.
}

#endif //PROJ_GRADES_COURSES_DLL_H
