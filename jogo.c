#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include "lab.h" //inclui o fixeiro lab no programa

void starter();
void draw_hand(int card_a,int card_b,int card_c,int card_d,int card_e,int first);
void swap(int vector[],int x,int y);
int player_choice();
void draw_card(int hand[],int position_hand);
int card_choice();
int card_choice_hint();
void play_card(int card_number);
int hint_play(int card_number);
void discarded_cards();
void discard_card(int card_number);
int menu();
void save();
int countLetters(char * const line);
void BOT_play_card(int card_number);
void how_to_play();
void load();
void BOT();
void BOT_discard(int card);
void BOT_play_hint(int card_number,int choice);

#define KEY_UP 72
#define KEY_DOWN 80
#define SPACE ' '
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define ESC	27

//criaçao do deck, 9=blue, 4=red, 2=green, 15=white, 14=yelow
	int deckcards[50][2] = {{1,9},{1,9},{1,9},{2,9},{2,9},{3,9},{3,9},{4,9},{4,9},{5,9},
					   	    {1,4},{1,4},{1,4},{2,4},{2,4},{3,4},{3,4},{4,4},{4,4},{5,4},
					        {1,2},{1,2},{1,2},{2,2},{2,2},{3,2},{3,2},{4,2},{4,2},{5,2},
					        {1,15},{1,15},{1,15},{2,15},{2,15},{3,15},{3,15},{4,15},{4,15},{5,15},
					        {1,14},{1,14},{1,14},{2,14},{2,14},{3,14},{3,14},{4,14},{4,14},{5,14}};
	
	//system("@cls||clear");
	
	int draw_deck[50];  //vetor com indice de cartas
	//deck_player1, desck_player2
	int hand_player1[5];
	int hand_player2[5];
	//draw_dimension = numero de cartas no draw_deck
	int draw_dimension = 50;
	//numero de vidas
	int lives=3;
	//numero de pistas
	int hints=8;
	//nome do jogador
	char name[40];
	//numero das cartas da mesa que começa em 0
	int card_a=0 , card_c=0 , card_d=0 , card_e=0 , card_b=0;
	//cor das cartas do bot para serem mudadas futuramente pelas dicas
	int card_a_color=8,card_b_color=8,card_c_color=8,card_d_color=8,card_e_color=8;
	//numero das cartas do bot para serem mudadas futuramente pelas dicas
	int number_hint_a=0,number_hint_b=0,number_hint_c=0,number_hint_d=0,number_hint_e=0;
	//cor das cartas do player para serem mudadas futuramente pelas dicas
	int card_ap_color=8,card_bp_color=8,card_cp_color=8,card_dp_color=8,card_ep_color=8;
	//numero das cartas do player para serem mudadas futuramente pelas dicas
	int number_hint_ap=0,number_hint_bp=0,number_hint_cp=0,number_hint_dp=0,number_hint_ep=0;
	//matriz das cartas discartadas
	int cards_discard[5][5];
	
	int ronda=0;
	
int main(void){
	system("MODE con cols=117 lines=28");
	int i,choice_start,firsttoplay,choice,player_card,aux=1;
	srand(time(NULL));
	
	firsttoplay=rand()%2;
	
	while(choice_start!=0 || choice_start!=1){
		system("@cls||clear");
		
	choice_start=menu();
	
	if (choice_start==0 || choice_start==1){
	
	
	if(choice_start==1){
		load();
		firsttoplay==0;}
	
	else
	starter();
	
	if(choice_start==0){
	system("@cls||clear");
	
	gotoxy(35,12);
	printf("Insert your name:");
	
	//pedir o nome ao jogador
	fgets(name,40,stdin);}
	
	while(draw_dimension > -2){
	
	//limpar o ecra e escrever o jogo no ecra no fim de cada turno
	system("@cls||clear");
	draw_hand(card_a,card_b,card_c,card_d,card_e,firsttoplay);
	
	//vez do jogador
	if(firsttoplay==0){
	//escolher o que o jogador pretende fazer
	choice = player_choice();
	
	if(choice==-1){
		return 0;}
	
	//jogar carta
	if(choice==0){
	player_card = card_choice(); //escolha de qual carta quer jogar
	if(player_card == -1){
	}
	else{
	play_card(player_card);	//jogar a carta
	draw_card(hand_player1,player_card);} //colocar nova carta no lugar da jogada
	//se perder todas as vidas dizer que perdeu
	if(lives==0){
		system("@cls||clear");
		gotoxy(0,0);
		for(i=0;i<27;i++)
			printf("GAME OVER\n");
		getch();
		return 0;
	}
	}
	
	//jogar pista
	else if(choice==1){
	//verifica se tem pistas disponiveis
	if(hints>0){
	player_card = card_choice_hint(); //escolha da carta para dar pista
	fflush(stdin);
	if(player_card!=-1)
	player_card=hint_play(player_card);} //dar a pista
	else{
	gotoxy(17,12);
	printf("you dont have any more hints"); //se nao tiver pistas avisa o jogador
	player_card=-1;//fazer com que o turno nao passe
	getch();}
	}
	
	//descartar carta
	else if(choice==2){
	//verifica se nao tem as pistas no maximo
	if(hints<8){
		player_card = card_choice(); //escolha da carta para discartar
		if(player_card!=-1)
		discard_card(player_card);} //discartar a carta escolhida
	
	else{
		fflush(stdin);
		gotoxy(16,12);
		printf("you cant discard with 8 hints"); //avisar o jogador se tiver as pistas no maximo e nao puder discartar
		player_card=-1;//fazer com que o turno nao passe
		getch();}
	

}
	if(player_card==-1){
	firsttoplay=0;
	}
	else{
	firsttoplay=1;}
	
	if(firsttoplay != 0){
	ronda++;}
	}
	
	

	//vez do bot
	if(firsttoplay==1){
		system("@cls||clear");
		draw_hand(card_a,card_b,card_c,card_d,card_e,firsttoplay);
		fflush(stdin);
		getch();
		BOT();
		firsttoplay=0;
		
		ronda++;
	}


	else if(choice==-1)
		return 0;
		
		save();//guardar a partida
}

	if(draw_dimension <-1){
		system("@cls||clear");
		gotoxy(40,13);
		printf("Ganhou o jogo com %d pontos!!!",card_a+card_b+card_c+card_d+card_e);
		getch();
		return 0;
	}
		
}

	
	else if(choice_start==2){ //se a escolha for How to Play, mostrar as regras e como jogar
		how_to_play();
	}
	
	else if(choice_start==3){ //se a escolha for Exit, sair
		return 0;
	}
	
}
}

//inicializador do jogo
void starter(){

	setlocale(LC_ALL, "");
	srand(time(NULL));
	int a;
	int b;
	int k;
	
	
	//construir um vetor draw_deck com valores de 1 a 50
	for(k=0;k<50;k++){			
		draw_deck[k]=k;
	}
	

	//Baralhar o draw_deck
	//método por troca de 2 elementos aleatorios, por 100x
	for(k=0;k<400;k++){
		a=rand()%51;
		b=rand()%51;
		swap(draw_deck,a,b);
	}
	
	//distribuir as cartas pelos jogadores
	for(k=1;k<=5;k++){
		draw_card(hand_player1,k-1);
		draw_card(hand_player2,k-1);
	}
	
	//colocar a matriz de discarte a 0
	for(k=0;k<4;k++){
		cards_discard[k][0]=0;
		cards_discard[k][1]=0;
		cards_discard[k][2]=0;
		cards_discard[k][3]=0;
		cards_discard[k][4]=0;
	}
	
	}

//subprograma para trocar 2 elementos de um vetor
void swap(int vector[],int x,int y){
	int aux;
	aux=vector[x];
	vector[x]=vector[y];
	vector[y]=aux;
}

//subprograma para descrever como se joga o jogo
void how_to_play(){
	system("@cls||clear");
		gotoxy(1,0);
		printf("HOW TO PLAY:");
		
		gotoxy(2,2);
		printf("-objecitve:");
		
		gotoxy(1,4);
		printf("To be able to play 25 cards on the table forming 5 piles, one of each color, with the cards in numbering order. That is, in the end, ideally, there will be a bunch of cards for each of the five colored cards with the numbers 1, 2, 3, 4, and 5, played in that order, with 5 at the top.");
	
		gotoxy(2,8);
		printf("-Rules:\n\n In turn to play a player must do one and only one of the following actions: Give a clue; Discard a card; Play a card;\n Give a clue:\n You can only use this action if clues are available. The only clues that can be given are relative to the color or number of cards of that player. Permitted clues are to indicate the position of: all cards of one color or all cards of a number. You can never simultaneously indicate the color and number of any card.\n Discard a card:\n This action adds a clue to the existing ones. This action cannot be used if all tracks are available. The player announces that he is going to discard a card and chooses one of his cards (without ever looking ahead of the cards in his hand) and places it in the discarded pile. Cards from the discard pile can be viewed by any player at any time.\n Playing a card:\n It is when playing cards to the table that the firework is built. The player announces that he will play a card and chooses the card to play at the table. One of the following two situations occurs:  The card can be played correctly on the table by starting a firework or continuing an existing one. In case the card played on the table is not sequential in the amount of its color it results in the loss of a life. Lives are not recoverable. After playing the player completes his 5-card hand by removing a new card from the deck (if there are any cards available in the deck), but without looking at the front of the card!"); 

		gotoxy(1,9);
		printf("");
getch();
}

//retirar uma carta do draw_deck e colocar no hand
void draw_card(int hand[],int position_hand){
	
	if(draw_dimension>0){
	hand[position_hand]=draw_deck[50-draw_dimension];
	draw_dimension--;}
	
	else{
		hand[position_hand]=-1;
		draw_dimension--;
	}
}
	
