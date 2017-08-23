//This part includes mouse pointer in c++

#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream.h>

union REGS i,o;
int initmouse();
void hidemouse();
void showmouseptr();

void getmousepos(int *but,int *x,int*y)
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*but=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
}

void mouse(int * m_pos)
{       int dd;
	delay(250);
	int gdriver=DETECT,gmode,errorcose,a,b,x,y,button,timer,but=0;
	initgraph(&gdriver,&gmode," ");
	i.x.bx=0;
	i.x.ax=7;
	i.x.cx=10;
	i.x.dx=300;
	int86(0x33,&i,&o);
	i.x.bx=0;
	i.x.ax=8;
	i.x.cx=30;
	i.x.dx=500;
	int86(0x33,&i,&o);
	if(initmouse()==0)
	{
		closegraph();
		restorecrtmode();
		getch();
		exit(0);
	}
	showmouseptr();
	while(but==0)
	{
		if(kbhit())
			getch();
		getmousepos(&but,&x,&y);
	       //	gotoxy(1,45);
	      //	cout<<"    "<<x<<"     "<<y<<"      ";
		if(but==1)
		{
			m_pos[0]=0;
		}
		else if(but==2)
		{
			m_pos[0]=1;
		}
		m_pos[1]=x,m_pos[2]=y;

	}
	hidemouse();
}

initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return o.x.ax;
}

void showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}

void hidemouse()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}
