#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

class library_data
{
    char bookName[70];
    int bookID;
    char departmentName[40];
    char authorName[30];
public:
    void write_library_data();
    void show_library_data();
    void show_library_data_tabwise() const;
    int return_book_id_library_data() const;
    char return_book_name_library_data();
};

class student_data
{
    int roll;
    char student_name[70];
    int book_id;
    int rec_day;
    int rec_mon;
    int rec_year;
    int ret_day;
    int ret_mon;
    int ret_year;
    char dept_name[6];
public:
    void write_student_data();
    void write_modified_student_data();
    void show_student_data();
    void show_for_delete_student_data();
    void show_student_data_tabwise();
    int return_student_id_student_data();
    void recive_time(int);
    int current_time();
};

//Library function declaration
void view_all_book();
void search_book();
void add_new_arrival_book();
void update_book_details();
void remove_book();
int main();
void booklist();

//student_entry function declaration
void new_entry();
void search_student_data(int);
void view_all_student();
void returned_book_register(int);
void student_entry();


int student_data::return_student_id_student_data()
{
    return roll;
}

void student_data::recive_time(int n)
{
    time_t now;

    tm* now_Local;

    now = time(0);

    now_Local = localtime(&now);

    //cout <<"Today is: "<<now_Local->tm_mday<<" "<<now_Local->tm_mon+1<<" "<<now_Local->tm_year+1900;

    //recive date register
    rec_day = now_Local->tm_mday+n-n;
    rec_mon = now_Local->tm_mon+1;
    rec_year = now_Local->tm_year+1900;

    //return date register
    ret_day = now_Local->tm_mday+n;
    ret_mon = now_Local->tm_mon+1;
    ret_year = now_Local->tm_year+1900;

}

void student_data::write_student_data()
{
    //student_data st;
    int n;
    cout<<"Enter Student ID : ";
    cin>>roll;
    cout<<"Enter Student Name : ";
    cin.ignore();
    cin.getline(student_name, 70);
    cout<<"Enter Book ID : ";
    cin>>book_id;
    cout<<"Enter Department Name : ";
    cin>>dept_name;
    cout<<"How many days student want to borrow the book: ";
    cout<<"[note: not more then 4 day. If violation does data will be reset!!!]";
    cin.ignore();
    cin>>n;
    if(n <= 4)
    {
        recive_time(n);
    }
    if( n > 4)
    {
        write_student_data();
    }
}

void student_data::write_modified_student_data()
{
    cout<<"Enter Student Name : ";
    cin.ignore();
    cin.getline(student_name, 70);
    cout<<"Enter Book ID : ";
    cin>>book_id;
    cout<<"Enter Department Name : ";
    cin>>dept_name;
}

void student_data::show_student_data()
{
    cout<<"Book ID : "<<book_id<<endl;
    cout<<"Student ID : "<<roll<<endl;
    cout<<"Student Name : "<<student_name<<endl;
    cout<<"Department : "<<dept_name<<endl;
    cout<<"Recive Time: "<< rec_day<<" / "<< rec_mon<<" / "<<rec_year<<endl;
    cout<<"Return Time : "<<ret_day<<" / "<< ret_mon<<" / "<<ret_year<<endl;
}

void student_data::show_for_delete_student_data()
{

    int day, mon, year;
    cout<<"Book ID : "<<book_id<<endl;
    cout<<"Student ID : "<<roll<<endl;
    cout<<"Student Name : "<<student_name<<endl;
    cout<<"Department : "<<dept_name<<endl;
    cout<<"Recive Time: "<< rec_day<<" / "<< rec_mon<<" / "<<rec_year<<endl;
    cout<<"Return Time : "<<ret_day<<" / "<< ret_mon<<" / "<<ret_year<<endl;

    /*cout<<"Enter Todays Date: ";
    cin>>day;
    cout<<"Enter Todays Month: ";
    cin>>mon;
    cout<<"Enter Todays Year: ";
    cin>>year;*/


    //////////////////////////////////////////////

    time_t now;

    tm* now_Local;

    now = time(0);

    now_Local = localtime(&now);

    //cout <<"Today is: "<<now_Local->tm_mday<<" "<<now_Local->tm_mon+1<<" "<<now_Local->tm_year+1900;

    day = now_Local->tm_mday;
    mon = now_Local->tm_mon+1;
    year = now_Local->tm_year+1900;
    //////////////////////////////////////////////


    if(day > ret_day || mon > ret_mon)
    {
        int d=0, m=0, y=0, charge=0;
      int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


      y = year - ret_year;
      if (mon < ret_mon)
      {
        y--;
        m = 12 - (ret_mon - mon);
      }
      else
      {m = mon - ret_mon;}

      if (day < ret_day)
      {
        m--;
        d = md[mon - 1] - (ret_day - day);
      }
      else
      {d = day - ret_day;}

      charge = d*5;
      cout << "\t\tTotal Fine: "<<charge<<" Taka"<<endl;
    }
    if(day < ret_day || mon < ret_mon)
    {
        cout<<"\t\t\tNo Due."<<endl;
    }

}

