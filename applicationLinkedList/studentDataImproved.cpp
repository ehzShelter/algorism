#include <iostream>
#include <string>
// standard c++11 headers
#include <regex>
#include <thread>
#include <chrono>
#include <tuple>

// studentData structure like a super variable
typedef struct studentData {
    std::string id;
    std::string name;
    std::string grade;
} student;

// typedef is so-called aliasing
typedef struct nodeStudent {
    studentData* student;
    struct nodeStudent* next;
} node;

// linked list first pointer
// use nullptr which is recommended for modern c++11
node* first = nullptr;

// prototypes
void progamRun(void);
void insertData(void);
void deleteData(void);
std::tuple<bool, node*> searchData(void);
void traverseData(void);
bool isEmpty(void);
void waitFew(void);
std::string inputData(const std::string& fieldName, const std::string& expression);
bool validate(const std::string& data, const std::string& expression);
void heapFree(void);
void middle(void);
void prepend(void);
void append(void);
int menuInsertion(void);
bool duplicateChecker(std::string id);
void searchAndUpdate(void);

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
                  << "5 - searchAndUpdate\n"
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
        else if (choice == 5) {
            searchAndUpdate();
        }
    } while (choice != 0);
}

int menuInsertion(void)
{
    std::cout << std::endl
              << "\nInsert Menu\n"
              << "1 - prepend\n"
              << "2 - append\n"
              << "3 - middle\n"
              << std::endl
              << std::endl;

    int insertChoice = stoi(inputData("insetionChoice", "\\d+"));

    return insertChoice;
}

void deleteData(void)
{
    if (isEmpty()) {
        std::cout << "Hell ...List is empty !" << std::endl;
        return;
    }

    std::string studentID = inputData("StudentIDAIUB", "\\d+");
    // get list's first node
    node* ptr = first;

    // myFlag to track element in existance
    bool myFlag = false;

    // try to deleteData student from list
    node* predptr = nullptr;
    while (ptr != nullptr) {
        // check for ID

        if (ptr->student->id == studentID) {
            // deleteData from first
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

bool duplicateChecker(std::string id)
{
    node* duptr = first;
    while (duptr != nullptr) {
        if (duptr->student->id == id) {
            std::cout << "\nID can't be Duplicated" << std::endl;
            return true;
        }
        duptr = duptr->next;
    }
    return false;
}

void prepend(void)
{
    // try to instantiate node for student
    node* newptr = new (node);
    if (newptr == nullptr) {
        delete (newptr);
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
    newptr->student->id = inputData("StudentIDAIUB", "\\d+");
    newptr->student->name = inputData("name", "\\D+");
    newptr->student->grade = inputData("StudentGrade", "[A-D][+-]?|F|UW|I");

    // avoid duplication
    if (duplicateChecker(newptr->student->id)) {
        delete (newptr->student);
        delete (newptr);
        return;
    }
    // check for empty list
    if (first == nullptr) {
        first = newptr;
    }
    // else check if student belongs at list's first
    else {
        newptr->next = first;
        first = newptr;
    }
}

void append(void)
{
    if (first == nullptr) {
        prepend();
        return;
    }

    node* predptr = first;

    // try to instantiate node for student
    node* newptr = new (node);
    if (newptr == nullptr) {
        return;
    }

    // initialize node
    newptr->next = nullptr;

    // try to instantiate student
    newptr->student = new (student);
    if (newptr->student == nullptr) {
        delete (newptr);
        return;
    }

    // try to initialize student
    newptr->student->id = inputData("StudentIDAIUB", "\\d+");
    newptr->student->name = inputData("name", "\\D+");
    newptr->student->grade = inputData("StudentGrade", "[A-D][+-]?|F|UW|I");

    while (true) {
        // avoid duplicates
        if (predptr->student->id == newptr->student->id) {
            std::cout << "Duplicate ID should be avoided" << std::endl;
            delete (newptr->student);
            delete (newptr);
            break;
        }

        else if (predptr->next == nullptr) {
            predptr->next = newptr;
            break;
        }
        predptr = predptr->next;
    }
}

void middle(void)
{

    int position = std::stoi(inputData("Insert Position", "\\d+"));

    if ((!isEmpty() || position == 1) && position > 0) {

        node* inserter = nullptr;
        node* scanner = first;

        for (int i = 1; i < position - 1; i++) {
            scanner = scanner->next;
            if (scanner == nullptr) {
                fprintf(stderr, "Invalid %dth(Nth) position Insertion\n,"
                                "so \"INSERTION SKIPPED\"\n",
                    position);
                return;
            }
        }
        // try to instantiate node for student
        node* newptr = new (node);
        if (newptr == nullptr) {
            return;
        }

        // initialize node
        newptr->next = nullptr;

        // try to instantiate student
        newptr->student = new (student);
        if (newptr->student == nullptr) {
            delete (newptr);
            return;
        }

        // try to initialize student
        newptr->student->id = inputData("StudentIDAIUB", "\\d+");
        newptr->student->name = inputData("name", "\\D+");
        newptr->student->grade = inputData("StudentGrade", "[A-D][+-]?|F|UW|I");
        // avoid duplication
        if (duplicateChecker(newptr->student->id)) {
            delete (newptr->student);
            delete (newptr);
            return;
        }

        if (position == 1 && isEmpty()) {
            first = newptr;
            return;
        }

        else if (position == 1 && !isEmpty()) {
            newptr->next = first;
            first = newptr;
            return;
        }

        inserter = scanner;

        newptr->next = inserter->next;
        inserter->next = newptr;
    }
    else {
        printf("Linked list is empty or invalid position\n");
    }
}

// It tries to insertData a student into list.
// EITHER it front or middle or end
void insertData(void)
{
    std::cout << "\nPlease Insert according to your choice" << std::endl;
    int insertChoice = menuInsertion();

    if (insertChoice == 1) {

        prepend();
    }
    // else try to insertData student in tail
    else if (insertChoice == 2) {

        append();
    }
    // check for insertion in middle
    else if (insertChoice == 3) {

        middle();
    }
    else {
        std::cout << "Bad choice" << std::endl;
        return;
    }
    traverseData();
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

// Searches for student in list via student's ID.
// A  tuple  is  an  object capable to hold a collection of elements. Each
// element can be of a different type.
std::tuple<bool, node*> searchData(void)
{
    // get list's first node
    node* ptr = first;

    if (isEmpty()) {
        std::cout << "Hell ...List is empty !" << std::endl;
        return std::make_tuple(false, ptr);
    }

    std::string studentID = inputData("StudentIDAIUB", "\\d+");

    // searchData for student
    while (ptr != nullptr) {
        if (ptr->student->id == studentID) {
            std::cout << "\nFound   ..!" << std::endl;

            std::cout << "NAME (" << ptr->student->name << ")"
                      << " Grade (" << ptr->student->grade << ")"
                      << " id (" << ptr->student->id << ")"
                      << std::endl;
            return std::tuple<bool, node*>(true, ptr);
        }
        ptr = ptr->next;
    }

    std::cout << "\nNot Found" << std::endl;
    return std::make_tuple(false, ptr);
}

void searchAndUpdate(void)
{
    bool boolean;
    node* pupil;

    std::tie(boolean, pupil) = searchData();

    if (boolean) {
        pupil->student->name = inputData("name", "\\D+");
        pupil->student->grade = inputData("StudentGrade", "[A-D][+-]?|F|UW|I");
    }
    traverseData();
}
