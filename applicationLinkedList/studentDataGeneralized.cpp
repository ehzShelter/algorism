#include <iostream>
#include <string>
// standard c++11 headers
#include <regex>
#include <thread>
#include <chrono>

// studentData structure like a super variable

typedef struct studentData {
    std::string id;
    std::string name;
    std::string grade;
} student;

// remember this is s self-referential structure nodeStudent
// typedef is so-called aliasing

typedef struct nodeStudent {
    studentData* student;
    struct nodeStudent* next;
} node;

// linked list head pointer
// use nullptr which is recommended for modern c++11
node* first = nullptr;

// prototypes
void progamRun(void);
void insertData(void);
void deleteData(void);
void searchData(void);
void traverseData(void);
bool isEmpty(void);
void waitFew(void);
std::string inputData(const std::string& fieldName, const std::string& expression);
bool validate(const std::string& data, const std::string& expression);
void heapFree(void);

int main(void)
{
    progamRun();
    // release runtime memory before quitting
    heapFree();
}

void progamRun(void)
{
    // print instructions
    int choice;
    do {
        std::cout << "\nMENU\n\n"
                  << "1 - insertData\n"
                  << "2 - deleteData\n"
                  << "3 - searchData\n"
                  << "4 - traverseData\n"
                  << "0 - quit\n\n";

        choice = std::stoi(inputData("choice", "\\d+"));

        if (choice == 0) {
            std::cout << "Programm quits\n";
        }
        else if (choice == 1) {
            insertData();
        }
        else if (choice == 2) {
            deleteData();
        }
        else if (choice == 3) {
            searchData();
        }
        else if (choice == 4) {
            traverseData();
        }
    } while (choice != 0);
}

void deleteData(void)
{
    if (isEmpty()) {
        std::cout << "Hell ...List is empty !" << std::endl;
        return;
    }

    // std::string studentID = inputData("StudentIDAIUB", "\\d+");
    std::string studentID = inputData("StudentIDAIUB", "\\d+\\-\\d+\\-\\d+");
    // get list's first node
    node* ptr = first;

    // myFlag to track element in existance
    bool myFlag = false;

    // try to deleteData student from list
    node* predptr = nullptr;
    while (ptr != nullptr) {
        // check for ID

        if (ptr->student->id == studentID) {
            // deleteData from head
            if (ptr == first) {
                first = ptr->next;
                delete (ptr->student);
                delete (ptr);
            }

            // deleteData from middle or tail
            else {
                predptr->next = ptr->next;
                delete (ptr->student);
                delete (ptr);
            }
            // confirmation flag to delete
            myFlag = true;

            // all done
            break;
        }
        else {
            predptr = ptr;
            ptr = ptr->next;
        }
    }

    if (myFlag == false) {
        std::cout << "\nID is not there to delete" << std::endl;
    }

    // traverseData list
    traverseData();
}

// It tries to insertData a student into list.
// EITHER it front or middle or end
void insertData(void)
{
    // try to instantiate node for student
    // can be used new or delete operator here but surely this is intutive
    node* newptr = new (node);
    if (newptr == nullptr) {
        delete(newptr);
        return;
    }

    // initialize node
    newptr->next = nullptr;

    // try to instantiate student
    newptr->student = new (student);
    if (newptr->student == nullptr) {
        delete (newptr->student);
        return;
    }


    // try to initialize student

    // If you want only numeric ID
    // newptr->student->id = inputData("StudentIDAIUB", "\\d+");
    // Specific AIUB Student ID
    // Pattern 15-30142-2
    newptr->student->id = inputData("StudentIDAIUB", "\\d+\\-\\d+\\-\\d+");
    newptr->student->name = inputData("name", "\\D+");
    newptr->student->grade = inputData("StudentGrade", "[A-D][+-]?|F|UW|I");

    // check for empty list
    if (first == nullptr) {
        first = newptr;
    }

    // else check if student belongs at list's head
    else if (newptr->student->id < first->student->id) {
        newptr->next = first;
        first = newptr;
    }

    // else try to insertData student in middle or tail
    else {
        node* predptr = first;
        while (true) {
            // avoid duplicates
            if (predptr->student->id == newptr->student->id) {
                delete (newptr->student);
                delete (newptr);
                break;
            }

            // check for insertion at tail
            else if (predptr->next == nullptr) {
                predptr->next = newptr;
                break;
            }

            // check for insertion in middle
            else if (predptr->next->student->id > newptr->student->id) {
                newptr->next = predptr->next;
                predptr->next = newptr;
                break;
            }

            // update pointer
            predptr = predptr->next;
        }
    }

    // traverseData list
    traverseData();
}

// Searches for student in list via student's ID.
void searchData(void)
{
    if (isEmpty()) {
        std::cout << "Hell ...List is empty !" << std::endl;
        return;
    }
    // prompt user for ID
    // std::string studentID = inputData("StudentIDAIUB", "\\d+");
    std::string studentID = inputData("StudentIDAIUB", "\\d+\\-\\d+\\-\\d+");
    // get list's first node
    node* ptr = first;

    // searchData for student
    bool found = false;
    while (ptr != nullptr) {
        if (ptr->student->id == studentID) {
            found = true;
            std::cout << "\nFound   ..!" << std::endl;

            std::cout << "NAME (" << ptr->student->name << ")"
                      << " Grade (" << ptr->student->grade << ")"
                      << " id (" << ptr->student->id << ")"
                      << std::endl;
        }
        ptr = ptr->next;
    }

    if (found == false) {
        std::cout << "Not Found" << std::endl;;
    }
}

// Traverses list, printing its numbers.
void traverseData(void)
{
    // traverseData list
    std::cout << "\nList contains: " << std::endl;
    node* ptr = first;
    while (ptr != nullptr) {
        std::cout << "NAME (" << ptr->student->name << ")"
                  << " Grade (" << ptr->student->grade << ")"
                  << " id (" << ptr->student->id << ")"
                  << std::endl;
        ptr = ptr->next;
    }

    std::cout << std::endl
              << std::endl;

      waitFew();
}

bool isEmpty(void)
{
    return (first == nullptr) ? true : false;
}

void waitFew(void)
{
    // C++11 threading
    // pause before continuing
    // http://en.cppreference.com/w/cpp/thread/sleep_for
    // The process thread will hold for 1 seconds
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool validate(const std::string& data, const std::string& expression)
{
    // regex c++11
    // http://cpprocks.com/files/c++11-regex-cheatsheet.pdf
    std::regex validationExpression = std::regex(expression);
    return std::regex_match(data, validationExpression);
}

std::string inputData(const std::string& fieldName, const std::string& expression)
{
    std::string data;

    std::cout << "Enter " << fieldName << ": ";
    getline(std::cin, data);

    // validate the data
    while (!(validate(data, expression))) {
        std::cout << "Invalid " << fieldName << ".\n";
        std::cout << "Enter " << fieldName << ": ";

        getline(std::cin, data);
    }
    return data;
}

// release heapMemory after execution
void heapFree(void)
{
    node* ptr = first;
    while (ptr != nullptr) {
        node* predptr = ptr;
        ptr = ptr->next;
        if (predptr->student != nullptr) {
            delete (predptr->student);
        }
        delete (predptr);
    }
}
