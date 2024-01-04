/*
Program Name: Student Records
Programmer Name: Jordan Forbes
Purpose: Implementation of students_bst.h file
Attempt Number: 1
Purpose for Update: n/a
Global Variable List: n/a
*/

#include "student_bst.h"

namespace DS{
    //Precondition: none
    //Postcondition: New allocation created for incoming students
    //      courses. Deep copy of grades is done.
    //      Grades bst is exactly the same arrangement (ie: no balance improvement).
    student::student(const student& source) : grades(nullptr), gradeCount(0), name("No Name"), studentId(0){
        operator=(source);
    }

    //Precondition: none
    //Postcondition: Any heap allocated by object is reclaimed and new allocation created for incoming students
    //      courses. Deep copy of grades is done. Reference to object is returned.
    //      Grades bst is exactly the same arrangement (ie: no balance improvement).
    student& student::operator=(const student& source){
        if(this == &source){
            return *this;
        }

        //Call clearGrades to delete this->grades and sets it to nullptr
        clearGrades(grades);

        //assigns name, student ID and root_ptr/grades from source
        name = source.name;
        studentId = source.studentId;
        gradeCount = source.gradeCount;
        grades = tree_copy(source.grades);

        return *this;
    }

    //Precondition: none
    //Postcondition: Adds the passed grade to students bst of grades. Grade count increases by one.
    //      The tree is ordered by grade (object level compare, see grade.h).
    void student::addGrade(const grade& g){
        addGrade(g, grades);
    }

    //Precondition: none
    //Postcondition: Returns true if gpa and credit count are equal of both objects. Student name is IGNORED.
    bool student::operator==(const student &rhs) const{
        return calcGPA() == rhs.calcGPA() && grades->data().getCourse().getCredits() == rhs.grades->data().getCourse().getCredits();
    }

    //Precondition: none
    //Postcondition: Returns true if left gpa is less than right gpa. If gpa equal, returns true if left has less
    //      credits than the right. Student name is IGNORED.
    bool student::operator<(const student &rhs) const{
        return calcGPA() < rhs.calcGPA() && grades->data().getCourse().getCredits() < rhs.grades->data().getCourse().getCredits();
    }

    //Precondition: root_ptr is grades pointer
    //Postcondition: Helper Function to creditsAttempted() that to help calculate total credits taken
    size_t creditsAttemptedHelper(student::node* root_ptr){
        if(root_ptr == nullptr){
            return 0;
        }
        return creditsAttemptedHelper(root_ptr->left()) + creditsAttemptedHelper(root_ptr->right()) + root_ptr->data().getCourse().getCredits();
    }

    //Precondition: none
    //Postcondition: Returns the number of credits student has attempted
    size_t student::creditsAttempted() const{
        return creditsAttemptedHelper(grades);
    }

    //Precondition: root_ptr is grades pointer
    //Postcondition: Helper Function to calcGPA() that to help calculate scale of each class
    double calcGPAHelper(student::node * root_ptr){
        if(root_ptr == nullptr){
            return 0;
        }

        return calcGPAHelper(root_ptr->left())
        + calcGPAHelper(root_ptr->right())
        + root_ptr->data().getCourse().getCredits() * root_ptr->data().getScale();

//        return (calcGPAHelper(root_ptr->left()) * root_ptr->data().getScale())  +
//        (calcGPAHelper(root_ptr->right()) * root_ptr->data().getScale()) +
//        (root_ptr->data().getCourse().getCredits() * root_ptr->data().getScale());
    }

    //Precondition: none
    //Postcondition: Calculates and returns the students gpa. GPA is based on average of grades weighted with
    //      course credits.
    double student::calcGPA() const{
        return calcGPAHelper(grades) / creditsAttempted();
    }

    //Precondition: None
    //Postcondition: Adds grade to appropriate spot in bst, either left or right. gradeCount is
    //increased by 1.
    //Recursive helper function of public addGrade
    void student::addGrade(const grade& g, node* root_ptr){
        //if tree empty a new grade is created
        if(root_ptr == nullptr){
            grades = new node(g);
            gradeCount += 1;
            //if grade <= current grade keeps going left until empty spot found
        }else if(g <= root_ptr->data()){
            if(root_ptr->left() == nullptr){
                root_ptr->left() = new node(g);
                gradeCount += 1;
            }else{
                addGrade(g, root_ptr->left());
            }
        }else{
            //if grade > current grade keeps going right until empty spot found
            if(root_ptr->right() == nullptr){
                root_ptr->right() = new node(g);
                gradeCount += 1;
            }else{
                addGrade(g, root_ptr->right());
            }
        }
    }

    //Precondition: none
    //Postcondition: output student grades in bst
    //Recursive helper function of public outputGrades
    //TODO: Student fills in the precondition/postcondition, include in your student_bst.cpp file
    void student::outputGrades(std::ostream &os, node* root_ptr) const{
        if(root_ptr == nullptr){
            return;
        }

        outputGrades(os, root_ptr->left());
        os << root_ptr->data() << '\n';
        outputGrades(os, root_ptr->right());
    }

    //Precondition: none
    //Postcondition: All nodes below root_ptr are freed, including root_ptr
    void student::clearGrades(node * root_ptr){
        if(root_ptr == nullptr){
            return;
        }

        clearGrades(root_ptr->left());
        clearGrades(root_ptr->right());
        delete root_ptr;

        root_ptr = nullptr;

        gradeCount = 0;
    }

    //Precondition: root_ptr is a pointer to the root of a subtree
    //Postcondition: A new tree is created in the heap as a duplicate of root_ptr, the new root is returned
    student::node* student::tree_copy(const node* root_ptr){

        if(root_ptr == nullptr){
            return nullptr;
        }else{
            node * copy_ptr = new node(root_ptr->data());
            copy_ptr->left() = tree_copy(root_ptr->left());
            copy_ptr->right() = tree_copy(root_ptr->right());
            return copy_ptr;
        }
    }
}