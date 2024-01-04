/*
Program Name: Project1
Programmer Name: S. Miller
Purpose: Defines the grade class
Version: 20230212
Purpose for Update: n/a
Global Variable List: n/a
*/

#ifndef PROJ_GRADES_DYN_GRADE_H
#define PROJ_GRADES_DYN_GRADE_H

#include "course.h"

namespace DS {

/*
Class grade

Convenience class to store the details of ONE grade.

Value Semantics declaration:
    It safe to use the copy constructor and the assignment operator

Dynamic Memory Usage declaration:
    None directly created

Invariant declaration:
    Once object is created, the values are immutable. No verification performed to ensure the values make sense.
*/

    class grade {
    public:
        //---===[ Constructors ]===---
        grade() : numericGrade(0), coursePtr(nullptr) {}
        explicit grade(const course * coursePtr) : numericGrade(0), coursePtr(coursePtr) {}
        explicit grade(const course * coursePtr, double numericGrade) : numericGrade(numericGrade), coursePtr(coursePtr) {}

        //---===[ Non-Modification Members / Assessor Methods ]===---
        const course& getCourse() const { return *coursePtr; }
        //Precondition: none
        //Postcondition:

        double getPercentage() const { return numericGrade; }
        //Precondition: none
        //Postcondition:

        double getScale() const { return static_cast<double>(scaleInt())/10.0; }
        //Precondition: none
        //Postcondition: Returns true if course subject and catalog number are the same in both objects

        const char* getLetter() const {
        //Precondition: none
        //Postcondition: Returns true if course subject and catalog number are the same in both objects
            switch(scaleInt()) {
                case 40: return "A";
                case 35: return "B+";
                case 30: return "B";
                case 25: return "C+";
                case 20: return "C";
                case 10: return "D";
                default: return "F";
            }
        }

        bool operator==(const grade &rhs) const { return numericGrade == rhs.numericGrade && *coursePtr == *rhs.coursePtr; }
        //Precondition: none
        //Postcondition: Returns true both the numerical grades and the pointed to courses are the same

        bool operator!=(const grade &rhs) const { return !(rhs == *this); }
        //Precondition: none
        //Postcondition: Returns true both the numerical grades or the pointed to courses are NOT the same

        bool operator<(const grade &rhs) const { return *coursePtr < *rhs.coursePtr || (*coursePtr == *rhs.coursePtr && numericGrade < rhs.numericGrade); }
        //Precondition: none
        //Postcondition: Returns true if the lefts course is less than the right OR the lefts numerical is less than the right

        bool operator>(const grade &rhs) const { return rhs < *this; }
        //Precondition: none
        //Postcondition: See <, except does >

        bool operator<=(const grade &rhs) const { return !(rhs < *this); }
        //Precondition: none
        //Postcondition: See <, except does <=

        bool operator>=(const grade &rhs) const { return !(*this < rhs); }
        //Precondition: none
        //Postcondition: See <, except does >=

    private:
        double numericGrade;        // Student grade out of 100 (ie: percentage)
        const course * coursePtr;   // Pointer to the related course

        //Allows toLettter to be a switch statement
        [[nodiscard]] unsigned short scaleInt() const {
        //Precondition: none
        //Postcondition: Internal function that calculated the GPA scale of numerical grade.
        //      However, it is returned as an integer so that dependant function(s) can use quick switch statements
            if ( numericGrade >= 90 )
                return 40;
            else if ( numericGrade >= 85)
                return 35;
            else if ( numericGrade >= 80)
                return 30;
            else if ( numericGrade >= 75)
                return 25;
            else if ( numericGrade >= 70)
                return 20;
            else if ( numericGrade >= 60)
                return 10;
            else
                return 0;
        }
    };

    std::ostream& operator<<(std::ostream &os, const grade &grade);
    //Precondition: none
    //Postcondition: Outputs the details of the grade object to the output stream. No carriage return at the end.
}

#endif //PROJ_GRADES_DYN_GRADE_H
