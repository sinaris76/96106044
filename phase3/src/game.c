#include "game.h"
#include "map.h"
#include <stdio.h>
#include <math.h>

void initiateGame(char* filename, Map* outMap, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    FILE *file;
    int i,j,temp;
    long long unsigned int temp2;
    char enter;
    outGame->cheeses=0;
    outGame->cherries=0;
    outGame->pineapples=0;
    outGame->ghosts=MAX_GHOST_COUNT;
    file =fopen(filename,"r");
    fscanf(file,"%d",&outMap->height);
    fscanf(file,"%d",&outMap->width);
    fscanf(file,"\n");
    for(j=0;j<outMap->height;j++) {
        for (i= 0; i < outMap->width; i++) {
            fscanf(file, "%c", &outMap->cells[i][j]);
            if (outMap->cells[i][j] == CELL_CHEESE)
                outGame->cheeses++;
            if (outMap->cells[i][j] == CELL_CHERRY)
                outGame->cherries++;
            if (outMap->cells[i][j] == CELL_PINEAPPLE)
                outGame->pineapples++;
        }
        fscanf(file,"%c",&enter);
    }
    fscanf(file,"%d",&outGame->score);
    fscanf(file,"%*s %d",&outPacman->dir);
    fscanf(file,"%d",&outPacman->health);
    fscanf(file," (%d,%d)",&outPacman->startY,&outPacman->startX);
    fscanf(file," (%lf,%lf)",&outPacman->y,&outPacman->x);
    outPacman->speed=2;

    for(i=0;i<4;i++) {
        outGhosts[i].speed=2;
        fscanf(file,"%*s");
        outGhosts[i].type=i;
        fscanf(file, "%d", &outGhosts[i].dir);
        fscanf(file, " %d", &temp);
        if(temp==0)
            outGhosts[i].blue=true;
        else
            outGhosts[i].blue=false;
        if(outGhosts[i].blue){
            fscanf(file," %llu",&temp2);
            outGhosts[i].blueCounterDown=temp2*CYCLES_PER_SEC;
        }
        fscanf(file," (%d,%d)",&outGhosts[i].startY,&outGhosts[i].startX);

        fscanf(file," (%lf,%lf)",&outGhosts[i].y,&outGhosts[i].x);

    }

}

void checkEatables(Map* map, Game* outGame, Pacman* outPacman, Ghost* outGhosts) {
    double nextplaceX=0;
    double nextplaceY=0;
    int flag, flag2=0,i;
    if(outPacman->dir==2 ){
     nextplaceX= floor(outPacman->x)+1 ;
     flag=0;}
    if(outPacman->dir==4){
     nextplaceX= floor(outPacman->x);
     flag=0;}
    if(outPacman->dir==3){
        nextplaceY= floor(outPacman->y) + 1;
        flag=1;}
    if(outPacman->dir==1){
        nextplaceY= floor(outPacman->y);
        flag=1;}
    if(outPacman->dir==-1){
        return;
    }
    if(!flag){
    if((fabs(outPacman->x-nextplaceX)<0.5)){
        if(nextplaceX==map->width)
            nextplaceX=0;
        if (map->cells[(int)nextplaceX][(int)outPacman->y]==CELL_CHEESE){
            outGame->cheeses--;
            outGame->score+=CHEESE_SCORE;
            map->cells[(int)nextplaceX][(int)outPacman->y]=CELL_EMPTY;}

        if (map->cells[(int)nextplaceX][(int)outPacman->y]== CELL_CHERRY){
            outGame->cherries--;
            outGame->score=outGame->score+=CHERRY_SCORE;
            map->cells[(int)nextplaceX][(int)outPacman->y]=CELL_EMPTY;}

        if (map->cells[(int)nextplaceX][(int)outPacman->y]==CELL_PINEAPPLE){
            outGame->pineapples--;
            outGame->score=outGame->score+=PINEAPPLE_SCORE;
            map->cells[(int)nextplaceX][(int)outPacman->y]=CELL_EMPTY;
            for(i=0;i<4;i++){
                outGhosts[i].blueCounterDown=BLUE_DURATION;
                outGhosts[i].blue=true;
            }

    }}}
    else{
        if((fabs(outPacman->y-nextplaceY)<0.5 )){
            if(nextplaceY==map->height)
                nextplaceY=0;
            if (map->cells[(int)outPacman->x][(int)nextplaceY]==CELL_CHEESE){
                outGame->cheeses--;
                outGame->score+=CHEESE_SCORE;
                map->cells[(int)outPacman->x][(int)nextplaceY]=CELL_EMPTY;}

            if (map->cells[(int)outPacman->x][(int)nextplaceY]== CELL_CHERRY){
                outGame->cherries--;
                outGame->score=outGame->score+=CHERRY_SCORE;
                map->cells[(int)outPacman->x][(int)nextplaceY]=CELL_EMPTY;}

            if (map->cells[(int)outPacman->x][(int)nextplaceY]==CELL_PINEAPPLE){
                outGame->pineapples--;
                outGame->score=outGame->score+=PINEAPPLE_SCORE;
                map->cells[(int)outPacman->x][(int)nextplaceY]=CELL_EMPTY;
                for(i=0;i<4;i++){
                        outGhosts[i].blueCounterDown=BLUE_DURATION;
                        outGhosts[i].blue=true;
                }
        }}
}}

void checkGhostCollision(Pacman* outPacman, Ghost* outGhost) {
    if(fabs((outPacman->y)-(outGhost->y))<0.5 && fabs((outPacman->x)-(outGhost->x))<0.5){
        if(outGhost->blue){
            outGhost->y=outGhost->startY;
            outGhost->x=outGhost->startX;
            outGhost->blue=false;
        }
        else{
            outPacman->x=outPacman->startX;
            outPacman->y=outPacman->startY;
            outPacman->health--;
        }
    }
}

bool isGameFinished(Game* game, Pacman* pacman) {
    if(game->pineapples==0 && game->cheeses==0)
        return 1;
    else if(pacman->health==0)
        return 1;
    else
        return 0;
}

void checkGhostState(Ghost* ghost) {
 if(ghost->blue==true){
     ghost->blueCounterDown=ghost->blueCounterDown-1;
     if(ghost->blueCounterDown==0){
         ghost->blue=false;
     }
 }
}
