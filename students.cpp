/*
Program Name: Student Records
Programmer Name: Jordan Forbes
Purpose: Implementation of students.h file
Attempt Number: 1
Purpose for Update: n/a
Global Variable List: n/a
*/

#include "students.h"


namespace DS{
    //Precondition: none
    //Postcondition: New allocation created for students. Deep copy of students is done.
    students::students(const students & students) : capacity(students.capacity), count(students.count), data(nullptr), currentIndex(students.currentIndex){
        data = new student*[capacity]{nullptr};
        operator=(students);
        //std::copy(students.data, students.data + students.capacity, data);
//        for(size_t i = 0; i < students.capacity; ++i){
//            data[i] = students.data[i];
//        }
    }

    //Precondition: none
    //Postcondition: Free's all allocations on heap
    students::~students(){
        for(size_t i = 0; i < capacity; ++i){
            delete data[i];
        }
        delete [] data;
    }

    //Precondition: none
    //Postcondition: Any heap allocated by object is reclaimed and new allocation created for incoming students
    //      Deep copy is done. Reference to object is returned.
    students& students::operator=(const students& students){
        if(this == &students){
            return *this;
        }

        delete [] data;
        count = students.count;
        capacity = students.capacity;
        currentIndex = students.currentIndex;
        data = new student*[capacity]{nullptr};
        for(size_t i = 0; i < capacity; ++i){
            if(students.data[i] != nullptr){
                data[i] = new student(*students.data[i]);
            }
        }
        return *this;
    }

    //Precondition: Student name given
    //Postcondition: Student is added to the next free spot after current. If no free spot, array will be expanded
    //      by one and used for the new student. It is possible that a free spot exist BEFORE current, however,
    //      that will be ignored. Current is set to the new student. New student id is returned.
    size_t students::add(const std::string& studentName){
        student* * temp = nullptr;

        //Checks if next index is the same as the capacity
        if(currentIndex + 1 == capacity){
            //creates new array of size capacity + 1 of student pointers and initializes it to nullptr
            temp = new student*[capacity + 1]{nullptr};
            //copies all data into temp and adds new student to end
            //std::copy(data, data + capacity, temp);
            for(size_t i = 0; i < capacity; ++i){
                if(data[i] != nullptr){
                    temp[i] = new student(*data[i]);
                }
            }
            temp[capacity] = new student(capacity, studentName);
            //deletes data array
            delete [] data;
            //assigns temp array to data
            data = temp;
            //capacity is incremented by 1
            capacity++;
            //Number of Students Incremented by 1
            count++;
            //currentStudent is chanegd to next student
            currentIndex++;
        } else{
            //current student is changed to next student
            currentIndex++;
            data[currentIndex] = new student(currentIndex, studentName);
            //increments count by 1. capacity stays the same
            count++;
        }
        return currentIndex;
    }

    //Precondition: First argument is the requested student id <= 999,999,999 and the second is the student name
    //Postcondition: Student is added to collection and the student id is returned. If required, the size of the
    //      array container is expanded to one more than student_id. Current is set to the new student.
    size_t students::add(size_t id, const std::string & studentName) {
        student* * temp = nullptr;

        //Checks if id + 1 is >= the capacity
        if(id + 1 >= capacity){
            //creates new array of size id + 1 of student pointers and initializes it to nullptr
            temp = new student*[id + 1]{nullptr};
            //copies all data into temp and adds new student to end
            //std::copy(data, data + capacity, temp);
            for(size_t i = 0; i < capacity; ++i){
                if(data[i] != nullptr){
                    temp[i] = new student(*data[i]);
                }
            }
            temp[id] = new student(id, studentName);
            //deletes data array
            delete [] data;
            //assigns temp array to data
            data = temp;
            //changes capacity to size of id + 1
            capacity = id + 1;
            //Number of student incremented by 1
            count++;
            //current student is now student at id
            currentIndex = id;
            return id;
        } else{
            //current student is now student at id
            currentIndex = id;
            //creates new student at id index
            data[currentIndex] = new student(id, studentName);
            //increments count by 1. capacity stays the same
            count++;
            return id;
        }
    }

    //Precondition: Current is valid
    //Postcondition: Removes and deallocates current student.  Array size not reduced. Current moves to the next student.
    void students::deactivate(){
        delete data[currentIndex];
        next();
//        for(size_t i = currentIndex; i < capacity; ++i){
//            if(data[i] != nullptr){
//                currentIndex = i;
//                return;
//            }
//        }
    }

    //Precondition: Student exists at index id
    //Postcondition: Student reference is returns
    student& students::at(size_t id){
        return *data[id];
    }

    //Precondition: None
    //Postcondition: Current student is reset back to the first student in the collection
    const student* students::reset(){
        for(size_t i = 0; i < capacity; ++i){
            if(data[i] != nullptr){
                currentIndex = i;
                return data[currentIndex];
            }
        }
        return nullptr;
    }

    //Precondition: current is valid
    //Postcondition: Current student is set to the next student after current. Nullptr is returned if reached
    //      the end of the collection.
    const student* students::next(){
        if(currentIndex + 1 == capacity){
            return nullptr;
        } else{
            for(size_t i = currentIndex; i < capacity; ++i){
                if(data[i] != nullptr && data[i] != data[currentIndex]){
                    currentIndex = i;
                    return data[currentIndex];
                }
            }
        }
        return nullptr;
    }

    //Precondition: current is valid
    //Postcondition: Current student is set to the student before current. Nullptr is returned if reached
    //      the end of the collection.
    const student* students::prev(){
        if(currentIndex == 0){
            return nullptr;
        } else{
            for(size_t i = currentIndex - 1; i > 0; --i){
                if(data[i] != nullptr){
                    currentIndex = i;
                    return data[currentIndex];
                }
            }
        }
        return nullptr;
    }

    //Precondition: None
    //Postcondition: Returns pointer to the current student. Returns nullptr if no current student.
    const student* students::current(){
        if(data[currentIndex] == nullptr){
            return nullptr;
        }
        return data[currentIndex];
    }

    //Precondition: None
    //Postcondition: Changes the capacity of the students array. When newSize
    //	is smaller than current capacity, array is shrunk to newSize or size
    //	closest to newSize that still contains all students
    void students::resize(size_t newSize){
        student* * temp = nullptr;

        if(newSize < capacity){
            temp = new student * [currentIndex];
            std::copy(data, data + count, temp);
        } else{
            temp = new student*[newSize];
            std::copy(data, data + count, temp);
        }
    }
}