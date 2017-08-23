#include<fstream.h>
#include<process.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>

int PERIODS=0;
int DAYS=0;
extern void pro();
extern void front();
extern void teachers();
extern void classes();
extern void tt();
extern void init_var();
extern void remove_var();
extern int *m,*p;
extern void mouse(int *);
extern void first();
extern void last();
char password[16];

void change()
{
	textbackground(0);
	textcolor(10);
	clrscr();
	textcolor(4);
	gotoxy(33,12);
	cprintf("WARNING !!!....");
	gotoxy(10,15);
	cprintf("If these values are changed all files(*.tch & *.cls) MUST be deleted");
	gotoxy(20,20);
	textcolor(10);
	cprintf("The current values are ::");
	gotoxy(25,23);
	cprintf("Periods  :: ");
	cout<<PERIODS;
	gotoxy(25,26);
	cprintf("Days     :: ");
	cout<<DAYS;
	gotoxy(10,wherey()+2);
	cprintf("Do you want to change these values ?");
	gotoxy(30,wherey()+2);
	cprintf("Yes");
	gotoxy(50,wherey());
	cprintf("No");
	do
	 {
		mouse(m);
		if(m[1]/8<49&&m[2]/8==wherey()-1)
		{
		   gotoxy(10,28);
		   cout<<"                                      ";
		   gotoxy(20,30);
		   textcolor(14);
		   int PERIODS2,DAYS2;
		   cprintf("Enter New Values ::             ");
		   gotoxy(25,33);
		   cprintf("Periods [ Max 9 ]  :: ");
		   cin>>PERIODS2;
		   gotoxy(25,36);
		   cprintf("Days [ Max 6 ]     :: ");
		   cin>>DAYS2;
		   if(PERIODS2<10&&DAYS2<7&&PERIODS2>0&&DAYS2>0)
			{
				PERIODS=PERIODS2;
				DAYS=DAYS2;
				ofstream f2("per.dat",ios::out|ios::binary);
				f2<<PERIODS2<<" "<<DAYS2;
				f2.close();
				return;
			}
		}
	 }while(!(m[1]/8>=49&&m[2]/8==wherey()-1));

}


void enter_pass(char * passwd)
{
	for(int i=0;i<15;i++)
	{
		passwd[i]=getch();
		if(passwd[i]=='\r')
		{
			passwd[i]='\0';
			break;
		}
		else
			cout<<"*";
	}
}

void passwd()
{
	do
	{
		clrscr();
		gotoxy(20,23);
		cprintf("Are you sure you want to change the password ?");
		gotoxy(30,26);
		cprintf("Yes");
		gotoxy(50,26);
		cprintf("No");
		mouse(m);
		if(m[1]/8>=49&&m[2]/8==25)
			return ;
	}while(!(m[1]/8<49&&m[2]/8==25));
	textcolor(10);
	clrscr();
	char pass1[16],pass2[16],pass3[16];
	 gotoxy(20,20);
	 textcolor(14);
	 cprintf("Current Password :: ");
	enter_pass(pass1);
	if(strcmpi(pass1,password))
	{
		gotoxy(20,25);
		cprintf("Incorrect Password");
		getch();
		return;
	}
	gotoxy(20,25);
	cprintf("New Password :: ");
	enter_pass(pass2);
	gotoxy(20,30);
	cprintf("Confirm New Password :: ");
	enter_pass(pass3);
	if(strcmpi(pass2,pass3))
	{
		textcolor(RED);
		gotoxy(20,35);
		cprintf("Passwords Do Not Match");
		getch();
		return;
	}
	ofstream file("data.dat",ios::out|ios::binary);
	file<<pass2<<"\n";
	file.close();
	strcpy(password,pass2);
}

void main()
{
      /*
	clrscr();
	delay(2000);
	if(!kbhit())
	{

		front();
		pro();
		getch();
	}
	else
		if(!getch()==27)
		{

			front();
			pro();
			getch();
		}
	*/
	clrscr();
	textmode(64);
	textbackground(0);
	textcolor(4);
	int opt;
	char pass[16];
	ifstream fin("data.dat",ios::in|ios::binary);
	if(!fin)
		strcpy(password,"Frendz");
	else
		fin.getline(password,15);
	clrscr();
	for(int v=3;v>0;--v)
	{
		clrscr();
		gotoxy(20,24);
		cprintf("Password :: ");
		enter_pass(pass);

		if(strcmpi(pass,password))
		{
			gotoxy(30,28);
			cprintf("Wrong password!!\n\n");
			cout<<v-1;
			cprintf(" chances left ");
			getch();
		}
		else
			break;
	}
	if(v==0)
	{
		textcolor(3+BLINK);
		clrscr();
		gotoxy(25,24);
		delay(250);
		cout<<"\a\a\a";
		gotoxy(35,10);
		cprintf("Alert");
		delay(250);
		cout<<"\a\a\a";
		gotoxy(31,23);
		cprintf("Intruders!!!");
		getch();
		return;
	}
	textbackground(0);
	textcolor(4);
	init_var();
	do
	{
		clrscr();
		gotoxy(35,16);
		textcolor(4);
		cprintf("MAIN MENU");
		gotoxy(35,17);
		cprintf("อออออออออ");
		gotoxy(30,20);
		textcolor(10);
		cprintf("Teacher Database");
		gotoxy(30,22);
		cprintf("Class Database ");
		gotoxy(30,24);
		cprintf("Time Table Creator");
		gotoxy(30,26);
		cprintf("Password Settings");
		gotoxy(30,28);
		cprintf("Change No. of periods");
		gotoxy(30,30);
		cprintf("Exit");
		mouse(m);
		opt=((m[2]/16)-8);
		switch(opt)
		{
			case 1: teachers();
				break;
			case 2: classes();
				break;
			case 3: tt();
				break;
			case 4: passwd();
				break;
			case 5: change();
				break;
		       //	case 6: last();
		}
	}while(opt!=6);
	remove_var();
}

