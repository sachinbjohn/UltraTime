#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<stdlib.h>
extern void change();
extern int PERIODS;
extern int DAYS;
extern int *m,*p;
extern void mouse(int *);

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
int class_count=0,teach_count=0;
Class   *c=NULL;
teacher  *t=NULL;

Class &C(int n)
 {
  Class *ptr=c;
  for(int i=0;i<n;i++)
    ptr=ptr->next;
  return *ptr;
 }
teacher &T(int n)
 {
  teacher *ptr=t;
  for(int i=0;i<n;i++)
   ptr=ptr->next;
  return *ptr;
}

void init_var()
{
	fstream f2("per.dat",ios::in|ios::binary);
	if(!f2)
	  {
	     clrscr();
	     gotoxy(5,16);
	     textcolor(RED);
	     cout<<"Please set the following ::\n"
		 <<"\n\t\tThe number of periods in a day\n"
		 <<" \n\t\tThe number of working days in a week....." ;
		 getch();
	     change();
	  }
	f2.seekg(0);
	f2>>PERIODS>>DAYS;
	f2.close();

}

void remove_var()
{

	for(int i=0;i<class_count;i++)
	   delete &C(i);
	for(i=0;i<teach_count;i++)
	delete &T(i);
}

void read_class(char  *f_name)
{
	for(int x=0;x<class_count;x++)
	  delete &C(x);
	char f_name2[15];
	strcpy(f_name2,f_name);
	strcat(f_name2,".cls");
	ifstream fin(f_name2,ios::in|ios::binary);
	int i=0;
	c=new Class;
	Class *prev=c;
	while(1)
	{

		fin.read((char *)&C(i),sizeof(Class));
		if(!fin||prev==NULL||i>120)
		 {
		  prev->next=NULL;
		  break;
		 }
		Class *newptr=new Class;
		prev->next=newptr;
		prev=newptr;
		i++;
	}
	fin.close();
	class_count=i;

}

void read_teach(char *f_name)
{
	for(int x=0;x<teach_count;x++)
	  delete &T(x);
	char f_name2[15];
	strcpy(f_name2,f_name);
	strcat(f_name2,".tch");
	ifstream fin(f_name2,ios::in|ios::binary);
	int i=0;
	t=new teacher;
	teacher *prev=t;
	while(1)
	{

		fin.read((char *)&T(i),sizeof(teacher));
		if(!fin||prev==NULL||i>120)
		 {
		  prev->next=NULL;
		  break;
		 }
	       teacher *newptr=new teacher;
		prev->next=newptr;
		prev=newptr;
		i++;
	}
	fin.close();
	teach_count=i;
}

void write_class(char *f_name)
{
	char f_name2[15];
	strcpy(f_name2,f_name);
	strcat(f_name2,".cls");
	ofstream fout(f_name2,ios::out|ios::binary);
	for(int i=0;i<class_count;i++)
		fout.write((char *)&C(i),sizeof(Class));
	fout.close();
}

