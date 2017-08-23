#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<process.h>
void last()
{
	clrscr();
	gotoxy(12,5);
	delay(750);
	textcolor(2);
	cprintf("Developed At COMPUTER LAB Of");
	delay(2000);
	textcolor(4+BLINK);
	gotoxy(25,17);
	cprintf("VIMALAGIRI PUBLIC SCHOOL");
	delay(2000);
	gotoxy(10,25);
	textcolor(14);
	cprintf("As a part of our school project 2009-2010 ");
	delay(2000);
	gotoxy(40,30);
	delay(2000);
	cout<<"Under the guidance of ";
	delay(2000);
	gotoxy(45,34);
	cout<<"Mrs Seema James";
	delay(2000);
	gotoxy(45,38);
	cout<<"Mrs Betsy N Kuriakose";
	delay(5000);
	textcolor(10);
	clrscr();
	gotoxy(25,15);
	textcolor(14);
	cprintf("CONTACT US AT");
	delay(2000);
	gotoxy(30,20);
	cout<<"sachinbjohn@gmail.com";
	delay(2000);
	gotoxy(30,24);
	cout<<"tomglint@gmail.com";
	delay(2000);
	gotoxy(30,28);
	cout<<"vishnu452@gmail.com";
	delay(2000);
	getch();

 }
void front()
{

	textmode(64);
	clrscr();
	_setcursortype(_NOCURSOR);
	delay(2000);
	textcolor(LIGHTBLUE+BLINK);
	clrscr();
	_setcursortype(_NOCURSOR);
	gotoxy(35,10);
	cout<<"ULTRA TIME";
	delay(2000);
	int x,y;
	textcolor(LIGHTBLUE);
	clrscr();
	_setcursortype(_NOCURSOR);
	gotoxy(35,10);
	cout<<"ULTRA TIME";
	textcolor(15);
	gotoxy(10,13);
	delay(500);
	cprintf("Ú");
	for(x=11,y=14;x<70;x++)
	{
		if(x%4==0)
		{
			gotoxy(10,y);
			cprintf("³");
			y++;
		}
		gotoxy(x,13);
		cprintf("Ä");
		delay(50);
	}
	gotoxy(70,13);
	cprintf("¿");
	gotoxy(10,29);
	cprintf("À");
	delay(20);
	for(x=11,y=14;x<70;x++)
	{
		if(x%4==0)
		{
			gotoxy(70,y);
			cprintf("³");
			y++;
		}
		gotoxy(x,29);
		cprintf("Ä");
		delay(50);
	}
	gotoxy(70,29);
	cprintf("Ù");
}

void frontpage()
{
	textmode(64);
	int x,y;
	textcolor(LIGHTBLUE);
	clrscr();
	_setcursortype(_NOCURSOR);
	gotoxy(35,10);
	cout<<"ULTRATIME";
	textcolor(15);
	gotoxy(10,13);
	cprintf("Ú");
	for(x=11,y=14;x<70;x++)
	{
		if(x%4==0)
		{
			gotoxy(10,y);
			cprintf("³");
			y++;
		}
		gotoxy(x,13);
		cprintf("Ä");
	}
	gotoxy(70,13);
	cprintf("¿");
	gotoxy(10,29);
	cprintf("À");
	for(x=11,y=14;x<70;x++)
	{
		if(x%4==0)
		{
			gotoxy(70,y);
			cprintf("³");
			y++;
		}
		gotoxy(x,29);
		cprintf("Ä");
	}
	gotoxy(70,29);
	cprintf("Ù");
}

void pro()
{
	delay(1000);
	textcolor(4);
	gotoxy(15,17);
	cprintf("ß ß ß  Programme Developed By ß ß ß");
	delay(1500);
	textcolor(6+BLINK);
	for(int y=2;y<=23;y++)
	{
		clrscr();
		_setcursortype(_NOCURSOR);
		frontpage();
		gotoxy(15,17);
		textcolor(4);
		cprintf("ß ß ß  Programme Developed By ß ß ß");
		gotoxy(45,y);
		cprintf("Sachin Basil John");
		delay(50);
	}
	for(int x=1;x<=45;x++)
	{
		clrscr();
		_setcursortype(_NOCURSOR);
		frontpage();
		textcolor(4);
		gotoxy(15,17);
		cprintf("ß ß ß  Programme Developed By ß ß ß");
		gotoxy(45,23);
		cprintf("Sachin Basil John");
		{
			gotoxy(x,25);
			cprintf("Tom Glint Issac");
			delay(50);
		}
	}
	delay(500);
	gotoxy(45,27);
	textcolor(4);
	cprintf("Vishnu.P.S");
	delay(2500);
}
