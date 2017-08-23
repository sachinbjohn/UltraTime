/*
  ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
  บ    þþþ Software Created By þþþ                               บ
  บ		   ฏฏฏSachin Basil John                          บ
  บ		   ฏฏฏTom Glint Issac                            บ
  บ                ฏฏฏVishnu.P.S                                 บ
  ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<ctype.h>

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

extern Class &C(int n);
extern teacher &T(int n);


void Class::exchange(int t_no,int a,int b,int x,int c_no) //Function to exchange a teacher if a clash occurs in the allotment
{
	for(int i=1;i<=PERIODS;i++)
		for(int j=1;j<=DAYS;j++)
			for(int k=0;k<r_subno;++k)
			{
				int N1=r_sub[k].t_no;
				if(T(N1).time[a-1][b]==c_no)
					continue;
				if(islower(r_sub[k].ct))
				{
					if(T(t_no).time[i][j]==-1&&T(N1).time[a][b]==-1)
					{
						gotoxy(10,48);
						cout<<"Exchange with "<<T(N1).name<<" at "<<i<<" "<<j<<" [Press ENTER] ";
						getch();
						deallot(i,j);
						allot(a,b,k,c_no);
						allot(i,j,x,c_no);
						return;
					}
				}
			}
}

int overwrite(int c_no,int t_no,int a,int b)
{
	int x,y;
	char sub[10];
	x=C(c_no).time[a][b];
	if(x<100)
		strcpy(sub,C(c_no).r_sub[x].topic);
	else
	{
		y=x-100;
		strcpy(sub,C(c_no).o_sub[y].name);
	}
	cout<<"\n\nSorry! "<<T(t_no).name<<" is already assigned to "
		<<sub<<" in "<<C(c_no).name;
	cout<<"\nDo you want to overwrite ? :: ";
	char ch;
	ch=getch();
	if(ch!='y'&&ch!='Y')
	return 0;
	if(C(c_no).check_allot(a,b,c_no))
		C(c_no).deallot(a,b);
	else
		C(c_no).demark(a,b);
	C(c_no).time[a][b]=-1;
	return 1;
}

void Class::disp_time()
{
	char temp_time[10][7][10];
	int n,t_no,i,j;
	clrscr();
	gotoxy(35,2);cout<<name;
	for(i=1;i<10;i++)
	  for(j=1;j<7;j++)
	    strcpy(temp_time[i][j],"----");
	for(i=1;i<=PERIODS;i++)
	{
		for(j=1;j<=DAYS;j++)
		{
			strcpy(temp_time[i][j]," ");
			if(time[i][j]!=-1)
			{
				n=time[i][j];
				if(n<100)
				{
					t_no=r_sub[n].t_no;
					strcpy(temp_time[i][j],T(t_no).name);
				}
				else
				strcpy(temp_time[i][j],o_sub[n-100].name);

			}
		}
	}
	strcpy(temp_time[1][0],"1");
	strcpy(temp_time[2][0],"2");
	strcpy(temp_time[3][0],"3");
	strcpy(temp_time[4][0],"4");
	strcpy(temp_time[5][0],"5");
	strcpy(temp_time[6][0],"6");
	strcpy(temp_time[7][0],"7");
	strcpy(temp_time[8][0],"8");
	strcpy(temp_time[9][0],"9");
	strcpy(temp_time[0][0],"  ");
	strcpy(temp_time[0][1],"Monday");
	strcpy(temp_time[0][2],"Tuesday");
	strcpy(temp_time[0][3],"Wednesday");
	strcpy(temp_time[0][4],"Thursday");
	strcpy(temp_time[0][5],"Friday");
	strcpy(temp_time[0][6],"Saturday");
	textcolor(14);
	for(i=7;i<84;i+=11)
		for(j=6;j<46;j++)
		{
			gotoxy(i,j);
			cprintf("ณ");
		}
	for(i=5;i<74;i++)
		for(j=5;j<49;j+=4)
		{
			gotoxy(i,j);
			cprintf("ฤ");
		}
	textcolor(RED);
	for(j=1;j<7;j++)
	{
		gotoxy(11*j-3,7);
		cprintf(temp_time[0][j]);
	}
	for(i=1;i<10;i++)
	{
		textcolor(RED);
		gotoxy(5,7+4*i);
		cprintf(temp_time[i][0]);
		textcolor(10);
		for(j=1;j<7;j++)
		{
			gotoxy(11*j-3,7+4*i);
			cprintf(temp_time[i][j]);
		}
	}
	textcolor(10);
	gotoxy(10,48);
	cout<<"Right click to exit";
}

void Class::mark(int a,int b,int x,int k)
{
	time[a][b]=x;
	int N1,N2;
	if(x<100)
	{
		r_sub[x].ct=toupper(r_sub[x].ct);
		N1=r_sub[x].t_no;
		N2=r_sub[x].assign_no;
		T(N1).a[N2].alloted_per++;
		T(N1).time[a][b]=k+1000;
	}
	else
	{
		int y=x-100;
		o_sub[y].ct=toupper(o_sub[y].ct);
		for(int i=0;i<o_sub[y].n;i++)
		{
			N1=o_sub[y].t_no[i];
			N2=o_sub[y].assign_no[i];
			T(N1).a[N2].alloted_per++;
			T(N1).time[a][b]=k+1000;
		}
	}
	periods_left--;
}

void Class::demark(int a,int b)
{
	int x=time[a][b];
	int N1,N2;
	if(x<100)
	{
		N1=r_sub[x].t_no;
		N2=r_sub[x].assign_no;
		T(N1).a[N2].alloted_per--;
		T(N1).time[a][b]=-1;
	}
	else
	{
		int y=x-100;
		for(int i=0;i<o_sub[y].n;i++)
		{
			N1=o_sub[y].t_no[i];
			N2=o_sub[y].assign_no[i];
			T(N1).a[N2].alloted_per--;
			T(N1).time[a][b]=-1;
		}
	}
	time[a][b]=-1;
	periods_left++;
}

void Class::allot(int a,int b,int x,int k)
{
	int N1,N2;
	if(x<100)
	{
		N1=r_sub[x].t_no;
		N2=r_sub[x].assign_no;
		T(N1).tot_allot++;
		T(N1).time[a][b]=k;
		T(N1).a[N2].alloted_per++;
		if(a>((PERIODS+1)/2))
			T(N1).a[N2].n_alloted_per++;
		else
			T(N1).a[N2].m_alloted_per++;
	}
	else
	{
		int y=x-100;
		for(int i=0;i<o_sub[y].n;i++)
		{
			N1=o_sub[y].t_no[i];
			N2=o_sub[y].assign_no[i];
			T(N1).tot_allot++;
			T(N1).time[a][b]=k;
			T(N1).a[N2].alloted_per++;
			if(a>(PERIODS/2))
				T(N1).a[N2].n_alloted_per++;
			else
				T(N1).a[N2].m_alloted_per++;
		}
	}
	periods_left--;
	time[a][b]=x;
}

void Class::deallot(int a,int b)
{
	int x=time[a][b];
	int N1,N2;
	if(x<100)
	{
		N1=r_sub[x].t_no;
		N2=r_sub[x].assign_no;
		T(N1).tot_allot--;
		T(N1).time[a][b]=-1;
		T(N1).a[N2].alloted_per--;
		if(a>((PERIODS+1)/2))
			T(N1).a[N2].n_alloted_per--;
		else
			T(N1).a[N2].m_alloted_per--;
	}
	else
	{
		int y=x-100;
		for(int j=0;j<o_sub[y].n;j++)
		{
			N1=o_sub[y].t_no[j];
			N2=o_sub[y].assign_no[j];
			T(N1).tot_allot--;
			T(N1).time[a][b]=-1;
			T(N1).a[N2].alloted_per--;
			if(a>((PERIODS+1)/2))
				T(N1).a[N2].n_alloted_per--;
			else
				T(N1).a[N2].m_alloted_per--;
		}
	}
	periods_left++;
	time[a][b]=-1;
}

int Class::check_allot(int a,int b,int k)
{
	int N1;
	int x=time[a][b];
	if(x<100)
		N1=r_sub[x].t_no;
	else
	{
		int y=x-100;
		N1=o_sub[y].t_no[0];
	}
	if(T(N1).time[a][b]==k)
		return 1;
	else
		return 0;
}

void Class::sp_make(int k)
{

  while(1)
   {
	clrscr();
	char ch;
	disp_time();
	int *m=NULL;
	int a,b,N1,x;
	mouse(m);
	if(m[0]==1)
	{ return;}
	a=(m[2]-32)/32;
	b=(m[1]+32)/88;
	cout<<a<<" "<<b;
	if(a*b==0||a>PERIODS||b>DAYS)
	{
	  continue;
	}
	if(time[a][b]==-1)
	{
		int ch;
		while(1)
		{
			clrscr();
			gotoxy(20,2);cprintf("Regular Subject(s)");
			for(int i=0;i<r_subno;i++)
			{
				gotoxy(23,wherey()+2);
				cout<<i+1<<". "<<r_sub[i].topic;
			}
			gotoxy(20,wherey()+2);
			cprintf("Optional Subject(s)");
			for(i=0;i<o_subno;i++)
			{
				gotoxy(23,wherey()+2);
				cout<<i+1<<". "<<o_sub[i].name;
			}
			mouse(p);
			ch=(p[2]/16)-1;
			if(ch>r_subno)
				ch=100+((p[2]/16)-(r_subno+2));
			if(ch>=0&&ch<=r_subno||ch>=100&&ch<=(100+o_subno));
			{	x=ch;
				break;
			}
		}
		if(x<100)
		{
			N1=r_sub[x].t_no;

			if(T(N1).time[a][b]!=-1)
			{
				int c_no=T(N1).time[a][b];
				if(c_no>=1000)
					c_no-=1000;
				if(c_no==k)
				{
				  continue;
				}
				if(!overwrite(c_no,N1,a,b))
				{
				  continue;
				}
			}
		}
		else
		{
			int y=x-100;
			for(int i=0;i<o_sub[y].n;i++)
			{
				N1=o_sub[y].t_no[i];

				if(T(N1).time[a][b]!=-1)
				{
					int c_no=T(N1).time[a][b];
					if(c_no>=1000)
						c_no-=1000;
					if(c_no==k)
					{
					  continue;
					}
					if(!overwrite(c_no,N1,a,b))
					{
						continue;
					}
				}
			}
		}
		time[a][b]=x;
		mark(a,b,x,k);
	}
	else
	{
		if(check_allot(a,b,k))
			deallot(a,b);
		else
			demark(a,b);
	}
  }
}

/*void Class::edit(int k)
{
	clrscr();

	char ch;
	disp_time();
	int *m=NULL;
	int a,b,N1,x;
	mouse(m);
	if(m[0]==1)
	{
		return;
	}
	a=(m[2]-48)/16;
	b=(m[1]+64)/112;
	cout<<a<<" "<<b;
	if(a*b==0)
	{
		sp_make(k);
		return;
	}
	if(time[a][b]==-1)
	{
		int ch;
		while(1)
		{
			clrscr();
			gotoxy(20,2);cprintf("Regular Subject(s)");
			for(int i=0;i<r_subno;i++)
			{
				gotoxy(23,wherey()+2);
				cout<<i+1<<". "<<r_sub[i].topic;
			}
			gotoxy(20,wherey()+2);
			cprintf("Optional Subject(s)");
			for(i=0;i<o_subno;i++)
			{
				gotoxy(23,wherey()+2);
				cout<<i+1<<". "<<o_sub[i].name;
			}
			mouse(p);
			ch=(p[2]/16)-1;
			if(ch>r_subno)
				ch=100+((p[2]/16)-(r_subno+2));
			if(ch>=0&&ch<=r_subno||ch>=100&&ch<=(100+o_subno));
			{	x=ch;
				break;
			}
		}
		if(x<100)
		{
			N1=r_sub[x].t_no;
			if(T(N1).time[a][b]!=-1)
			{
				int c_no=T(N1).time[a][b];
				cout<<"\n\nSorry! "<<T(N1).name<<"is already assigned to "<<C(c_no).name;
				cout<<"\nDo you want to overwrite ? ";
				char ch;
				cin>>ch;
				if(ch=='Y'||ch=='y')
					C(c_no).deallot(a,b);
				else
				{
					sp_make(k);
					return;
				}
			}
		}
		else
		{
			int y=x-100;
			for(int i=0;i<o_sub[y].n;i++)
			{
				N1=o_sub[y].t_no[i];
				if(T(N1).time[a][b]!=-1)
				{
					int c_no=T(N1).time[a][b];
					cout<<"\n\nSorry! "<<T(N1).name<<" is assigned to "<<C(c_no).name;
					cout<<"\nDo you want to overwrite ? :: ";
					char ch;
					cin>>ch;
					if(ch=='y'||ch=='Y')
						C(c_no).deallot(a,b);
					else
					{
						sp_make(k);
						return;
					}
				}
			}
		}
		allot(a,b,x,k);
	}
	else
		deallot(a,b);
	sp_make(k);
}
----------------------------------------------------------------------------
void Class::modify()
{
	gotoxy(10,wherey()+2);
	cprintf("Class Name :: ");
	cout<<name;
	gotoxy(15,wherey()+2);
	cprintf("Regular Subjects\n");
	for(int i=0;i<r_subno;i++)
	{
		gotoxy(20,wherey()+1);
		cout<<i+1<<". "<<r_sub[i].topic;
	}
	gotoxy(15,wherey()+2);
	cprintf("Optional subjects\n");
	for(i=0;i<o_subno;i++)
	{
		gotoxy(20,wherey()+1);
		cout<<i+1<<". "<<o_sub[i].name;
		for(int j=0;j<o_sub[i].n;j++)
		{
			gotoxy(25,wherey()+1);
			cout<<j+1<<". "<<o_sub[i].topic[j];
		}
	}
	char n_name[10],n_rsub[20][10],n_osub_name[10],n_osub_topic[15][10],confirm;
	gotoxy(10,wherey()+2);
	cprintf("Do you want to Modify?");
	cprintf("\r\n\r\n");
	gotoxy(30,wherey());
	cprintf("Yes");
	gotoxy(50,wherey());
	cprintf("No");
	do
	{       mouse(m);
		if(m[1]/8<49&&m[2]/8==wherey()-1)
		{
			gotoxy(30,wherey());
			cout<<"    ";
			gotoxy(50,wherey());
			cout<<"   ";
			gotoxy(10,wherey()-2);
			cprintf("      New Name [. for old one] :: ");
			gets(n_name);
			if(strcmpi(n_name,"."))
				strcpy(name,n_name);
			gotoxy(15,wherey()+1);
			clrscr();
			cout<<"\n\n";
			cprintf("New Subjects [. for old one, 'enter' to terminate ]\r\n");
			for(i=0;i<20;i++)
			{
				gotoxy(20,wherey()+1);
				cout<<i+1<<". ";
				gets(n_rsub[i]);
				if(!strcmpi(n_rsub[i],"\0"))
					break;
				else if(strcmpi(n_rsub[i],"."))
					strcpy(r_sub[i].topic,n_rsub[i]);
			}
			r_subno=i;
			clrscr();
			gotoxy(50,4);
			cprintf("Optional Subjects");
			for(i=0;i<o_subno;i++)
			{
				gotoxy(52,wherey()+1);
				cout<<i+1<<". "<<o_sub[i].name;
				for(int j=0;j<o_sub[i].n;j++)
				{
					gotoxy(54,wherey()+1);
					cout<<j+1<<". "<<o_sub[i].topic[j];
				}
			}
			gotoxy(10,4);
			cprintf("New Optional Subjects\r\n");
			for(i=0;i<10;i++)
			{
				gotoxy(13,wherey()+1);
				cout<<i+1<<". ";
				gets(n_osub_name);
				if(!strcmpi(n_osub_name,"\0"))
					break;
				else if(strcmpi(n_osub_name,"."))
					strcpy(o_sub[i].name,n_osub_name);
				gotoxy(18,wherey()+1);cprintf("Enter subjects\r\n");
				for(int j=0;j<15;j++)
				{
					gotoxy(20,wherey()+1);
					cout<<j+1<<". ";
					gets(n_osub_topic[j]);
					if(!strcmpi(n_osub_topic[j],"\0"))
						break;
					else if(strcmpi(n_osub_topic[j],"."))
						strcpy(o_sub[i].topic[j],n_osub_topic[j]);
				}
				o_sub[i].n=j;
			}
			o_subno=i;
			gotoxy(10,wherey()+2);
			cout<<"Class "<<name<<" Modified";
			mouse(p);
			if(m[0]==0)
				break;
		}
	}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
}
*/
void Class::modify()
{
	int ch;
	do
	{
		clrscr();
		gotoxy(20,wherey()+2);
		cprintf("Name :: ");
		cprintf(name);
		gotoxy(15,wherey()+2);
		textcolor(RED);
		cprintf("Regular Subject(s)");
		textcolor(10);
		for(int i=0;i<r_subno;i++)
		{
			gotoxy(23,wherey()+2);
			cout<<i+1<<". "<<r_sub[i].topic;
		}
		gotoxy(20,wherey()+2);
		cout<<"Add a new subject";
		gotoxy(15,wherey()+2);
		cout<<"View Optional Subjects";
		gotoxy(15,wherey()+2);
		cout<<"Back";
		mouse(p);
		ch=(p[2]/16);
		if(ch-3==r_subno+2)
		   return;
		if(ch==1)
		{
			gotoxy(27,ch*2+1);
			cout<<"                                   ";
			gotoxy(27,ch*2+1);
			cin>>name;
		}
		else
		{
		  if(ch!=2&&ch-3<r_subno)
		    {
		      if(p[0]==0)
			{
			 gotoxy(26,ch*2+1);
			 cout<<"                                             ";
			 gotoxy(26,ch*2+1);
			 gets(r_sub[ch-3].topic);
			}
		      else
		       {
			 for(i=ch-3;i<r_subno;i++)
			    r_sub[i]=r_sub[i+1];
			 r_subno--;
		       }
		   }
		  else if(ch-3==r_subno)
		    {
		      if(r_subno==19)
		       {
				clrscr();
				gotoxy(25,20);
				cout<<"\nSubject limit exceeded ";
				getch();
				continue;
		       }
		      gotoxy(20,ch*2+1);
		      cout<<"                                             ";
		      gotoxy(23,ch*2+1);
		      cout<<i+1<<". ";
		      gets(r_sub[ch-3].topic);
		      r_subno++;
		     }
	       }
	}while(ch!=r_subno+4);
	while(1)
	{
		clrscr();
		gotoxy(20,2);
		textcolor(RED);
		cprintf("Optional Subject(s)");
		textcolor(10);
		for(int i=0;i<o_subno;i++)
		{
			gotoxy(23,wherey()+2);
			cout<<i+1<<". "<<o_sub[i].name;
			for(int j=0;j<o_sub[i].n;j++)
			   {
			     gotoxy(25,wherey()+1);
			     cout<<j+1<<". "<<o_sub[i].topic[j];
			   }
			gotoxy(25,wherey()+1);
			cout<<"Add new subject";
		}
		gotoxy(23,wherey()+2);
		cout<<"Add new subject";
		gotoxy(23,wherey()+2);
		cout<<"Quit";
		mouse(p);
		int j,sum=0;
		ch=p[2]/8-2;
		for(i=0;i<o_subno;i++)
		 {
		   if(sum+o_sub[i].n+3<ch)
		      sum+=o_sub[i].n+3;
		   else
		     { j=ch-sum-2;
		       break;
		     }

		 }
		 if(i==o_subno)
		 {
		     if(sum+1==ch)
		      {
			  if(o_subno==10)
			  {
			     clrscr();
			     gotoxy(25,20);
			     cout<<"\nSubject limit exceeded ";
			     getch();
			     continue;
			  }
			  clrscr();
			  gotoxy(15,2);
			  cout<<"Enter name :: ";
			  gets(o_sub[i].name);
			  gotoxy(15,wherey()+2);
			  cprintf("Enter the subjects :: ");
			  for(int j=0;j<15;j++)
			  {
				gotoxy(20,wherey()+1);
				cout<<j+1<<". ";
				gets(o_sub[i].topic[j]);
				if(!strcmpi(o_sub[i].topic[j],"\0"))
				break;
			  }
			  o_sub[i].n=j;
			  o_subno++;
		      }
		     else if(sum+3==ch)
			   return;
		 }
		 else
		 {
		     if(j==o_sub[i].n)
		     {
			  if(o_sub[i].n==15)
			   {
			     clrscr();
			     gotoxy(25,20);
			     cout<<"\nSubject limit exceeded";
			     getch();
			     continue;
			   }
			  gotoxy(24,ch+3);
			  cout<<"                                       ";
			  gotoxy(24,ch+3);
			  cout<<j+1<<". ";
			  gets(o_sub[i].topic[j]);
			  o_sub[i].n++;
		     }
		     else if(j==-1)
		     {
			  if(p[0]==0)
			      {
				  gotoxy(26,ch+3);
				  cout<<"                                       ";
				  gotoxy(26,ch+3);
				  gets(o_sub[i].name);
			      }
			  else
			      {
				  for(int x=i;x<o_subno;x++)
				     o_sub[x]=o_sub[x+1];
				  o_subno--;
			      }
		     }
		     else if(j<o_sub[i].n)
		     {
			if(p[0]==0)
			{
				gotoxy(28,ch+3);
				cout<<"                                       ";
				gotoxy(28,ch+3);
				gets(o_sub[i].topic[j]);
			}
			else
			{
				for(int x=j;x<o_sub[i].n;x++)
				      strcpy(o_sub[i].topic[x],o_sub[i].topic[x+1]);
				o_sub[i].n--;
			}
		     }
		}
	}

		       /*	if(ch<r_subno)
			{

			//----------
			if(ch>r_subno)
				ch=100+((p[2]/16)-(r_subno+2));
			if(ch>=0&&ch<=r_subno||ch>=100&&ch<=(100+o_subno));
			{	x=ch;
				break;
			}*/
}
Class::Class()
{
	periods_left=DAYS*PERIODS;
	next=NULL;
	for(int i=0;i<10;i++)
		for(int j=0;j<7;j++)
			time[i][j]=-1;
	for(i=0;i<20;i++)
	{
		r_sub[i].t_no=-1;
		r_sub[i].assign_no=-1;
		r_sub[i].prior=0;
		r_sub[i].ct='n';
		strcpy(r_sub[i].topic," ");
	}
	for(i=0;i<10;i++)
	{
		for(int j=0;j<15;j++)
		{
			o_sub[i].t_no[j]=-1;
			o_sub[i].assign_no[j]=-1;
			strcpy(o_sub[i].topic[j]," ");

		}
		o_sub[i].n=0;
		o_sub[i].ct='n';
		o_sub[i].prior=0;
		o_sub[i].no_of_period=-1;
		strcpy(o_sub[i].name," ");

	}
}

