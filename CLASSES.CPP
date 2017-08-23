#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>

extern int *m,*p;
extern void mouse(int *);
char filename[15];
char file[15];
class Class
{    	public:
	char name[10];
	int r_subno,o_subno;
	int periods_left;
	struct r_subject
	{
		char topic[10];
		int t_no;
		int assign_no;
		float prior;
		char ct;
	};
	r_subject r_sub[20];
	struct o_subject
	{
		char name[10],topic[15][10];
		int n,t_no[15],assign_no[15];
		float prior;
		char ct;
		int no_of_period;
	};
	o_subject o_sub[10];
	int time[10][7];
	Class *next;
	Class();
	int assign(int teach_count);
	void display();
	void get();
	int max_prior(int a,int b);
	int max_prior2(int a,int b);
	void exchange(int t_no,int a,int b,int x,int k);
	void make(int a,int b,int k);
	void modify();
	void disp_time();
	void mark(int a,int b,int x,int k);
	void demark(int a,int b);
	void allot(int a,int b,int x,int k);
	void deallot(int a,int b);
	void sp_make(int k);
	int check_allot(int a,int b,int c_no);
	friend int overwrite(int c_no,int t_no,int a,int b);

};

extern Class& C(int n);
extern int class_count;
extern void read_class(char * f_name);
extern void read_teach(char *f_name);

void add_c()
{
  while(1)
   {
	clrscr();
	gotoxy(39,12);
	textcolor(4);
	cprintf("ADD");
	gotoxy(39,13);
	cprintf("อออ");
	textcolor(10);
	do
	{
		gotoxy(20,23);
		cprintf("Are you sure you want to create a class ?");
		gotoxy(30,26);
		cprintf("Yes");
		gotoxy(50,26);
		cprintf("No");
		mouse(m);
		if(m[1]/8>=49&&m[2]/8==25)
			return ;
	}while(!(m[1]/8<49&&m[2]/8==25));
	clrscr();
	gotoxy(20,6);
	cprintf("Enter the details of the class ::");

	strcpy(file,filename);
	strcat(file,".cls");
	ofstream fout(file,ios::app|ios::binary);
	Class C1;
	C1.get();
	fout.write((char*)&C1,sizeof(Class));
	fout.close();
	gotoxy(10,wherey()+2);
	cprintf("The class has been added");
	delay(1000);
   }
}

void view_c()
{
  while(1)
   {
	read_class(filename);
	read_teach(filename);
	clrscr();int opt;
	gotoxy(35,2);
	textcolor(4);
	cprintf("VIEW MENU");
	gotoxy(35,3);
	cprintf("อออออออออ");
	textcolor(10);
	gotoxy(35,4);
	if(class_count==0)
	{
		gotoxy(15,4);
		cprintf("There  are no classes to display");
	}
	for(int i=0;i<class_count;i++)
		cout<<"\n\t\t"<<C(i).name;
	cout<<"\n\t\t";
	cprintf("Back");
	mouse(m);
	opt=(m[2]/8)-3;
	if(opt<=class_count)
	{
		clrscr();
		C(opt-1).display();

	}
	else if(opt==class_count+1)
		return;
   }
}

void Delete_c()
{
  while(1)
   {
	read_class(filename);
	clrscr();
	int opt;
	gotoxy(37,2);
	textcolor(4);
	cprintf("DELETE");
	gotoxy(37,3);
	cprintf("ออออออ");
	textcolor(10);
	gotoxy(37,4);
	ofstream fout;
	if(class_count==0)
	{
		gotoxy(10,4);
		cprintf("There  are no classes to display");
	}
	for(int i=0;i<class_count;i++)
		cout<<"\n\t\t"<<C(i).name;
	cout<<"\n\t\t";
	cprintf("Delete all");
	cout<<"\n\t\t";
	cprintf("Back");
	mouse(m);
	opt=(m[2]/8)-3;
	if(opt==class_count+1)
	{
		clrscr();
		gotoxy(10,20);
		gotoxy(10,wherey()+2);
		cprintf("Are you sure you want to delete all classes ?");
		gotoxy(30,wherey()+2);
		cprintf("Yes");
		gotoxy(50,wherey());
		cprintf("No");
		do
		{
			mouse(m);
			if(m[1]/8<49&&m[2]/8==wherey()-1)
			{

				strcpy(file,filename);
				strcat(file,".cls");
				fout.open(file,ios::out);
				gotoxy(20,wherey()+1);
				cprintf("All classes deleted");
				mouse(p);
				fout.close();
				return ;
			}

		}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
	}
	if(opt==class_count+2)
	{
		return ;
	}
	fout.open("temp",ios::out|ios::binary);
	for(i=0;i<class_count;i++)
		if(i==opt-1)
		{
			clrscr();
			gotoxy(10,6);
			cprintf("The details of the class are : ");
			C(i).display();
			clrscr();
			gotoxy(10,20);
			gotoxy(10,wherey()+2);
			cprintf("Are you sure you want to delete this class ? ");
			gotoxy(30,wherey()+2);
			cprintf("Yes");
			gotoxy(50,wherey());
			cprintf("No");
			do
			{
				mouse(m);
				if(m[1]/8<49&&m[2]/8==wherey()-1)
				{
					cout<<"\n\n\t\tClass "<<C(i).name<<" Deleted ";
					mouse(p);
					break;
				}
				else if(!(m[1]/8>=49&&m[2]/8==wherey()-1));
					fout.write((char *)&C(i),sizeof(Class));
			}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
		}
		else
		{
			fout.write((char *)&C(i),sizeof(Class));
		}
	fout.close();

	strcpy(file,filename);
	strcat(file,".cls");
	remove(file);
	rename("temp",file);
  }
}

