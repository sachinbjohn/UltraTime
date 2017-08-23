#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<string.h>

extern int *m,*p;
extern void mouse(int *);
extern char filename[15];
extern char file[15];
class teacher
{
	public:
	char name[10];
	char sub_teaching[20][10];
	int no_of_sub,no_of_class,no_of_assignment;
	char class_teaching[15][10];
	int time[10][7];
	struct assignment
	{
		char Class[10];
		char subj[10];
		int no_of_period,m_alloted_per,n_alloted_per,alloted_per;
	};
	assignment a[25];
	int tot_per,tot_allot;
	teacher *next;
	teacher();
	void assign(char *STD,char *SUBJ,int p);
	void get();
	void display();
	void disp_time();
	int search(char *STD,char *SUBJ);
	float prior_cal(int n,int period,int x,int y,int s_no,char ct);
	void  clear_assign(int n);
	void modify();
	friend int search_name(char* NAME);
};
extern teacher &T(int n);
extern int teach_count;
extern  void read_teach(char * f_name);
extern void read_class(char * f_name);
void add_t()
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
		gotoxy(20,24);
		cprintf("Are you sure you want to create a Teacher ?");
		gotoxy(30,26);
		cprintf("Yes");
		gotoxy(50,26);
		cprintf("No");
		mouse(m);
		if(m[1]/8>=49&&m[2]/8==25)
			return ;
	}while(!(m[1]/8<49&&m[2]/8==25));
	clrscr();
	gotoxy(10,6);
	cprintf("Enter the details of the teacher ::");
	strcpy(file,filename);
	strcat(file,".tch");
	ofstream fout(file,ios::app|ios::binary);
	teacher *T1=new teacher;
	T1->get();
	fout.write((char*)T1,sizeof(teacher));
	fout.close();
	gotoxy(10,wherey()+2);
	cprintf("The teacher has been added");
	delay(1000);
	delete T1;
   }
}

void view_t()
{
   while(1)
    {
	read_teach(filename);
	read_class(filename);
	clrscr();
	int opt;
	gotoxy(35,2);
	textcolor(4);
	cprintf("VIEW MENU");
	gotoxy(35,3);
	cprintf("อออออออออ");
	textcolor(10);
	gotoxy(10,4);
	if(teach_count==0)
	{
		gotoxy(10,4);
		cprintf("There  are no teachers to display");
		gotoxy(10,4);}
	for(int i=0;i<teach_count;i++)
	{
		if(i<=39)
		{
			gotoxy(10,wherey()+1);
			cout<<T(i).name;
			if(i==39)
				gotoxy(30,4);
		}
		else if(i<=79)
		{
			gotoxy(30,wherey()+1);
			cout<<T(i).name;
			if(i==79)
				gotoxy(50,4);
		}
		else if(i<=119)
		{
			gotoxy(50,wherey()+1);
			cout<<T(i).name;
		}
	}
	if(wherex()>=30)
		if(wherex()>=50)
			gotoxy(50,wherey()+1);
		else
			gotoxy(30,wherey()+1);
	else
		gotoxy(10,wherey()+1);
	cprintf("Back");
	m[2]=0;mouse(m);
	if(m[1]/8>49)
		opt=((m[2]/8)+80-3);
	else if(m[1]/8>29)
		opt=((m[2]/8)+40-3);
	else
		opt=(m[2]/8)-3;
	if(opt<=teach_count)
	{
		if(opt<1)
		    continue;
		clrscr();
		T(opt-1).display();

	}
	else if(opt==teach_count+1)
		return;
    }
}

