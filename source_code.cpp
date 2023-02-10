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

int main() 
{
	onlyDisplay od;
	cout << "Press F11 for better Experience...\n";
	od.authentication();
	return 0;
}