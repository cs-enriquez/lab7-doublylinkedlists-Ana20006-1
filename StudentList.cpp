#include <iostream>
using namespace std;

// Student class definition
class Student {
public:
    string name;
    int id;
    float GPA;

    Student(string n = "unknown", int i = -1, float g = 0.0) : name(n), id(i), GPA(g) {}
};

// Node class definition for doubly linked list
class Node {
public:
    Student data;
    Node* next;
    Node* prev;

    Node(Student s) : data(s), next(nullptr), prev(nullptr) {}
};

// StudentList class definition
class StudentList {
private:
    Node* head;    // Pointer to the head of the list
    Node* tail;    // Pointer to the tail of the list
    int numStudents; // Number of students in the list

public:
    // Constructor to initialize the list
    StudentList() {
        head = nullptr;
        tail = nullptr;
        numStudents = 0;
    }

    // Return the number of students currently in the list
    int listSize() {
        return numStudents;
    }

    // Add a Node with a student to the front (head) of the list
    void addFront(Student s) {
        Node* newNode = new Node(s);
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode; // If the list was empty, set tail to newNode
        }
        numStudents++;
    }

    // Add a Node with a student to the back (tail) of the list
    void addBack(Student s) {
        Node* newNode = new Node(s);
        newNode->prev = tail;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == nullptr) {
            head = newNode; // If the list was empty, set head to newNode
        }
        numStudents++;
    }

    // Print out the names of each student in the list
    void printList() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
        } else {
            Node* current = head;
            while (current != nullptr) {
                cout << current->data.name << endl;
                current = current->next;
            }
        }
    }

    // Remove the Node with the student at the back (tail) of the list
    void popBack() {
        if (tail == nullptr) {
            cout << "Error: List is empty." << endl;
            return;
        }

        Node* temp = tail;
        tail = tail->prev; // Move tail to the previous node

        if (tail != nullptr) {
            tail->next = nullptr; // Disconnect the last node
        } else {
            head = nullptr; // If the list is now empty
        }

        delete temp; // Free memory
        numStudents--;
    }

    // Remove the Node with the student at the front (head) of the list
    void popFront() {
        if (head == nullptr) {
            cout << "Error: List is empty." << endl;
            return;
        }

        Node* temp = head;
        head = head->next; // Move head to the next node

        if (head != nullptr) {
            head->prev = nullptr; // Disconnect the first node
        } else {
            tail = nullptr; // If the list is now empty
        }

        delete temp; // Free memory
        numStudents--;
    }

    // Insert a student at the position "index"
    void insertStudent(Student s, int index) {
        if (index < 0 || index > numStudents) {
            cout << "Index is not in range. Student added to end of list." << endl;
            addBack(s);
            return;
        }
        if (index == 0) {
            addFront(s);
            return;
        }
        if (index == numStudents) {
            addBack(s);
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        Node* newNode = new Node(s);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        numStudents++;
    }

    // Find the student with the given id number and return them
    Student retrieveStudent(int idNum) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.id == idNum) {
                return current->data;
            }
            current = current->next;
        }
        cout << "No student found with ID number " << idNum << endl;
        return Student("nobody", -1, 0.0); // Return a dummy student
    }

    // Remove a Node with a student from the list with a given id number
    void removeStudentById(int idNum) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.id == idNum) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    } else {
                        tail = nullptr; // List is now empty
                    }
                } else {
                    current->prev->next = current->next;
                }
                if (current == tail) {
                    tail = current->prev;
                    if (tail != nullptr) {
                        tail->next = nullptr;
                    }
                } else {
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    }
                }
                delete current; // Free memory
                numStudents--;
                return;
            }
            current = current->next;
        }
        cout << "No student found with ID number." << endl;
    }

    // Change the GPA of the student with the given id number to newGPA
    void updateGPA(int idNum, float newGPA) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.id == idNum) {
                current->data.GPA = newGPA;
                return;
            }
            current = current->next;
        }
        cout << "No student found with ID number." << endl;
    }

    // Add all students from otherList to this list
    void mergeList(StudentList& otherList) {
        if (otherList.head == nullptr) {
            return; // Nothing to merge
        }
        if (head == nullptr) {
            head = otherList.head; // If current list is empty
            tail = otherList.tail;
        } else {
            tail->next = otherList.head; // Connect to the end of this list
            otherList.head->prev = tail;
            tail = otherList.tail;
        }
        numStudents += otherList.numStudents; // Update size
        otherList.head = nullptr; // Empty the other list
        otherList.tail = nullptr;
        otherList.numStudents = 0;
    }

    // Create a StudentList of students whose GPA is at least minGPA
    StudentList honorRoll(float minGPA) {
        StudentList honorRollList;
        Node* current = head;
        while (current != nullptr) {
            if (current->data.GPA >= minGPA) {
                honorRollList.addBack(current->data); // Add student to honor roll
            }
            current = current->next;
        }
        return honorRollList; // Return the new list
    }
};
