#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern void mouse(int *);
const int priority[10]={20,15,12,10,8,6,4,3,2,1};
int m[3];
int p[3];
extern int PERIODS,DAYS;
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

extern teacher &T(int n);
extern Class &C(int n);

/*(void teacher::modify()
{
	gotoxy(10,wherey()+2);
	cprintf("Teacher Name :: ");
	cout<<name;
	gotoxy(15,wherey()+1);
	cprintf("Subjects\n");
	for(int i=0;i<no_of_sub;i++)
	{
		gotoxy(20,wherey()+1);
		cout<<i+1<<". "<<sub_teaching[i];
	}
	clrscr();
	cout<<"\n";
	gotoxy(15,wherey()+2);
	cprintf("Classes\n");
	for(i=0;i<no_of_class;i++)
	{
		gotoxy(20,wherey()+1);
		cout<<i+1<<".  "<<class_teaching[i];
	}
	char n_name[10],n_sub[20][10],n_class[15][10];
	gotoxy(10,wherey()+2);
	cprintf("Do you want to Modify?\r\n\r\n");
	gotoxy(30,wherey());
	cprintf("Yes");
	gotoxy(50,wherey());
	cprintf("No");
	do
	{
		mouse(m);
		if(m[1]/8<49&&m[2]/8==wherey()-1)
		{
			gotoxy(30,wherey());
			cout<<"    ";
			gotoxy(50,wherey());
			cout<<"   ";
			gotoxy(10,wherey()-2);
			cprintf("      New Name (. for old one) : ");
			gets(n_name);
			if(strcmpi(n_name,"."))
				strcpy(name,n_name);
			gotoxy(15,wherey()+1);
			cprintf("New Subjects ( . for old one )\r\n");
			for(i=0;i<20;i++)
			{
				gotoxy(20,wherey()+1);
				cout<<i+1<<". ";
				gets(n_sub[i]);
				if(!strcmpi(n_sub[i],"\0"))
					break;
				else if(strcmpi(n_sub[i],"."))
					strcpy(sub_teaching[i],n_sub[i]);
			}
			no_of_sub=i;
			gotoxy(15,wherey()+1);
			cprintf("New Classes [. for old one]\r\n");
			for(i=0;i<15;i++)
			{
				gotoxy(20,wherey()+1);cout<<i+1<<". ";
				gets(n_class[i]);
				if(!strcmpi(n_class[i],"\0"))
					break;
				else if(strcmpi(n_class[i],"."))
					strcpy(class_teaching[i],n_class[i]);
			}
			no_of_class=i;
			gotoxy(10,wherey()+2);
			cout<<name<<" Modified";
			mouse(p);
			if(m[0]==0)
				break;
		}
	}while(!(m[1]/8>=49&&m[2]/8==wherey()-1));
}
*/
void teacher::modify()
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
		cprintf(" Subject(s) Teaching");
		textcolor(10);
		for(int i=0;i<no_of_sub;i++)
		{
			gotoxy(23,wherey()+2);
			cout<<i+1<<". "<<sub_teaching[i];
		}
		gotoxy(20,wherey()+2);
		cout<<"Add a new subject";
		gotoxy(15,wherey()+2);
		cout<<"View Classes teaching";
		gotoxy(15,wherey()+2);
		cout<<"Back";
		mouse(p);
		ch=(p[2]/16);
		if(ch-3==no_of_sub+2)
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
		  if(ch!=2&&ch-3<no_of_sub)
		    {
		      if(p[0]==0)
			{
			 gotoxy(26,ch*2+1);
			 cout<<"                                             ";
			 gotoxy(26,ch*2+1);
			 gets(sub_teaching[ch-3]);
			}
		      else
		       {
			 for(i=ch-3;i<no_of_sub;i++)
			    strcpy(sub_teaching[i],sub_teaching[i+1]);
			 no_of_sub--;
		       }
		   }
		  else if(ch-3==no_of_sub)
		    {
		      if(no_of_sub==19)
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
		      gets(sub_teaching[ch-3]);
		      no_of_sub++;
		     }
	       }
	}while(ch!=no_of_sub+4);
	do
	{
		clrscr();
		gotoxy(15,2);
		textcolor(RED);
		cprintf(" Class(es) Teaching");
		textcolor(10);
		for(int i=0;i<no_of_class;i++)
		{
			gotoxy(23,wherey()+2);
			cout<<i+1<<". "<<class_teaching[i];
		}
		gotoxy(20,wherey()+2);
		cout<<"Add a new class";
		gotoxy(15,wherey()+2);
		cout<<"Quit";
		mouse(p);
		ch=(p[2]/16);
		if(ch!=2&&ch-1<no_of_class)
		    {
		      if(p[0]==0)
			{
			 gotoxy(26,ch*2+2);
			 cout<<"                                             ";
			 gotoxy(26,ch*2+2);
			 gets(class_teaching[ch-1]);
			}
		      else
		       {
			 for(i=ch-1;i<no_of_class;i++)
			    strcpy(class_teaching[i],class_teaching[i+1]);
			 no_of_class--;
		       }
		   }
		  else if(ch-1==no_of_class)
		    {
		      if(no_of_class==15)
		       {
				clrscr();
				gotoxy(25,20);
				cout<<"\nClass limit exceeded ";
				getch();
				continue;
		       }
		      gotoxy(20,ch*2+2);
		      cout<<"                                             ";
		      gotoxy(23,ch*2+2);
		      cout<<i+1<<". ";
		      gets(class_teaching[ch-1]);
		      no_of_class++;
		     }

	}while(ch!=no_of_class+2);
}
void teacher::assign(char *STD,char *SUBJ,int p)
{
	int n=no_of_assignment;
	strcpy(a[n].Class,STD);
	strcpy(a[n].subj,SUBJ);
	a[n].no_of_period=p;
	tot_per+=p;
	no_of_assignment++;
}

