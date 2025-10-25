#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 10         //Max 10 students
#define MAX_NAME_LEN 20         //Max 20 name charscters
#define MAX_PHONE_LEN 11        //Max 11 telephone number
#define MAX_ADDRESS_LEN 20      //Max 20 address characters

struct Student{  //induvidual student data
    char name[MAX_NAME_LEN];
    int roll;
    char telephone[MAX_PHONE_LEN];
    char address[MAX_ADDRESS_LEN];
};

struct SReg{
    int count;  //number of students
    struct Student studentArray[MAX_STUDENTS];  //fixed student array size
};

/*
     **ASSOCIATED FUNCTIONS**
    (as given in the question)

    1. int add(SReg sr, Student s)          - adds a new student s to the student register sr. A new student is a student for whom the roll does not already exist in the student register sr. If s already exists in sr (that is, the roll field of s matches with roll field of some entry of sr), the function returns 0, otherwise the function returns 1. 
    2. Student get(SReg sr, int r)          - returns the student from sr whose roll field matches with r. If there is no such student in sr, the roll field of the returned Student is 0. 
    3. int delete(SReg sr, int r)           - deletes the student from sr whose roll field matches with r. If there is no such student in sr, the function returns 0; it returns 1 otherwise. 
    4. int modify(SReg sr, Student s)       - updates the fields of an existing student of sr whose roll field matches with that of s, taking values from the corresponding fields of s. The function returns 0 if no such student exists in sr; otherwise it returns 1.
    5. sortStudents(SReg sr)                - sorts the students of the student register sr in alphabetically ascending order of names. 
    6. int getCount(SReg sr)                - returns the number of students in the student register sr
    7. export(SReg sr, string fname)        - saves the student register sr to a file having name fname
    8. load(SReg sr, string fname)          - loads students in the student register sr from the file having name fname
    9. displayAll(struct Sreg sr)           - displays all the students along with all their details
    

*/

void entry(){
        int choice;

         /*
     option:

     1. Enter details of student
     2. Search student by roll no.
     3. Delete student by roll no.
     4. Modify student details by roll no.
     5. Sort student by name
     6. Count of total students
     7. Export filename
     8. Load filename
     9. Display Student Register

     *default*: "Invalid choice"

    */
        printf("--------------------------------\n");
        printf("\n=== Student Register System ===\n");
        printf("--------------------------------\n");
        printf(" 1. Enter details of student\n 2. Search student by roll no.\n 3. Delete student by roll no.\n 4. Modify student details by roll no.\n 5. Sort student by name\n 6. Count of total students\n 7. Export filename\n 8. Load filename\n 9. Display Student Register\n");
        printf("--------------------------------\n");
        

    }


//----------------------------------------------------------------------------------//

int add(struct SReg *sr, struct Student s) {
    if (sr->count >= MAX_STUDENTS)
        return 0;
    for (int i = 0; i < sr->count; i++) {
        if (sr->studentArray[i].roll == s.roll)
            return 0;
    }
    sr->studentArray[sr->count++] = s;
    return 1;
}


//----------------------------------------------------------------------------------//


int modify(struct SReg *sr, int r) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->studentArray[i].roll == r) {
            printf("Current Details:\n");
            printf("Name     : %s\n", sr->studentArray[i].name);
            printf("Roll     : %d\n", sr->studentArray[i].roll);
            printf("Telephone: %s\n", sr->studentArray[i].telephone);
            printf("Address  : %s\n\n", sr->studentArray[i].address);

            printf("Enter new name: ");
            scanf(" %s", sr->studentArray[i].name);

            printf("Enter new telephone: ");
            scanf(" %s", sr->studentArray[i].telephone);

            printf("Enter new address: ");
            scanf(" %s", sr->studentArray[i].address);

            return 1; 
        }
    }
    return 0; 
}


//----------------------------------------------------------------------------------//


struct Student get(struct SReg sr, int r) {
    for (int i = 0; i < sr.count; i++) {
        if (sr.studentArray[i].roll == r)
            return sr.studentArray[i];
    }
}


//----------------------------------------------------------------------------------//


int delete(struct SReg *sr, int roll) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->studentArray[i].roll == roll) {
            for (int j = i; j < sr->count - 1; j++) {
                sr->studentArray[j] = sr->studentArray[j + 1];
            }
            sr->count--;
            return 1;
        }
    }
    return 0;
}


//----------------------------------------------------------------------------------//


