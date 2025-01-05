#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
/*

 Mini project in cpp to demonstrate the simplest and functional concepts in CPP:
1. Registering records on a file
2.Displaying all records from a file
3. Searching for a record
4. Deleting a record
5. Editing a record.

*/
struct Address{
	char kk[30];
	int woreda;
};

struct student{
	int id;
	char firstName[30];
	int age;
	Address address;
};

void searchStudentById(char* fileName,int id){

		ifstream in(fileName,ios::binary);
		student s;
		
		if(in.is_open()){
			in.read((char*)&s,sizeof(s));
		    while(!in.eof()){
		    	if(s.id==id){
		    	cout<<"The student is found.\n";
		    	cout<<s.id<<"\t"<<s.firstName;
				cout<<"\t"<<s.age<<"\t";
				cout<<s.address.kk<<"\t";
				cout<<s.address.woreda<<endl;
				in.close();
				return;
				}
				else    	
				  in.read((char*)&s,sizeof(s));	
			}
		in.close();
		cout<<"The student is not found.\n";
	}else{
		cout<<"File cannot be opened.\n";
   }
}
void displayAlltudents(char* fileName){

		ifstream in(fileName,ios::binary);
		student s;

		if(in.is_open()){
			in.read((char*)&s,sizeof(s));
		    while(!in.eof()){

		cout<<s.id<<"\t"<<s.firstName;
		cout<<"\t"<<s.age<<"\t";
		cout<<s.address.kk<<"\t";
		cout<<s.address.woreda<<endl;
		in.read((char*)&s,sizeof(s));	
		}
		
		in.close();
	}else{
		cout<<"File could not be opened!\n";
	}
}
void getData(student s[],int &n){
	cout<<"How many students do you want to register?";
	cin>>n;
	
	for(int i=0;i<n;i++){
		cout<<"Enter Id:";
		cin>>s[i].id;
		
		cout<<"Enter First Name:";
		cin>>s[i].firstName;
		cout<<"Enter Age:";
		cin>>s[i].age;
		cout<<"Enter Kifle Ketema:";
		cin>>s[i].address.kk;
		cout<<"Enter Woreda:";
		cin>>s[i].address.woreda;
	}
}


void deleteStudentById(char* fileName,int id){
	char* fileTemp="temp.dat";
	ofstream out(fileTemp,ios::binary);
	ifstream in(fileName,ios::binary);
	
	student s;
	in.read((char*)&s,sizeof(s));
	int flag=0;
	  while(!in.eof()){
	  	 if(s.id!=id){
	  	 	out.write((char*)&s,sizeof(s));
		   }
		   
		   if(s.id==id)
		     flag=1;
		in.read((char*)&s,sizeof(s));
	  }
	  in.close();
	  out.close();
	  remove(fileName);
	  rename(fileTemp,fileName);
	
	if(flag==1)
	   cout<<"Student record is deleted.\n";
	else
	    cout<<"No such student.\n";
	  
	
}

void editStudentById(char* fileName,int id){
	char* fileTemp="temp.dat";
	ofstream out(fileTemp,ios::binary);
	ifstream in(fileName,ios::binary);
	
	student s;
	in.read((char*)&s,sizeof(s));
	  while(!in.eof()){
	  	 if(s.id==id){
	  	 	cout<<"Enter new name :";
	  	 	cin>>s.firstName;
	  	 	
	  	 	cout<<"Enter new age :";
	  	 	cin>>s.age;
	  	 	
	  	 	cout<<"Enter new Kifle ketema :";
	  	 	cin>>s.address.kk;
	  	 	
	  	 	cout<<"Enter new woreda :";
	  	 	cin>>s.address.woreda;
	  	 	
	  	 	out.write((char*)&s,sizeof(s));
         	 }
		   else{
		   	out.write((char*)&s,sizeof(s));
		   }
		in.read((char*)&s,sizeof(s));
	  }
	  in.close();
	  out.close();
	  remove(fileName);
	  rename(fileTemp,fileName);
	
	
	
}
void registerStudents(char* fileName,student s[],int n){
	
	ofstream out(fileName,ios::binary | ios::app);
	if(out.is_open()){
		for(int i=0;i<n;i++){
			out.write((char*)&s[i],sizeof(s[i]));
		}
		out.close();
	}else{
		cout<<"File cannot be opened.\n";
	}
	
	
}

int main(int argc, char** argv) {
	
 int choice;
 char ans;
 student s[100];
 int n;
 char* fileName="student1.dat"; 	
	do{
	cout<<"========MENU=========\n";
	cout<<"1:Register students on a file.\n";
	cout<<"2:Display all students from a file.\n";
	cout<<"3:Search a student by Id.\n";
	cout<<"4:Delete a student by Id.\n";
	cout<<"5:Edit a student's Record.\n";
	cout<<"6:Exit The Program.\n";
	
	cout<<"Enter your choice:";
	cin>>choice;
	system("clear");	
	switch(choice){
		case 1:
			getData(s,n);
			registerStudents(fileName,s,n);
			break;
		case 2:
			displayAlltudents(fileName);
			//displayAlltudents("temp.dat");
			break;
		case 3:
			int id;
			cout<<"Enter the Id of the student you want to search:";
			cin>>id;
			searchStudentById(fileName,id);
			break;
			
		case 4:
			cout<<"Enter ID:";
			cin>>id;
			deleteStudentById(fileName,id);
			break;
		case 5:
			cout<<"Enter ID:";
			cin>>id;
			editStudentById(fileName,id);
		     break;
		case 6:
			break;
	}
cout<<"Do you want to continue?(y/n):";
 cin>>ans;		
	}while(ans!='n');
	
	return 0;
}