void teacher::teacher()
{
	strcpy(name,"  ");
	no_of_assignment=0;
	tot_per=tot_allot=0;
	next=NULL;
	for(int i=0;i<10;i++)
		for(int j=0;j<7;j++)
			time[i][j]=-1;
	for(i=0;i<25;i++)
	{
		a[i].m_alloted_per=0;
		a[i].n_alloted_per=0;
		a[i].alloted_per=0;
		a[i].no_of_period=0;
	}
	no_of_sub=no_of_class=0;
}

void teacher::display()
{
	gotoxy(20,wherey()+2);
	cprintf("Name :: ");
	cout<<name;
	gotoxy(20,wherey()+2);
	cprintf("Subject(s)\n");
	for(int i=0;i<no_of_sub;i++)
	{
		gotoxy(23,wherey()+1);
		cout<<i+1<<". "<<sub_teaching[i];
	}
	gotoxy(20,wherey()+2);
	cprintf("Class(es)\n");
	for(i=0;i<no_of_class;i++)
	{
		gotoxy(23,wherey()+1);
		cout<<i+1<<". "<<class_teaching[i];
	}
	gotoxy(20,wherey()+2);
	cprintf("Assignments\n");
	for(i=0;i<no_of_assignment;i++)
	{
		gotoxy(25,wherey()+2);
		cout<<i+1<<".  Class :: "<<a[i].Class;
		gotoxy(30,wherey()+1);
		cout<<"Subject :: "<<a[i].subj;
		gotoxy(30,wherey()+1);
		cout<<"Total Periods :: "<<a[i].no_of_period;
		gotoxy(30,wherey()+1);
		cout<<"Periods alloted :: "<<a[i].m_alloted_per+a[i].n_alloted_per;
	}
	gotoxy(20,wherey()+2);
	cprintf("Total Periods :: ");
	cout<<tot_per;
	mouse(m);
}

void teacher::get()
{
	gotoxy(10,wherey()+2);
	cprintf("Name :: ");
	gets(name);
	gotoxy(10,wherey()+2);
	cprintf("Subjects [Press 'enter' to stop] ::\n");
	for(int i=0;i<19;i++)
	{
		gotoxy(15,wherey()+1);
		cout<<i+1<<". ";
		gets(sub_teaching[i]);
		if(!strcmpi(sub_teaching[i],"\0"))
			break;
	}
	no_of_sub=i;
	gotoxy(10,wherey()+2);
	cprintf("Classes [Input '*' to represent all classes ] ::\n");
	for(i=0;i<15;i++)
	{
		gotoxy(15,wherey()+1);
		cout<<i+1<<". ";
		gets(class_teaching[i]);
		if(!strcmpi(class_teaching[i],"*"))
		   {    i++;
			break;
		   }
		if(!strcmpi(class_teaching[i],"\0"))
			break;
	}
	no_of_class=i;
}

int teacher::search(char *STD,char *SUBJ)
{
	int x=0;
	for(int i=0;i<no_of_sub;i++)
	{
		if(!strcmpi(SUBJ,sub_teaching[i]))
		{
			x++;
			break;
		}
	}
	for(i=0;i<no_of_class;i++)
	{
		if(!strcmpi(STD,class_teaching[i])||!strcmpi(class_teaching[i],"*"))
		{
			x++;
			break;
		}
	}
	return x;
}

void teacher::clear_assign(int n)
{
	tot_per-=a[n].no_of_period;
	for(int i=n;i<no_of_assignment;i++)
		a[i]=a[i+1];
	no_of_assignment--;

}

float teacher::prior_cal(int n,int period,int x,int y,int s_no,char ct)
{

	float prior;
	float tot_d=tot_per-tot_allot;
	float d=a[n].no_of_period-(a[n].m_alloted_per+a[n].n_alloted_per);
	int sum=0;
	float rn=random(800)/50.0+random(800)/60.0+random(800)/70.0;
	for(int i=1;i<=PERIODS;i++)
	{
		if(time[i][y]==-1)
			sum+=5;
		for(int j=1;j<y;j++)
			if(time[i][j]==-1)
				sum+=5;
	}

	sum+=priority[s_no];
	if(ct=='y'&&x==1)
	     sum+=150;
	if(a[n].alloted_per==a[n].no_of_period)
		return 0;
	prior=500+(d*500/period)+(d*500/a[n].no_of_period)+(tot_d*150/tot_per)+rn
		   +(tot_d*80/period)+sum;
	if(x>((PERIODS+1)/2))
		prior+=((a[n].m_alloted_per*50/a[n].no_of_period)-(a[n].n_alloted_per*50/a[n].no_of_period));
	else
		prior-=((a[n].m_alloted_per*50/a[n].no_of_period)-(a[n].n_alloted_per*50/a[n].no_of_period));

	if(d==1)
	  prior-=50;
	return prior;
}
void teacher::disp_time()
{
	clrscr();
	gotoxy(35,4);
	cout<<name;
	char temp_time[10][7][10];
	int n,i,j;
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
				if(time[i][j]<1000)
				     strcpy(temp_time[i][j],C(n).name);
				else
				    strcpy(temp_time[i][j],C(n-1000).name);

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
	      cprintf("³");
	    }
	for(i=5;i<74;i++)
	  for(j=5;j<49;j+=4)
	    {
	      gotoxy(i,j);
	      cprintf("Ä");
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
       mouse(p);
}


int search_name(int n,char * NAME)
{
	int pos=-1;
	for(int i=0;i<n;i++)
		if(!strcmpi(T(i).name,NAME))
		{
			pos=i;
			break;
		}
	return pos;
}
