#include <iostream>

#ifndef PROJECT_VERSION
#define PROJECT_VERSION 3
#endif

#if PROJECT_VERSION==1
#include "courses.h"
#else
#include "courses_dll.h"
#endif
#if PROJECT_VERSION>=3
#include "student_bst.h"
#else
#include "student.h"
#endif
#include "students.h"
#include "grade.h"

using namespace DS;

int main() {

    courses c;
    c.add("COMSC", 101, "Computer Programming 1", 4);
    c.add("COMSC", 110, "Computer Programming 2", 4);
    c.add("COMSC", 201, "Data Structures", 4);
    c.add("COMSC", 210, "Discrete Structures", 4);
    c.add("COMSC", 217, "Computer Architecture", 4);
    c.add("ENG", 101, "Writing and Research", 3);
    c.add("ENG", 102, "Writing and Literature", 3);
    c.add("MATH", 161, "Precalculus", 4);
    c.add("MATH", 181, "Calculus 1", 4);
    c.add("MATH", 191, "Calculus 2", 4);
    c.add("MATH", 230, "Calculus 3", 4);
    c.add("MATH", 240, "Differential Equations", 4);
    c.add("PHYSC", 121, "Engineering Physics 1", 5);
    c.add("PHYSC", 122, "Engineering Physics 2", 5);
    c.add("BIOL", 115, "Biology 1", 4);
    c.add("BIOL", 127, "Biology 2", 4);

    //Output the list of available courses
    std::cout << c;

    students s;
    size_t id;

    //Add a student, id will auto generate
    id = s.add("George Carlin");
    s.at(id).addGrade(grade(c.find("COMSC", 101), 76));
    s.at(id).addGrade(grade(c.find("MATH", 181), 89));
    s.at(id).addGrade(grade(c.find("COMSC", 110), 68));

//    std::cout << s.at(id);

    //Add a student, id will auto generate
    id = s.add("Britney Spears");
    s.at(id).addGrade(grade(c.find("COMSC", 101), 97));
    s.at(id).addGrade(grade(c.find("COMSC", 110), 86));

    id = s.add(7, "Marcus");
    s.at(id).addGrade(grade(c.find("COMSC", 101), 98));

    //id = s.add(5, "Barney"); Bug here
    //s.at(id).addGrade(grade(c.find("COMSC", 101), 98));

    id = s.add(8, "Mr Bean");
    s.at(id).addGrade(grade(c.find("COMSC", 101), 98));

    id = s.add("Tom Hanks");
    s.at(id).addGrade(grade(c.find("COMSC", 101), 87));
    s.at(id).addGrade(grade(c.find("COMSC", 110), 81));
    s.at(id).addGrade(grade(c.find("COMSC", 201), 91));

    s.reset();
    std::cout << s;

    //The following call are here to confirm stubs exist
    //Recommended you change them to tests that confirm results
    if ( s.at(1) == s.at(2) || s.at(1) < s.at(2))
        std::cout << 1;
    student sc(100, "Sam Sam");
    student sc2(sc);
    sc = sc2;
    s.deactivate();
    s.prev();
    students s2(s);
    s.add("Megan");
    s = s2;
    courses c2(c);
    c.add("TEST", 100, "TEST", 4);
    c2 = c;

    return 0;
}
