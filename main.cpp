#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

/*
Project title: Inventory Management System for Pharmacies.

*/

struct Expiry {
	int day;
	int month;
	int year;
};

struct Usage {
	char period[50];
	char frequency[70];
	char directions[200];
};

struct Medicine{
	int ID;
	char medName[100];
	char category[100];
	Usage usage;
	Expiry date;

};


void getInfo(Medicine m[], int &n){
	cout<<"How many medicine(s) do you want to insert into the inventory?  ";
	cin>>n;

	for(int i=0; i<n; i++){
		cout<<"Enter the unique ID of the medicine:  ";
		cin>>m[i].ID;
		cout<<"Enter the unique name of the medicine:  ";
		cin>>m[i].medName;
		cout<<"Enter the category of the medicine (Antifungal, Anti-pain, Antibiotic, Painkiller, Supplement, Vitamin etc):  ";
		cin>>m[i].category;
		cout<<"Enter the usage Period of the medicine (Daily, Weekly, Monthly):  ";
		cin>>m[i].usage.period;
		cout<<"Enter the frequency for the usage (Once, 2-times OR 3-times):  ";
		cin>>m[i].usage.frequency;
		cout<<"Enter the directions of use, i.e Administration mechanism (Oral, Nasal, Intravenous or Injection):  ";
		cin>>m[i].usage.directions;
		cout<<"Enter the expiry DATE of the drug:  ";
		cin>>m[i].date.day;
		cout<<"Enter the expiry MONTH of the drug:  ";
		cin>>m[i].date.month;
		cout<<"Enter the expiry YEAR of the drug:  ";
		cin>>m[i].date.year;
	}
}


void registerMedicine(char* fileName,Medicine m[],int n){

	ofstream out(fileName,ios::binary | ios::app);
	if(out.is_open()){
		for(int i=0;i<n;i++){
			out.write((char*)&m[i],sizeof(m[i]));
		}
	out.close();
	} else{
		cout<<"File cannot be opened.\n";
      }
}

void searchMedicine(char* fileName, int id){
	ifstream in(fileName, ios::binary);
	Medicine m;
// search for the medicine based on the input ID
	if (in.is_open()) {
		in.read((char*)&m,sizeof(m));
		while (!in.eof()) {
			if(m.ID=id){
				system("clear");
		cout << "\n\t=== Inventory ===\n";
        cout << left << setw(10) << "ID" << setw(20) << "Category" << setw(15) << "Usage Period"
             << setw(15) << "Frequency" << setw(20) << "Directions" << setw(15) << "Expiry Date" << "\n";
        cout << "--------------------------------------------------------------------------------------------\n";

        while (in.read((char*)&m, sizeof(m))) {
            cout << left << setw(10) << m.ID << setw(20) << m.category << setw(15) << m.usage.period
                 << setw(15) << m.usage.frequency << setw(20) << m.usage.directions
                 << setw(0) << m.date.day << "/" << m.date.month << "/" << m.date.year << "\n";
        }
			}
			else{
				in.read((char*)&m,sizeof(m));
				cout<<"Medicine is NOT found!\n";
			}
		}
		in.close();

	}else {
		cout<<"File could not be opened.\n";
	}
}


void displayInventory(char* fileName){
// display the entire inventory read from the .db file created:
	ifstream in(fileName, ios::binary);
	Medicine m;
	if(in.is_open()){
            system("clear");
		cout << "\n\t\t\t\t=== Inventory ===\n";
        cout << left << setw(10) << "ID" << setw(20) << "Category" << setw(15) << "Usage Period  "
             << setw(15) << "Frequency" << setw(20) << "Directions" << setw(15) << "Expiry Date" << "\n";
        cout << "--------------------------------------------------------------------------------------------\n";

        while (in.read((char*)&m, sizeof(m))) {
            cout << left << setw(10) << m.ID << setw(20) << m.category << setw(15) << m.usage.period
                 << setw(15) << m.usage.frequency << setw(20) << m.usage.directions
                 << setw(0) << m.date.day << "/" << m.date.month << "/" << m.date.year << "\n";
        }
		in.close();
	} else{
		cout<<"File could not be opened!\n";
	}
}