//desenhar as cartas no ecra
void draw_hand(int card_a,int card_b,int card_c,int card_d,int card_e,int first){
	int count;
	
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(H,8);
	//desenhar as cartas do jogador 2 com os respetivos numeros e cores
	SetConsoleTextAttribute(H,card_a_color);//muda a cor da carta comforme as dicas
	drawRect(2,1,10,8,deckcards[hand_player2[0]][0],deckcards[hand_player2[0]][1],number_hint_a);
	SetConsoleTextAttribute(H,card_b_color);//muda a cor da carta comforme as dicas
	drawRect(14,1,10,8,deckcards[hand_player2[1]][0],deckcards[hand_player2[1]][1],number_hint_b);
	SetConsoleTextAttribute(H,card_c_color);//muda a cor da carta comforme as dicas
	drawRect(26,1,10,8,deckcards[hand_player2[2]][0],deckcards[hand_player2[2]][1],number_hint_c);
	SetConsoleTextAttribute(H,card_d_color);//muda a cor da carta comforme as dicas
	drawRect(38,1,10,8,deckcards[hand_player2[3]][0],deckcards[hand_player2[3]][1],number_hint_d);
	SetConsoleTextAttribute(H,card_e_color);//muda a cor da carta comforme as dicas
	drawRect(50,1,10,8,deckcards[hand_player2[4]][0],deckcards[hand_player2[4]][1],number_hint_e);
	SetConsoleTextAttribute(H,15);//reseta a cor da consola
	gotoxy(3,10);
	printf("BOT");//escreve BOT no sitio apropiado
	if(first==1){
	gotoxy(7,10);
	printf("<-your turn");}
	SetConsoleTextAttribute(H,8);
	
	//desenhar as cartas do jogador 1
	SetConsoleTextAttribute(H,card_ap_color);
	drawRect(2,15,10,8,0,0,number_hint_ap);
	SetConsoleTextAttribute(H,card_bp_color);
	drawRect(14,15,10,8,0,0,number_hint_bp);
	SetConsoleTextAttribute(H,card_cp_color);
	drawRect(26,15,10,8,0,0,number_hint_cp);
	SetConsoleTextAttribute(H,card_dp_color);
	drawRect(38,15,10,8,0,0,number_hint_dp);
	SetConsoleTextAttribute(H,card_ep_color);
	drawRect(50,15,10,8,0,0,number_hint_ep);
	SetConsoleTextAttribute(H,15);
	
	gotoxy(3,24);
	printf("%s",name);//escreve o nome do jogador no sitio apropiado
	count=countLetters(name);
	if(first==0){
	gotoxy(4+count,24);
	printf("<-your turn");}
	
	//deenha a mesa com os respetivos numeros e cores
	SetConsoleTextAttribute(H,9);
	drawRect(67,9,8,6,card_a,9,0);
	SetConsoleTextAttribute(H,4);
	drawRect(77,9,8,6,card_b,4,0);
	SetConsoleTextAttribute(H,2);
	drawRect(87,9,8,6,card_c,2,0);
	SetConsoleTextAttribute(H,15);
	drawRect(97,9,8,6,card_d,15,0);
	SetConsoleTextAttribute(H,14);
	drawRect(107,9,8,6,card_e,14,0);
	
	SetConsoleTextAttribute(H,15);//reseta a cor da consola

	//desenhar as vidas e as pistas no ecra
	gotoxy(105,1);
	printf("LIVES: %d",lives);
	gotoxy(105,3);
	printf("HINTS: %d",hints);
	gotoxy(105,5);
	printf("ROUND: %d",ronda+1);
	
	SetConsoleTextAttribute(H,8);
	drawRect(100,18,11,8,0,0,0);
	gotoxy(105,22);
	printf("%d",draw_dimension);
	gotoxy(104,19);
	printf("Deck:");
	SetConsoleTextAttribute(H,15);

	//desenhar as opçoes de jogo no ecra
	gotoxy(73,2);
	printf("Play Card");
	gotoxy(73,3);
	printf("Use Hint");
	gotoxy(73,4);
	printf("Discard Card");
	
	gotoxy(0,27);
	printf("click ESC to cancel/Exit");
	
	discarded_cards();//desenhar as cartas discartadas no ecra
	
	gotoxy(2,24);	
}

//subprograma para decidir o que o jogador pretende fazer
int player_choice()	{
	int flag=0;
	int c=0;

	gotoxy(72,2);
	printf(">");
	
	//ciclo que permite o jogador selecionar atravez das setas direcionais
	while(c!=13){
	switch(c=getch()){
			case KEY_UP:
			if(flag==0){
				gotoxy(72,2);
				printf("%c",SPACE);
				gotoxy(72,4);
				printf(">");
				flag=2;}
			
			else if(flag==1){
				gotoxy(72,3);
				printf("%c",SPACE);
				gotoxy(72,2);
				printf(">");
				flag=0;}
			
			else if(flag==2){
				gotoxy(72,4);
				printf("%c",SPACE);
				gotoxy(72,3);
				printf(">");
				flag=1;}
			
			break;
		
		case KEY_DOWN:
			if(flag==0){
			gotoxy(72,2);
			printf("%c",SPACE);
			gotoxy(72,3);
			printf(">");
			flag=1;}	
			
			else if(flag==1){
			gotoxy(72,3);
			printf("%c",SPACE);
			gotoxy(72,4);
			printf(">");
			flag=2;}
			
			else if(flag==2){
			gotoxy(72,4);
			printf("%c",SPACE);
			gotoxy(72,2);
			printf(">");
			flag=0;}	
			
			break;
			
			//permite o jogador cancelar a açao
			case ESC:
			return -1;}
}
	return flag;}

//subprograma para o jogador escolher que carta quer jogar ou discartar
int card_choice(){
	int flag=0;
	int c=0;

	gotoxy(7,14);
	printf("V");
	
	//ciclo que permite o jogador escolher atravez das setas direcionais
	while(c!=13){
	switch(c=getch()){
	
	case KEY_RIGHT:
		
		if(flag==0){
		gotoxy(7,14);
		printf("%c",SPACE);
		gotoxy(19,14);
		printf("V");
		flag=1;
		}	
		
		else if(flag==1)	{
		gotoxy(19,14);
		printf("%c",SPACE);
		gotoxy(31,14);
		printf("V");
		flag=2;
		}
		
		else if(flag==2){
		gotoxy(31,14);
		printf("%c",SPACE);
		gotoxy(43,14);
		printf("V");
		flag=3;
		}
		
		else if(flag==3){
		gotoxy(43,14);
		printf("%c",SPACE);
		gotoxy(55,14);
		printf("V");
		flag=4;
		}
		
		else if(flag==4){
		gotoxy(55,14);
		printf("%c",SPACE);
		gotoxy(7,14);
		printf("V");
		flag=0;
		}
		
		break;
	
	case KEY_LEFT:
		
		if(flag==0){
		gotoxy(7,14);
		printf("%c",SPACE);
		gotoxy(55,14);
		printf("V");
		flag=4;
		}	
		
		else if(flag==1)	{
		gotoxy(19,14);
		printf("%c",SPACE);
		gotoxy(7,14);
		printf("V");
		flag=0;
		}
		
		else if(flag==2){
		gotoxy(31,14);
		printf("%c",SPACE);
		gotoxy(19,14);
		printf("V");
		flag=1;
		}
		
		else if(flag==3){
		gotoxy(43,14);
		printf("%c",SPACE);
		gotoxy(31,14);
		printf("V");
		flag=2;
		}
		
		else if(flag==4){
		gotoxy(55,14);
		printf("%c",SPACE);
		gotoxy(43,14);
		printf("V");
		flag=3;
		}
		
		break;
		
		//permite o jogador cancelar a açao
		case ESC:
			return -1;}	


}
	return flag;}

//subprograma que permite o jogador escolher uma carta para dar dica	
int card_choice_hint(){
	int flag=0;
	int c=0;

	gotoxy(7,10);
	printf("^");
	
	//ciclo que permite o jogador escolher atravez das setas direcionais
	while(c!=13){
	switch(c=getch()){
	
	case KEY_RIGHT:
		
		if(flag==0){
		gotoxy(7,10);
		printf("%c",SPACE);
		gotoxy(19,10);
		printf("^");
		flag=1;
		}	
		
		else if(flag==1)	{
		gotoxy(19,10);
		printf("%c",SPACE);
		gotoxy(31,10);
		printf("^");
		flag=2;
		}
		
		else if(flag==2){
		gotoxy(31,10);
		printf("%c",SPACE);
		gotoxy(43,10);
		printf("^");
		flag=3;
		}
		
		else if(flag==3){
		gotoxy(43,10);
		printf("%c",SPACE);
		gotoxy(55,10);
		printf("^");
		flag=4;
		}
		
		else if(flag==4){
		gotoxy(55,10);
		printf("%c",SPACE);
		gotoxy(7,10);
		printf("^");
		flag=0;
		}
		
		break;
	
	case KEY_LEFT:
		
		if(flag==0){
		gotoxy(7,10);
		printf("%c",SPACE);
		gotoxy(55,10);
		printf("^");
		flag=4;
		}	
		
		else if(flag==1)	{
		gotoxy(19,10);
		printf("%c",SPACE);
		gotoxy(7,10);
		printf("^");
		flag=0;
		}
		
		else if(flag==2){
		gotoxy(31,10);
		printf("%c",SPACE);
		gotoxy(19,10);
		printf("^");
		flag=1;
		}
		
		else if(flag==3){
		gotoxy(43,10);
		printf("%c",SPACE);
		gotoxy(31,10);
		printf("^");
		flag=2;
		}
		
		else if(flag==4){
		gotoxy(55,10);
		printf("%c",SPACE);
		gotoxy(43,10);
		printf("^");
		flag=3;
		}
		
		break;
		
		//permite o jogador cancelar a açao
		case ESC:
			return -1;}	


}
	return flag;}

//subprograma para efetuar o jogar de uma carta	
void play_card(int card_number){
	int i;
	int aux,a;
	int c_a,c_b,c_c,c_d,c_e;
	c_a=card_a;
	c_b=card_b;
	c_c=card_c;
	c_d=card_d;	
	c_e=card_e;
	
		
		//ciclo para verificar qual o numero da carta jogada
		for(i=0;i<16;i++){
			if(deckcards[hand_player1[card_number]][1] == i){
				aux = i;
				break;}
	}
	
	//verifica a cor da carta jogada e se a carta jogada esta certa senao tira uma vida
	if(aux==9){
		if(deckcards[hand_player1[card_number]][0]==(c_a+1)){
		card_a++;
			gotoxy(15,12);
			printf("You played a Blue %d, a right card!",deckcards[hand_player1[card_number]][0]);
			getch();}	
		else{
			lives--;
			gotoxy(6,12);
			printf("You played a Blue %d, a wrong card, you lost a life :(",deckcards[hand_player1[card_number]][0]);
			getch();}
	}
	
	if(aux==4){
		if(deckcards[hand_player1[card_number]][0]==(c_b+1)){
		card_b++;
			gotoxy(15,12);
			printf("You played a Red %d, a right card!",deckcards[hand_player1[card_number]][0]);
			getch();}	
		else{
			lives--;
			gotoxy(6,12);
			printf("You played a Red %d, a wrong card, you lost a life :(",deckcards[hand_player1[card_number]][0]);
			getch();}
	}
	
	if(aux==2){
		if(deckcards[hand_player1[card_number]][0]==(c_c+1)){
		card_c++;
			gotoxy(15,12);
			printf("You played a Green %d, a right card!",deckcards[hand_player1[card_number]][0]);
			getch();}	
		else{
			lives--;
			gotoxy(6,12);
			printf("You played a Green %d, a wrong card, you lost a life :(",deckcards[hand_player1[card_number]][0]);
			getch();}
	}
	
	if(aux==15){
		if(deckcards[hand_player1[card_number]][0]==(c_d+1)){
		card_d++;
			gotoxy(15,12);
			printf("You played a White %d, a right card!",deckcards[hand_player1[card_number]][0]);
			getch();}	
		else{
			lives--;
			gotoxy(6,12);
			printf("You played a White %d, a wrong card, you lost a life :(",deckcards[hand_player1[card_number]][0]);
			getch();}
	}
	
	if(aux==14){
		if(deckcards[hand_player1[card_number]][0]==(c_e+1)){
		card_e++;
			gotoxy(15,12);
			printf("You played a Yellow %d, a right card!",deckcards[hand_player1[card_number]][0]);
			getch();}	
		else{
			lives--;
			gotoxy(6,12);
			printf("You played a Yellow %d, a wrong card, you lost a life :(",deckcards[hand_player1[card_number]][0]);
			getch();}
	}
	
	if(card_number==0){
		card_ap_color=8;
		number_hint_ap=0;
	}
	
	else if(card_number==1){
		card_bp_color=8;
		number_hint_bp=0;
	}
	
	else if(card_number==2){
		card_cp_color=8;
		number_hint_cp=0;
	}
	
	else if(card_number==3){
		card_dp_color=8;
		number_hint_dp=0;
	}
	
	else if(card_number==4){
		card_ep_color=8;
		number_hint_ep=0;
	}
		
}	

