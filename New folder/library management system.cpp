#include<iostream>
#include<iomanip>
#include <string.h>
#include <fstream>
using namespace std;

class Book {
   public: char bno[6];
    char bname[50];
    char aname[50];

public:
    void createBook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter Book No.: ";
        cin >> bno;
        cin.ignore(); // Clear the newline left in the buffer
        cout << "Enter Book Name: ";
        cin>>bname;
        cin.ignore();
        cout<<"Enter Author Name: ";
        cin>>aname;
        cout << "\n\n\nBook Created..";
    }

    void showBook() {
        cout <<"\nBook Number: "<<bno;
        cout <<"\nBook Name: "<<bname;
        cout <<"\nBook Author Name: "<<aname;
    }

    void modifyBook() {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name: ";
        cin>>bname;
        cout << "Modify Author's Name: ";
        cin>>aname;
    }

    char* retBno(){
        return bno;
    }

    void report() {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class Student {
    char admno[6];
    char name[20];
    char stbno[20];
    int token;

public:
    void createStudent() {
        system("cls");
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No.: ";
        cin >> admno;
        cin.ignore(); // Clear the newline left in the buffer
        cout << "Enter The Student Name: ";
    	cin>>name;
        token = 0;
        stbno[0]='\0';
        cout << "\n\nStudent Record Created...";
    }

    void showStudent() {
        cout <<"\nAdmission Number: " <<admno;
        cout <<"\nStudent Name: " <<name;
        cout <<"\nNo of Books Issued: "<<token;
        if (token == 1) {
            cout << "\nBook Number: " << stbno;
        }
    }

    void modifyStudent() {
        cout << "\nAdmission No.: " << admno;
        cout << "\nModify Student Name: ";
        cin>>name;
    }

    char* retAdmNo() {
        return admno;
    }

    char* retStbNo() {
        return stbno;
    }

    int retToken() {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void setStbNo(char t[]) {
        strcpy(stbno,t);
    }

    void report() {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
};

fstream fp;
void writeBook(Book &bk) {
    char ch;
    fp.open("book.txt", ios::out | ios::app);
    do {
        system("cls");
        bk.createBook();
        fp.write((char*)&bk, sizeof(bk));
        cout << "\n\nDo you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent(Student &st) {
    char ch;
    fp.open("student.txt", ios::out | ios::app);
    do {
        system("cls");
        st.createStudent();
        fp.write((char*)&st, sizeof(st));
        cout << "\n\nDo you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displayBook(char n[],Book &bk) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.txt", ios::in);
    while (fp.read((char*)&bk, sizeof(bk))) {
        if(strcmpi(bk.retBno(),n)==0) {
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\n\nBook does not exist";
    }
    cin.ignore();
    cin.get();
}

void displayStudent(char n[],Student &st) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.txt", ios::in);
    while (fp.read((char*)&st, sizeof(st))) {
        if(strcmpi(st.retAdmNo(),n)==0) {
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\n\nStudent does not exist";
    }
    cin.ignore();
    cin.get();
}

void modifyBook(Book &bk) {
    char n[6];
    int found = 0;
    system("cls");
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter the book no.: ";
    cin >> n;
    cin.ignore();
    fp.open("book.txt", ios::in | ios::out);
    while (fp.read((char*)&bk, sizeof(bk)) && found == 0) {
        if(strcmpi(bk.retBno(),n)==0) {
            bk.showBook();
            cout << "\nEnter the new details of the book";
            bk.modifyBook();
            int pos =1*sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk,sizeof(bk));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\n\nRecord Not Found";
    }
    cin.ignore();
    cin.get();
}

void modifyStudent(Student &st) {
    char n[6];
    int found = 0;
    system("cls");
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter the Admission no.: ";
    cin >> n;
    cin.ignore();
    fp.open("student.txt", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(st)) && found == 0) {
        if(strcmpi(st.retAdmNo(),n)==0) {
            st.showStudent();
            cout << "\nEnter the new details of the student";
            st.modifyStudent();
            int pos =1*sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(st));
            cout << "\n\nRecord Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\n\nRecord Not Found";
    }
    cin.ignore();
    cin.get();
}

void deleteStudent() {
    char n[6];
}

int main() {
    char choice;
	Book bk;
	Student st;
    do {
        system("cls"); // Clear the screen (Windows-specific)
        cout << "\nMAIN MENU";
        cout << "\n1. Create Book Record";
        cout << "\n2. Create Student Record";
        cout << "\n3. Display Book Record";
        cout << "\n4. Display Student Record";
        cout << "\n5. Modify Book Record";
        cout << "\n6. Modify Student Record";
        cout << "\n7. Exit";
        cout << "\nEnter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case '1':
                writeBook(bk);
                break;
            case '2':
                writeStudent(st);
                break;
            case '3':
                char bookNo[6];
                cout << "Enter Book Number: ";
                cin >> bookNo;
                displayBook(bookNo,bk);
                break;
            case '4':
                char admissionNo[6];
                cout << "Enter Admission Number: ";
                cin >> admissionNo;
                displayStudent(admissionNo,st);
                break;
            case '5':
                modifyBook(bk);
                break;
            case '6':
                modifyStudent(st);
                break;
            case '7':
                cout << "Exiting the program...";
                break;
            default:
                cout << "Invalid choice. Please try again.";
        }
    } while (choice != '7');

    return 0;
}
