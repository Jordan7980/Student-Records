/*
Program Name: Project1
Programmer Name: S. Miller
Purpose: Defines the students class
Version: 20230411
Purpose for Update: Added student_bst handling for project3
Global Variable List: n/a
*/
#ifndef PROJECT_VERSION
#define PROJECT_VERSION 3
#endif

#ifndef PROJ_GRADES_DYN_STUDENTS_H
#define PROJ_GRADES_DYN_STUDENTS_H

#include<cassert>
#include<string>
#include <ostream>
#if PROJECT_VERSION >= 3
#include "student_bst.h"
#else
#include "student.h"
#endif


namespace DS {

/*
Class students

Class to store a collection of students.
The idea of this collection is that every student can be looked up in constant time, provided you know their student id.
Student ids can be any integer from 1 to 999,999,999 it will have a potentially very large array. However, students
are removed from the collection when they are inactive (not registered). Therefore, not all array indexes will have a student.
Therefore, an array of pointers is used so that each student id (index) will be set to nullptr when no student exists
with that student id. When adding a student, the next available student id (after current) will be used, unless a
student id is provided by user.

Value Semantics declaration:
    It safe to use the copy constructor and the assignment operator

Dynamic Memory Usage declaration:
    Each student is stored on the heap. Heap management is done by this class.

Invariant declaration:
    Current will always reference
*/

    class students {
    public:
        //---===[ Constructors/Destructor ]===---
        students() : capacity(1), count(0), data(nullptr), currentIndex(0) { data = new student*[capacity]; data[0] = nullptr; }
        //Precondition: none
        //Postcondition: Default constructor allocates an array of size 1, no student is ever stored at index 0
        //      since student id's start at 1.

        students(const students&);
        //Precondition: none
        //Postcondition: New allocation created for students. Deep copy of students is done.

        ~students();
        //Precondition: none
        //Postcondition: Free's all allocations on heap

        //---===[ Modification Members / Mutator Methods ]===---

        students& operator=(const students&);
        //Precondition: none
        //Postcondition: Any heap allocated by object is reclaimed and new allocation created for incoming students
        //      Deep copy is done. Reference to object is returned.

        size_t add(const std::string&);
        //Precondition: Student name given
        //Postcondition: Student is added to the next free spot after current. If no free spot, array will be expanded
        //      by one and used for the new student. It is possible that a free spot exist BEFORE current, however,
        //      that will be ignored. Current is set to the new student. New student id is returned.

        size_t add(size_t, const std::string&);
        //Precondition: First argument is the requested student id <= 999,999,999 and the second is the student name
        //Postcondition: Student is added to collection and the student id is returned. If required, the size of the
        //      array container is expanded to one more than student_id. Current is set to the new student.

        void deactivate();
        //Precondition: Current is valid
        //Postcondition: Removes and deallocates current student.  Array size not reduced. Current moves to the next student.

        student& at(size_t id);
        //Precondition: Student exists at index id
        //Postcondition: Student reference is returns

        const student* reset();
        //Precondition: None
        //Postcondition: Current student is reset back to the first student in the collection

        const student* next();
        //Precondition: current is valid
        //Postcondition: Current student is set to the next student after current. Nullptr is returned if reached
        //      the end of the collection.

        const student* prev();
        //Precondition: current is valid
        //Postcondition: Current student is set to the student before current. Nullptr is returned if reached
        //      the end of the collection.

        const student* current();
        //Precondition: None
        //Postcondition: Returns pointer to the current student. Returns nullptr if no current student.

        //---===[ Non-Modification Members / Assessor Methods ]===---
		
        size_t size() const { return count; }
		//Precondition: None
        //Postcondition: Returns the number of students stored in container

    private:
        size_t capacity;        //Size of array allocation
        size_t count;           //Number of students stored (possibly sparse)
        student ** data;        //Array of pointers, pointing to students
        size_t currentIndex;    //Current index object is referencing

		//Private function, used internally
		//Precondition: None
        //Postcondition: Changes the capacity of the students array. When newSize 
		//	is smaller than current capacity, array is shrunk to newSize or size
		//	closest to newSize that still contains all students
        void resize(size_t newSize=0);
    };

    std::ostream &operator<<(std::ostream &, const students&);
    //Precondition: none
    //Postcondition: Outputs each of the students stored along with their courses and calculated gpa.
}

#endif //PROJ_GRADES_DYN_STUDENTS_H