//subprograma para efetuar a jogada de uma dica
int hint_play(int card_number){
	int choice=0;
	int c=0;

	
	gotoxy(17,12);
	printf("color");
	gotoxy(41,12);
	printf("number");
	
	gotoxy(16,12);
	printf(">");
	
	//cilclo para o jogador escolher se quer dar dica na cor ou no numero
	while(c!=13){
	
	switch(c=getch()){
		
		case KEY_RIGHT:
			
			if(choice==0){
				gotoxy(16,12);
				printf("%c",SPACE);
				gotoxy(40,12);
				printf(">");
				choice=1;
			}
			
			else if(choice==1){
				gotoxy(40,12);
				printf("%c",SPACE);
				gotoxy(16,12);
				printf(">");
				choice=0;
			}
			
			break;
			
		case KEY_LEFT:
			
			if(choice==0){
				gotoxy(16,12);
				printf("%c",SPACE);	
				gotoxy(40,12);
				printf(">");
				choice=1;
			}
			
			else if(choice==1){
				gotoxy(40,12);
				printf("%c",SPACE);
				gotoxy(16,12);
				printf(">");
				choice=0;
			}
			
			break;
			
			case ESC :
			
			return -1;}
			}


	//coloca a cor da carta escolhida na sua cor e verifica se existe mais alguma da mesma cor e coloca-a tambem da sua cor
	if(choice==0){
		if(card_number==0){
			card_a_color=deckcards[hand_player2[0]][1];
		
			if(deckcards[hand_player2[1]][1]==deckcards[hand_player2[0]][1])
			card_b_color=deckcards[hand_player2[0]][1];
		
			if(deckcards[hand_player2[2]][1]==deckcards[hand_player2[0]][1])
			card_c_color=deckcards[hand_player2[0]][1];
			
			if(deckcards[hand_player2[3]][1]==deckcards[hand_player2[0]][1])
			card_d_color=deckcards[hand_player2[0]][1];
			
			if(deckcards[hand_player2[4]][1]==deckcards[hand_player2[0]][1])
			card_e_color=deckcards[hand_player2[0]][1];}
			
		
		if(card_number==1){
			card_b_color=deckcards[hand_player2[1]][1];
		
			if(deckcards[hand_player2[0]][1]==deckcards[hand_player2[1]][1])
			card_a_color=deckcards[hand_player2[1]][1];
		
			if(deckcards[hand_player2[2]][1]==deckcards[hand_player2[1]][1])
			card_c_color=deckcards[hand_player2[1]][1];
			
			if(deckcards[hand_player2[3]][1]==deckcards[hand_player2[1]][1])
			card_d_color=deckcards[hand_player2[1]][1];
			
			if(deckcards[hand_player2[4]][1]==deckcards[hand_player2[1]][1])
			card_e_color=deckcards[hand_player2[1]][1];}
			
		
		if(card_number==2){
			card_c_color=deckcards[hand_player2[2]][1];
		
			if(deckcards[hand_player2[0]][1]==deckcards[hand_player2[2]][1])
			card_a_color=deckcards[hand_player2[2]][1];
		
			if(deckcards[hand_player2[1]][1]==deckcards[hand_player2[2]][1])
			card_b_color=deckcards[hand_player2[2]][1];
			
			if(deckcards[hand_player2[3]][1]==deckcards[hand_player2[2]][1])
			card_d_color=deckcards[hand_player2[2]][1];
			
			if(deckcards[hand_player2[4]][1]==deckcards[hand_player2[2]][1])
			card_e_color=deckcards[hand_player2[2]][1];}
			
			
		if(card_number==3){
			card_d_color=deckcards[hand_player2[3]][1];
		
			if(deckcards[hand_player2[0]][1]==deckcards[hand_player2[3]][1])
			card_a_color=deckcards[hand_player2[3]][1];
		
			if(deckcards[hand_player2[1]][1]==deckcards[hand_player2[3]][1])
			card_b_color=deckcards[hand_player2[3]][1];
			
			if(deckcards[hand_player2[2]][1]==deckcards[hand_player2[3]][1])
			card_c_color=deckcards[hand_player2[3]][1];
			
			if(deckcards[hand_player2[4]][1]==deckcards[hand_player2[3]][1])
			card_e_color=deckcards[hand_player2[3]][1];}
			
			
		if(card_number==4){
			card_e_color=deckcards[hand_player2[4]][1];
		
			if(deckcards[hand_player2[0]][1]==deckcards[hand_player2[4]][1])
			card_a_color=deckcards[hand_player2[4]][1];
		
			if(deckcards[hand_player2[2]][1]==deckcards[hand_player2[4]][1])
			card_c_color=deckcards[hand_player2[4]][1];
			
			if(deckcards[hand_player2[3]][1]==deckcards[hand_player2[4]][1])
			card_d_color=deckcards[hand_player2[4]][1];
			
			if(deckcards[hand_player2[1]][1]==deckcards[hand_player2[4]][1])
			card_b_color=deckcards[hand_player2[4]][1];}
	}
	
	//coloca o numero da carta escolhida no seu numero e verifica se existe mais alguma com o mesmo numero e coloca-a tambem no seu numero
	else if(choice==1){
		if(card_number==0){
			number_hint_a=deckcards[hand_player2[0]][0];
		
			if(deckcards[hand_player2[1]][0]==deckcards[hand_player2[0]][0])
			number_hint_b=deckcards[hand_player2[0]][0];
		
			if(deckcards[hand_player2[2]][0]==deckcards[hand_player2[0]][0])
			number_hint_c=deckcards[hand_player2[0]][0];
			
			if(deckcards[hand_player2[3]][0]==deckcards[hand_player2[0]][0])
			number_hint_d=deckcards[hand_player2[0]][0];
			
			if(deckcards[hand_player2[4]][0]==deckcards[hand_player2[0]][0])
			number_hint_e=deckcards[hand_player2[0]][0];}
			
		if(card_number==1){
			number_hint_b=deckcards[hand_player2[1]][0];
		
			if(deckcards[hand_player2[0]][0]==deckcards[hand_player2[1]][0])
			number_hint_a=deckcards[hand_player2[1]][0];
		
			if(deckcards[hand_player2[2]][0]==deckcards[hand_player2[1]][0])
			number_hint_c=deckcards[hand_player2[1]][0];
			
			if(deckcards[hand_player2[3]][0]==deckcards[hand_player2[1]][0])
			number_hint_d=deckcards[hand_player2[1]][0];
			
			if(deckcards[hand_player2[4]][0]==deckcards[hand_player2[1]][0])
			number_hint_e=deckcards[hand_player2[1]][0];}
			
		if(card_number==2){
			number_hint_c=deckcards[hand_player2[2]][0];
		
			if(deckcards[hand_player2[1]][0]==deckcards[hand_player2[2]][0])
			number_hint_b=deckcards[hand_player2[2]][0];
		
			if(deckcards[hand_player2[0]][0]==deckcards[hand_player2[2]][0])
			number_hint_a=deckcards[hand_player2[2]][0];
			
			if(deckcards[hand_player2[3]][0]==deckcards[hand_player2[2]][0])
			number_hint_d=deckcards[hand_player2[2]][0];
			
			if(deckcards[hand_player2[4]][0]==deckcards[hand_player2[2]][0])
			number_hint_e=deckcards[hand_player2[2]][0];}
			
		if(card_number==3){
			number_hint_d=deckcards[hand_player2[3]][0];
		
			if(deckcards[hand_player2[1]][0]==deckcards[hand_player2[3]][0])
			number_hint_b=deckcards[hand_player2[3]][0];
		
			if(deckcards[hand_player2[2]][0]==deckcards[hand_player2[3]][0])
			number_hint_c=deckcards[hand_player2[3]][0];
			
			if(deckcards[hand_player2[0]][0]==deckcards[hand_player2[3]][0])
			number_hint_a=deckcards[hand_player2[3]][0];
			
			if(deckcards[hand_player2[4]][0]==deckcards[hand_player2[3]][0])
			number_hint_e=deckcards[hand_player2[3]][0];}
			
		if(card_number==4){
			number_hint_e=deckcards[hand_player2[4]][0];
		
			if(deckcards[hand_player2[1]][0]==deckcards[hand_player2[4]][0])
			number_hint_b=deckcards[hand_player2[4]][0];
		
			if(deckcards[hand_player2[2]][0]==deckcards[hand_player2[4]][0])
			number_hint_c=deckcards[hand_player2[4]][0];
			
			if(deckcards[hand_player2[3]][0]==deckcards[hand_player2[4]][0])
			number_hint_d=deckcards[hand_player2[4]][0];
			
			if(deckcards[hand_player2[0]][0]==deckcards[hand_player2[4]][0])
			number_hint_a=deckcards[hand_player2[4]][0];}
		}
		
	//retita uma dica
	hints--;
		
}

//subprograma para discartar carta					
void discard_card(int card_number){
	int i;
	
	switch (deckcards[hand_player1[card_number]][1]){
		
		case 9:
			gotoxy(21,12);
			printf("You discarded a Blue %d!",deckcards[hand_player1[card_number]][0]);
			getch();
			break;
		
		case 4:
			gotoxy(21,12);
			printf("You discarded a Red %d!",deckcards[hand_player1[card_number]][0]);
			getch();
			break;
			
		case 2:
			gotoxy(21,12);
			printf("You discarded a Green %d!",deckcards[hand_player1[card_number]][0]);
			getch();
			break;
		
		case 15:
			gotoxy(21,12);
			printf("You discarded a White %d!",deckcards[hand_player1[card_number]][0]);
			getch();
			break;
		
		case 14:
			gotoxy(21,12);
			printf("You discarded a Yellow %d!",deckcards[hand_player1[card_number]][0]);
			getch();
			break;
	}
	
	//verifica o numero e a cor da carta discartada e adiciona 1 á matriz no lugar apropiado
	for(i=0;i<5;i++){
	if(deckcards[hand_player1[card_number]][0]==i+1 && deckcards[hand_player1[card_number]][1]==9){
		cards_discard[i][0]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player1[card_number]][0]==i+1 && deckcards[hand_player1[card_number]][1]==4){
		cards_discard[i][1]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player1[card_number]][0]==i+1 && deckcards[hand_player1[card_number]][1]==2){
		cards_discard[i][2]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player1[card_number]][0]==i+1 && deckcards[hand_player1[card_number]][1]==15){
		cards_discard[i][3]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player1[card_number]][0]==i+1 && deckcards[hand_player1[card_number]][1]==14){
		cards_discard[i][4]++;
	}
}
	
	
	draw_card(hand_player1,card_number);
		hints++;
	
	if(card_number==0){
		card_ap_color=8;
		number_hint_ap=0;
	}
	
	else if(card_number==1){
		card_bp_color=8;
		number_hint_bp=0;
	}
	
	else if(card_number==2){
		card_cp_color=8;
		number_hint_cp=0;
	}
	
	else if(card_number==3){
		card_dp_color=8;
		number_hint_dp=0;
	}
	
	else if(card_number==4){
		card_ep_color=8;
		number_hint_ep=0;
	}	
}

