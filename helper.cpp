/*
Program Name: Project2
Programmer Name: S. Miller
Purpose: Put all ostream << operator overloads in one file
Version: 20230411
Purpose for Update: Added new version of student output for project3
Global Variable List: n/a

NOTE:
This file supports multiple different versions of the project.
Changing the "active" version requires that you change the compiler variable PROJECT_VERSION.
For project 2 this should remain as 2. However, if you place this file into your project 1 code, you will
want to change it to 1.

*/

//You may need to copy the next three lines to your code OR make sure helper.cpp is defined in the beginning of CMakeLists.txt
#ifndef PROJECT_VERSION
#define PROJECT_VERSION 3
#endif

#include<iomanip>
#include "course.h"
#include "grade.h"
#if PROJECT_VERSION >= 2
#include "courses_dll.h"
#else
#include "courses.h"
#endif
#if PROJECT_VERSION >= 3
#include "student_bst.h"
#else
#include "student.h"
#endif
#include "students.h"

namespace DS {

    std::ostream& operator<<(std::ostream &os, const students& obj) {
        students studentsCopy(obj); //Need to create a copy of object due to needing to change object state (ie: current)
        const student * s = studentsCopy.current();
        if ( s == nullptr ) //When current is invalid, start from beginning of collection
            s = studentsCopy.reset();
        while ( s != nullptr ) {
            os << *s << std::endl;
            s = studentsCopy.next();
        }
        return os;
    }

#if PROJECT_VERSION >= 3

    std::ostream &operator<<(std::ostream &os, const student &student) {
        //
        os <<  std::setfill('0') << std::setw(9) << student.getId()
           << "\t" << student.getName() << std::endl;
        if ( student.getGradeCount() > 0 ) {
            student.outputGrades(os);
            os << "\tGPA:\t" << std::setprecision(3) << student.calcGPA();
        } else {
            os << "\tNo grades";
        }
        return os;
    }
#else
    std::ostream &operator<<(std::ostream &os, const student &student) {
        //
        os <<  std::setfill('0') << std::setw(9) << student.getId()
           << "\t" << student.getName() << std::endl;
        if ( student.getGradeCount() > 0 ) {
            for (size_t i = 0; i < student.getGradeCount(); ++i)
                os << student.getGrades()[i] << std::endl;
            os << "\tGPA:\t" << std::setprecision(3) << student.calcGPA();
        } else {
            os << "\tNo grades";
        }
        return os;
    }
#endif

    std::ostream& operator<<(std::ostream &os, const grade &grade) {
        os << "\t" << grade.getLetter() << "\t" << grade.getCourse();
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const course &course) {
        os << course.getSubject() << " " << course.getCatalog()
            << "\t" << course.getCredits() << "cr"
            << "\t" << course.getTitle();
        return os;
    }

#if PROJECT_VERSION >= 2
    std::ostream &operator<<(std::ostream &os, const courses & courses) {
        for (auto c : courses) {
            os << c << std::endl;
        }
        return os;
    }
#else
    std::ostream &operator<<(std::ostream &os, const courses &courses) {
        for (size_t i = 0; i < courses.size(); ++i) {
            os << courses.at(i) << std::endl;
        }
        return os;
    }
#endif

}
