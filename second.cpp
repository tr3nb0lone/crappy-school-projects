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
		cout<<"Enter the unique ID of the medicinei\n";
		cin>>m[i].ID;
		cout<<"Enter the category of the medicine (Antifungal, Anti-pain, Antibiotic, Painkiller)\n";
		cin>>m[i].category;
		cout<<"Enter the usage (Period, Frequency and Directions) of the medicine\n";
		cin>>m[i].usage.period;
		cout<<"Enter the frequency for the usage (Once, 2-times OR 3-times)\n";
		cin>>m[i].usage.frequency;
		cout<<"Enter the directions of use (Oral, Nasal, Intravenous or Injection)\n";
		cin>>m[i].usage.directions;
		cout<<"Enter the expiry date of the drug:\n";
		cin>>m[i].date.day;
		cout<<"Enter the expiry month of the drug:\n";
		cin>>m[i].date.month;
		cout<<"Enter the expiry year of the drug:\n";
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

void searchMed(char* fileName, int ID){
	ifstream in(fileName, ios::binary);
	Medicine m;
// search for the mediciine based on the input ID	
	if (in.is_open()) {
		in.read((char*)&m,sizeof(m));
		while (!in.eof()) {
			if(m.ID=m.ID){
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




int main() {

char ans;
int choice;
Medicine m[100];
int n;
char* fileName="inventory.db";

do{
// enter the menu:
 cout<<"Please enter your choice of action: \n";
 cin>>choice;
switch(choice){
		case 1:
		// getInfo(m,n);
		// registerMed;
		   break;
	}	
      } while(ans != 'n');

return 0;
}

