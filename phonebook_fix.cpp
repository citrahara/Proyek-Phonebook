#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include "phonebook_fix.h"

using namespace std;
using namespace registerp;

int main()
{
    phonebook con;
    int menu;

    while(1)
    {
        char nm[20];
		cout<<"\n";
		cout<<"============Menu============\n\n";
		cout<<"1) Register a person\n";
        cout<<"2) Edit a contact\n";
        cout<<"3) Search contact number\n";
        cout<<"4) Search contact name \n";
		cout<<"5) Delete a contact \n"; 
        cout<<"6) Display All Contacts\n";
        cout<<"7) Exit\n";
        cout<<"Your menu choice : ";
        cin>>menu;
        switch(menu)
        {
            case 1 : con.newcontact();
                 break;
            
			case 2 : con.editnumber();
                 break;
			
			case 3 :con.searchname();
                break;
           
            case 4 :
            cout<<"\n\nEnter Contact Name : " << endl;
            cin>>nm;
            con.display(nm);
            break;
            
			case 5:   con.deletecon();
            	break;

			case 6 :  con.display();
            	break;
              
           case 7:  exit(1);

           default:
                cout<<"Invalid Option!"<<endl;

        }

    }


return 0;
}