void modify_c()
{
  while(1)
   {
	read_class(filename);
	clrscr();
	int opt;
	gotoxy(35,2);
	textcolor(4);
	cprintf("MODIFY MENU");
	gotoxy(35,3);
	cprintf("อออออออออออ");
	textcolor(10);
	gotoxy(35,4);
	ofstream fout("temp",ios::out|ios::binary);
	if(class_count==0)
	{
		gotoxy(10,4);
		cprintf("There are no classes to display");
	}
	for(int i=0;i<class_count;i++)
		cout<<"\n\t\t"<<C(i).name;
	cout<<"\n\t\t";cprintf("Back");
	mouse(m);
	opt=(m[2]/8)-3;
	if(opt<=class_count)
	{
		clrscr();
		C(opt-1).modify();
		for(i=0;i<class_count;i++)
			fout.write((char *)&C(i),sizeof(Class));
		fout.close();
		strcpy(file,filename);
		strcat(file,".cls");
		remove(file);
		rename("temp",file);
	}
	else if(opt==class_count+1)
		return;
  }
}

void copy_c()
{
  while(1)
  {
	read_class(filename);
	clrscr();
	int opt;
	gotoxy(38,2);
	textcolor(4);
	cprintf("COPY");
	gotoxy(38,3);
	cprintf("ออออ");
	textcolor(10);
	gotoxy(38,4);
	ofstream fout;
	strcpy(file,filename);
	strcat(file,".cls");
	fout.open(file,ios::app|ios::binary);
	if(class_count==0)
	{
		gotoxy(10,4);
		cprintf("There are no classes to display");
	}
	for(int i=0;i<class_count;i++)
		cout<<"\n\t\t"<<C(i).name;
	cout<<"\n\t\t";
	cprintf("Back");
	mouse(m);
	opt=(m[2]/8)-3;
	if(opt<=class_count)
	{
		clrscr();
		gotoxy(10,6);
		cprintf("The class details are :: ");
		C(opt-1).display();
		Class *C1 =new Class;
		*C1=C(opt-1);
		clrscr();
		gotoxy(10,20);
		gotoxy(10,wherey()+2);
		cprintf("Do you want to copy this class ?");
		gotoxy(30,wherey()+2);
		cprintf("Yes");
		gotoxy(50,wherey());
		cprintf("No");
		do
		{
			mouse(m);
			if(m[1]/8<49&&m[2]/8==wherey()-1)
			{
				clrscr();
				C(opt-1).display();
				gotoxy(10,wherey()+2);
				cprintf("Enter the name of new class :: ");
				gets(C1->name);
				fout.write((char *)C1,sizeof(Class));
				cout<<"\n\n\t\tClass "<<C1->name<<" Copied ";
				mouse(p);
				break;
			}
		}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
		fout.close();
		delete C1;
	}
	else if(opt==class_count+1)
		return;
  }
}

void classes()
{
	int ch;
	clrscr();
	textcolor(4);
	gotoxy(5,23);
	cprintf("Enter the name of file containing Class database :: ");
	gotoxy(5,27);
	cprintf("[Press \'enter\' to  perform operations on Default File ]");
	gotoxy(60,23);
	gets(filename);
	if(!strcmpi(filename,"\0"))
		strcpy(filename,"DEFAULT1");

	do
	{
		clrscr();
		gotoxy(36,14);
		textcolor(4);
		cprintf("CLASSES");
		gotoxy(36,15);
		cprintf("อออออออ");
		textcolor(10);
		gotoxy(30,18);
		cprintf("Add a new class");
		gotoxy(30,20);
		cprintf("View all classes");
		gotoxy(30,22);
		cprintf("Modify an existing class ");
		gotoxy(30,24);
		cprintf("Delete a class");
		gotoxy(30,26);
		cprintf("Copy a class");
		gotoxy(30,28);
		cprintf("Back");
		mouse(m);
		ch=(m[2]/16)-7;
		switch(ch)
		{
			case 1: add_c();
				break;
			case 2: view_c();
				break;
			case 3: modify_c();
				break;
			case 4: Delete_c();
				break;
			case 5: copy_c();
				break;
			case 6: break;
		}
	}while(ch!=6);
}