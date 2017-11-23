#include <stdio.h>
#include <stdlib.h>

int main() {
	int line,column,minute,second, points, heart,PacDir,PacStartX,PacStartY,PacNowX,PacNowY,BlinkyDir,BlinkyStartX,BlinkyStartY,BlinkyNowX,BlinkyNowY,BlinkyType;
	
	int PinkyDir,PinkyStartX,PinkyStartY,PinkyNowX,PinkyNowY,PinkyType,InkyDir,InkyStartX,InkyStartY,InkyNowX,InkyNowY,InkyType,ClydeDir,ClydeStartX,ClydeStartY,ClydeNowX,ClydeNowY,ClydeType;
	
	char plan[100][100];
	
	int i,j;
	
	scanf("%d %d\n",&line,&column);
	
	for(i=0 ; i<line ; i++){
		for(j=0 ; j<column ; j++){
			scanf("%c",&plan[line][column]);
		}
		scanf("\n");}
		
	scanf("%d:%d %d",&minute,&second,&points);
	scanf("\n");
	scanf("pacman: %d %d (%d,%d) (%d,%d)",&PacDir,&heart,&PacStartX,&PacStartY,&PacNowX,&PacNowY);
	scanf("\n");
	scanf("blinky: %d %d (%d,%d) (%d,%d)",&BlinkyDir,&BlinkyType,&BlinkyStartX,&BlinkyStartY,&BlinkyNowX,&BlinkyNowY);
	scanf("\n");
	scanf("pinky: %d %d (%d,%d) (%d,%d)",&PinkyDir,&PinkyType,&PinkyStartX,&PinkyStartY,&PinkyNowX,&PinkyNowY);
	scanf("\n");
	scanf("clyde: %d %d (%d,%d) (%d,%d)",&ClydeDir,&ClydeType,&ClydeStartX,&ClydeStartY,&ClydeNowX,&ClydeNowY);
	scanf("\n");
	scanf("inky: %d %d (%d,%d) (%d,%d)",&InkyDir,&InkyType,&InkyStartX,&InkyStartY,&InkyNowX,&InkyNowY);
		

	return 0;
}
