#include <ios>
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
	cout<<"How many medicine(s) do you want to insert into the inventory?  ";
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
				cout<<"Medicine is found!\n";
				cout<<m.ID<<"\t"<<m.category<<"\t";
				cout<<m.usage.period<<"\t"<<m.usage.frequency<<"\t"<<m.usage.directions;
				cout<<"\t"<<m.date.year<<endl;
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

	Medicine m;

	in.read((char*)&m,sizeof(m));
	int flag=0;
	  while(!in.eof()){
	  	 if(m.ID!=id){
	  	 	out.write((char*)&m,sizeof(m));
		   }
		   
		   if(m.ID==id)
		     flag=1;
		in.read((char*)&m,sizeof(m));
	  }
	  in.close();
	  out.close();
	  remove(fileName);
	  rename(tempFile,fileName);
	
	if(flag==1)
	   cout<<"Medicine record for ID "<<m.ID<< " is deleted successfully!.\n";
	else
	    cout<<"No such record.\n";
	  
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
	cout<<"\tEnter 1 to register a new medicine.\n";
	cout<<"\tEnter 2 to display entries of the Inventory.\n";
	cout<<"\tEnter 3 to search pre-existing medicine.\n";
	cout<<"\tEnter 4 to edit a Medicine's record.\n";
	cout<<"\tEnter 5 to Delete an entry from the Inventory.\n";
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
		}
		cout<<"Do you want to continue? (Y)es/(N)o  ";
		cin>>ans;
      }while(ans != 'n' && ans != 'N');

return 0;

}
