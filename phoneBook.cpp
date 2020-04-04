//Header files
#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<windows.h>
using namespace std;

//Functions

void to_do(); // Function of Main menu to do various tasks
void add_contact(); // Function to add a contact
void display_contact(); // Function to display all contacts
void search_contact(); // Function to search contact
void delete_contact(); // Function to delete contact
void modify_contact(); // Function to modify contact
void filter_contact(); // Function to filter contact
void loading(int); // For delay in loading
void the_end(); // Details

//class Definition

class phonebook
{
    char name[40];
    char mobile[15];
    char email[35];
    char relation[9];
    char gender[7];

public:

    char *getname()
    {
        return name;
    }
    char *getmobile()
    {
        return mobile;
    }
    char *getgender()
    {
        return gender;
    }
    void getdata();
    void putdata()
    {
        cout<<"\n*********CONTACT DETILS*********\n";
        cout<<"Name: "<<name<<endl;
        cout<<"Mobile Number: "<<mobile<<endl;
        cout<<"eMail: "<<email<<endl;
        cout<<"Relation: "<<relation<<endl;
        cout<<"Gender: "<<gender<<endl;
    }
}p1;

void phonebook :: getdata()
{
        char temp;
        int i=0;
        cout<<"\n*********ADD CONTACT*********\n";
        cout<<"Enter name: ";
        cin.ignore();
        cin.getline(name,40);
        cout<<"Enter mobile number: ";
        while(i<10)
        {
            temp=getch();
            if(temp>='0'&&temp<='9')
            {
                mobile[i]=temp;
                cout<<mobile[i];
                i++;
            }
            else if(temp=='\b' && i>=1)
            {
                cout<<"\b \b";
                i--;
            }
            else
            {
                cout<<"\nInvalid mobile number!!!!!\n";
                cout<<"Enter mobile number: ";
                i=0;
            }
        }
        cout<<"\nEnter email: ";
        cin.getline(email,35);
        strlwr(email);
        cout<<"Enter relation: ";
        cin.getline(relation,9);
        cout<<"Enter gender: ";
        cin.getline(gender,7);
        cout<<endl;
    }
void add_contact()
{
    ofstream fout;
    fout.open("maincontact.txt",ios::out|ios::binary|ios::app);
    p1.getdata();
    fout.write((char*)&p1,sizeof(p1));
    fout.close();
    cout<<"\nContact saved!!!!!\n";
}

void display_contact()
{
    ifstream fin;
    fin.open("maincontact.txt",ios::out|ios::binary|ios::app);
    while(fin.read((char*)&p1,sizeof(p1)))
    {
        p1.putdata();
    }
    fin.close();
    cout<<"\nAll contacts displayed!!!!!\n";
}

