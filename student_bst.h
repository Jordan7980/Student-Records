/*
Program Name: Project1
Programmer Name: S. Miller
Purpose: Defines the student class implemented with a binary search tree
Version: 20230411
Purpose for Update: changed to binary search tree
Global Variable List: n/a
*/

#ifndef PROJ_GRADES_DYN_STUDENT_BST_H
#define PROJ_GRADES_DYN_STUDENT_BST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include "grade.h"
#include "course.h"
#include "node_btree.h"

namespace DS {


/*
Class student

Convenience class to store the details of ONE student.

Value Semantics declaration:
    It safe to use the copy constructor and the assignment operator

Dynamic Memory Usage declaration:
    Student name is stored as string on the heap. Grades are stored manually on the heap.

Invariant declaration:
    Once object is created, the values are immutable other than grades. No verification performed to ensure the values make sense.
*/

    class student {
    public:
        typedef DSBTREE::node<grade> node;
        //---===[ Constructors/Destructor ]===---
        student() : studentId(0), name("NONAME"), grades(nullptr), gradeCount(0) {}
        explicit student(size_t studentId, std::string name) : studentId(studentId), name(std::move(name)), grades(nullptr), gradeCount(0) {}
        explicit student(size_t studentId, char* name) : studentId(studentId), name(name), grades(nullptr), gradeCount(0) {}

        student(const student&);
        //Precondition: none
        //Postcondition: New allocation created for incoming students
        //      courses. Deep copy of grades is done.
        //      Grades bst is exactly the same arrangement (ie: no balance improvement).

        ~student() { clearGrades(); };
        //Precondition: none
        //Postcondition: Free's all allocations on heap

        //---===[ Modification Members / Mutator Methods ]===---
        //Precondition: none
        //Postcondition: Any heap allocated by object is reclaimed and new allocation created for incoming students
        //      courses. Deep copy of grades is done. Reference to object is returned.
        //      Grades bst is exactly the same arrangement (ie: no balance improvement).
        student& operator=(const student&);

        void addGrade(const grade& g);
        //Precondition: none
        //Postcondition: Adds the passed grade to students bst of grades. Grade count increases by one.
        //      The tree is ordered by grade (object level compare, see grade.h).

        //---===[ Non-Modification Members / Assessor Methods ]===---
        bool operator==(const student &rhs) const;
        //Precondition: none
        //Postcondition: Returns true if gpa and credit count are equal of both objects. Student name is IGNORED.

        bool operator!=(const student &rhs) const { return !(rhs == *this); }
        //Precondition: none
        //Postcondition: Returns true if gpa or credit count are not equal of both objects. Student name is IGNORED.

        bool operator<(const student &rhs) const;
        //Precondition: none
        //Postcondition: Returns true if left gpa is less than right gpa. If gpa equal, returns true if left has less
        //      credits than the right. Student name is IGNORED.

        bool operator>(const student &rhs) const { return rhs < *this; }
        //Precondition: none
        //Postcondition: See <, except >

        bool operator<=(const student &rhs) const { return !(rhs < *this); }
        //Precondition: none
        //Postcondition: See <, except <=

        bool operator>=(const student &rhs) const { return !(*this < rhs); }
        //Precondition: none
        //Postcondition: See <, except >=

        size_t getId() const { return studentId; }
        //Precondition: none
        //Postcondition: Returns the unique student identification number

        const std::string& getName() const { return name; }
        //Precondition: none
        //Postcondition: Returns the students name

        const node* getGrades() const { return grades; }
        //Precondition: none
        //Postcondition: Returns the root pointer of the grades bst

        size_t getGradeCount() const { return gradeCount; }
        //Precondition: none
        //Postcondition: Returns the number of grades the student has

        size_t creditsAttempted() const;
        //Precondition: none
        //Postcondition: Returns the number of credits student has attempted

        double calcGPA() const;
        //Precondition: none
        //Postcondition: Calculates and returns the students gpa. GPA is based on average of grades weighted with
        //      course credits.

        //Precondition: none
        //Postcondition: Outputs each grade to the passed ostream, each grade ends in an endl
        void outputGrades(std::ostream &os) const { outputGrades(os, grades); };


    private:
        size_t studentId;   // Unique identification number of the student, if provided, assumed it is unique
        std::string name;   // First and last name of the student
        node * grades;     // Pointer to the root node of the student grades binary search tree
        size_t gradeCount;  // The quantity of course grades the student has

        void addGrade(const grade& g, node* root_ptr);
        //Recursive helper function of public addGrade
        //TODO: Student fills in the precondition/postcondition, include in your student_bst.cpp file

        void outputGrades(std::ostream &os, node* root_ptr) const;
        //Recursive helper function of public outputGrades
        //TODO: Student fills in the precondition/postcondition, include in your student_bst.cpp file

        //Precondition: none
        //Postcondition: All grades are removed and freed from heap
        void clearGrades() { clearGrades(grades); gradeCount = 0; };

        //Precondition: none
        //Postcondition: All nodes below root_ptr are freed, including root_ptr
        void clearGrades(node * root_ptr);

        //Precondition: root_ptr is a pointer to the root of a subtree
        //Postcondition: A new tree is created in the heap as a duplicate of root_ptr, the new root is returned
        node* tree_copy(const node* root_ptr);

    };

    std::ostream& operator<<(std::ostream &os, const student &student);
    //Precondition: none
    //Postcondition: Outputs student along with their courses and calculated gpa.
}
#endif //PROJ_GRADES_DYN_STUDENT_BST_H
