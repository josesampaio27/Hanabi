#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include <conio.h>


//coloca o Cursor na posicao X,Y
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//desenha um retangulo com linhas duplas na posicao X,Y com as dimensoes Width e Height 
void drawRect(int x, int y, int width, int height,int number, int collor,int number_hint)
{
	  setlocale(LC_ALL, "C");
	int i,j;


	
	gotoxy(x, y);
	printf("%c", 201);
	for (i = 1; i < width; i++) {
		printf("%c", 205);
	}

	printf("%c", 187);
	gotoxy(x, height + y);
	printf("%c", 200);

	for (i = 1; i < width; i++) {
		printf("%c", 205);
	}

	printf("%c", 188);

	for (i = y + 1; i < height + y; i++)
	{
		gotoxy(x, i);
		printf("%c", 186);

		gotoxy(x + width, i);
		printf("%c", 186);

	} 
	
	if(number!=0){
	//desenha o numero na carta
	gotoxy(x+(width/2),y+2);
		printf("%d",number);}
		
	if(collor!=0){
	
	//desenha as cores nas cartas
	if(collor==4){
		gotoxy((x+(width/2)-1),y+(height-2));
		printf("red");
	 }
	else{
	gotoxy((x+(width/2)-2),y+(height-2));
		if(collor==9)
		printf("blue");
		else if(collor==2)
		printf("green");
		else if(collor==15)
		printf("white");
		else if(collor==14)
		printf("yelow");}}
		
		if(number_hint != 0){
			gotoxy(x+(width/2),y+4);
			printf("%d",number_hint);
		}
	

	
	 setlocale(LC_ALL, "");
}