void search_contact()
{
    fstream fifi;
    char tname[40], tmobile[15];
    int ch,found=0;
    cout<<"\n\n1: Search By Name\n2: Search by mobile number\nEnter: ";
    cin>>ch;
    if(ch==1)
    {
        cout<<"\n\nEnter Name to search : ";
        cin.ignore();
        cin.getline(tname,40);
        fifi.open("maincontact.txt",ios::out|ios::binary|ios::in);
        fifi.seekg(0,ios::beg);
        char copyy[40];
        char copyy2[40];
        while(fifi.read((char *)&p1,sizeof(p1)))
        {
            strcpy(copyy,p1.getname());
            strlwr(copyy);
            strcpy(copyy2,p1.getname());
            strlwr(copyy2);
            strlwr(tname);
            if((strcmp(tname,copyy2)==0))
            {
                found=1;
                p1.putdata();
            }
            char *split=strtok(copyy," ");
            while(split !=NULL && strcmp(copyy2,tname)!=0)
            {
                if((strcmp(tname,split)==0))
                {
                    found=1;
                    p1.putdata();
                }
                split=strtok(NULL," ");
            }
        }
        fifi.clear();
        if(found==0)
        {
            cout<<"\n\nNo contacts found!!!!!";
        }
    }
    else if(ch==2)
    {
        cout<<"\nEnter Mobile number to search : ";
        cin.ignore();
        cin.getline(tmobile,15);
        fifi.open("maincontact.txt",ios::out|ios::binary|ios::in);
        fifi.seekg(0,ios::beg);
        while(fifi.read((char *)&p1,sizeof(p1)))
        {
            if(strcmp(tmobile,p1.getmobile())==0)
            {
                found=1;
                p1.putdata();
            }
        }
        fifi.clear();
        if(found==0)
        {
            cout<<"\n\nNo contacts found!!!!!";
        }
    }
    else
    {
        cout<<"\n\nInvalid choice!!!!!";
        search_contact();
    }
    fifi.close();
}
void delete_contact()
{
    ifstream fin;
    ofstream fout;
    char tmobile[15];
    int countt=0;
    fin.open("maincontact.txt",ios::out|ios::binary|ios::app);
    fout.open("temporary.txt",ios::out|ios::binary);
    cout<<"Enter mobile number to delete: ";
    cin.ignore();
    cin.getline(tmobile,15);
    fin.seekg(0,ios::beg);
    while(fin.read((char*)&p1,sizeof(p1)))
    {
        if(strcmp(tmobile,p1.getmobile())==0)
        {
            cout<<"\nContact deleted!!!!!\n";
            p1.putdata();
            countt++;
        }
        else
        {
            fout.write((char*)&p1,sizeof(p1));
        }
    }
    fin.close();
    fout.close();
    if(countt==0)
    {
        cout<<"Contact not founded!!!!!";
    }
    remove("maincontact.txt");
    rename("temporary.txt","maincontact.txt");
}