void editMedicine(char *filePath){

	fstream file(filePath,ios::binary | ios::out | ios::in);
	int id;

	Medicine m;
	Medicine m1;
	cout<<"Enter id of the medicine you want to edit:  ";
     	cin>>m1.ID;
	if(file.is_open()){

		while(file.read((char*)&m,sizeof(m))){
		if(m1.ID==m.ID){
		cout<<"Enter the newest ID of the medicine:  ";
		cin>>m1.ID;
		cout<<"Enter the new category of the medicine (Antifungal, Anti-pain, Antibiotic, Painkiller):  ";
		cin>>m1.category;
		cout<<"Enter the new usage (Period, Frequency and Directions) of the medicine:  ";
		cin>>m1.usage.period;
		cout<<"Enter the new frequency for the usage (Once, 2-times OR 3-times):  ";
		cin>>m1.usage.frequency;
		cout<<"Enter the new directions of use (Oral, Nasal, Intravenous or Injection):  ";
		cin>>m1.usage.directions;
		cout<<"Enter the newer expiry date of the drug:  ";
		cin>>m1.date.day;
		cout<<"Enter the expiry month of the drug:  ";
		cin>>m1.date.month;
		cout<<"Enter the expiry year of the drug:  ";
		cin>>m1.date.year;

		file.seekp(file.tellg()-sizeof(m1),ios::beg);
		file.write((char*)&m1,sizeof(m1));
		file.close();
		cout<<"Record is sucessfully updated.\n";
		break;
		}

	}

		file.close();
	}else{
		cout<<"File cannot be opened.\n";
	}

}



void deleteMedicine(char* fileName, int id){

	char* tempFile = "tempFile.db";
	ofstream out(tempFile, ios::binary);
	ifstream in(fileName, ios::binary);

	if(in.is_open() && out.is_open()){
       	    int id;
	       Medicine m;
	       cout<<"Enter ID of the Medicine you want to delete:  ";
	       cin>>id;
		while(in.read((char*)&m,sizeof(m))){
			  if(id!=m.ID){
			  	out.write((char*)&m,sizeof(m));
			  }
	}
	in.close();
	out.close();
	remove(fileName);
	rename(tempFile,fileName);
	cout<<"One record is successfully deleted.\n";
		}

	else{
		cout<<"File cannot be opened.\n";
	}


}



void displayHelp(){
	cout<<"Usage:   this is a usage.\n";

}




int main(){

char ans;
int choice;
Medicine m[100];
int n;
char* fileName="inventory.db";

    do{
	cout<<"=============================== MENU ===============================\n";
	cout<<"\t\tPharmacy Inventory Management System: \n";
	cout<<"\tEnter 1 to REGISTER a new medicine.\n";
	cout<<"\tEnter 2 to DISPLAY entries of the Inventory.\n";
	cout<<"\tEnter 3 to SEARCH a pre-existing medicine.\n";
	cout<<"\tEnter 4 to EDIT a Medicine's record.\n";
	cout<<"\tEnter 5 to DELETE an entry from the Inventory.\n";
	cout<<"\tEnter 6 to display a brief instructions for the program.\n"; 
	cout<<"\tEnter 7 to exit the program.\n"; 
	cout<<"============================== ~~~~~~ ==============================\n";
	cout<<"Please enter your choice of action:  ";
	cin>>choice;
	system("clear");
        switch(choice){
		case 1:
	                getInfo(m,n);
 		        registerMedicine(fileName,m,n);
		        break;
		case 2:
			displayInventory(fileName);
			break;
		case 3:
			int id;
			cout<<"Enter the ID of the medicine you are looking for:  ";
			cin>>id;
			searchMedicine(fileName, id);
			break;
		case 4:
			editMedicine(fileName);
			break;
	        case 5:
	            deleteMedicine(fileName, id);
	            break;
		case 6:
			displayHelp();
			break;
		case 7:
			exit(0);
	}
		cout<<"Do you want to continue? (Y)es/(N)o  ";
		cin>>ans;
      }while(ans != 'n' && ans != 'N');

return 0;

}