void student_data::show_student_data_tabwise()
{
    cout<<roll<<setw(16)<<" "<<student_name<<setw(14)<<book_id<<setw(17)<<dept_name<<setw(4)<<rec_day<<" / "<< rec_mon<<" / "<<rec_year<<setw(15)<<ret_day<<" / "<< ret_mon<<" / "<<ret_year<<endl;
}

void new_entry()
{
    char ch;

    cout<<"New Entry"<<endl<<endl;
    student_data st;
    ofstream outfile;
    outfile.open("student.txt",ios::binary|ios::app);
    st.write_student_data();//iput ney
    outfile.write(reinterpret_cast<char *> (&st), sizeof(student_data));
    outfile.close();
    cout<<"Student record has been created!!!"<<endl;
    cin.ignore();

    cout<<"Enter another new record? (y/n): ";
    cin>>ch;
    switch(ch)
    {
        case 'y': new_entry();
        break;
        case 'n': student_entry();
        break;
        default: cout<<"\a"; student_entry();
    }
    cin.ignore();
    cin.get();
}

void search_student_data(int n)
{
    student_data st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_data)))
	{
		if(st.return_student_id_student_data() == n)
		{
	  		 st.show_student_data();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
	student_entry();
}

void view_all_student()
{
    student_data st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\t\t\t\t\tALL BOOKS DETAILS \n\n";
	cout<<"=============================================================================================================\n";
	cout<<"Student ID       Student Name        Book ID        Department Name        Receive Date        Return date"<<endl;
	cout<<"=============================================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_data)))
	{
		st.show_student_data_tabwise();
	}
	inFile.close();
	cin.ignore();
	cin.get();
	student_entry();
}

void modify_student_data(int n)
{
	student_data st;
	fstream inFile;
	inFile.open("student.txt",ios::binary|ios::in|ios::out);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		student_entry();
	}
	bool flag=false;
    while(!inFile.eof() && flag==false)
    {
        inFile.read(reinterpret_cast<char *> (&st), sizeof(student_data));
        if(st.return_student_id_student_data()==n)
        {
            st.show_student_data();
            cout<<"\n\nPlease Enter The New Details of student"<<endl;
            st.write_modified_student_data();
                int pos=(-1)*static_cast<int>(sizeof(st));
                inFile.seekp(pos,ios::cur);
                inFile.write(reinterpret_cast<char *> (&st), sizeof(student_data));
                cout<<"\n\n\t Record Updated";
                flag=true;
        }
    }

	inFile.close();
	if(flag==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}

void returned_book_register(int n)
{

    char choose;

    student_data st;
	ifstream inFile;
	inFile.open("student.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_data)))
	{
		if(st.return_student_id_student_data() == n)
		{
	  		 st.show_for_delete_student_data();
			 flag=true;
		}
	}

	cin.get();
	//st.fine();
	/*while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student_data)))
	{
		if(st.return_student_id_student_data() == n)
		{
	  		 st.fine();
			 flag=true;
		}
	}*/
	inFile.close();
	if(flag==false)
    {
        cout<<"\n\nrecord not exist";
        cin.get();
        student_entry();
    }

	cin.ignore();
	cin.get();
    ////////////////////////////////////////////////////////////
    cout<<"You want to delete the data? (y/n): ";
    cin>>choose;

    if(choose == 'y')
    {
        student_data st;
        ifstream infile;
        infile.open("student.txt",ios::binary);
        if(!infile)
        {
            cout<<"File could not be open !! Press any Key...";
            cin.ignore();
            cin.get();
            return;
        }

        ofstream outfile;
        outfile.open("Temp.txt",ios::out);
        //infile.seekg(0,ios::beg);
        while(infile.read((char *) (&st), sizeof(student_data))) //Data char e sajabe and read korbe
        {
            if(st.return_student_id_student_data() != n) //st.return_book_id_library_data() != n
            {
                outfile.write((char *) (&st) , sizeof(student_data)); //copy korbe search er sathe mille nibe na
            }
        }
        outfile.close();
        infile.close();
        remove("student.txt");
        rename("Temp.txt","student.txt");
        cin.ignore();
        cout<<"Student Data is been deleted!!!"<<endl;
        cin.get();
    }

    student_entry();
}



int library_data::return_book_id_library_data() const
{
    return bookID;
}
/*
char library_data::return_book_name_library_data()
{
    return bookName;
}
*/
void library_data::write_library_data()
{
    cout<<"Enter Book ID : ";
    cin>>bookID;
    cout<<"Enter Book Name : ";
    cin.ignore();
    cin.getline(bookName, 70);
    cout<<"Enter Department Name : ";
    cin.getline(departmentName, 40);
    cout<<"Enter Author Name : ";
    cin.getline(authorName, 30);
}


void library_data::show_library_data()
{
    cout<<"Book ID : "<<bookID<<endl;
    cout<<"Book Name : "<<bookName<<endl;
    cout<<"Department Name : "<<departmentName<<endl;
    cout<<"Author Name : "<<authorName<<endl;
}

void library_data::show_library_data_tabwise() const
{
    cout<<bookID<<setw(6)<<" "<<bookName<<setw(10)<<authorName<<setw(4)<<departmentName<<endl;
}

void intro()
{
	cout<<"\n\n\n\t\t\t  LIBRARY";
	cout<<"\n\n\t\t      MANAGMENT SYSTEM";
	cout<<"\n\n\t\t\t  PROJECT";
	cout<<"\n\n\n\tMADE BY : TEAM SYSTEM TRON";
	cout<<"\n\tFROM SHANTO-MARIAM UNIVERSITY OF CREATIVE TECHNOLOGY";
	cin.get();
}

void view_all_book()
{
    library_data lib;
	ifstream inFile;
	inFile.open("library.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		booklist();
	}
	cout<<"\n\n\t\tALL BOOKS DETAILS \n\n";
	cout<<"===============================================================\n";
	cout<<"Book ID       Book Name        Author Name     Department Name"<<endl;
	cout<<"===============================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&lib), sizeof(library_data)))
	{
		lib.show_library_data_tabwise();
	}

	inFile.close();
	cin.ignore();
	cin.get();
	booklist();
}

void search_book(int n)
{
    library_data lib;
	ifstream inFile;
	inFile.open("library.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&lib), sizeof(library_data)))
	{
		if(lib.return_book_id_library_data() == n)
		{
	  		 lib.show_library_data();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
	booklist();
}
/*
void search_book_by_name(char ch)
{
    library_data lib;
	ifstream inFile;
	inFile.open("library.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&lib), sizeof(library_data)))
	{
		if(lib.return_book_name_library_data()== ch ) //strcmp(a,b == 0)
		{
	  		 lib.show_library_data();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}

void search_book()
{
    int choose;
    int n;
    char ch[70];
    cout<<"\tSearch Book\n"<<endl;
    cout<<"1. SEARCH BOOK BY ID"<<endl;
    cout<<"2. SEARCH BOOK BY NAME"<<endl;
    cout<<"3. RETURN TO BOOKLIST"<<endl;
    cout<<"4. RETURN TO MAIN MENU"<<endl;
    system("cls");
    switch(choose)
    {
        case 1: cout<<"Enter Book ID: ";cin>>n;
                search_book_by_id(n);
        break;
        case 2: cout<<"Enter Book ID: ";
                cin.ignore();
                cin.getline(ch, 70);
                search_book_by_name(ch);
        break;
        case 3: booklist();
        break;
        case 4: main();
        break;
        default: cout<<"\a"; search_book();
    }
}
*/
void add_new_arrival_book()
{
    char ch;
    library_data lib;
    ofstream outfile;
    outfile.open("library.txt",ios::binary|ios::app);
    lib.write_library_data();//iput ney
    outfile.write(reinterpret_cast<char *> (&lib), sizeof(library_data));
    outfile.close();
    cout<<"Book record has been created!!!"<<endl;
    cin.ignore();

    cout<<"Enter another new record? (y/n): ";
    cin>>ch;
    switch(ch)
    {
        case 'y': add_new_arrival_book();
        break;
        case 'n': booklist();
        break;
        default: cout<<"\a"; booklist();
    }
    cin.ignore();
    cin.get();
    booklist();
}

void remove_book(int n)
{

    library_data lib;
    ifstream infile;
    infile.open("library.txt",ios::binary);
    if(!infile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}

	ofstream outfile;
	outfile.open("Temp.txt",ios::out);
	//infile.seekg(0,ios::beg);
	while(infile.read(reinterpret_cast<char *> (&lib), sizeof(library_data))) //Data char e sajabe and read korbe
    {
        if(lib.return_book_id_library_data() != n) //lib.return_book_id_library_data() != n
        {
            outfile.write((char *) (&lib) , sizeof(library_data)); //copy korbe search er sathe mille nibe na
        }
    }
    outfile.close();
    infile.close();
    remove("library.txt");
    rename("Temp.txt","library.txt");
    cin.ignore();
    cout<<"Book Data is been deleted!!!"<<endl;
    cin.get();
    booklist();
}

void update_book_details(int n)
{
    library_data lib;
	fstream inFile;
	inFile.open("library.txt",ios::binary|ios::in|ios::out);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
    while(!inFile.eof() && flag==false)
    {
        inFile.read(reinterpret_cast<char *> (&lib), sizeof(library_data));
        if(lib.return_book_id_library_data()==n)
        {
            lib.show_library_data();
            cout<<"\n\nPlease Enter The New Details of Books"<<endl;
            lib.write_library_data();
                int pos=(-1)*static_cast<int>(sizeof(lib));
                inFile.seekp(pos,ios::cur);
                inFile.write(reinterpret_cast<char *> (&lib), sizeof(library_data));
                cout<<"\n\n\t Record Updated";
                flag=true;
        }
    }

	inFile.close();
	if(flag==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
	booklist();
}

void booklist()
{
    system("cls");
    int n;
    int choose;
    cout<<"\tBOOK LIST\n"<<endl;
    cout<<"1. VIEW ALL BOOK."<<endl;
    cout<<"2. SEARCH BOOK."<<endl;
    cout<<"3. ADD NEW ARRIVAL BOOK"<<endl;
    cout<<"4. UPDATE BOOK DETAILS"<<endl;
    cout<<"5. REMOVE BOOK"<<endl;
    cout<<"6. RETURN TO MAIN MENU"<<endl;
    cout<<"Enter number (1 - 6): ";
    cin>>choose;
    system("cls");
    switch(choose)
    {
        case 1: view_all_book();
        break;
        case 2: cout<<"Enter Book ID: ";cin>>n;
                search_book(n);
        break;
        case 3: add_new_arrival_book();
        break;
        case 4: cout<<"Enter Book ID: ";cin>>n;
                update_book_details(n);
        break;
        case 5: cout<<"Enter Book ID: ";cin>>n;
                remove_book(n);
        break;
        case 6: main();
        break;
        default: cout<<"\a"; booklist();
    }

}

void student_entry()
{
    system("cls");
    int choose;
    int n;
    cout<<"\tSTUDENT ENTRY\n"<<endl;
    cout<<"1. NEW ENTRY"<<endl;
    cout<<"2. SEARCH STUDENT DATA"<<endl;
    cout<<"3. VIEW ALL"<<endl;
    cout<<"4. RETUREND BOOK REGISTER"<<endl;
    cout<<"5. MODIFY STUDENT DATA"<<endl;
    cout<<"6. RETURN TO MAIN MENU"<<endl;
    cout<<"Enter number (1 - 6): ";
    cin>>choose;

    system("cls");
    switch(choose)
    {
        case 1: new_entry();
        break;
        case 2: cout<<"Enter Student Roll";
                cin>>n; search_student_data(n);
        break;
        case 3: view_all_student();
        break;
        case 4: cout<<"Enter Student Roll";
                cin>>n; returned_book_register(n);
        break;
        case 5: cout<<"Enter Student Roll";
                cin>>n; modify_student_data(n);
        break;
        case 6: main();
        default: cout<<"\a"; student_entry();
        }

}


int main()
{
    intro();
    system("cls");
    int choose;
    cout<<"\n\n1. BOOK LIST"<<endl;
    cout<<"2. STUDENT ENTRY"<<endl;
    cout<<"3. ABOUT US"<<endl;
    cout<<"*** Book id diye search kora zbe ze omuk book ke ke nise okay? *** backup feature ashbe"<<endl;
    cout<<"\n\n\tPlease Enter Your Choice (1-3) :";
	cin>>choose;
    system("cls");
    switch(choose)
    {
        case 1: booklist();
        break;
        case 2: student_entry();
        break;
        /*case 3: about_us();
        break;*/
        default: cout<<"\a"; booklist();
    }
}