//desenha a matriz das cartas discartadas
void discarded_cards(){
	int i,k=0;
	
	HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(76,17);
	printf("1");
	
	gotoxy(79,17);
	printf("2");
	
	gotoxy(82,17);
	printf("3");
	
	gotoxy(85,17);
	printf("4");
	
	gotoxy(88,17);
	printf("5");
	
	SetConsoleTextAttribute(H,9);
	for(i=0;i<5;i++){
		gotoxy(76+k,18);
		printf("%d",cards_discard[i][0]);
		k=k+3;
	}
	k=0;
	
	//ciclos para desenhar os numeros da matriz, cada linha na respetiva cor
	SetConsoleTextAttribute(H,4);
	for(i=0;i<5;i++){
		gotoxy(76+k,20);
		printf("%d",cards_discard[i][1]);
		k=k+3;
	}
	k=0;
	
	SetConsoleTextAttribute(H,2);
	for(i=0;i<5;i++){
		gotoxy(76+k,22);
		printf("%d",cards_discard[i][2]);
		k=k+3;
	}
	k=0;
	
	SetConsoleTextAttribute(H,15);
	for(i=0;i<5;i++){
		gotoxy(76+k,24);
		printf("%d",cards_discard[i][3]);
		k=k+3;
	}
	k=0;
	
	SetConsoleTextAttribute(H,14);
	for(i=0;i<5;i++){
		gotoxy(76+k,26);
		printf("%d",cards_discard[i][4]);
		k=k+3;
	}
	k=0;
	
	SetConsoleTextAttribute(H,9);
	gotoxy(68,18);
	printf("Blue");
	
	SetConsoleTextAttribute(H,4);
	gotoxy(68,20);
	printf("Red");
	
	SetConsoleTextAttribute(H,2);
	gotoxy(68,22);
	printf("Green");
	
	SetConsoleTextAttribute(H,15);
	gotoxy(68,24);
	printf("White");
	
	SetConsoleTextAttribute(H,14);
	gotoxy(68,26);
	printf("Yellow");
	
	SetConsoleTextAttribute(H,15);
	

}

//desenha o menu
int menu(){
	int flag=0;
	int c=0;

	drawRect(52,6,17,13,0,0,0);
	
	gotoxy(55,8);
	printf("New Game");
	
	gotoxy(55,11);
	printf("Load Game");
	
	gotoxy(55,14);
	printf("How to Play");
	
	gotoxy(55,17);
	printf("Exit");
	
	gotoxy(0,27);
	printf("Made and developed by José Sampaio and Paulo Moreira");
	
	gotoxy(54,8);
	printf(">");
	
	while(c!=13){
	switch(c=getch()){
			case KEY_UP:
			if(flag==0){
				gotoxy(54,8);
				printf("%c",SPACE);
				gotoxy(54,17);
				printf(">");
				flag=3;}
			
			else if(flag==1){
				gotoxy(54,11);
				printf("%c",SPACE);
				gotoxy(54,8);
				printf(">");
				flag=0;}
			
			else if(flag==2){
				gotoxy(54,14);
				printf("%c",SPACE);
				gotoxy(54,11);
				printf(">");
				flag=1;}
				
			else if(flag==3){
				gotoxy(54,17);
				printf("%c",SPACE);
				gotoxy(54,14);
				printf(">");
				flag=2;}
			
			break;
		
		case KEY_DOWN:
			if(flag==0){
			gotoxy(54,8);
			printf("%c",SPACE);
			gotoxy(54,11);
			printf(">");
			flag=1;}	
			
			else if(flag==1){
			gotoxy(54,11);
			printf("%c",SPACE);
			gotoxy(54,14);
			printf(">");
			flag=2;}
			
			else if(flag==2){
			gotoxy(54,14);
			printf("%c",SPACE);
			gotoxy(54,17);
			printf(">");
			flag=3;}
			
			else if(flag==3){
			gotoxy(54,17);
			printf("%c",SPACE);
			gotoxy(54,8);
			printf(">");
			flag=0;}		
			
			break;
			
		}
}
	return flag;}

void save(){
	int i,j;
	
	FILE *save = NULL;
	
	save = fopen("save.txt","w");
	
	fprintf(save,"hand_player1 - ");
	for(i=0;i<5;i++)
	fprintf(save,"%d ",hand_player1[i]);
	fprintf(save,"\n");
	
	fprintf(save,"hand_player2 - ");
	for(i=0;i<5;i++)
	fprintf(save,"%d ",hand_player2[i]);
	fprintf(save,"\n");
	
	fprintf(save,"draw_deck - ");
	for(i=0;i<50;i++)
	fprintf(save,"%d ",draw_deck[i]);
	fprintf(save,"\n");
	
	fprintf(save,"cards_discard - ");
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
	fprintf(save,"%d ",cards_discard[i][j]);}
	}
	fprintf(save,"\n");
	
	fprintf(save,"lives - ");
	fprintf(save,"%d",lives);
	fprintf(save,"\n");
	
	fprintf(save,"ronda - ");
	fprintf(save,"%d",ronda);
	fprintf(save,"\n");
	
	fprintf(save,"hints - ");
	fprintf(save,"%d",hints);
	fprintf(save,"\n");
	
	fprintf(save,"draw_dimension - ");
	fprintf(save,"%d",draw_dimension);
	fprintf(save,"\n");
	
	fprintf(save,"card_a - %d, card_b -%d, card_c - %d, card_d - %d, card_e - %d",card_a,card_b,card_c,card_d,card_e);
	fprintf(save,"\n");
	
	fprintf(save,"card_a_color - %d, card_b_color -%d, card_c_color - %d, card_d_color - %d, card_e_color - %d",card_a_color,card_b_color,card_c_color,card_d_color,card_e_color);
	fprintf(save,"\n");
	
	fprintf(save,"card_ap_color - %d, card_bp_color -%d, card_cp_color - %d, card_dp_color - %d, card_ep_color - %d",card_ap_color,card_bp_color,card_cp_color,card_dp_color,card_ep_color);
	fprintf(save,"\n");
	
	fprintf(save,"number_hint_a - %d, number_hint_b -%d, number_hint_c - %d, number_hint_d - %d, number_hint_e - %d",number_hint_a,number_hint_b,number_hint_c,number_hint_d,number_hint_e);
	fprintf(save,"\n");
	
	fprintf(save,"number_hint_ap - %d, number_hint_bp -%d, number_hint_cp - %d, number_hint_dp - %d, number_hint_ep - %d",number_hint_ap,number_hint_bp,number_hint_cp,number_hint_dp,number_hint_ep);
	fprintf(save,"\n");
	
	fprintf(save,"name - ");
	fprintf(save,"%s",name);
	
	fclose(save);
	
}

void load(){
	int i,j;
	
	FILE *save = NULL;
	
	save = fopen("save.txt","r");
	
	fscanf(save,"hand_player1 - ");
	for(i=0;i<5;i++)
	fscanf(save,"%d ",&hand_player1[i]);
	
	fscanf(save,"hand_player2 - ");
	for(i=0;i<5;i++)
	fscanf(save,"%d ",&hand_player2[i]);
	
	fscanf(save,"draw_deck - ");
	for(i=0;i<50;i++)
	fscanf(save,"%d ",&draw_deck[i]);
	
	fscanf(save,"cards_discard - ");
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
	fscanf(save,"%d ",&cards_discard[i][j]);}
	}
	
	fscanf(save,"lives - ");
	fscanf(save,"%d\n",&lives);
	
	fscanf(save,"ronda - ");
	fscanf(save,"%d\n",&ronda);
	
	fscanf(save,"hints - ");
	fscanf(save,"%d\n",&hints);
	
	fscanf(save,"draw_dimension - ");
	fscanf(save,"%d\n",&draw_dimension);
	
	fscanf(save,"card_a - %d, card_b -%d, card_c - %d, card_d - %d, card_e - %d\n",&card_a,&card_b,&card_c,&card_d,&card_e);
	
	fscanf(save,"card_a_color - %d, card_b_color -%d, card_c_color - %d, card_d_color - %d, card_e_color - %d\n",&card_a_color,&card_b_color,&card_c_color,&card_d_color,&card_e_color);
	
	fscanf(save,"card_ap_color - %d, card_bp_color -%d, card_cp_color - %d, card_dp_color - %d, card_ep_color - %d\n",&card_ap_color,&card_bp_color,&card_cp_color,&card_dp_color,&card_ep_color);
	
	fscanf(save,"number_hint_a - %d, number_hint_b -%d, number_hint_c - %d, number_hint_d - %d, number_hint_e - %d\n",&number_hint_a,&number_hint_b,&number_hint_c,&number_hint_d,&number_hint_e);
	
	fscanf(save,"number_hint_ap - %d, number_hint_bp -%d, number_hint_cp - %d, number_hint_dp - %d, number_hint_ep - %d\n",&number_hint_ap,&number_hint_bp,&number_hint_cp,&number_hint_dp,&number_hint_ep);
	
	fscanf(save,"name - ");
	fscanf(save,"%[^\n]",&name);
	
	fclose(save);
}

//subprograma para contar quantos caracteres tem uma string
int countLetters(char * const line){
    int index = 0;
    int count = 0;

    while(line[index])
    {
        if (line[index] >= 'a' && line[index] <= 'z')
            count++;
            
        if (line[index] == ' ')
        	count++;

        if (line[index] >= 'A' && line[index] <= 'Z')
            count++;

        index++;
    }
    return count;
}

