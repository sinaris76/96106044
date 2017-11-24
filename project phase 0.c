#include <stdio.h>
#include <stdlib.h>

int pacplace(int *PacNowX, int *PacNowY, int PacDir,char plan[100][100],int line, int column){
	int y=*PacNowY,x=*PacNowX, flag1=0;
		if(PacDir==1){
			*PacNowX=*PacNowX-1;
			if(*PacNowX<0)
			*PacNowX=line-1;}
		if(PacDir==2){
			*PacNowY=*PacNowY+1;
			if(*PacNowY>column-1)
			*PacNowY=0;}
		if(PacDir== 3){
			*PacNowX=*PacNowX+1;
			if(*PacNowX>line-1)
			*PacNowX=0;}
		if(PacDir==4){
			*PacNowY=*PacNowY-1;
			if(*PacNowY<0)
			*PacNowY=column-1;}
		if(plan[*PacNowY][*PacNowX]=='#'){
			*PacNowY=y;	
			*PacNowX=x;
			flag1=1;}
	return flag1;
}
int pacpoints(int *points,int* heart,int PacNowX, int PacNowY, char plan[100][100], int PinkyNowX,int PinkyNowY,int PinkyType, int BlinkyNowX,int BlinkyNowY,int BlinkyType,int InkyNowX,int InkyNowY,int InkyType,int ClydeNowX,int ClydeNowY,int ClydeType){
	int flag=0;
	if (plan[PacNowX][PacNowY]=='*'){
		*points=*points+1;
		plan[PacNowX][PacNowY]='_';}
		
	if (plan[PacNowX][PacNowY]=='^'){
		*points=*points+20;
		plan[PacNowX][PacNowY]='_';}
		
	if (plan[PacNowX][PacNowY]=='O'){
		*points=*points+50;
		plan[PacNowX][PacNowY]='_';}
		
	if(PacNowX==BlinkyNowX && PacNowY==BlinkyNowY){
		if(BlinkyType){
		*heart=*heart-1;
		flag=1;}
		else
		*points=*points+50;}
	if(PacNowX==PinkyNowX && PacNowY==PinkyNowY){
		if(PinkyType){
		*heart=*heart-1;
		flag=1;}
		else
		*points=*points+50;}
	if(PacNowX==InkyNowX && PacNowY==InkyNowY){
		if(InkyType){
		*heart=*heart-1;
		flag=1;}
		else
		*points=*points+50;}
	if(PacNowX==ClydeNowX && PacNowY==ClydeNowY){
		if(ClydeType){
		*heart=*heart-1;
		flag=1;}
		else
		*points=*points+50;}
		return flag;
}

int winning(int heart, char plan[100][100], int line , int column){
	int win,i,j;
	if(heart==0)
		win=0;
	else{
		for(i=0;i<line;i++){
			for(j=0;j<column;j++){
				if(plan[i][j]=='O'|| plan[i][j]=='*'){
				win=0;
				return win;}		
			}}
			win=1;}
	return win;
}

int main() {
	int line,column,minute,second, points, heart,PacDir,PacStartX,PacStartY,PacNowX,PacNowY,BlinkyDir,BlinkyStartX,BlinkyStartY,BlinkyNowX,BlinkyNowY,BlinkyType,BlinkyTime;
	
	int PinkyDir,PinkyStartX,PinkyStartY,PinkyNowX,PinkyNowY,PinkyType,PinkyTime,InkyDir,InkyStartX,InkyStartY,InkyNowX,InkyNowY,InkyType,InkyTime,ClydeDir,ClydeStartX,ClydeStartY,ClydeNowX,ClydeNowY,ClydeType,ClydeTime;
	
	char plan[100][100];
	
	int i,j,flag,flag1,win;
	
	scanf("%d %d\n",&line,&column);
	
	for(i=0 ; i<line ; i++){
		for(j=0 ; j<column ; j++){
			scanf("%c",&plan[i][j]);
		}
		scanf("\n");}
		
	scanf("%d:%d %d",&minute,&second,&points);
	scanf("\n");
	scanf("pacman: %d %d (%d,%d) (%d,%d)",&PacDir,&heart,&PacStartX,&PacStartY,&PacNowX,&PacNowY);
	scanf("\n");
	scanf("blinky: %d %d ",&BlinkyDir,&BlinkyType);
	if(BlinkyType==0)
		scanf("%d ",&BlinkyTime);
	scanf("(%d,%d) (%d,%d)",&BlinkyStartX,&BlinkyStartY,&BlinkyNowX,&BlinkyNowY);
	scanf("\n");
	scanf("pinky: %d %d ",&PinkyDir,&PinkyType);
	if(PinkyType==0)
		scanf("%d ",&PinkyTime);
	scanf("(%d,%d) (%d,%d)",&PinkyStartX,&PinkyStartY,&PinkyNowX,&PinkyNowY);
	scanf("\n");
	scanf("clyde: %d %d ",&ClydeDir,&ClydeType);
	if(ClydeType==0)
		scanf("%d ",&ClydeTime);
	scanf("(%d,%d) (%d,%d)",&ClydeStartX,&ClydeStartY,&ClydeNowX,&ClydeNowY);
	scanf("\n");
	scanf("inky: %d %d ",&InkyDir,&InkyType);
	if(InkyType==0)
		scanf("%d ",&InkyTime);
	scanf("(%d,%d) (%d,%d)",&InkyStartX,&InkyStartY,&InkyNowX,&InkyNowY);
		
   flag1=pacplace(&PacNowX,&PacNowY,PacDir,plan,line,column);
   if (flag1==0){
   flag=pacpoints(&points, &heart,PacNowX,PacNowY,plan,PinkyNowX,PinkyNowY,PinkyType,BlinkyNowX,BlinkyNowY,BlinkyType,InkyNowX,InkyNowY,InkyType,ClydeNowX,ClydeNowY,ClydeType);
	if(flag==1 && heart!=0){
		PacNowX=PacStartX;
		PacNowY=PacStartY;
	}}
	win=winning(heart,plan,line,column);
	
printf("(%d,%d)\n",PacNowX,PacNowY);
printf("%d\n",points);

if(win)
printf("Yes");
else
printf("No");
	return 0;
}
