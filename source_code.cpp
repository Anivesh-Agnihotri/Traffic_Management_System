//Smart Traffic Management System
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
using namespace std;

#define pass 1234
int i, choice, dd=0, mm=0, yy=0, hr=0, mint=0, sound=0;

void date_time();
void gotoxy(int x, int y);

class onlyDisplay{
	public:
		void authentication();
		void load();
		void menu();		
};

class features{
	public:
		void record_veh();
		void booths();
		void helpline();
		void control();
};

class vehData {
	private:
    	unsigned long long int owner_no;
		int seater, generation, RTO_no;
		char veh_type[10], owner_name[50], des_pat[10], address[100], issued_date[20], veh_no[15];
	public:
		vehData(){strcpy(veh_no, "ABXXXXXXXX");}
		void read_data();
		int store_data();
		void view_data();
		void show_data();
		void header();
		void search_data(char *);
		void delete_data(char *);
		void update_data(char *);
};
void vehData::header() {
	cout << endl;
	cout<<setw(13)<<"Vehicle No"<<setw(15)<<"Vehicle Type"<<setw(18)<<"Owner Name"<<setw(18)<<"Phone Number"<<setw(10)<<"Seater"<<setw(15)<<"Generation"<<setw(10)<<"Fuel"<<setw(10)<<"RTO No"<<setw(20)<<"Issued Date"<<setw(35)<<"Address\n";
	int i;
	for(i=0; i<=170; i++)
		cout << "_";
	cout << endl;
}

void vehData::show_data() {
	cout<<"\n\n"<<setw(13)<<veh_no<<setw(15)<<veh_type<<setw(18)<<owner_name<<setw(18)<<owner_no<<setw(10)<<seater<<setw(15)<<generation<<setw(10)<<des_pat<<setw(10)<<RTO_no<<setw(20)<<issued_date<<setw(35)<<address;
}



int main() 
{
	onlyDisplay od;
	cout << "Press F11 for better Experience...\n";
	od.authentication();
	return 0;
}

void features::record_veh() {
	system("cls");
	onlyDisplay d; vehData vh;
	char get[15];
	gotoxy(65, 5);
	cout << "\xB2\xB2\xB2\xB2  Choose Option  \xB2\xB2\xB2\xB2"; gotoxy(55, 10);
	cout << "\xB2  1. Add a Record"; gotoxy(55, 12);
	cout << "\xB2  2. Delete a Record"; gotoxy(55, 14);
	cout << "\xB2  3. Update a Record"; gotoxy(55, 16);
	cout << "\xB2  4. Back to Main Menu";
	while(choice != 4) {
		gotoxy(55, 22);
		cout << "Enter your choice : ";
		cin >> choice;
		switch(choice) {
			case 1: {
				vh.read_data();
				vh.store_data();
				break;
			}
			case 2: {
				system("cls");
				gotoxy(65, 1); cout << "\xB2\xB2 Delete Record \xB2\xB2\n\n";
				gotoxy(50, 22);
				cout << "Enter the Vehicle No to delete : ";
				cin.ignore();
    			cin.getline(get, 14);
				vh.delete_data(get);
				break;
			}
			case 3: {
				system("cls");
				gotoxy(65, 1); cout << "\xB2\xB2 Update Record \xB2\xB2\n\n";
				gotoxy(50, 22);
				cout << "Enter the Vehicle No to Update : ";
				cin.ignore();
    			cin.getline(get, 14);
				vh.update_data(get);
				break;
			}
			case 4: d.menu();
		}
	}
}

int vehData::store_data() {
	features f;
	if(veh_no == 0) {
		cout<<"\nData Not intialized";
//		return 0;
	} else {
		ofstream fout;
		fout.open("file1.dat", ios::app|ios::binary);
		fout.write((char*)this, sizeof(*this));
		fout.close();
		cout << "\n\tData stored Successfully";
//		return 1;
	}
	cout << "\n\tPress any key to continue...";
	getch();
	f.record_veh();
}

void vehData::read_data() {
	system("cls");
	gotoxy(65, 1); cout << "\xB2\xB2 Please enter the details \xB2\xB2\n\n";
    int type;
	cout << "\n\tVehicle No : ";
    cin.ignore();
    cin.getline(veh_no, 14);
	cout << "\n\t1. Two Wheeler (eg. Bike)\t2. Three Wheeler (eg. Auto)\t3. Four Wheeler (eg. Car)\n\n\tVehicle Type : ";
	cin >> type;
	if(type==1) strcpy(veh_type, "2 Wheeler");
	else if(type==2) strcpy(veh_type, "3 Wheeler");
	else if(type==3) strcpy(veh_type, "4 Wheeler");
	else strcpy(veh_type, "None");
	
	cout << "\tOwner Name: ";
    cin.ignore();
    cin.getline(owner_name, 49);
    cout << "\tMobile No : ";
    cin >> owner_no;
    cout << "\tSeater : ";
    cin >> seater;
    cout << "\tGeneration : ";
    cin >> generation;
    cout << "\tDesiel / Petrol : ";
    cin.ignore();
    cin.getline(des_pat, 9);
    cout << "\tRTO No : ";
    cin >> RTO_no;
	cout << "\tAddress : ";
    cin.ignore();
    cin.getline(address, 99);
	//Date and Time
	date_time();
	sprintf(issued_date, "%d:%d %d/%d/%d", hr, mint, dd, mm, yy);
}

void vehData::delete_data(char *t) {
	features f;
	int counter=0;
	ifstream fin;
	ofstream fout;
	fin.open("file1.dat", ios::in|ios::binary);
	if(!fin)
		cout << "\nFile NOT Found";
	else {
		fout.open("tempFile.dat", ios::out|ios::binary);
		fin.read((char*)this, sizeof(*this));
		while(!fin.eof()) {
			if(strcmp(t, veh_no)) {
				fout.write((char*)this, sizeof(*this)); counter++;
			}fin.read((char*)this, sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("file1.dat");
		rename("tempFile.dat", "file1.dat");
		gotoxy(50, 25);
		if(counter==0) cout << "Unable to Delete";
		else cout << "\n\tDeleted Successfully";
	}
	gotoxy(50, 27);
	cout << "\n\tPress any key to continue...";
	getch();
	f.record_veh();
}