int Class::max_prior(int a,int b)
{
	int N1,N2,pos=-1;
	float max=-1;
	for(int i=0;i<r_subno;i++)
	{
		N1=r_sub[i].t_no;
		N2=r_sub[i].assign_no;
		char ct=r_sub[i].ct;
		r_sub[i].prior=T(N1).prior_cal(N2,periods_left,a,b,i,ct);
		if(r_sub[i].prior>max)
		{
			if(T(N1).time[a][b]==-1)
			{
				max=r_sub[i].prior;
				pos=i;
			}
		}
	}
	int check;
	for(i=0;i<o_subno;i++)
	{
		check=0;
		o_sub[i].prior=0;
		for(int j=0;j<o_sub[i].n;j++)
		{
			N1=o_sub[i].t_no[j];
			N2=o_sub[i].assign_no[j];
			o_sub[i].prior+=T(N1).prior_cal(N2,periods_left,a,b,i,'n');
			check+=T(N1).time[a][b];
		}
		if(o_sub[i].n!=0)
			o_sub[i].prior/=o_sub[i].n;

		if((o_sub[i].prior>max)&&(check==-o_sub[i].n))
		{
			max=o_sub[i].prior;
			pos=100+i;
		}
	}
	if(max==0)
		return -1;
	else
		return pos;
}