void write_teach(char *f_name)
{
	char f_name2[15];
	strcpy(f_name2,f_name);
	strcat(f_name2,".tch");
	ofstream fout(f_name2,ios::out|ios::binary);
	for(int i=0;i<teach_count;i++)
		fout.write((char *)&T(i),sizeof(teacher));
	fout.close();
}
void assignment()
{
	int opt,ch;
	ofstream fout;
	do
	{
		clrscr();
		read_class("DEFAULT2");
		gotoxy(10,4);
		cprintf("Selected assignments will be deleted ... ");

		clrscr();
		if(class_count==0)
		{
		   gotoxy(10,4);
		   cprintf("No classes have been assigned !!!...        ");
		   read_teach("DEFAULT1");
		   write_teach("DEFAULT2");
		}
		gotoxy(32,2);
		textcolor(4);
		cprintf("OLD ASSIGNMENT");
		gotoxy(32,3);
		cprintf("ออออออออออออออ");
		textcolor(10);
		gotoxy(35,4);
		for(int i=0;i<class_count;i++)
		{
			gotoxy(20,wherey()+2);
			cout<<C(i).name;
		}
		gotoxy(20,wherey()+2);
		cprintf("Assign teachers to a new class");
		gotoxy(20,wherey()+2);
		cprintf("Back");
		mouse(m);
		opt=(m[2]-40)/16;
		clrscr();
		if(opt==class_count)
		  {
		     read_class("DEFAULT1");
		     do
		     {
			gotoxy(35,4);
			for(int i=0;i<class_count;i++)
			{
				gotoxy(20,wherey()+2);
				cout<<C(i).name;
			}
			gotoxy(20,wherey()+2);
			cprintf("Back");
			mouse(p);
			ch=(p[2]-40)/16;
			if(ch==class_count)
			   break;
			else if(ch>=0&&ch<class_count)
			  {
				clrscr();
				gotoxy(35,4);
				int verify=C(ch).assign(teach_count);
				if(verify!=0)
				   {
				     fout.open("DEFAULT2.cls",ios::app|ios::binary);
				     fout.write((char*)&C(ch),sizeof(Class));
				     write_teach("DEFAULT2");
				     fout.close();
				   }
			  }
		      }while(ch<0||ch>class_count);
		  }
		else if(opt>=0&&opt<class_count)
		   {
		     int verify=C(opt).assign(teach_count);
		     if(verify==1)
		       {
			 write_class("DEFAULT2");
			 write_teach("DEFAULT2");
		       }
		     if(verify==0)
		       {
			write_teach("DEFAULT2");
			fout.open("DEFAULT2.cls",ios::out|ios::binary);
			for(int i=0;i<class_count;i++)
			  {
			     cout<<" F ";
			     if(i!=opt)
			      { fout.write((char *)&C(i),sizeof(Class));
				cout<<"S";
			      }
			      getch();
			  }
		       }
		   }
	}while(opt!=class_count+1);




}
/*
void assignment()
{
	int opt;
	char ch;
	ifstream file1;
	ofstream file3;
    ass1:
	clrscr();
	read_class("DEFAULT2");
	read_teach("DEFAULT2");
	gotoxy(10,4);
	cprintf("Selected assignments will be deleted ... ");
	if(class_count==0)
	{
		gotoxy(10,4);
		cprintf("No classes have been assigned !!!...        ");
		read_teach("DEFAULT1");
		write_teach("DEFAULT2");
	}
	do
	{
		gotoxy(32,2);
		textcolor(4);
		cprintf("OLD ASSIGNMENT");
		gotoxy(32,3);
		cprintf("ออออออออออออออ");
		textcolor(10);
		gotoxy(35,4);
		for(int i=0;i<class_count;i++)
		{
			gotoxy(20,wherey()+2);
			cout<<C(i).name;
		}
		gotoxy(20,wherey()+2);
		cprintf("Proceed to New Assignment");
		mouse(m);
		opt=(m[2]-24)/16;
	}while(opt<1||opt>(class_count+1));
	if(opt<=class_count)
	{
		file3.open("temp",ios::out|ios::binary);
		for(int i=0;i<class_count;i++)
		{
			if(i!=opt-1)
				file3.write((char *)&C(i),sizeof(Class));
			else
			{
				clrscr();
				C(i).display();
				gotoxy(10,wherey()+5);
				cprintf("Do you  want to Delete This ? :: ");
				cin>>ch;
				if(ch!='y'&&ch!='Y')
					file3.write((char *)&C(i),sizeof(Class));
			}
		}
		file3.close();
		remove("DEFAULT2.cls");
		rename("temp","DEFAULT2.cls");
		int x,n;
		if(ch=='y'||ch=='Y')
		{
			for(i=0;i<C(opt-1).r_subno;i++)
			{
				x=C(opt-1).r_sub[i].t_no;
				n=C(opt-1).r_sub[i].assign_no;
				T(x).clear_assign(n);
			}
			for(i=0;i<C(opt-1).o_subno;i++)
			{
				for(int j=0;j<C(opt-1).o_sub[i].n;++j)
				{
					x=C(opt-1).o_sub[i].t_no[j];
					n=C(opt-1).o_sub[i].assign_no[j];
					T(x).clear_assign(n);
				}
			}
		}
	}
	if(opt!=class_count+1)
		goto ass1;
	ass2:
	clrscr();
	read_class("DEFAULT1");
	file3.open("DEFAULT2.cls",ios::app|ios::binary);
	gotoxy(10,24);
	cprintf("The following assignments will be appended ....");delay(1000);
	clrscr();
	do
	{
		gotoxy(32,2);
		textcolor(4);
		cprintf("NEW ASSIGNMENT");
		gotoxy(32,3);
		cprintf("ออออออออออออออ");
		textcolor(10);
		gotoxy(35,4);
		for(int i=0;i<class_count;i++)
		{
			gotoxy(20,wherey()+2);
			cout<<C(i).name;
		}
		gotoxy(20,wherey()+2);
		cprintf("Back");
		mouse(m);
		opt=(m[2]-24)/16;
	}while(opt<1||opt>(class_count+1));
	if(opt<=class_count)
	{
		clrscr();
		gotoxy(35,4);

		int verify=C(opt-1).assign(teach_count);
		if(verify!=0)
		  file3.write((char*)&C(opt-1),sizeof(Class));
		gotoxy(10,wherey()+2);
		cprintf("Do you want to Assign Teachers to another Class ? :: ");
		ch=getch();
		file3.close();
		if(ch=='y'||ch=='Y')
			goto ass2;
		else
			write_teach("DEFAULT2");
	}
	else
		if(opt!=class_count+1)
			goto ass2;
}
   */
