#include <iostream>
#include <fstream>
#include <cstdlib> 

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
	char category[100];
	Usage usage;
	Expiry date;

};


void getInfo(Medicine m[], int &n){
	cout<<"How many medicine(s) do you want to insert into the inventory?\n";
	cin>>n;
	
	for(int i=0; i<n; i++){

		cout<<"Enter the unique ID of the medicine:  ";
		cin>>m[i].ID;
		cout<<"Enter the category of the medicine (Antifungal, Anti-pain, Antibiotic, Painkiller):  ";
		cin>>m[i].category;
		cout<<"Enter the usage (Period, Frequency and Directions) of the medicine:  ";
		cin>>m[i].usage.period;
		cout<<"Enter the frequency for the usage (Once, 2-times OR 3-times):  ";
		cin>>m[i].usage.frequency;
		cout<<"Enter the directions of use (Oral, Nasal, Intravenous or Injection):  ";
		cin>>m[i].usage.directions;
		cout<<"Enter the expiry date of the drug:  ";
		cin>>m[i].date.day;
		cout<<"Enter the expiry month of the drug:  ";
		cin>>m[i].date.month;
		cout<<"Enter the expiry year of the drug:  ";
		cin>>m[i].date.year;
	}
}


void registerMeds(char* fileName,Medicine m[],int n){
	
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

void searchMed(char* fileName, int id){
	ifstream in(fileName, ios::binary);
	Medicine m;
// search for the mediciine based on the input ID	
	if (in.is_open()) {
		in.read((char*)&m,sizeof(m));
		while (!in.eof()) {
			if(m.ID=id){
				cout<<"Medicine is found!\n";
				cout<<m.ID<<"\t"<<m.category<<"\t";
				cout<<m.usage.period<<"  "<<m.usage.frequency<<"  "<<m.usage.directions;
				cout<<m.date.year<<endl;
				in.close();
				return;
			}
			else
				in.read((char*)&m,sizeof(m));
		}
		in.close();
		cout<<"Medicine is NOT found!\n";
	}else {
		cout<<"File could not be opened.\n";
	}
}


void displayInventory(char* fileName){
// display the entire inventory read from the .db file created:
	ifstream in(fileName, ios::binary);
	Medicine m;
	if(in.is_open()){
		in.read((char*)&m,sizeof(m));
	while(!in.eof()){
		cout<<m.ID<<"\t"<<m.category<<"\t";
		cout<<m.usage.period<<"  "<<m.usage.frequency<<"  "<<m.usage.directions;
		cout<<m.date.year<<endl;
		in.read((char*)&m,sizeof(m));	
	}
		in.close();
	} else{
		cout<<"File could not be opened!\n";
	}
}


void editMed(char* fileName, int id){

	char* tempFile = "tempFile.db";
	ofstream out(tempFile, ios::binary);
	ifstream in(fileName, ios::binary);

	Medicine m;
	in.read((char*)&m,sizeof(m));
	while(!in.eof()){
        	if(m.ID=id){
                cout<<"Enter the newest ID of the medicine:  ";
		cin>>m.ID;
		cout<<"Enter the new category of the medicine (Antifungal, Anti-pain, Antibiotic, Painkiller):  ";
		cin>>m.category;
		cout<<"Enter the new usage (Period, Frequency and Directions) of the medicine:  ";
		cin>>m.usage.period;
		cout<<"Enter the new frequency for the usage (Once, 2-times OR 3-times):  ";
		cin>>m.usage.frequency;
		cout<<"Enter the new directions of use (Oral, Nasal, Intravenous or Injection):  ";
		cin>>m.usage.directions;
		cout<<"Enter the newer expiry date of the drug:  ";
		cin>>m.date.day;
		cout<<"Enter the expiry month of the drug:  ";
		cin>>m.date.month;
		cout<<"Enter the expiry year of the drug:  ";
		cin>>m.date.year;
			out.write((char*)&m, sizeof(m));
	}else {
			out.write((char*)&m, sizeof(m));
	}
		in.read((char*)&m, sizeof(m));
    } 
  		  in.close();
		  out.close();
		  remove(fileName);
	 	  rename(tempFile, fileName);
}


int main(){

char ans;
int choice;
Medicine m[100];
int n;
char* fileName="inventory.db";

 do{
 // enter the menu:
 cout<<"\nPlease enter your choice of action:  ";
 cin>>choice;
switch(choice){
		case 1:
	                getInfo(m,n);
 		        registerMeds(fileName,m,n);
		        break;
		case 2:
			displayInventory(fileName);
			break;
		case 3:
			int id;
			cout<<"Enter the ID of the medicine you are looking for:  ";
			cin>>id;
			searchMed(fileName, id);
			break;
		case 4:
			cout<<"Enter the ID of the medicine you are looking to modify:  ";
			cin>>id;
			editMed(fileName, id);
			break;
	}	
      }while(ans != 'n');

return 0;
}