void sortStudents(struct SReg *sr) {
    for (int i = 0; i < sr->count - 1; i++) {
        for (int j = i + 1; j < sr->count; j++) {
            if (strcmp(sr->studentArray[i].name, sr->studentArray[j].name) > 0) {
                struct Student temp = sr->studentArray[i];
                sr->studentArray[i] = sr->studentArray[j];
                sr->studentArray[j] = temp;
            }
        }
    }
    printf("Students sorted alphabetically by name.\n");
}


//----------------------------------------------------------------------------------//


int getCount(struct SReg sr) {
    return sr.count;
}


//----------------------------------------------------------------------------------//


void export(struct SReg sr, char fname[]) {
    FILE *fp = fopen(fname, "w");   //w=to write
    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }
    for (int i = 0; i < sr.count; i++) {
        fprintf(fp, "%s,%d,%s,%s\n", sr.studentArray[i].name, sr.studentArray[i].roll,
                sr.studentArray[i].telephone, sr.studentArray[i].address);
    }
    fclose(fp);
    printf("Exported to file: %s\n", fname);
}


//----------------------------------------------------------------------------------//


void load(struct SReg *sr, char fname[]) {
    FILE *fp = fopen(fname, "r");   //r=to read
    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }
    sr->count = 0;
    while (fscanf(fp, " %s,%d,%s,%s\n", sr->studentArray[sr->count].name,
                  &sr->studentArray[sr->count].roll,
                  sr->studentArray[sr->count].telephone,
                  sr->studentArray[sr->count].address) != EOF) {
        sr->count++;
        if (sr->count >= MAX_STUDENTS) break;
    }
    fclose(fp);
    printf("Loaded from file: %s\n", fname);
}


//----------------------------------------------------------------------------------//


void displayAll(struct SReg sr) {
    if (sr.count == 0) {
        printf("No students to display.\n");
        return;
    }
    for (int i = 0; i < sr.count; i++) {
        printf("Name    : %s\n", sr.studentArray[i].name);
        printf("Roll No. : %d\n", sr.studentArray[i].roll);
        printf("Telehone   : %s\n", sr.studentArray[i].telephone);
        printf("Address : %s\n", sr.studentArray[i].address);
        printf("--------------------------------\n");
    }
}


//=================================================================================//
//=================================================================================//



int main(){
    struct SReg studentRegister = {0}; //initializing with 0 students
    struct Student s; //induvidual data in struct for student s
    int choice, roll, result;
    char YN; //Y=Yes, N=No
    char filename[100];

    while(1){   // To create a Loop
    entry();

    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("--------------------------------\n");

    switch (choice) {
    case 1:  //Enter details of student
         if (studentRegister.count >= MAX_STUDENTS) {
                printf("Register is full!\n");
                break;
            }

            printf("Enter student name: \n");
            scanf(" %s", s.name);

            printf("Enter roll number: \n");
            scanf("%d", &s.roll);

            printf("Enter phone number: \n");
            scanf(" %s", s.telephone);

            printf("Enter address: \n");
            scanf(" %s", s.address);

            if (add(&studentRegister, s))
                printf("Student added successfully!\n");
            else
                printf("Failed to add (duplicate roll or full register)!\n");
        break;

    case 2: //Search student by roll no.
        printf("Enter roll to modify: ");
        scanf("%d", &roll);
            if (modify(&studentRegister, roll))
                printf("Modified student data successfully!\n\n");
            else
                printf("Roll No. not found!\n\n");
        break;


    case 3: //Delete student by roll no.
        printf("Enter roll to delete: ");
        scanf("%d", &roll);
            if (delete(&studentRegister, roll))
                printf("Deleted student data successfully!\n");
            else
                printf("Roll No. not found!\n");
        break;

    case 4: //Modify student details by roll no.
        printf("Enter roll to modify: ");
        scanf("%d", &roll); 
            if (modify(&studentRegister, roll))
                printf("Modified student data successfully!\n\n");
            else
                printf("Roll No. not found!\n\n");
        break;

    case 5: //Sort student by name
        sortStudents(&studentRegister);
        break;

    case 6: //Count of total students
        printf("Total students in Student Register: %d\n", getCount(studentRegister));
        break;

    case 7: //Export filename 
        printf("Enter filename to export: ");
        scanf("%s", filename);
        export(studentRegister, filename);
        break;

    case 8: //Load filename 
        printf("Enter filename to load: ");
        scanf("%s", filename);
        load(&studentRegister, filename);
        break;

    case 9: //Display Student Register
        displayAll(studentRegister);
        break;


    default:
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("XXXXXX   INVALID CHOICE!  XXXXXX\n");
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    }
}

}