int Class::max_prior2(int a,int b)
{
	int N1,N2,pos=-1;
	float max=-1;
	for(int i=0;i<r_subno;i++)
	{
		N1=r_sub[i].t_no;
	       N2=r_sub[i].assign_no;
		char ct=r_sub[i].ct;
		r_sub[i].prior=T(N1).prior_cal(N2,periods_left,a,b,i,ct);
		if(r_sub[i].prior>max)
		{
			max=r_sub[i].prior;
			pos=i;
		}
	}
	for(i=0;i<o_subno;i++)
	{

		o_sub[i].prior=0;
		for(int j=0;j<o_sub[i].n;j++)
		{
			N1=o_sub[i].t_no[j];
		       N2=o_sub[i].assign_no[j];
			o_sub[i].prior+=T(N1).prior_cal(N2,periods_left,a,b,i,'n');
		}
		if(o_sub[i].n!=0)
			o_sub[i].prior/=o_sub[i].n;
		if((o_sub[i].prior>max))
		{
			max=o_sub[i].prior;
			pos=100+i;
		}
	}
	return pos;
}

void Class::make(int a,int b,int k)
{
	int x;
	if(time[a][b]!=-1)
	{
		if(check_allot(a,b,k))
			return;
		else
		{
			x=time[a][b];
			demark(a,b);
			allot(a,b,x,k);
			return;
		}
	}
	x=max_prior(a,b);
	if(x==-1)
	{
		gotoxy(10,48);
		cout<<"\n\nSorry cannot allot for this period [Press ENTER] ";
		getch();
		disp_time();
		x=max_prior2(a,b);
		int N1;
		if(x<100)
		{
			N1=r_sub[x].t_no;
			exchange(N1,a,b,x,k);
			disp_time();
		}
		return;
	}
	allot(a,b,x,k);

}

