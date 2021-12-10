
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <stdio.h>
using namespace std;

namespace registerp
{
class phonebook
{

	char name[20],connum[12];
		public:
			void getdata();
			void showdata();
			char *getname(){ return name; }
			char *getconnum(){ return connum; }
			void edit(char *nm,char *cn)
			{
    			strcpy(name,nm);
    			strcpy(connum,cn);
			}
    		void newcontact();
    		void editnumber();
    		void display(char *nm);
    		void searchname();			
    		void deletecon();
    		void display();
};

void phonebook :: getdata()
{
    cout<<"\nContact Name : "<< endl;
    cin>>name;
    repeat:
    cout<<"Contact Number : " << endl;
    cin>>connum;
}

void phonebook :: showdata(){
    cout << "\n";
	cout<<setw(20)<<name;
    cout<<setw(15)<<connum;
    cout << "\n";

}

void phonebook :: newcontact()
{
    int found=0;
    char rrep[12];
    char nmopi[20];

        getdata();
        strcpy(nmopi,name);
        strcpy(rrep,connum);
        
    fstream file;
    file.open("contact.txt", ios::in | ios::app | ios::binary );
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(rrep,getconnum())==0)
        {
            found=1;
            break;
        }
    }
    file.clear();
    file.close();
    
	if(found==1)
        cout<<"\n\nContact already exist!\n";
    else
    {
        file.open("contact.txt", ios::app | ios::binary );
        edit(nmopi,rrep);
        file.write((char *) this, sizeof(*this));
        cout<<"Successfull!\n";
        file.close();
    }

}

void phonebook :: editnumber()
{  
    int in;
        fstream file;
        file.open("contact.txt", ios::ate | ios::in | ios::out | ios::binary );
		cout << "Choose." <<endl;
		cout <<"1 : Edit Contact Name" << endl;
		cout <<"2 : Edit Contact Number" << endl;
		cin >> in;
                 
		if(in == 1)
		{ 
		char c,ch,nm[20],newnm[15],newcn[15];
        int cnt=0,found=0;
        cout<<"\n\nEnter Contact Name : " << endl;
        cin>>nm;
		file.seekg(0,ios::beg);
        while(file.read((char *) this, sizeof(*this)))
        {
            cnt++;
            if(strcmp(nm,getname()) == 0)
            {
            	found = 1;
                break;
            }
        }
        file.clear();
                 
		if(found==0)
        cout<<"\n\nContact Not Found!\n";
        else
        {   strcpy(newcn,connum);
			int location = (cnt-1) * sizeof(*this);
            cin.get(ch);
            if(file.eof())
            file.clear();

            cout<<"Enter New Contact Name: " << endl;
            cin>>newnm;
            file.seekp(location);
            edit(newnm,newcn);
            file.write((char *) this, sizeof(*this));
            file.flush();
        }
        }
        if(in == 2)
            {
            char c, ch, nm[20], cn[15], newnewcn[15];
			int cnt=0,found=0;
			cout<<"\n\nEnter Contact Number : "<< endl;
			cin>>cn;
			file.seekg(0,ios::beg);
                 
			while(file.read((char *) this, sizeof(*this)))
            {
            	cnt++;
                if(strcmp(cn,getconnum())==0)
                    {
                    	found=1;
                        break;
                    }
            }
        file.clear();
                 
		if(found == 0)
        cout<<"\n\nContact Not Found!\n";
        else
        {  strcpy(nm,name);
            	int location = (cnt-1) * sizeof(*this);
                cin.get(ch);
                if(file.eof())
                file.clear();

                cout<<"Enter New Contact Number: " << endl;
                cin>>newnewcn;
                file.seekp(location);
                edit(nm,newnewcn);
                file.write((char *) this, sizeof(*this));
                file.flush();
        }
        }

        file.close();
}

void phonebook :: display(char *nm)               
{  
    char c,cn[12];
    int cnt,found=0;

    fstream file;
    file.open("contact.txt", ios::ate | ios::in | ios::out | ios::binary );
    file.seekg(0,ios::beg);
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(nm,getname())==0)
        {
            found=1;
            showdata();
        }
    }
    file.clear();
    if(found==0)
        cout<<"\n\nContact Not Found!\n";
    file.close();

}

void phonebook :: searchname()
{
    char c,ch,nm[20],cn[12];
    int cnt,found=0;
    cout<<"\n\nEnter Contact Number : " << endl;
    cin>>cn;
    fstream file;
    file.open("contact.txt", ios::ate | ios::in | ios::out | ios::binary );
    file.seekg(0,ios::beg);
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(cn,getconnum())==0)
        {
            found=1;
            showdata();
        }
    }
    file.clear();
    
	if(found==0)
        cout<<"\n\nContact Not Found!\n";
    file.close();
}

void phonebook :: deletecon()
{
    char bb[20],newcn[12];
    cout<<"Enter Contact Name : " << endl;
    cin>>bb;
    fstream file;
    file.open("contact.txt",  ios::in | ios::binary );
    fstream fout;
    fout.open("tempfile.txt",ios::out | ios::binary);
    int i=0,j=0,found=0;
    file.read((char *) this, sizeof(*this));
    while(!file.eof())
    {
        i++;
        if(strcmp(bb,getname()))
        {
            fout.write((char*)this,sizeof(*this));
            j++;
        }
        file.read((char*)this,sizeof(*this));


    }
    fout.close();
    file.close();
    if(i-j<=1)
    {

        file.close();
        remove("contact.txt");
        rename("tempfile.txt","contact.txt");
        if(j<i)
        cout<<"Contact Deleted Successfully"<<endl;


        if(j==i)
        cout<<"Contact Not Found!"<<endl;

    }
    else
    {
        cout<<"\n\nSame Contacts Name Exist\n"<<endl;
        file.open("contact.txt", ios::ate | ios::in | ios::out | ios::binary );
        file.seekg(0,ios::beg);
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(bb,getname())==0)
        {
            found=1;
            showdata();
            cout<<endl;
        }
    }
        file.clear();
        file.close();
        cout<<"\n\nEnter Contact Number :  "<<endl;
        cin>>newcn;
        file.open("contact.txt",  ios::in | ios::binary );
        fout.open("tempfileph.txt",ios::out | ios::binary);
        file.read((char *) this, sizeof(*this));
        i=0;
        j=0;
        while(!file.eof())
        {
            i++;
            if(strcmp(newcn,getconnum()))
            {
                fout.write((char*)this,sizeof(*this));
                j++;
            }
            file.read((char*)this,sizeof(*this));
        }
        fout.close();
        file.close();
        remove("contact.txt");
        rename("tempfileph.txt","contact.txt");
        if(j<i)cout<<"\n\nContact Deleted Successfully\n\n"<<endl;
        else cout<<"Contact Not Found!"<<endl;
    }

   }

void phonebook :: display()
{
    fstream file;
    file.open("contact.txt", ios::ate | ios::in | ios::out | ios::binary );
    file.seekg(0,ios::beg);
    cout<<"\n\nAll Contact in Phonebook\n";
    while(file)
    {
        file.read((char *) this, sizeof(*this));
        if(!file.eof())
            showdata();
    }
    file.clear();
    file.close();
}
}
