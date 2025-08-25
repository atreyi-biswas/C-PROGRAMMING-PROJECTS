#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define MAX_STUDENTS 10         //Max 10 students(Not needed here)
//#define MAX_NAME_LEN 20         //Max 20 name charscters(Not needed here)
#define MAX_PHONE_LEN 11        //Max 11 telephone number
//#define MAX_ADDRESS_LEN 20      //Max 20 address characters(Not needed here)

typedef struct Student{  //induvidual student data
    char *name;                       // CHANGED (was fixed-size array, now dynamic)
    int roll;
    char telephone[MAX_PHONE_LEN];    // fixed size (unchanged)
    char *address;                    // CHANGED (was fixed-size array, now dynamic)
} Student;

typedef struct SReg{
    int maxStuds;                     // CHANGED (can define at runtime)
    int count;                        // number of students
    Student **arrStudPtr;             // CHANGED (was fixed array, now dynamic array of pointers)
} SReg;

//NEW FUNCTIONS

Student* createStudentRecord() {
    Student *s = (Student*)malloc(sizeof(Student));   // malloc for one student struct
    if (!s) return NULL;

    char temp[200];

    printf("Enter student name: ");
    scanf(" %[^\n]", temp);  //read all characters until a newline (\n) is found.
    s->name = (char*)malloc(strlen(temp) + 1);        // malloc for name
    strcpy(s->name, temp);

    printf("Enter roll number: ");
    scanf("%d", &s->roll);

    printf("Enter phone number: ");
    scanf(" %s", s->telephone);

    printf("Enter address: ");
    scanf(" %[^\n]", temp);  //read all characters until a newline (\n) is found.
    s->address = (char*)malloc(strlen(temp) + 1);     // malloc for address
    strcpy(s->address, temp);

    return s;
}

Student* createStudentRecordFromFile(char *name, int roll, char *phone, char *address) {
    Student *s = (Student*)malloc(sizeof(Student));   // malloc
    if (!s) return NULL;

    s->name = (char*)malloc(strlen(name) + 1);        // malloc for name
    strcpy(s->name, name);

    s->roll = roll;
    strcpy(s->telephone, phone);

    s->address = (char*)malloc(strlen(address) + 1);  // malloc for address
    strcpy(s->address, address);

    return s;
}

void freeStudentRecord(Student *s) {
    if (s) {
        free(s->name);        // free name
        free(s->address);     // free address
        free(s);              // free struct
    }
}

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
        printf("---------------------------------\n");
        printf("==== Student Register System ====\n");
        printf("---------------------------------\n");
        printf(" 1. Enter details of student\n 2. Search student by roll no.\n 3. Delete student by roll no.\n 4. Modify student details by roll no.\n 5. Sort student by name\n 6. Count of total students\n 7. Export filename\n 8. Load filename\n 9. Display Student Register\n");
        printf("---------------------------------\n");
        

    }


//----------------------------------------------------------------------------------//

int add(struct SReg *sr, struct Student *s) {
    if (sr->count >= sr->maxStuds)
        return 0;
    for (int i = 0; i < sr->count; i++) {
        if (sr->arrStudPtr[i]->roll == s->roll)
            return 0;  //to avoid duplicate roll
    }
    sr->arrStudPtr[sr->count++] = s;
    return 1;
}


//----------------------------------------------------------------------------------//


int modify(struct SReg *sr, int r) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->arrStudPtr[i]->roll == r) {
            char temp[200];

            printf("Current Details:\n");
            printf("Name     : %s\n", sr->arrStudPtr[i]->name);
            printf("Roll     : %d\n", sr->arrStudPtr[i]->roll);
            printf("Telephone: %s\n", sr->arrStudPtr[i]->telephone);
            printf("Address  : %s\n\n", sr->arrStudPtr[i]->address);

            printf("Enter new name: ");
            scanf(" %s", sr->arrStudPtr[i]->name);
            free(sr->arrStudPtr[i]->name);                      // free old memory
            sr->arrStudPtr[i]->name = (char*)malloc(strlen(temp) + 1);
            strcpy(sr->arrStudPtr[i]->name, temp);

            printf("Enter new telephone: ");
            scanf(" %s", sr->arrStudPtr[i]->telephone);

            printf("Enter new address: ");
            scanf(" %s", sr->arrStudPtr[i]->address);
            free(sr->arrStudPtr[i]->address);                   // free old memory
            sr->arrStudPtr[i]->address = (char*)malloc(strlen(temp) + 1);
            strcpy(sr->arrStudPtr[i]->address, temp);

            return 1; 
        }
    }
    return 0; 
}


//----------------------------------------------------------------------------------//