void BOT(){
	int card_color[5];
    int card_number[5]; 
	int aux=-1,i,j,aux2=0;
	
		card_color[0] = card_ap_color, card_color[1] = card_bp_color,card_color[2] = card_cp_color,card_color[3] = card_dp_color,card_color[4] = card_ep_color;
		card_number[0] = number_hint_ap ,card_number[1] = number_hint_bp, card_number[2] = number_hint_cp, card_number[3] = number_hint_dp, card_number[4] = number_hint_ep;
		
	if(ronda==0){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0]==1)
			aux=i;
		}
		
	if(aux!=(-1)){
		BOT_play_hint(aux,1);
		return 0;}
	}
	
	//carta azul
	if(card_a_color==9){
		if(number_hint_a==card_a+1){
			BOT_play_card(0);
			draw_card(hand_player2,0);
			number_hint_a=0;
			card_a_color=8;
			return 0;}
	}
	if(card_b_color==9){
		if(number_hint_b==card_a+1){
			BOT_play_card(1);
			draw_card(hand_player2,1);
			number_hint_b=0;
			card_b_color=8;
			return 0;}
	}
	if(card_c_color==9){
		if(number_hint_c==card_a+1){
			BOT_play_card(2);
			draw_card(hand_player2,2);
			number_hint_c=0;
			card_c_color=8;
			return 0;}
	}
	if(card_d_color==9){
		if(number_hint_d==card_a+1){
			BOT_play_card(3);
			draw_card(hand_player2,3);
			number_hint_d=0;
			card_d_color=8;
			return 0;}
	}
	if(card_e_color==9){
		if(number_hint_e==card_a+1){
			BOT_play_card(4);
			draw_card(hand_player2,4);
			number_hint_e=0;
			card_e_color=8;
			return 0;}
	}
	
	//carta vermelha
	if(card_a_color==4){
		if(number_hint_a==card_b+1){
			BOT_play_card(0);
			draw_card(hand_player2,0);
			number_hint_a=0;
			card_a_color=8;
			return 0;}
	}
	if(card_b_color==4){
		if(number_hint_b==card_b+1){
			BOT_play_card(1);
			draw_card(hand_player2,1);
			number_hint_b=0;
			card_b_color=8;
			return 0;}
	}
	if(card_c_color==4){
		if(number_hint_c==card_b+1){
			BOT_play_card(2);
			draw_card(hand_player2,2);
			number_hint_c=0;
			card_c_color=8;
			return 0;}
	}
	if(card_d_color==4){
		if(number_hint_d==card_b+1){
			BOT_play_card(3);
			draw_card(hand_player2,3);
			number_hint_d=0;
			card_d_color=8;
			return 0;}
	}
	if(card_e_color==4){
		if(number_hint_e==card_b+1){
			BOT_play_card(4);
			draw_card(hand_player2,4);
			number_hint_e=0;
			card_e_color=8;
			return 0;}
	}
	
	//carta verde
	if(card_a_color==2){
		if(number_hint_a==card_c+1){
			BOT_play_card(0);
			draw_card(hand_player2,0);
			number_hint_a=0;
			card_a_color=8;
			return 0;}
	}
	if(card_b_color==2){
		if(number_hint_b==card_c+1){
			BOT_play_card(1);
			draw_card(hand_player2,1);
			number_hint_b=0;
			card_b_color=8;
			return 0;}
	}
	if(card_c_color==2){
		if(number_hint_c==card_c+1){
			BOT_play_card(2);
			draw_card(hand_player2,2);
			number_hint_c=0;
			card_c_color=8;
			return 0;}
	}
	if(card_d_color==2){
		if(number_hint_d==card_c+1){
			BOT_play_card(3);
			draw_card(hand_player2,3);
			number_hint_d=0;
			card_d_color=8;
			return 0;}
	}
	if(card_e_color==2){
		if(number_hint_e==card_c+1){
			BOT_play_card(4);
			draw_card(hand_player2,4);
			number_hint_e=0;
			card_e_color=8;
			return 0;}
	}
	
	//carta branca
	if(card_a_color==15){
		if(number_hint_a==card_d+1){
			BOT_play_card(0);
			draw_card(hand_player2,0);
			number_hint_a=0;
			card_a_color=8;
			return 0;}
	}
	if(card_b_color==15){
		if(number_hint_b==card_d+1){
			BOT_play_card(1);
			draw_card(hand_player2,1);
			number_hint_b=0;
			card_b_color=8;
			return 0;}
	}
	if(card_c_color==15){
		if(number_hint_c==card_d+1){
			BOT_play_card(2);
			draw_card(hand_player2,2);
			number_hint_c=0;
			card_c_color=8;
			return 0;}
	}
	if(card_d_color==15){
		if(number_hint_d==card_d+1){
			BOT_play_card(3);
			draw_card(hand_player2,3);
			number_hint_d=0;
			card_d_color=8;
			return 0;}
	}
	if(card_e_color==15){
		if(number_hint_e==card_d+1){
			BOT_play_card(4);
			draw_card(hand_player2,4);
			number_hint_e=0;
			card_e_color=8;
			return 0;}
	}
	
	//carta amarela
	if(card_a_color==14){
		if(number_hint_a==card_e+1){
			BOT_play_card(0);
			draw_card(hand_player2,0);
			number_hint_a=0;
			card_a_color=8;
			return 0;}
	}
	if(card_b_color==14){
		if(number_hint_b==card_e+1){
			BOT_play_card(1);
			draw_card(hand_player2,1);
			number_hint_b=0;
			card_b_color=8;
			return 0;}
	}
	if(card_c_color==14){
		if(number_hint_c==card_e+1){
			BOT_play_card(2);
			draw_card(hand_player2,2);
			number_hint_c=0;
			card_c_color=8;
			return 0;}
	}
	if(card_d_color==14){
		if(number_hint_d==card_e+1){
			BOT_play_card(3);
			draw_card(hand_player2,3);
			number_hint_d=0;
			card_d_color=8;
			return 0;}
	}
	if(card_e_color==14){
		if(number_hint_e==card_e+1){
			BOT_play_card(4);
			draw_card(hand_player2,4);
			number_hint_e=0;
			card_e_color=8;
			return 0;}
	}

	
	if(card_a==0 && card_b==0 && card_c==0 && card_d==0 && card_e==0){
		if(number_hint_a==1){
		BOT_play_card(0);
		draw_card(hand_player2,0);
		number_hint_a=0;
		card_a_color=8;	
		return 0;
		}
		
		else if(number_hint_b==1){
		BOT_play_card(1);
		draw_card(hand_player2,1);
		number_hint_b=0;
		card_b_color=8;	
		return 0;	
		}
		
		else if(number_hint_c==1){
		BOT_play_card(2);
		draw_card(hand_player2,2);
		number_hint_c=0;
		card_c_color=8;	
		return 0;
		}
		
		else if(number_hint_d==1){
		BOT_play_card(3);
		draw_card(hand_player2,3);
		number_hint_d=0;
		card_d_color=8;	
		return 0;
		}
		
		else if(number_hint_e==1){
		BOT_play_card(4);
		draw_card(hand_player2,4);
		number_hint_e=0;
		card_e_color=8;	
		return 0;
		}
	}
	
	if((card_a_color == 9 ||card_b_color == 9 ||card_c_color == 9 ||card_d_color == 9 ||card_e_color == 9) && card_a == 5){
		if(card_a_color==9){
		BOT_discard(0);
		return 0;}
		
		if(card_b_color==9){
		BOT_discard(1);
		return 0;}
		
		if(card_c_color==9){
		BOT_discard(2);
		return 0;}
		
		if(card_d_color==9){
		BOT_discard(3);
		return 0;}
		
		if(card_e_color==9){
		BOT_discard(4);
		return 0;}
	}
	
	if((card_a_color == 4 ||card_b_color == 4 ||card_c_color == 4 ||card_d_color == 4 ||card_e_color == 4) && card_b == 5){
		if(card_a_color==4){
		BOT_discard(0);
		return 0;}
		
		if(card_b_color==4){
		BOT_discard(1);
		return 0;}
		
		if(card_c_color==4){
		BOT_discard(2);
		return 0;}
		
		if(card_d_color==4){
		BOT_discard(3);
		return 0;}
		
		if(card_e_color==4){
		BOT_discard(4);
		return 0;}
	}
	
	if((card_a_color == 2 ||card_b_color == 2 ||card_c_color == 2 ||card_d_color == 2 ||card_e_color == 2) && card_c == 5){
		if(card_a_color==2){
		BOT_discard(0);
		return 0;}
		
		if(card_b_color==2){
		BOT_discard(1);
		return 0;}
		
		if(card_c_color==2){
		BOT_discard(2);
		return 0;}
		
		if(card_d_color==2){
		BOT_discard(3);
		return 0;}
		
		if(card_e_color==2){
		BOT_discard(4);
		return 0;}
	}
	
	if((card_a_color == 15 ||card_b_color == 15 ||card_c_color == 15 ||card_d_color == 15 ||card_e_color == 15) && card_d == 5){
		if(card_a_color==15){
		BOT_discard(0);
		return 0;}
		
		if(card_b_color==15){
		BOT_discard(1);
		return 0;}
		
		if(card_c_color==15){
		BOT_discard(2);
		return 0;}
		
		if(card_d_color==15){
		BOT_discard(3);
		return 0;}
		
		if(card_e_color==15){
		BOT_discard(4);
		return 0;}
	}
	
	if((card_a_color == 14 ||card_b_color == 14 ||card_c_color == 14 ||card_d_color == 14 ||card_e_color == 14) && card_e == 5){
		if(card_a_color==14){
		BOT_discard(0);
		return 0;}
		
		if(card_b_color==14){
		BOT_discard(1);
		return 0;}
		
		if(card_c_color==14){
		BOT_discard(2);
		return 0;}
		
		if(card_d_color==14){
		BOT_discard(3);
		return 0;}
		
		if(card_e_color==14){
		BOT_discard(4);
		return 0;}
	}
	
	//carta a
	
	if(number_hint_a <= card_a && card_a_color==9 && number_hint_a != 0){
		BOT_discard(0);
		return 0;
	}
	
	if(number_hint_b <= card_a && card_b_color==9 && number_hint_b != 0){
		BOT_discard(1);
		return 0;
	}
	
	if(number_hint_c <= card_a && card_c_color==9 && number_hint_c != 0){
		BOT_discard(2);
		return 0;
	}
	
	if(number_hint_d <= card_a && card_d_color==9 && number_hint_d != 0){
		BOT_discard(3);
		return 0;
	}
	
	if(number_hint_e <= card_a && card_e_color==9 && number_hint_e != 0){
		BOT_discard(4);
		return 0;
	}
	
	//carta b
	
	if(number_hint_a <= card_b && card_a_color==4 && number_hint_a != 0){
		BOT_discard(0);
		return 0;
	}
	
	if(number_hint_b <= card_b && card_b_color==4 && number_hint_b != 0){
		BOT_discard(1);
		return 0;
	}
	
	if(number_hint_c <= card_b && card_c_color==4 && number_hint_c != 0){
		BOT_discard(2);
		return 0;
	}
	
	if(number_hint_d <= card_b && card_d_color==4 && number_hint_d != 0){
		BOT_discard(3);
		return 0;
	}
	
	if(number_hint_e <= card_b && card_e_color==4 && number_hint_e != 0){
		BOT_discard(4);
		return 0;
	}
	
	//carta c
	
	if(number_hint_a <= card_c && card_a_color==2 && number_hint_a != 0){
		BOT_discard(0);
		return 0;
	}
	
	if(number_hint_b <= card_c && card_b_color==2 && number_hint_b != 0){
		BOT_discard(1);
		return 0;
	}
	
	if(number_hint_c <= card_c && card_c_color==2 && number_hint_c != 0){
		BOT_discard(2);
		return 0;
	}
	
	if(number_hint_d <= card_c && card_d_color==2 && number_hint_d != 0){
		BOT_discard(3);
		return 0;
	}
	
	if(number_hint_e <= card_c && card_e_color==2 && number_hint_e != 0){
		BOT_discard(4);
		return 0;
	}
	
	//carta d
	
	if(number_hint_a <= card_d && card_a_color==15 && number_hint_a != 0){
		BOT_discard(0);
		return 0;
	}
	
	if(number_hint_b <= card_d && card_b_color==15 && number_hint_b != 0){
		BOT_discard(1);
		return 0;
	}
	
	if(number_hint_c <= card_d && card_c_color==15 && number_hint_c != 0){
		BOT_discard(2);
		return 0;
	}
	
	if(number_hint_d <= card_d && card_d_color==15 && number_hint_d != 0){
		BOT_discard(3);
		return 0;
	}
	
	if(number_hint_e <= card_d && card_e_color==15 && number_hint_e != 0){
		BOT_discard(4);
		return 0;
	}
	
	//carta e
	
	if(number_hint_a <= card_e && card_a_color==14 && number_hint_a != 0){
		BOT_discard(0);
		return 0;
	}
	
	if(number_hint_b <= card_e && card_b_color==14 && number_hint_b != 0){
		BOT_discard(1);
		return 0;
	}
	
	if(number_hint_c <= card_e && card_c_color==14 && number_hint_c != 0){
		BOT_discard(2);
		return 0;
	}
	
	if(number_hint_d <= card_e && card_d_color==14 && number_hint_d != 0){
		BOT_discard(3);
		return 0;
	}
	
	if(number_hint_e <= card_e && card_e_color==14 && number_hint_e != 0){
		BOT_discard(4);
		return 0;
	}
	

	
	if(hints>0){
	//carta azul-cor
	if(deckcards[hand_player1[0]][1]==9 || deckcards[hand_player1[1]][1]==9 || deckcards[hand_player1[2]][1]==9 || deckcards[hand_player1[3]][1]==9 || deckcards[hand_player1[4]][1]==9){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_a+1 && deckcards[hand_player1[i]][1] == 9){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][1] == deckcards[hand_player1[i]][1] && j != i)
						aux2++;
				}
				if(aux2==0 && card_color[i] == 8){
				BOT_play_hint(i,0);
				return 0;
			}
		}
		aux2=0;
		}
	}
	
	//carta vermelha-cor
	if(deckcards[hand_player1[0]][1]==4 || deckcards[hand_player1[1]][1]==4 || deckcards[hand_player1[2]][1]==4 || deckcards[hand_player1[3]][1]==4 || deckcards[hand_player1[4]][1]==4){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_b+1 && deckcards[hand_player1[i]][1] == 4){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][1] == deckcards[hand_player1[i]][1] && j != i)
						aux2++;
				}
			if(aux2==0 && card_color[i] == 8){
				BOT_play_hint(i,0);
				return 0;
			}
			}
		aux2=0;
		}
	}
	
	//carta verde-cor
	if(deckcards[hand_player1[0]][1]==2 || deckcards[hand_player1[1]][1]==2 || deckcards[hand_player1[2]][1]==2 || deckcards[hand_player1[3]][1]==2 || deckcards[hand_player1[4]][1]==2){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_c+1 && deckcards[hand_player1[i]][1] == 2){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][1] == deckcards[hand_player1[i]][1] && j != i)
						aux2++;
				}
				if(aux2==0 && card_color[i] == 8){
				BOT_play_hint(i,0);
				return 0;
			}
		}
		aux2=0;
		}
	}
	
	//carta branca-cor
	if(deckcards[hand_player1[0]][1]==15 || deckcards[hand_player1[1]][1]==15 || deckcards[hand_player1[2]][1]==15 || deckcards[hand_player1[3]][1]==15 || deckcards[hand_player1[4]][1]==15){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_d+1 && deckcards[hand_player1[i]][1] == 15){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][1] == deckcards[hand_player1[i]][1] && j != i)
						aux2++;
			}
			if(aux2==0 && card_color[i] == 8){
				BOT_play_hint(i,0);
				return 0;
			}
		}
		aux2=0;
		}
	}
	
	//carta amarela-cor
	if(deckcards[hand_player1[0]][1]==14 || deckcards[hand_player1[1]][1]==14 || deckcards[hand_player1[2]][1]==14 || deckcards[hand_player1[3]][1]==14 || deckcards[hand_player1[4]][1]==14){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_e+1 && deckcards[hand_player1[i]][1] == 14){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][1] == deckcards[hand_player1[i]][1] && j != i)
						aux2++;
			}
			if(aux2==0 && card_color[i] == 8){
				BOT_play_hint(i,0);
				return 0;
			}
		}
		aux2=0;
		}

	}




	//carta azul-numero
	if(deckcards[hand_player1[0]][1]==9 || deckcards[hand_player1[1]][1]==9 || deckcards[hand_player1[2]][1]==9 || deckcards[hand_player1[3]][1]==9 || deckcards[hand_player1[4]][1]==9){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_a+1 && deckcards[hand_player1[i]][1] == 9){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][0] == deckcards[hand_player1[i]][0] && j != i)
						aux2++;
				}
				if(aux2==0 && card_number[i] == 0){
				BOT_play_hint(i,1);
				return 0;
			}
		}
		aux2=0;
		}
	}
	
	//carta vermelha-numero
	if(deckcards[hand_player1[0]][1]==4 || deckcards[hand_player1[1]][1]==4 || deckcards[hand_player1[2]][1]==4 || deckcards[hand_player1[3]][1]==4 || deckcards[hand_player1[4]][1]==4){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_b+1 && deckcards[hand_player1[i]][1] == 4){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][0] == deckcards[hand_player1[i]][0] && j != i)
						aux2++;
				}
				if(aux2==0 && card_number[i] == 0){
				BOT_play_hint(i,1);
				return 0;
			}
		}
		aux2=0;
		}
	}
	
	//carta verde-numero
	if(deckcards[hand_player1[0]][1]==2 || deckcards[hand_player1[1]][1]==2 || deckcards[hand_player1[2]][1]==2 || deckcards[hand_player1[3]][1]==2 || deckcards[hand_player1[4]][1]==2){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_c+1 && deckcards[hand_player1[i]][1] == 2){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][0] == deckcards[hand_player1[i]][0] && j != i)
						aux2++;
				}
				if(aux2==0 && card_number[i] == 0){
				BOT_play_hint(i,1);
				return 0;
			}
		}
		aux2=0;
		}
	}	


	//carta branca-numero
	if(deckcards[hand_player1[0]][1]==15 || deckcards[hand_player1[1]][1]==15 || deckcards[hand_player1[2]][1]==15 || deckcards[hand_player1[3]][1]==15 || deckcards[hand_player1[4]][1]==15){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_d+1 && deckcards[hand_player1[i]][1] == 15){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][0] == deckcards[hand_player1[i]][0] && j != i)
						aux2++;
				}
				if(aux2==0 && card_number[i] == 0){
				BOT_play_hint(i,1);
				return 0;
			}
		}
		aux2=0;
		}
	}
	
	//carta amarela-numero
	if(deckcards[hand_player1[0]][1]==14 || deckcards[hand_player1[1]][1]==14 || deckcards[hand_player1[2]][1]==14 || deckcards[hand_player1[3]][1]==14 || deckcards[hand_player1[4]][1]==14){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_e+1 && deckcards[hand_player1[i]][1] == 14){
				for(j=0;j<5;j++){
					if(deckcards[hand_player1[j]][0] == deckcards[hand_player1[i]][0] && j != i)
						aux2++;
				}
				if(aux2==0 && card_number[i] == 0){
				BOT_play_hint(i,1);
				return 0;
			}
		}
		aux2=0;
		}
	}
	

	
	if(deckcards[hand_player1[0]][1]==9 || deckcards[hand_player1[1]][1]==9 || deckcards[hand_player1[2]][1]==9 || deckcards[hand_player1[3]][1]==9 || deckcards[hand_player1[4]][1]==9){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_a+1 && deckcards[hand_player1[i]][1] == 9){
				if(i==0){
					if(number_hint_ap == 0 && card_ap_color == 8){
						BOT_play_hint(0,rand()%2);
						return 0;
					}
					
					if(number_hint_ap == 0){
						BOT_play_hint(0,1);
						return 0;}
					else if(card_ap_color == 8){
						BOT_play_hint(0,0);
						return 0;}
				}
				
				if(i==1){
					if(number_hint_bp == 0 && card_bp_color == 8){
						BOT_play_hint(1,rand()%2);
						return 0;}
						
					if(number_hint_bp == 0){
						BOT_play_hint(1,1);
						return 0;}
					else if(card_bp_color == 8){
						BOT_play_hint(1,0);
						return 0;}
				}		
				
				if(i==2){
						if(number_hint_cp == 0 && card_cp_color == 8){
						BOT_play_hint(2,rand()%2);
						return 0;
					}
					
					if(number_hint_cp == 0){
						BOT_play_hint(2,1);
						return 0;}
					else if(card_cp_color == 8){
						BOT_play_hint(2,0);
						return 0;}
				}		
				
				if(i==3){
					if(number_hint_dp == 0 && card_dp_color == 8){
						BOT_play_hint(3,rand()%2);
						return 0;
					}
					
					if(number_hint_dp == 0){
						BOT_play_hint(3,1);
						return 0;}
					else if(card_dp_color == 8){
						BOT_play_hint(3,0);
						return 0;}
				}		
				
				if(i==4){
					if(number_hint_ep == 0 && card_ep_color == 8){
						BOT_play_hint(4,rand()%2);
						return 0;
					}
					
					if(number_hint_ep == 0){
						BOT_play_hint(4,1);
						return 0;}
					else if(card_ep_color == 8){
						BOT_play_hint(4,0);
						return 0;}
				}				
	}
}
}


	if(deckcards[hand_player1[0]][1]==4 || deckcards[hand_player1[1]][1]==4 || deckcards[hand_player1[2]][1]==4 || deckcards[hand_player1[3]][1]==9 || deckcards[hand_player1[4]][1]==4){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_b+1 && deckcards[hand_player1[i]][1] == 4){
				if(i==0){
					if(number_hint_ap == 0 && card_ap_color == 8){
						BOT_play_hint(0,rand()%2);
						return 0;
					}
					
					if(number_hint_ap == 0){
						BOT_play_hint(0,1);
						return 0;}
					else if(card_ap_color == 8){
						BOT_play_hint(0,0);
						return 0;}
				}
				
				if(i==1){
					if(number_hint_bp == 0 && card_bp_color == 8){
						BOT_play_hint(1,rand()%2);
						return 0;
					}
					
					if(number_hint_bp == 0){
						BOT_play_hint(1,1);
						return 0;}
					else if(card_bp_color == 8){
						BOT_play_hint(1,0);
						return 0;}
				}		
				
				if(i==2){
					if(number_hint_cp == 0 && card_cp_color == 8){
						BOT_play_hint(2,rand()%2);
						return 0;
					}
					
					if(number_hint_cp == 0){
						BOT_play_hint(2,1);
						return 0;}
					else if(card_cp_color == 8){
						BOT_play_hint(2,0);
						return 0;}
				}		
				
				if(i==3){
					if(number_hint_dp == 0 && card_dp_color == 8){
						BOT_play_hint(3,rand()%2);
						return 0;
					}
					
					if(number_hint_dp == 0){
						BOT_play_hint(3,1);
						return 0;}
					else if(card_dp_color == 8){
						BOT_play_hint(3,0);
						return 0;}
				}		
				
				if(i==4){
					if(number_hint_ep == 0 && card_ep_color == 8){
						BOT_play_hint(4,rand()%2);
						return 0;
					}
					
					if(number_hint_ep == 0){
						BOT_play_hint(4,1);
						return 0;}
					else if(card_ep_color == 8){
						BOT_play_hint(4,0);
						return 0;}
				}				
	}
}
}

	if(deckcards[hand_player1[0]][1]==2 || deckcards[hand_player1[1]][1]==2 || deckcards[hand_player1[2]][1]==2 || deckcards[hand_player1[3]][1]==2 || deckcards[hand_player1[4]][1]==2){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_c+1 && deckcards[hand_player1[i]][1] == 2){
				if(i==0){
					if(number_hint_ap == 0 && card_ap_color == 8){
						BOT_play_hint(0,rand()%2);
						return 0;
					}
					
					if(number_hint_ap == 0){
						BOT_play_hint(0,1);
						return 0;}
					else if(card_ap_color == 8){
						BOT_play_hint(0,0);
						return 0;}
				}
				
				if(i==1){
					if(number_hint_bp == 0 && card_bp_color == 8){
						BOT_play_hint(1,rand()%2);
						return 0;}
						
					if(number_hint_bp == 0){
						BOT_play_hint(1,1);
						return 0;}
					else if(card_bp_color == 8){
						BOT_play_hint(1,0);
						return 0;}
				}		
				
				if(i==2){
						if(number_hint_cp == 0 && card_cp_color == 8){
						BOT_play_hint(2,rand()%2);
						return 0;
					}
					
					if(number_hint_cp == 0){
						BOT_play_hint(2,1);
						return 0;}
					else if(card_cp_color == 8){
						BOT_play_hint(2,0);
						return 0;}
				}		
				
				if(i==3){
					if(number_hint_dp == 0 && card_dp_color == 8){
						BOT_play_hint(3,rand()%2);
						return 0;
					}
					
					if(number_hint_dp == 0){
						BOT_play_hint(3,1);
						return 0;}
					else if(card_dp_color == 8){
						BOT_play_hint(3,0);
						return 0;}
				}		
				
				if(i==4){
					if(number_hint_ep == 0 && card_ep_color == 8){
						BOT_play_hint(4,rand()%2);
						return 0;
					}
					
					if(number_hint_ep == 0){
						BOT_play_hint(4,1);
						return 0;}
					else if(card_ep_color == 8){
						BOT_play_hint(4,0);
						return 0;}
				}				
	}
}
}

	if(deckcards[hand_player1[0]][1]==15 || deckcards[hand_player1[1]][1]==15 || deckcards[hand_player1[2]][1]==15 || deckcards[hand_player1[3]][1]==15 || deckcards[hand_player1[4]][1]==15){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_d+1 && deckcards[hand_player1[i]][1] == 15){
				if(i==0){
					if(number_hint_ap == 0 && card_ap_color == 8){
						BOT_play_hint(0,rand()%2);
						return 0;
					}
					
					if(number_hint_ap == 0){
						BOT_play_hint(0,1);
						return 0;}
					else if(card_ap_color == 8){
						BOT_play_hint(0,0);
						return 0;}
				}
				
				if(i==1){
					if(number_hint_bp == 0 && card_bp_color == 8){
						BOT_play_hint(1,rand()%2);
						return 0;}
						
					if(number_hint_bp == 0){
						BOT_play_hint(1,1);
						return 0;}
					else if(card_bp_color == 8){
						BOT_play_hint(1,0);
						return 0;}
				}		
				
				if(i==2){
						if(number_hint_cp == 0 && card_cp_color == 8){
						BOT_play_hint(2,rand()%2);
						return 0;
					}
					
					if(number_hint_cp == 0){
						BOT_play_hint(2,1);
						return 0;}
					else if(card_cp_color == 8){
						BOT_play_hint(2,0);
						return 0;}
				}		
				
				if(i==3){
					if(number_hint_dp == 0 && card_dp_color == 8){
						BOT_play_hint(3,rand()%2);
						return 0;
					}
					
					if(number_hint_dp == 0){
						BOT_play_hint(3,1);
						return 0;}
					else if(card_dp_color == 8){
						BOT_play_hint(3,0);
						return 0;}
				}		
				
				if(i==4){
					if(number_hint_ep == 0 && card_ep_color == 8){
						BOT_play_hint(4,rand()%2);
						return 0;
					}
					
					if(number_hint_ep == 0){
						BOT_play_hint(4,1);
						return 0;}
					else if(card_ep_color == 8){
						BOT_play_hint(4,0);
						return 0;}
				}				
	}
}
}

	if(deckcards[hand_player1[0]][1]==14 || deckcards[hand_player1[1]][1]==14 || deckcards[hand_player1[2]][1]==14 || deckcards[hand_player1[3]][1]==14 || deckcards[hand_player1[4]][1]==14){
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] == card_e+1 && deckcards[hand_player1[i]][1] == 14){
				if(i==0){
					if(number_hint_ap == 0 && card_ap_color == 8){
						BOT_play_hint(0,rand()%2);
						return 0;
					}
					
					if(number_hint_ap == 0){
						BOT_play_hint(0,1);
						return 0;}
					else if(card_ap_color == 8){
						BOT_play_hint(0,0);
						return 0;}
				}
				
				if(i==1){
					if(number_hint_bp == 0 && card_bp_color == 8){
						BOT_play_hint(1,rand()%2);
						return 0;}
						
					if(number_hint_bp == 0){
						BOT_play_hint(1,1);
						return 0;}
					else if(card_bp_color == 8){
						BOT_play_hint(1,0);
						return 0;}
				}		
				
				if(i==2){
						if(number_hint_cp == 0 && card_cp_color == 8){
						BOT_play_hint(2,rand()%2);
						return 0;
					}
					
					if(number_hint_cp == 0){
						BOT_play_hint(2,1);
						return 0;}
					else if(card_cp_color == 8){
						BOT_play_hint(2,0);
						return 0;}
				}		
				
				if(i==3){
					if(number_hint_dp == 0 && card_dp_color == 8){
						BOT_play_hint(3,rand()%2);
						return 0;
					}
					
					if(number_hint_dp == 0){
						BOT_play_hint(3,1);
						return 0;}
					else if(card_dp_color == 8){
						BOT_play_hint(3,0);
						return 0;}
				}		
				
				if(i==4){
					if(number_hint_ep == 0 && card_ep_color == 8){
						BOT_play_hint(4,rand()%2);
						return 0;
					}
					
					if(number_hint_ep == 0){
						BOT_play_hint(4,1);
						return 0;}
					else if(card_ep_color == 8){
						BOT_play_hint(4,0);
						return 0;}
				}				
	}
}
}
int min=100;

	if(number_hint_ap == 0 || number_hint_bp == 0 || number_hint_cp == 0 || number_hint_dp == 0 || number_hint_ep == 0){
		
		for(i=0;i<5;i++){
			if(deckcards[hand_player1[i]][0] < min)	
				min=deckcards[hand_player1[i]][0];
		}
		
		while(1==1){
		
		if(deckcards[hand_player1[0]][0] == min && number_hint_ap == 0){
				BOT_play_hint(0,1);	
				return 0;}
			
		if(deckcards[hand_player1[1]][0] == min && number_hint_bp == 0){
				BOT_play_hint(1,1);	
				return 0;}
		
		if(deckcards[hand_player1[2]][0] == min && number_hint_cp == 0){
				BOT_play_hint(2,1);	
				return 0;}
		
		if(deckcards[hand_player1[3]][0] == min && number_hint_dp == 0){
				BOT_play_hint(3,1);	
				return 0;}
				
		if(deckcards[hand_player1[4]][0] == min && number_hint_ep == 0){
				BOT_play_hint(4,1);	
				return 0;}
		
		min++;
}
	}
	
	else if(card_ap_color == 8 || card_bp_color == 8 || card_cp_color == 8 || card_dp_color == 8 || card_ep_color == 8){
		while(1==1){

int rand_color = rand()%5;
		
		if(rand_color == 0){
			if(card_ap_color != 8){
				BOT_play_hint(0,0);
				return 0;
			}
		}
		
		if(rand_color == 1){
			if(card_bp_color != 8){
				BOT_play_hint(1,0);
				return 0;
			}
		}
		
		if(rand_color == 2){
			if(card_cp_color != 8){
				BOT_play_hint(2,0);
				return 0;
			}
		}
		
		if(rand_color == 3){
			if(card_dp_color != 8){
				BOT_play_hint(3,0);
				return 0;
			}
		}
		
		if(rand_color == 4){
			if(card_ep_color != 8){
				BOT_play_hint(4,0);
				return 0;
			}
		}
	}
}
	
	
}
	if(card_a>0 && card_b>0 && card_c>0 && card_d>0 && card_e>0){
		
		if(number_hint_a == 1){
			BOT_discard(0);
			return 0;
		}
		
		else if(number_hint_a == 1){
			BOT_discard(0);
			return 0;
		}
		
		else if(number_hint_b == 1){
			BOT_discard(1);
			return 0;
		}
		
		else if(number_hint_c == 1){
			BOT_discard(2);
			return 0;
		}
		
		else if(number_hint_d == 1){
			BOT_discard(3);
			return 0;
		}
		
		else if(number_hint_e == 1){
			BOT_discard(4);
			return 0;
		}
	}
	

	if((card_a_color==8 && number_hint_a==0) || (card_b_color==8 && number_hint_b==0) || (card_c_color==8 && number_hint_c==0) || (card_d_color==8 && number_hint_d==0) || (card_e_color==8 && number_hint_e==0)){
		
		if(card_a_color == 8 && number_hint_a == 0){
			BOT_discard(0);
			return 0;
		}
		
		if(card_b_color == 8 && number_hint_b == 0){
			BOT_discard(1);
			return 0;
		}
		
		if(card_c_color == 8 && number_hint_c == 0){
			BOT_discard(2);
			return 0;
		}
		
		if(card_d_color == 8 && number_hint_d == 0){
			BOT_discard(3);
			return 0;
		}
		
		if(card_e_color == 8 && number_hint_e == 0){
			BOT_discard(4);
			return 0;
		}
	}
	
	if(card_a_color == 8 || card_b_color == 8 || card_c_color == 8 || card_d_color == 8 || card_e_color == 8){
		
	int	min = 100;
		
		if(number_hint_a<min && card_a_color==8)
			min=number_hint_a;
		if(number_hint_b<min && card_b_color==8)
			min=number_hint_b;
		if(number_hint_c<min && card_c_color==8)
			min=number_hint_c;
		if(number_hint_d<min && card_d_color==8)
			min=number_hint_d;
		if(number_hint_e<min && card_e_color==8)
			min=number_hint_e;
			
		if(min==number_hint_a && card_a_color==8){
			BOT_discard(0);
			return 0;}
		
		if(min==number_hint_b && card_b_color==8){
			BOT_discard(1);
			return 0;}
		
		if(min==number_hint_c && card_c_color==8){
			BOT_discard(2);
			return 0;}
		
		if(min==number_hint_d && card_d_color==8){
			BOT_discard(3);
			return 0;}
		
		if(min==number_hint_e && card_e_color==8){
			BOT_discard(4);
			return 0;}
		
	}
	
	if(card_a_color==8 || number_hint_a==0 || card_b_color==8 || number_hint_b==0 || card_c_color==8 || number_hint_c==0 || card_d_color==8 || number_hint_d==0 || card_e_color==8 || number_hint_e==0){
		
		if(card_a_color==8 || number_hint_a==0){
			BOT_discard(0);
			return 0;
		}
		
		if(card_b_color==8 || number_hint_b==0){
			BOT_discard(1);
			return 0;
		}
		
		if(card_c_color==8 || number_hint_c==0){
			BOT_discard(2);
			return 0;
		}
		
		if(card_d_color==8 || number_hint_d==0){
			BOT_discard(3);
			return 0;
		}
		
		if(card_e_color==8 || number_hint_e==0){
			BOT_discard(4);
			return 0;
		}
	}
	
	else{
		BOT_discard(rand()%5);
		return 0;
	}
		
	}