void viewtime()
{
	int ch1=0,ch2;
	while(ch1!=3)
	{
		clrscr();
		gotoxy(35,18);
		textcolor(4);
		cprintf("TIME TABLE");
		gotoxy(35,19);
		cprintf("ออออออออออ");
		gotoxy(30,22);
		textcolor(10);
		cprintf("Class wise ");
		gotoxy(30,24);
		cprintf("Teacher wise ");
		gotoxy(30,26);
		cprintf("Back");
		mouse(m);
		ch1=(m[2]/16)-9;
		switch(ch1)
		{
			case 1: while(1)
				{
					clrscr();
					gotoxy(35,2);
					textcolor(4);
					cprintf("CLASS MENU");
					gotoxy(35,3);
					cprintf("อออออออออออ");
					textcolor(10);
					gotoxy(35,4);
					if(class_count==0)
					{
						gotoxy(10,4);
						cprintf("There  are no classes to display");
					}
					for(int i=0;i<class_count;i++)
					{
						gotoxy(20,wherey()+1);
						cout<<C(i).name;
					}
					gotoxy(20,wherey()+1);
					cprintf("Back");
					mouse(m);
					ch2=(m[2]/8)-3;
					if(ch2==class_count+1)
						break;
					else
					if(ch2>class_count+1||ch2<1)
						continue;
					C(ch2-1).disp_time();
					mouse(p);
				}
				break;
			case 2: while(1)
				{
					clrscr();
					gotoxy(35,2);
					textcolor(4);
					cprintf("TEACHER MENU");
					gotoxy(35,3);
					cprintf("ออออออออออออ");
					textcolor(10);
					gotoxy(10,4);
					if(teach_count==0)
					{
						gotoxy(10,4);
						cprintf("There  are no teachers to display");
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
				m[2]=0;mouse(m);
				if(m[1]/8>49)
					ch2=((m[2]/8)+80-3);
				else if(m[1]/8>29)
					ch2=((m[2]/8)+40-3);
				else
					ch2=(m[2]/8)-3;
					if(ch2==teach_count+1)
						break;
					else
					if(ch2>teach_count+1||ch2<1)
						continue;
					T(ch2-1).disp_time();
				}
				break;
		}
	}
}

void manual()
{

	clrscr();
	int opt;
	do
	{
		clrscr();
		gotoxy(35,2);
		textcolor(4);
		cprintf("MANUAL EDIT");
		gotoxy(35,3);
		cprintf("อออออออออออ");
		textcolor(10);
		gotoxy(35,4);
		if(class_count==0)
		{
			gotoxy(10,4);
			cprintf("There  are no classes to display");
		}
		for(int i=0;i<class_count;i++)
		{
			gotoxy(20,wherey()+2);
			cout<<C(i).name;
		}
		gotoxy(20,wherey()+2);
		cprintf("Next");
		gotoxy(20,wherey()+2);
		cprintf("Back");
		mouse(m);
		opt=(m[2]-24)/16;
		if(opt<=class_count)
		{
			C(opt-1).sp_make(opt-1);

		}
		else if(opt==class_count+1)
		{

			clrscr();
			gotoxy(20,20);
			char f_name[15];
			gotoxy(10,wherey()+4);
			cprintf("Do you want to save this time table ?");
			gotoxy(30,wherey()+2);
			cprintf("Yes");
			gotoxy(50,wherey());
			cprintf("No");
			do

			{
				p[1]=0;p[2]=0;mouse(p);
				if(p[1]/8<49&&p[2]/8==wherey()-1)
				{
				  gotoxy(25,wherey()+2);
				  cprintf("Enter File Name :: " );
				  gets(f_name);
				  write_class(f_name);
				  write_teach(f_name);
				  gotoxy(40,wherey()+2);
				  cprintf("SAVING COMPLETE ");
				  mouse(p);
				  break;
				}
			}while(!(p[1]/8>=49&&p[2]/8==wherey()-1));
			for(int j=1;j<=DAYS;j++)
				for(int i=1;i<=PERIODS;i++)
					for(int k=0;k<class_count;k++)
						C(k).make(i,j,k);
			cout<<"Generation of timetable complete";getch();
			viewtime();
			clrscr();
			gotoxy(20,20);
			gotoxy(10,wherey()+4);
			cprintf("Do you want to save this time table ?");
			gotoxy(30,wherey()+2);
			cprintf("Yes");
			gotoxy(50,wherey());
			cprintf("No");
			do
			{
				p[1]=0;p[2]=0;mouse(p);
				if(p[1]/8<49&&p[2]/8==wherey()-1)
				{
					  gotoxy(25,wherey()+2);
					  cprintf("Enter File Name :: " );
					  gets(f_name);
					  write_class(f_name);
					  write_teach(f_name);
					  gotoxy(40,wherey()+2);
					  cprintf("SAVING COMPLETE ");
					  mouse(p);
					  break;
				}
			}while(!(p[1]/8>=49&&p[2]/8==wherey()-1));

	       }
	}while(opt!=class_count+1&&opt!=class_count+2);

}



void load()
{
	int opt;
	do
	{
		clrscr();
		gotoxy(33,18);
		textcolor(4);
		cprintf("LOADED TIMETABLE");
		gotoxy(33,19);
		cprintf("ออออออออออออออออ");
		textcolor(10);
		gotoxy(30,22);
		cprintf("View");
		gotoxy(30,24);
		cprintf("Edit");
		gotoxy(30,26);
		cprintf("Back");
		mouse(m);
		opt=(m[2]/16)-9;
		switch(opt)
		{
			case 1:	viewtime();
				break;
			case 2:	manual();
				break;

		}
	}while(opt!=3);
}

void tt()
{
	randomize();
	int ch;
	do
	{
		clrscr();
		gotoxy(31,16);
		textcolor(4);
		cprintf("TIME TABLE CREATOR");
		gotoxy(31,17);
		cprintf("ออออออออออออออออออ");
		textcolor(10);
		gotoxy(20,20);
		cprintf("Assign teachers");
		gotoxy(20,22);
		cprintf("Make a new time table");
		gotoxy(20,24);
		cprintf("Load existing time table ");
		gotoxy(20,26);
		cprintf("Delete existing time table");
		gotoxy(20,28);
		cprintf("Back");
		mouse(m);
		ch=(m[2]/16)-8;
		switch(ch)
		{
			case 1:	ifstream fin("DEFAULT2.tch");
				if(!fin)
				{
					read_teach("DEFAULT1");
					write_teach("DEFAULT2");
				}
				fin.close();
				assignment();
				break;
			case 2:
				read_class("DEFAULT2");
				read_teach("DEFAULT2");
				manual();
				break;
			case 3:{
				char f_name[15];
				clrscr();
				gotoxy(20,25);
				cprintf("Enter the File Name :: ");
				gets(f_name);
				read_class(f_name);
				read_teach(f_name);
				load();
				break;
			       }
			case 4:{
				char f_name1[15],f_name2[15];
				clrscr();
				gotoxy(10,24);
				cprintf("Enter File Name to be Deleted :: ");
				char F_NAME[15];
				gets(F_NAME);
				strcpy(f_name1,F_NAME);
				strcpy(f_name2,f_name1);
				strcat(f_name2,".cls");
				strcat(f_name1,".tch");
				remove(f_name1);
				remove(f_name2);
				cout<<"\n\n\t\t"<<F_NAME<<"  deleted";
				delay(1000);
				break;
			       }
			case 5:	break;
		}
	}while(ch!=5);
}