Student* get(struct SReg sr, int r) {
    for (int i = 0; i < sr.count; i++) {
        if (sr.arrStudPtr[i]->roll == r)
            return sr.arrStudPtr[i];
    }
    return 0;
}


//----------------------------------------------------------------------------------//


int delete(struct SReg *sr, int roll) {
    for (int i = 0; i < sr->count; i++) {
        if (sr->arrStudPtr[i]->roll == roll) {
            freeStudentRecord(sr->arrStudPtr[i]);
            for (int j = i; j < sr->count - 1; j++) {
                sr->arrStudPtr[j] = sr->arrStudPtr[j + 1];
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
            if (strcmp(sr->arrStudPtr[i]->name, sr->arrStudPtr[j]->name) > 0) {
                struct Student *temp = sr->arrStudPtr[i];  // swapping pointers
                sr->arrStudPtr[i] = sr->arrStudPtr[j];
                sr->arrStudPtr[j] = temp;
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
    FILE *fp = fopen(fname, "w");   // write mode
    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }
    for (int i = 0; i < sr.count; i++) {
        fprintf(fp, "%s,%d,%s,%s\n",
                sr.arrStudPtr[i]->name,
                sr.arrStudPtr[i]->roll,
                sr.arrStudPtr[i]->telephone,
                sr.arrStudPtr[i]->address);
    }
    fclose(fp);
    printf("Exported to file: %s\n", fname);
}


//----------------------------------------------------------------------------------//


void load(struct SReg *sr, char fname[]) {
    FILE *fp = fopen(fname, "r");   // r = to read
    if (!fp) {
        printf("File could not be opened.\n");
        return;
    }

    sr->count = 0;
    char line[500];
    char name[200], phone[20], address[200];
    int roll;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%[^,],%d,%[^,],%[^\n]", name, &roll, phone, address) == 4) {   //read everything until you hit a comma (,), read all characters until a newline (\n) is found.

            Student *s = createStudentRecordFromFile( name, roll, phone, address );

            if (s && sr->count < sr->maxStuds) {
                sr->arrStudPtr[sr->count++] = s;
            }
        }
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
        printf("Name    : %s\n", sr.arrStudPtr[i]->name);
        printf("Roll No. : %d\n", sr.arrStudPtr[i]->roll);
        printf("Telehone   : %s\n", sr.arrStudPtr[i]->telephone);
        printf("Address : %s\n", sr.arrStudPtr[i]->address);
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

    printf("Enter maximum number of students: ");
    scanf("%d", &studentRegister.maxStuds);

    studentRegister.count = 0;
    studentRegister.arrStudPtr = (Student**)malloc(
                                    sizeof(Student*) * studentRegister.maxStuds
                                );

    while(1){   // To create a Loop
    entry();

    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("--------------------------------\n");

    switch (choice) {
    case 1:  //Enter details of student
         if (studentRegister.count >= studentRegister.maxStuds) {
                printf("Register is full!\n");
                break;
            }

            Student *s = createStudentRecord();   // dynamic input

            if (add(&studentRegister, s))
                printf("Student added successfully!\n");
            else {
                printf("Failed to add (duplicate roll or full register)!\n");
                freeStudentRecord(s);  // free if not added
            }
        break;

    case 2: //Search student by roll no.
        printf("Enter roll to search: ");
        scanf("%d", &roll);

        {
            Student *s = get(studentRegister, roll);   // use get()
            if (s)
                printf("Student Found: %s, %d, %s, %s\n",
                       s->name,
                       s->roll,
                       s->telephone,
                       s->address);
            else
                printf("Roll No. not found!\n\n");
        }
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
return 0;

}

/*
COMPARING WITH ORIGINAL CODE:
1. Originally, Name and Address were fixed-size arrays, Hence memory would be wasted if character length was shorter than max length. Now, dynamially allocated because of typedef.
2. Maximum size (maxStuds) chosen by user at runtime.Each student itself allocated separately which is more flexible(because of malloc)
3.calls createStudentRecord() which uses malloc for name & address. reads input into temporary buffer(because of pointers), then copies.
4.Originally, it just shifted array elements when deleting students, Now, must also free() the memory for that student’s name, address, and the struct itself before shifting pointers.
5.Originally, used fprintf & fscanf with fixed arrays .Now, still uses fprintf (same format), but when loading: Reads line -> parses values -> calls createStudentRecordFromFile() -> allocates memory dynamically.
6.Originally, no need for malloc/free. Everything on stack or static array.Now, must manage memory manually:malloc when creating student or register, free in delete(), Free all students & array at program exit.
7.Originally, limited to compile-time constant (Ex: #define MAX_STUDENTS 10).Now, limit is chosen at runtime.

Conclusion:
Original code = simple but wastes memory and fixed size.
New code = a bit more complex, but saves memory and flexible (size decided at runtime, exact allocation per student).
*/