void modify_contact()
{
    fstream hifi;
    int j,countt=0;
    char tmobile[15];
    hifi.open("maincontact.txt",ios::out|ios::binary|ios::in);
    cout<<"Enter mobile number to modify: ";
    cin.ignore();
    cin.getline(tmobile,15);
    hifi.seekg(0,ios::beg);
    while(hifi.read((char*)&p1,sizeof(p1)))
    {
        j=hifi.tellg();
        if(strcmp(tmobile,p1.getmobile())==0)
        {
            cout<<"\nFollowing Record will be modified!!!!!\n";
            p1.putdata();
            countt++;
            cout<<"\nRe-Enter the New Details!!!!!\n";
            p1.getdata();
            hifi.seekg(j-sizeof(p1));
            hifi.write((char*)&p1,sizeof(p1));
            cout<<"\nData Modified Successfully!!!!!\n";
        }
    }
    hifi.close();
    if(countt==0)
    {
        cout<<"\nThere is no contact with mobile number: "<<tmobile<<endl;
    }
}
void filter_contact()
{
    fstream kifi;
    char male[10]="Male", female[10]="Female",smale[10]="male",sfemale[10]="female";
    int ch,found=0;
    cout<<"\n\n1: Filter by Male\n2: Filter by Female\nEnter: ";
    cin>>ch;
    if(ch==1)
    {
        kifi.open("maincontact.txt",ios::out|ios::binary|ios::in);
        kifi.seekg(0,ios::beg);
        cout<<"\nMale contacts:~\n";
        while(kifi.read((char *)&p1,sizeof(p1)))
        {
            if(strcmp(male,p1.getgender())==0 || strcmp(smale,p1.getgender())==0 )
            {
                found=1;
                p1.putdata();
            }
        }
        kifi.clear();
        if(found==0)
        {
            cout<<"\n\nNo Male contacts found!!!!!";
        }
    }
    else if(ch==2)
    {
        cout<<"\nFemale contacts:~\n";
        kifi.open("maincontact.txt",ios::out|ios::binary|ios::in);
        kifi.seekg(0,ios::beg);
        while(kifi.read((char *)&p1,sizeof(p1)))
        {
            if(strcmp(female,p1.getgender())==0 || strcmp(sfemale,p1.getgender())==0 )
            {
                found=1;
                p1.putdata();
            }
        }
        kifi.clear();
        if(found==0)
        {
            cout<<"\n\nNo Female contacts found!!!!!";
        }
    }
    else
    {
        cout<<"\n\nInvalid choice!!!!!";
        filter_contact();
    }
    kifi.close();
}
void to_do()
{
    int c;
    do
    {

        cout<<"\n\n\t\t\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PHONE BOOK \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\n";
        cout<<"\n\t\t";
        for(int i=0;i<=18;i++)
        {
            loading(10000000);
            cout<<":";
        }
        cout<<" TO-DO ";
        for(int i=0;i<=17;i++)
        {
            loading(10000000);
            cout<<":";
        }
        cout<<endl;
        cout<<"\n\t\t1-Add a new contact\n";
        cout<<"\t\t2-View all contacts\n";
        cout<<"\t\t3-Modify a contact\n";
        cout<<"\t\t4-Delete a contact\n";
        cout<<"\t\t5-Search any contact\n";
        cout<<"\t\t6-Filter contacts\n";
        cout<<"\t\t0-Exit\n";
        cout<<"\n\t\tPress to do certain task: ";
        cin>>c;
        switch(c)
        {
            case 1:
            {
                system("cls");
                add_contact();
                break;
            }
            case 2:
            {
                system("cls");
                display_contact();
                break;
            }
            case 3:
            {
                system("cls");
                modify_contact();
                break;
            }
            case 4:
            {
                system("cls");
                delete_contact();
                break;
            }
            case 5:
            {
                system("cls");
                search_contact();
                break;
            }
            case 6:
            {
                system("cls");
                filter_contact();
                break;
            }
            default:
            {
                system("cls");
                the_end();
                break;
            }
        }
        getch();
    }while(c);
}
void loading(int m)
{
    int i,k;
    for(i=0;i<m;i++)
    {
        k=i;
    }
}
void the_end()
{
    int i;
    string str="Powered by UmangAjw\n\n";
    for (i=0 ; i<str.size(); i++)
    {
        cout << str[i];
        Sleep(100);
    }
}
int main()
{
    system("color 3F");
    int ch;
    int i = 0;
    char temp;
    char pwd[20],mainpwd[20]="ucandoit";
    cout<<"\nEnter password to look up into PhoneBook: ";
    for(i=0; ; )
    {
        temp=getch();
        if((temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z')||(temp>='0'&&temp<='9'))
        {
            pwd[i]=temp;
            ++i;
            cout<<"*";
        }
        if(temp=='\b'&&i>=1)
        {
            cout<<"\b \b";
            --i;
        }
        if(temp=='\r')
        {
            pwd[i]='\0';
            break;
        }
    }
    string str="\nLoading";
    for (i=0 ; i<str.size(); i++)
    {
        cout << str[i];
        Sleep(100);
    }
    for(int i=0;i<=6;i++)
    {
        loading(10000000);
        cout<<".";
    }
    Sleep(1000);
    if(strcmp(pwd,mainpwd)==0)
    {
        cout<<"\n\nPassword Matched!!!!!";
        Sleep(1000);
        system("cls");
        to_do();
    }
    else
    {
        cout<<"\n\n\aNOOB! Wrong password!!!!!";
        trytry:
            cout<<"\n\n1:Re-Enter password\n0:Exit\nEnter: ";
            cin>>ch;
            if(ch==1)
            {
                system("cls");
                main();
            }
            else if(ch==0)
            {
                system("cls");
                the_end();
            }
            else
            {
                cout<<"\nInvalid Choice!";
                loading(10000000);
                system("cls");
                goto trytry;
            }
    }
    return 0;
}