void BOT_play_card(int card_number){
	int i;
	int aux,a;
	int c_a,c_b,c_c,c_d,c_e;
	c_a=card_a;
	c_b=card_b;
	c_c=card_c;
	c_d=card_d;	
	c_e=card_e;
	
		switch (deckcards[hand_player2[card_number]][1]){
		
		case 9:
			gotoxy(20,12);
			printf("The BOT will play the Blue %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
		
		case 4:
			gotoxy(20,12);
			printf("The BOT will play the Red %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
			
		case 2:
			gotoxy(20,12);
			printf("The BOT will play the Green %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
		
		case 15:
			gotoxy(20,12);
			printf("The BOT will play the White %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
		
		case 14:
			gotoxy(20,12);
			printf("The BOT will play the Yellow %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
	}
		
		//ciclo para verificar qual o numero da carta jogada
		for(i=0;i<16;i++){
			if(deckcards[hand_player2[card_number]][1] == i){
				aux = i;
				break;}
	}
	
	//verifica a cor da carta jogada e se a carta jogada esta certa senao tira uma vida
	if(aux==9){
		if(deckcards[hand_player2[card_number]][0]==(c_a+1)){
		card_a++;}	
		else
			lives--;
	}
	
	if(aux==4){
		if(deckcards[hand_player2[card_number]][0]==(c_b+1)){
		card_b++;}	
		else
			lives--;
	}
	
	if(aux==2){
		if(deckcards[hand_player2[card_number]][0]==(c_c+1)){
		card_c++;}	
		else
			lives--;
	}
	
	if(aux==15){
		if(deckcards[hand_player2[card_number]][0]==(c_d+1)){
		card_d++;}	
		else
			lives--;
	}
	
	if(aux==14){
		if(deckcards[hand_player2[card_number]][0]==(c_e+1)){
		card_e++;}	
		else
			lives--;
	}
	
	

		
}	

void BOT_play_hint(int card_number,int choice){
	
	//coloca a cor da carta escolhida na sua cor e verifica se existe mais alguma da mesma cor e coloca-a tambem da sua cor
	if(choice==0){
		if(card_number==0){
			card_ap_color=deckcards[hand_player1[0]][1];
		
			if(deckcards[hand_player1[1]][1]==deckcards[hand_player1[0]][1])
			card_bp_color=deckcards[hand_player1[0]][1];
		
			if(deckcards[hand_player1[2]][1]==deckcards[hand_player1[0]][1])
			card_cp_color=deckcards[hand_player1[0]][1];
			
			if(deckcards[hand_player1[3]][1]==deckcards[hand_player1[0]][1])
			card_dp_color=deckcards[hand_player1[0]][1];
			
			if(deckcards[hand_player1[4]][1]==deckcards[hand_player1[0]][1])
			card_ep_color=deckcards[hand_player1[0]][1];}
			
		
		if(card_number==1){
			card_bp_color=deckcards[hand_player1[1]][1];
		
			if(deckcards[hand_player1[0]][1]==deckcards[hand_player1[1]][1])
			card_ap_color=deckcards[hand_player1[1]][1];
		
			if(deckcards[hand_player1[2]][1]==deckcards[hand_player1[1]][1])
			card_cp_color=deckcards[hand_player1[1]][1];
			
			if(deckcards[hand_player1[3]][1]==deckcards[hand_player1[1]][1])
			card_dp_color=deckcards[hand_player1[1]][1];
			
			if(deckcards[hand_player1[4]][1]==deckcards[hand_player1[1]][1])
			card_ep_color=deckcards[hand_player1[1]][1];}
			
		
		if(card_number==2){
			card_cp_color=deckcards[hand_player1[2]][1];
		
			if(deckcards[hand_player1[0]][1]==deckcards[hand_player1[2]][1])
			card_ap_color=deckcards[hand_player1[2]][1];
		
			if(deckcards[hand_player1[1]][1]==deckcards[hand_player1[2]][1])
			card_bp_color=deckcards[hand_player1[2]][1];
			
			if(deckcards[hand_player1[3]][1]==deckcards[hand_player1[2]][1])
			card_dp_color=deckcards[hand_player1[2]][1];
			
			if(deckcards[hand_player1[4]][1]==deckcards[hand_player1[2]][1])
			card_ep_color=deckcards[hand_player1[2]][1];}
			
			
		if(card_number==3){
			card_dp_color=deckcards[hand_player1[3]][1];
		
			if(deckcards[hand_player1[0]][1]==deckcards[hand_player1[3]][1])
			card_ap_color=deckcards[hand_player1[3]][1];
		
			if(deckcards[hand_player1[1]][1]==deckcards[hand_player1[3]][1])
			card_bp_color=deckcards[hand_player1[3]][1];
			
			if(deckcards[hand_player1[2]][1]==deckcards[hand_player1[3]][1])
			card_cp_color=deckcards[hand_player1[3]][1];
			
			if(deckcards[hand_player1[4]][1]==deckcards[hand_player1[3]][1])
			card_ep_color=deckcards[hand_player1[3]][1];}
		
			
		if(card_number==4){
			card_ep_color=deckcards[hand_player1[4]][1];
		
			if(deckcards[hand_player1[0]][1]==deckcards[hand_player1[4]][1])
			card_ap_color=deckcards[hand_player1[4]][1];
		
			if(deckcards[hand_player1[2]][1]==deckcards[hand_player1[4]][1])
			card_cp_color=deckcards[hand_player1[4]][1];
			
			if(deckcards[hand_player1[3]][1]==deckcards[hand_player1[4]][1])
			card_dp_color=deckcards[hand_player1[4]][1];
			
			if(deckcards[hand_player1[1]][1]==deckcards[hand_player1[4]][1])
			card_bp_color=deckcards[hand_player1[4]][1];}
	}
	
	//coloca o numero da carta escolhida no seu numero e verifica se existe mais alguma com o mesmo numero e coloca-a tambem no seu numero
	else if(choice==1){
		if(card_number==0){
			number_hint_ap=deckcards[hand_player1[0]][0];
		
			if(deckcards[hand_player1[1]][0]==deckcards[hand_player1[0]][0])
			number_hint_bp=deckcards[hand_player1[0]][0];
		
			if(deckcards[hand_player1[2]][0]==deckcards[hand_player1[0]][0])
			number_hint_cp=deckcards[hand_player1[0]][0];
			
			if(deckcards[hand_player1[3]][0]==deckcards[hand_player1[0]][0])
			number_hint_dp=deckcards[hand_player1[0]][0];
			
			if(deckcards[hand_player1[4]][0]==deckcards[hand_player1[0]][0])
			number_hint_ep=deckcards[hand_player1[0]][0];}
			
		if(card_number==1){
			number_hint_bp=deckcards[hand_player1[1]][0];
		
			if(deckcards[hand_player1[0]][0]==deckcards[hand_player1[1]][0])
			number_hint_ap=deckcards[hand_player1[1]][0];
		
			if(deckcards[hand_player1[2]][0]==deckcards[hand_player1[1]][0])
			number_hint_cp=deckcards[hand_player1[1]][0];
			
			if(deckcards[hand_player1[3]][0]==deckcards[hand_player1[1]][0])
			number_hint_dp=deckcards[hand_player1[1]][0];
			
			if(deckcards[hand_player1[4]][0]==deckcards[hand_player1[1]][0])
			number_hint_ep=deckcards[hand_player1[1]][0];}
			
		if(card_number==2){
			number_hint_cp=deckcards[hand_player1[2]][0];
		
			if(deckcards[hand_player1[1]][0]==deckcards[hand_player1[2]][0])
			number_hint_bp=deckcards[hand_player1[2]][0];
		
			if(deckcards[hand_player1[0]][0]==deckcards[hand_player1[2]][0])
			number_hint_ap=deckcards[hand_player1[2]][0];
			
			if(deckcards[hand_player1[3]][0]==deckcards[hand_player1[2]][0])
			number_hint_dp=deckcards[hand_player1[2]][0];
			
			if(deckcards[hand_player1[4]][0]==deckcards[hand_player1[2]][0])
			number_hint_ep=deckcards[hand_player1[2]][0];}
			
		if(card_number==3){
			number_hint_dp=deckcards[hand_player1[3]][0];
		
			if(deckcards[hand_player1[1]][0]==deckcards[hand_player1[3]][0])
			number_hint_bp=deckcards[hand_player1[3]][0];
		
			if(deckcards[hand_player1[2]][0]==deckcards[hand_player1[3]][0])
			number_hint_cp=deckcards[hand_player1[3]][0];
			
			if(deckcards[hand_player1[0]][0]==deckcards[hand_player1[3]][0])
			number_hint_ap=deckcards[hand_player1[3]][0];
			
			if(deckcards[hand_player1[4]][0]==deckcards[hand_player1[3]][0])
			number_hint_ep=deckcards[hand_player1[3]][0];}
			
		if(card_number==4){
			number_hint_ep=deckcards[hand_player1[4]][0];
		
			if(deckcards[hand_player1[1]][0]==deckcards[hand_player1[4]][0])
			number_hint_bp=deckcards[hand_player1[4]][0];
		
			if(deckcards[hand_player1[2]][0]==deckcards[hand_player1[4]][0])
			number_hint_cp=deckcards[hand_player1[4]][0];
			
			if(deckcards[hand_player1[3]][0]==deckcards[hand_player1[4]][0])
			number_hint_dp=deckcards[hand_player1[4]][0];
			
			if(deckcards[hand_player1[0]][0]==deckcards[hand_player1[4]][0])
			number_hint_ap=deckcards[hand_player1[4]][0];}
		}
		
	//retita uma dica
	hints--;	
}

void BOT_discard(int card_number){
	int i;
	
		switch (deckcards[hand_player2[card_number]][1]){
		
		case 9:
			gotoxy(20,12);
			printf("The BOT will discard the Blue %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
		
		case 4:
			gotoxy(20,12);
			printf("The BOT will discard the Red %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
			
		case 2:
			gotoxy(20,12);
			printf("The BOT will discard the Green %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
		
		case 15:
			gotoxy(20,12);
			printf("The BOT will discard the White %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
		
		case 14:
			gotoxy(20,12);
			printf("The BOT will discard the Yellow %d!",deckcards[hand_player2[card_number]][0]);
			getch();
			break;
	}
	
	//verifica o numero e a cor da carta discartada e adiciona 1 á matriz no lugar apropiado
	for(i=0;i<5;i++){
	if(deckcards[hand_player2[card_number]][0]==i+1 && deckcards[hand_player2[card_number]][1]==9){
		cards_discard[i][0]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player2[card_number]][0]==i+1 && deckcards[hand_player2[card_number]][1]==4){
		cards_discard[i][1]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player2[card_number]][0]==i+1 && deckcards[hand_player2[card_number]][1]==2){
		cards_discard[i][2]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player2[card_number]][0]==i+1 && deckcards[hand_player2[card_number]][1]==15){
		cards_discard[i][3]++;
	}
}

	for(i=0;i<5;i++){
	if(deckcards[hand_player2[card_number]][0]==i+1 && deckcards[hand_player2[card_number]][1]==14){
		cards_discard[i][4]++;
	}
}
	
	
	draw_card(hand_player2,card_number);
		hints++;
	
	if(card_number==0){
		card_a_color=8;
		number_hint_a=0;
	}
	
	if(card_number==1){
		card_b_color=8;
		number_hint_b=0;
	}	
	
	if(card_number==2){
		card_c_color=8;
		number_hint_c=0;
	}	
	
	if(card_number==3){
		card_d_color=8;
		number_hint_d=0;
	}	
	
	if(card_number==4){
		card_e_color=8;
		number_hint_e=0;
}


}