int Class::assign(int teach_count)
{
    int total=0,count,temp[120],opt,ch,n;
    int clear_to_go=0;
    while(1)
    {
	clrscr();
	gotoxy(20,wherey()+2);
	cprintf("Name :: ");
	cprintf(name);
	gotoxy(15,wherey()+2);
	textcolor(RED);
	cprintf("Regular Subject(s)");
	textcolor(10);
	for(int i=0;i<r_subno;i++)
	{
		gotoxy(23,wherey()+2);
		cout<<i+1<<". "<<r_sub[i].topic;
		int t_no=r_sub[i].t_no;
		int assign_no=r_sub[i].assign_no;
		if(t_no!=-1)
		{
		    gotoxy(40,wherey());
		    cout<<T(t_no).name;
		    gotoxy(55,wherey());
		    cout<<T(t_no).a[assign_no].no_of_period;
		}
	}
	gotoxy(15,wherey()+2);
	cout<<"View Optional Subjects";
	gotoxy(15,wherey()+2);
	cout<<"Cancel all assignments";
	gotoxy(15,wherey()+2);
	cout<<"Finish";
	mouse(m);
	ch=(m[2]/16)-3;
	if(ch==r_subno+1)
	 {
	   int t_no,assign_no;
	   for(i=0;i<r_subno;i++)
	    {
		t_no=r_sub[i].t_no;
		assign_no=r_sub[i].assign_no;
		T(t_no).clear_assign(assign_no);
		r_sub[i].t_no=r_sub[i].assign_no=-1;
	    }
	    for(i=0;i<o_subno;i++)
	    {
		for(int j=0;j<o_sub[i].n;++j)
		{
			t_no=o_sub[i].t_no[j];
			assign_no=o_sub[i].assign_no[j];
			T(t_no).clear_assign(assign_no);
			o_sub[i].t_no[j]=o_sub[i].assign_no[j]=-1;
		 }
	    }
	  return 0;
	 }
	else if(ch==r_subno+2)
	{
	   if(clear_to_go==-1)
	      {
		clrscr();
		gotoxy(20,25);
		cout<<"Sorry ! Total number of period assigned is "<<total;
		gotoxy(20,wherey()+3);
		cout<<"It should be "<<DAYS*PERIODS;
		mouse(p);
	      }
	   if(clear_to_go==0)
	     {
		clrscr();
		gotoxy(10,25);
		cout<<"Sorry ! Not all subjects have not been assigned teachers !!!!!!!";
		mouse(p);
	     }
	   if(clear_to_go==1)
	     return 1;
	}
	else if(ch>=0&&ch<r_subno)
	 {
	    if(r_sub[ch].assign_no!=-1)
		{
			int x=r_sub[ch].t_no;
			T(x).clear_assign(r_sub[ch].assign_no);
			r_sub[ch].t_no=r_sub[ch].assign_no=-1;

		}
	      clrscr();
	      gotoxy(25,20);
	      cout<<"Choose a teacher..........";
	      delay(1000);
	      count=0;
	      clrscr();
	      for(int j=0;j<teach_count;j++)
		 {
		      if(T(j).search(name,r_sub[ch].topic)==2)
			{
				temp[count]=j;
				count++;
			}
		 }
	      if(count==0)
		{
		   textcolor(RED);
		   cout<<"\n\n";
		   cprintf("\r\n\n No teachers are available ");
		   cprintf("\r\n\n Please restart assignment process after checking teacher database\n");
		   cprintf("\r\n\n Exiting  now.......");
		   delay(1000);
		   break;
		}
	      else
	       {
		 do
		 {
			gotoxy(20,1);
			textcolor(RED);
			cprintf("LIST OF TEACHERS");
			gotoxy(20,2);
			cprintf("ออออออออออออออออ\n");

			for(int x=0;x<count;x++)
			{
			   int t_no=temp[x];
			   if(x<=39)
			    {
				gotoxy(10,wherey()+1);
				cout<<T(t_no).name;
				if(x==39)
				   gotoxy(30,4);
			    }
			   else if(x<=79)
			    {
				gotoxy(30,wherey()+1);
				cout<<T(t_no).name;
				if(x==79)
				   gotoxy(50,4);
			    }
			   else if(x<=119)
			    {
				gotoxy(50,wherey()+1);
				cout<<T(t_no).name;
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
			textcolor(10);
			p[2]=0;mouse(p);
			if(p[1]/8>49)
			   opt=((p[2]/8)+80-3);
			else if(p[1]/8>29)
			   opt=((p[2]/8)+40-3);
			else
			   opt=(p[2]/8)-3;
			if(opt==count)
			    break;
			if(opt<count)
			 {
			   if(opt<0)
				continue;
			   else
			    {
				gotoxy(20,50);
				cout<<"Enter the number of periods :: ";
				cin>>n;
			    }
			     int addr=temp[opt];
			     r_sub[ch].t_no=addr;
			     r_sub[ch].assign_no=T(addr).no_of_assignment;
			     T(addr).assign(name,r_sub[ch].topic,n);
			 }
		  }while(opt<0||opt>count);
	       }
	 }
	else if(ch==r_subno)
	 {

	    do
	    {
		clrscr();
		gotoxy(20,2);
		textcolor(RED);
		cprintf("Optional Subject(s)");
		textcolor(10);
		for(int i=0;i<o_subno;i++)
		{
			gotoxy(23,wherey()+2);
			cout<<i+1<<". "<<o_sub[i].name;
			gotoxy(40,wherey());
			if(o_sub[i].no_of_period==-1)
			    cout<<"No of periods not assigned";
			else
			    cout<<"       "<<o_sub[i].no_of_period;

			for(int j=0;j<o_sub[i].n;j++)
			   {
			     gotoxy(25,wherey()+1);
			     cout<<j+1<<". "<<o_sub[i].topic[j];
			     if(o_sub[i].assign_no[j]!=-1)
			       {
				  int t_no=o_sub[i].t_no[j];
				  gotoxy(40,wherey());
				  cout<<T(t_no).name;
			       }
			   }
		}
		gotoxy(23,wherey()+2);
		cout<<"Return to regular subjects";
		mouse(p);
		int j,sum=0;
		ch=p[2]/8-2;
		for(i=0;i<o_subno;i++)
		 {
		   if(sum+o_sub[i].n+2<ch)
		      sum+=o_sub[i].n+2;
		   else
		     { j=ch-sum-2;
		       break;
		     }

		 }
		 if(i==o_subno&&ch==sum+1)    break;///////////////
		 if(i>=0&&i<o_subno)
		 {
		     if(j==-1)
		       {
			   gotoxy(20,50);
			   cout<<"Enter the number of periods :: ";
			   cin>>o_sub[i].no_of_period;
			   if(o_sub[i].assign_no[j]!=-1)
				    {
					int x=o_sub[i].t_no[j];
					T(x).clear_assign(o_sub[i].assign_no[j]);
					o_sub[i].assign_no[j]=T(x).no_of_assignment;
					T(x).assign(name,o_sub[i].topic[j],o_sub[i].no_of_period);

				    }


		       }
		     if(j>=0&&j<o_sub[i].n)
		       {
			    if(o_sub[i].no_of_period==-1)
				{
				  gotoxy(20,50);
				  cout<<"Assign no. of periods first !";
				  getch();
				  continue;
				}

				  if(o_sub[i].assign_no[j]!=-1)
				    {
					int x=o_sub[i].t_no[j];
					T(x).clear_assign(o_sub[i].assign_no[j]);
					o_sub[i].t_no[j]=o_sub[i].assign_no[j]=-1;
				    }

			     count=0;
			     for(int k=0;k<teach_count;k++)
				if(T(k).search(name,o_sub[i].topic[j])==2)
				{
					temp[count]=k;
					count++;
				}
			     clrscr();
			     gotoxy(25,20);
			     cout<<"Choose a teacher..........";
			     delay(1000);
			     clrscr();
			     if(count==0)
			     {
				textcolor(RED);
				cout<<"\n\n";
				cprintf("\r\n\n No teachers are available ");
				cprintf("\r\n\n Please restart assignment process after checking teacher database\n");
				cprintf("\r\n\n Exiting  now.......");
				delay(1000);
				break;
			     }
			     else
			     {
			       int opt2;
				do
				{
					gotoxy(20,1);
					textcolor(RED);
					cprintf("LIST OF TEACHERS");
					gotoxy(20,2);
					cprintf("ออออออออออออออออ");
					for(int x=0;x<count;x++)
					{
						int t_no=temp[x];
						gotoxy(25,wherey()+2);
						cout<<T(t_no).name;
					}
					gotoxy(25,wherey()+2);
					cprintf("Back");
					mouse(p);
					opt2=(p[2]+8)/16-2;
					if(opt2==count)
					   break;
					if(opt2<count&&opt2>=0)
					{
						int addr=temp[opt2];
						o_sub[i].t_no[j]=addr;
						o_sub[i].assign_no[j]=T(addr).no_of_assignment;
						T(addr).assign(name,o_sub[i].topic[j],o_sub[i].no_of_period);
					}
				  }while(opt2<0||opt2>count);
			     }
			}


		 }//


	   }while(i!=o_subno);

	 } ///
	 total=0;
	 int t_no,assign_no,check=0,tot_check=0;
	 for(int a=0;a<r_subno;a++,tot_check++)
	   {
	     t_no=r_sub[a].t_no;
	     assign_no=r_sub[a].assign_no;
	     if(assign_no!=-1)
		check++;
	     total+=T(t_no).a[assign_no].no_of_period;
	   }
	 for(a=0;a<o_subno;a++)
	   {
	     total+=o_sub[a].no_of_period ;
	     for(int b=0;b<o_sub[a].n;b++,tot_check++)
	      {
		if(o_sub[a].assign_no[b]!=-1)
		  check++;
	      }
	   }
	 if(total!=DAYS*PERIODS)
	    clear_to_go=-1;
	 if(check!=tot_check)
	    clear_to_go=0;
	 if(total==DAYS*PERIODS && check==tot_check)
	    clear_to_go=1;
    }

}

/*int Class::assign(int teach_count)
{
	int total=0,count,temp[100],opt,n;
	for(int i=0;i<r_subno;i++)
	{
		if(r_sub[i].assign_no!=-1)
		{
			int x=r_sub[i].t_no;
			T(x).clear_assign(r_sub[i].assign_no);
		}
		clrscr();
		count=1;
		cout<<"\n\n     "<<r_sub[i].topic<<" ::\n";
		for(int j=0;j<teach_count;j++)
		     if(T(j).search(name,r_sub[i].topic)==2)
			{
				cout<<"\n               "<<count<<". "<<T(j).name;
				temp[count]=j;
				count++;
				if(count%10==0)
				  {
				    cout<<"\Press Enter to continue.....";
				    getch();
				    clrscr();
				  }
			}
		     if(count==1)
			{
			   textcolor(RED);
			   cout<<"\n\n";
			   cprintf("\r\n\n No teachers are available ");
			   cprintf("\r\n\n Please restart assignment process after checking teacher database\n");
			   cprintf("\r\n Exiting assignment now.........");
			   cprintf("\r\n\n Press any key to continue....\n\n\n");
			   textcolor(10);
			   return 0;
			}
		cout<<"\n\n          ";cprintf("Enter your option :: ");
		cin>>opt;
		if(opt<count)
		{
			cout<<"\n\n          ";cprintf("Enter the No. of period(s) :: ");
			cin>>n;
			total+=n;
			int addr=temp[opt];
			cout<<"\n\t\t"<<T(addr).name<<" assigned\n";
			r_sub[i].t_no=addr;
			r_sub[i].assign_no=T(addr).no_of_assignment;
			T(addr).assign(name,r_sub[i].topic,n);
		}
		else
		{
			cprintf("   Wrong Entry. Try again !!!..");
			total-=n;
			i--;
		}
	}
	for(i=0;i<o_subno;i++)
	{
		cout<<"\n\n     "<<o_sub[i].name<<" ::";
		cout<<"\n\n          ";cprintf("Enter the No. of periods :: ");
		cin>>n;
		total+=n;
		for(int k=0;k<o_sub[i].n;k++)
		{
			if(o_sub[i].assign_no[k]!=-1)
			{
				int x=o_sub[i].t_no[k];
				T(x).clear_assign(o_sub[i].assign_no[k]);
			}
			count=1;
			cout<<"\n\n   "<<o_sub[i].topic[k]<<" :\n";
			for(int j=0;j<teach_count;j++)
				if(T(j).search(name,o_sub[i].topic[k])==2)
				{
					cout<<"\n      "<<count<<".  "<<T(j).name;
					temp[count]=j;
					count++;
				}
			cprintf("\r\n\r\n          Enter your option :: ");
			cin>>opt;
			if(opt<count)
			{
				int addr=temp[opt];
				cout<<"\n\t\t"<<T(addr).name<<" assigned\n";
				o_sub[i].t_no[k]=addr;
				o_sub[i].assign_no[k]=T(addr).no_of_assignment;
				T(addr).assign(name,o_sub[i].topic[k],n);
			}
			else
			{
				cprintf("   Wrong Entry. Try again!!");
				total-=n;
				i--;
			}
		}
	}
     Ct:
	cout<<"\n\n          Choose the Class Teacher :: ";
	for(i=0;i<r_subno;++i)
	{
		int t_no=r_sub[i].t_no;
		cout<<"\n                    "<<i+1<<". "<<T(t_no).name;
	}
	cout<<"\n\n         Enter your option :: ";
	cin>>opt;
	if(opt>r_subno)
	{
		cout<<"\nWrong entry. try again";
		goto Ct;
	}
	r_sub[opt-1].ct='y';
	if(total!=PERIODS*DAYS)
	{
		cout<<"\nWARNING. The total number of periods now assigned is "<<total;
		cout<<"\nIt should be "<<PERIODS*DAYS;
		cout<<"\n\n";
		getch();
		return 0;
	}
	return 1;
}
*/
void Class::get()
{
	gotoxy(10,wherey()+2);
	cprintf("Name :: ");
	gets(name);
	gotoxy(10,wherey()+2);
	cprintf("Enter Regular Subjects\n[Press 'enter' to stop] ");
	for(int i=0;i<19;i++)
	{
		gotoxy(15,wherey()+1);
		cout<<i+1<<". ";
		gets(r_sub[i].topic);
		if(!strcmpi(r_sub[i].topic,"\0"))
			break;
	}
	r_subno=i;
	clrscr();
	cout<<"\n\n";
	gotoxy(10,wherey()+2);

	for(i=0;i<10;i++)
	{
		clrscr();
		cprintf("Enter Optional Subjects\n [Press 'Enter' to stop] ");
		gotoxy(15,wherey()+1);
		cout<<i+1<<". Enter name :: ";
		gets(o_sub[i].name);
		if(!strcmpi(o_sub[i].name,"\0"))
			break;
		gotoxy(18,wherey()+1);
		cprintf("Enter the subjects :: ");
		for(int j=0;j<15;j++)
		{
			gotoxy(20,wherey()+1);
			cout<<j+1<<". ";
			gets(o_sub[i].topic[j]);
			if(!strcmpi(o_sub[i].topic[j],"\0"))
			break;
		}
		o_sub[i].n=j;
	}
	o_subno=i;
}

void Class::display()
{
	gotoxy(20,wherey()+2);
	cprintf("Name :: ");
	cout<<name;
	gotoxy(20,wherey()+2);
	cprintf("Regular Subject(s)\n");
	for(int i=0;i<r_subno;i++)
	{
		gotoxy(23,wherey()+1);
		cout<<i+1<<". "<<r_sub[i].topic;
		int t_no=r_sub[i].t_no;
		if(t_no!=-1)
		  {
		    gotoxy(50,wherey());
		    cout<<T(t_no).name;
		  }
	}
	gotoxy(20,wherey()+2);
	cprintf("Optional Subject(s)\n");
	for(i=0;i<o_subno;i++)
	{
		gotoxy(23,wherey()+1);
		cout<<i+1<<". "<<o_sub[i].name;
		for(int j=0;j<o_sub[i].n;j++)
		{
			gotoxy(28,wherey()+1);
			cout<<j+1<<". "<<o_sub[i].topic[j];
		}
	}
	gotoxy(20,wherey()+2);
	cprintf("Period(s) Left :: ");
	cout<<periods_left;
	mouse(p);
}