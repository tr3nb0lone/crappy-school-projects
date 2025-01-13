void updateStudent(char *filePath){
	
		fstream file(filePath,ios::binary | ios::out | ios::in);
	
	int id;
	
	
		student s;
		student s1;
		cout<<"Enter id of the studnet you want to edit:";
     	cin>>s1.id;
	if(file.is_open()){
	
		while(file.read((char*)&s,sizeof(s))){
			if(s1.id==s.id){
				cout<<"Enter new name :";
				cin>>s1.fname;
				cout<<"Enter new GPA :";
				cin>>s1.gpa;
						
			 file.seekp(file.tellg()-sizeof(s),ios::beg);
				file.write((char*)&s1,sizeof(s1));
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

void deleteStudent(char* originalFilePath,char* tempFilePath ){
		ifstream infile(originalFilePath,ios::binary);
		ofstream outfile(tempFilePath,ios::binary);
		if(infile.is_open() && outfile.is_open()){
       	    int id;
	       student s;
	       cout<<"Enter id of the student you want to delete:";
	       cin>>id;
		while(infile.read((char*)&s,sizeof(s))){
			  if(id!=s.id){
			  	outfile.write((char*)&s,sizeof(s));
			  }
	}
	infile.close();
	outfile.close();
	remove(originalFilePath);
	rename(tempFilePath,originalFilePath);
	cout<<"One record is successfully deleted.\n";		
		}
		
	else{
		cout<<"File cannot be opened.\n";
	}
	
	
}