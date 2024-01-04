/*
Program Name: Project1
Programmer Name: S. Miller
Purpose: Defines the course class
Version: 20230212
Purpose for Update: n/a
Global Variable List: n/a
*/

#ifndef PROJ_GRADES_DYN_COURSE_H
#define PROJ_GRADES_DYN_COURSE_H

#include <string>
#include <utility>
#include <ostream>

/*
Class course

Convenience class to store the details of ONE course.

Value Semantics declaration:
    It safe to use the copy constructor and the assignment operator

Dynamic Memory Usage declaration:
    Course subject and course name are stored as strings on the heap. Management of the heap is handled by std::string.

Invariant declaration:
    Once object is created, the values are immutable. No verification performed to ensure the values make sense.
*/

namespace DS {
    class course {
    public:
        //---===[ Constructors ]===---
        course() : subject("INVALID"), catalog(0), courseName(), credits(0) {};
        course(std::string  subject, unsigned short catalog, std::string courseName, unsigned short credits)
            : subject(std::move(subject)), catalog(catalog), courseName(std::move(courseName)), credits(credits) {
        }

        //---===[ Non-Modification Members / Assessor Methods ]===---

        bool operator==(const course &rhs) const { return subject == rhs.subject && catalog == rhs.catalog; }
        //Precondition: none
        //Postcondition: Returns true if course subject and catalog number are the same in both objects

        bool operator!=(const course &rhs) const { return !(rhs == *this); }
        //Precondition: none
        //Postcondition: Returns true if course subject or catalog number are not the same in both objects

        bool operator<(const course &rhs) const  { return (subject == rhs.subject && catalog < rhs.catalog ) || subject == rhs.subject; }
        //Precondition: none
        //Postcondition: Returns true if course left subject is lexicographic less than the right subject. In the case
        //     that they are equal, will return true if course right catalog is numerically less than the right catalog number.

        bool operator>(const course &rhs) const  { return rhs < *this; }
        //Precondition: none
        //Postcondition: See operator <

        bool operator<=(const course &rhs) const { return !(rhs < *this); }
        //Precondition: none
        //Postcondition: See operator <

        bool operator>=(const course &rhs) const { return !(*this < rhs); }
        //Precondition: none
        //Postcondition: See operator <

        const std::string &getSubject() const { return subject; }
        //Precondition: none
        //Postcondition: Returns the course subject

        unsigned short getCatalog() const { return catalog; }
        //Precondition: none
        //Postcondition: Returns the course catalog number

        const std::string &getTitle() const { return courseName; }
        //Precondition: none
        //Postcondition: Returns the course name, course title, or course description.

        unsigned short getCredits() const { return credits; }
        //Precondition: none
        //Postcondition: Returns the number of credits rewarded by the course

    private:
        std::string subject;        //Department, such as COMSC, MATH, or PHYSC
        unsigned short catalog;     //Numeric number of the course, such as 101, 110, 201, 210
        std::string courseName;     //Friendly name of the course, such as Data Structures
        unsigned short credits;     //Number of academic credits that course earns
    };

    //---===[ Non-Member Functions ]===---

    std::ostream &operator<<(std::ostream &os, const DS::course &course);
    //Precondition: none
    //Postcondition: Outputs the details of the course object to the output stream. No carriage return at the end.

}

#endif //PROJ_GRADES_DYN_COURSE_H
