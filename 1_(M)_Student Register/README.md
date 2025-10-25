# 🧾 Assignment 1 – Student Register using Arrays  
**Course**: Data Structure Lab (CS 2172)  
**Institute**: IIEST Shibpur  
**Language**: C 
**Duration**: 1 week  

---

## 📘 Problem Statement

Design and implement a simple **Student Register** in C using fixed-size arrays and structures. The register should allow operations such as:

- Add a new student 👤  
- Retrieve a student by roll number 🔍  
- Modify student details 🛠️  
- Delete a student ❌  
- Count total students 🔢  
- Sort students alphabetically by name 🗂️  
- Save to a file 💾  
- Load from a file 📂  

No dynamic memory allocation is allowed. Use only `scanf`, `printf`, `fopen`, etc.

---

## 🧱 Data Structures

```c
#define MAX_STUDENTS 10

struct Student {
    char name[20];        // Format: "LastName, FirstName"
    int roll;             // 6-digit number, must not start with 0
    char telephone[11];   // Non-empty string
    char address[20];     // Can be empty
};

struct SReg {
    int count; // Initially 0
    struct Student studentArray[MAX_STUDENTS];
};
```

---

## 🛠️ Functional Requirements

| Function Signature | Description |
|--------------------|-------------|
| `int add(struct SReg *sr, struct Student s)` | Adds a new student to the register if the roll is unique. Returns `1` if successful, `0` otherwise. |
| `struct Student get(struct SReg sr, int r)` | Returns the student with the specified roll number. If not found, returned student's `roll` is `0`. |
| `int delete(struct SReg *sr, int r)` | Deletes the student with the given roll number. Returns `1` if deleted, `0` if not found. |
| `int modify(struct SReg *sr, struct Student s)` | Modifies details of the student whose roll matches. Returns `1` if successful, `0` if not found. |
| `void sortStudents(struct SReg *sr)` | Sorts students alphabetically by `name` in ascending order. |
| `int getCount(struct SReg sr)` | Returns the total number of students in the register. |
| `void export(struct SReg sr, char *fname)` | Saves all student data to a file with the given name. |
| `void load(struct SReg *sr, char *fname)` | Loads student data from the file into the register. |

---

## 🧪 Sample Usage in `main()`

Your `main()` function should demonstrate the following:

- Add multiple students
- Display total student count
- Get and print a student by roll number
- Modify a student
- Delete a student
- Sort and print the sorted list
- Export to and load from a file

---

## 📁 Folder Structure

```
assignment1/
├── student_register.c      # Full source code
├── students.txt            # Example file used in export/load
└── README.md               # This file
```

---

## ⚠️ Constraints

- Only 10 students can be stored (`MAX_STUDENTS`)
- Roll numbers must be 6-digit integers (and unique)
- Telephone number must not be empty
- Use only static memory and `scanf`/`printf`/file I/O

---

## 📚 Disclaimer

This project is part of the **CS 2172 – Data Structure Lab** at **IIEST Shibpur**.  
All code and documentation is created for academic and learning purposes only.