void Delete_t()
{
   while(1)
    {
	read_teach(filename);
	clrscr();
	int opt;
	gotoxy(37,2);
	textcolor(4);
	cprintf("DELETE");
	gotoxy(37,3);
	cprintf("ออออออ");
	gotoxy(37,4);
	textcolor(10);
	ofstream fout;
	if(teach_count==0)
	{
		gotoxy(10,4);
		cprintf("There  are no teachers to display");
		gotoxy(10,4);}
	for(int i=0;i<teach_count;i++)
	{
		if(i<=39)
		{
			gotoxy(10,wherey()+1);
			cout<<T(i).name;
			if(i==39)gotoxy(30,4);
		}
		else if(i<=79)
		{
			gotoxy(30,wherey()+1);
			cout<<T(i).name;
			if(i==79)gotoxy(50,4);
		}
		else if(i<=119)
		{
			gotoxy(50,wherey()+1);
			cout<<T(i).name;
		}
	}
	if(wherex()>=30)
		if(wherex()>=50)
		{
			gotoxy(50,wherey()+1);
			cprintf("Delete all");
			gotoxy(50,wherey()+1);
			cprintf("Back");
		}
		else
		{
			gotoxy(30,wherey()+1);
			cprintf("Delete all");
			gotoxy(30,wherey()+1);
			cprintf("Back");
		}
		else
		{
			gotoxy(10,wherey()+1);
			cprintf("Delete all");
			gotoxy(10,wherey()+1);
			cprintf("Back");
		}
	mouse(m);
	if(m[1]/8>49)
		opt=((m[2]/8)+80-3);
	else if(m[1]/8>29)
		opt=((m[2]/8)+40-3);
	else
		opt=(m[2]/8)-3;
	if(opt==teach_count+1)
	{
		clrscr();
		gotoxy(10,20);
		gotoxy(10,wherey()+2);
		cprintf("Are you sure you want to delete all Teachers ?");
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
				strcat(file,".tch");
				fout.open(file,ios::out);
				gotoxy(20,wherey()+1);
				cprintf("All Teachers deleted");
				mouse(p);
				fout.close();
				return ;
			}

		}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
	}
	if(opt==teach_count+2)
	{
		return ;
	}
	fout.open("temp",ios::out|ios::binary);
	for(i=0;i<teach_count;i++)
		if(i==opt-1)
		{
			clrscr();
			gotoxy(10,2);
			cprintf("The details of the teacher are :: ");
			T(i).display();
			clrscr();
			gotoxy(10,20);
			gotoxy(10,wherey()+2);
			cprintf("Are you sure you want to delete this Teacher ?");
			gotoxy(30,wherey()+2);
			cprintf("Yes");
			gotoxy(50,wherey());
			cprintf("No");
			do
			{
				mouse(m);
				if(m[1]/8<49&&m[2]/8==wherey()-1)
				{
					cout<<"\n\n\t\tTeacher "<<T(i).name<<" Deleted ";
					mouse(p);
					break;
				}
				else if(!(m[1]/8>=49&&m[2]/8==wherey()-1));
					fout.write((char *)&T(i),sizeof(teacher));
			}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
		}
		else
		{
			fout.write((char *)&T(i),sizeof(teacher));
		}
	fout.close();
	strcpy(file,filename);
	strcat(file,".tch");
	remove(file);
	rename("temp",file);
   }
}

void modify_t()
{
  while(1)
   {
	read_teach(filename);
	clrscr();
	int opt;
	gotoxy(35,2);
	textcolor(4);
	cprintf("MODIFY MENU");
	gotoxy(35,3);
	cprintf("อออออออออออ");
	gotoxy(35,4);
	textcolor(10);
	ofstream fout("temp",ios::out|ios::binary);
	if(teach_count==0)
	{
		gotoxy(10,4);
		cprintf("There are no Teachers to display");
		gotoxy(10,4);
	}
	for(int i=0;i<teach_count;i++)
	{
		if(i<=39)
		{
			gotoxy(10,wherey()+1);
			cout<<T(i).name;
			if(i==39)gotoxy(30,4);
		}
		else if(i<=79)
		{
			gotoxy(30,wherey()+1);
			cout<<T(i).name;
			if(i==79)gotoxy(50,4);
		}
		else if(i<=119)
		{
			gotoxy(50,wherey()+1);
			cout<<T(i).name;
		}
	}
	if(wherex()>=30)
		if(wherex()>=50)
			gotoxy(50,wherey()+1);
		else
			gotoxy(30,wherey()+1);
		else
			gotoxy(10,wherey()+1);
	cprintf("Back");
	mouse(m);
	if(m[1]/8>49)
		opt=((m[2]/8)+80-3);
	else if(m[1]/8>29)
		opt=((m[2]/8)+40-3);
	else
		opt=(m[2]/8)-3;

	if(opt<=teach_count)
	{
		clrscr();
		T(opt-1).modify();
		for(i=0;i<teach_count;i++)
			fout.write((char *)&T(i),sizeof(teacher));
		fout.close();
		strcpy(file,filename);
		strcat(file,".tch");
		remove(file);
		rename("temp",file);

	}
	else if(opt==teach_count+1)
		return;
  }
}
void copy_t()
{
  while(1)
   {
	read_teach(filename);
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
	strcat(file,".tch");
	fout.open(file,ios::app|ios::binary);
	if(teach_count==0)
	{
		gotoxy(10,4);
		cprintf("There are no Teacher(s) to display");
		gotoxy(10,4);}
	for(int i=0;i<teach_count;i++)
	{
		if(i<=39)
		{
			gotoxy(10,wherey()+1);
			cout<<T(i).name;
			if(i==39)gotoxy(30,4);
		}
		else if(i<=79)
		{
			gotoxy(30,wherey()+1);
			cout<<T(i).name;
			if(i==79)gotoxy(50,4);
		}
		else if(i<=119)
		{
			gotoxy(50,wherey()+1);
			cout<<T(i).name;
		}
	}
	if(wherex()>=30)
		if(wherex()>=50)
			gotoxy(50,wherey()+1);
		else
			gotoxy(30,wherey()+1);
		else
			gotoxy(10,wherey()+1);
	cprintf("Back");
	mouse(m);
	if(m[1]/8>49)
		opt=((m[2]/8)+80-3);
	else if(m[1]/8>29)
		opt=((m[2]/8)+40-3);
	else
		opt=(m[2]/8)-3;

	if(opt<=teach_count)
	{
		clrscr();
		gotoxy(10,2);
		cprintf("The teacher details are :: ");
		T(opt-1).display();
		teacher *T1=new teacher;
		*T1 = T(opt-1);
		gotoxy(10,wherey()+2);
		cprintf("Do you want to copy this teacher ?");
		gotoxy(30,wherey()+2);
		cprintf("Yes");
		gotoxy(50,wherey());
		cprintf("No");
		do
		{
			mouse(m);
			if(m[1]/8<49&&m[2]/8==wherey()-1)
			{
				gotoxy(30,wherey());
				cprintf("   ");
				gotoxy(50,wherey());
				cprintf("  ");
				gotoxy(10,wherey()-2);
				cprintf(" Enter the name of new teacher :: ");
				gets(T1->name);
				fout.write((char *)T1,sizeof(teacher));
				cout<<"\n\n\t\tTeacher "<<T1->name<<" has been copied ";
				mouse(p);
				break;
			}
		}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
		fout.close();
		delete T1;

	}
	else if(opt==teach_count+1)
		return;
   }
}

void teachers()
{
	int ch;
	clrscr();
	gotoxy(5,23);
	textcolor(4);
	cprintf("Enter the name of file containing teacher database :: ");
	gotoxy(5,27);
	cprintf("[Press \'Enter\' to  perform operations on Default File ]");
	gotoxy(60,23);
	gets(filename);
	if(!strcmpi(filename,"\0"))
	  strcpy(filename,"DEFAULT1");

	do
	{
		clrscr();
		gotoxy(36,14);
		textcolor(4);
		cprintf("TEACHERS");
		gotoxy(36,15);
		cprintf("ออออออออ");
		textcolor(10);
		gotoxy(30,18);
		cprintf("Add a new teacher");
		gotoxy(30,20);
		cprintf("View all teachers");
		gotoxy(30,22);
		cprintf("Modify an existing teacher");
		gotoxy(30,24);
		cprintf("Delete a teacher");
		gotoxy(30,26);
		cprintf("Copy a teacher");
		gotoxy(30,28);
		cprintf("Back");
		mouse(m);
		ch=(m[2]/16)-7;
		switch(ch)
		{
			case 1: add_t();
				break;
			case 2: view_t();
				break;
			case 3: modify_t();
				break;
			case 4: Delete_t();
				break;
			case 5: copy_t();
				break;
			case 6: break;
		}
	}while(ch!=6);
}