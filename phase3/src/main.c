#include <stdio.h>
#include <game.h>
#include <physics.h>
#include <map.h>
#include <input.h>
#include <time.h>
#include "game.h"
#include "map.h"
#include <../sdl/sdl2-include/SDL.h>
#include <../sdl/sdl2-gfx-include/SDL2_gfxPrimitives.h>
#ifdef main
# undef main
#endif
void Drawghost(SDL_Renderer *renderer,double x,double y, int r,int g,int b,int eye);
void drawPac(Direction dir,SDL_Renderer **renderer,Pacman *outPacman,int H1,int W1,float mdegree,int* deg){
    int deg1;
    switch (dir) {
        case DIR_UP:
            outPacman->y=outPacman->y-0.025+((outPacman->y-0.025<=-1)*(H1+0.001));
            if(outPacman->y<=0 && outPacman->y>=-1)
                filledPieRGBA(*renderer,outPacman->x*80+30+38,(outPacman->y+H1)*80+30+38,38,-90+mdegree*10,270-mdegree*10,240, 249, 62,0xff);
            filledPieRGBA(*renderer,outPacman->x*80+30+38,outPacman->y*80+30+38,38,-90+mdegree*10,270-mdegree*10,240, 249, 62,0xff);
            *deg=1;
            break;
        case DIR_DOWN:
            outPacman->y=outPacman->y+0.025-((outPacman->y+0.025>=H1)*H1);
            if(outPacman->y<=H1 && outPacman->y>=H1-1)
                filledPieRGBA(*renderer,outPacman->x*80+30+38,(outPacman->y-H1)*80+30+38,38,-270+mdegree*10,90-mdegree*10,240, 249, 62,0xff);
            filledPieRGBA(*renderer,outPacman->x*80+30+38,outPacman->y*80+30+38,38,-270+mdegree*10,90-mdegree*10,240, 249, 62,0xff);
            *deg=3;
            break;
        case DIR_RIGHT:
            outPacman->x=outPacman->x+0.025-((outPacman->x+0.025>=W1)*W1);
            if(outPacman->x<=W1 && outPacman->x>=W1-1)
                filledPieRGBA(*renderer,(outPacman->x-W1)*80+30+38,outPacman->y*80+30+38,38,1+mdegree*10,360-mdegree*10,240, 249, 62,0xff);
            filledPieRGBA(*renderer,outPacman->x*80+30+38,outPacman->y*80+30+38,38,1+mdegree*10,360-mdegree*10,240, 249, 62,0xff);
            *deg=4;
            break;
        case DIR_LEFT:
            outPacman->x=outPacman->x-0.025+((outPacman->x-0.025<=-1)*W1);
            if(outPacman->x<=0 && outPacman->x>=-1)
                filledPieRGBA(*renderer,(outPacman->x+W1)*80+30+38,outPacman->y*80+30+38,38,-180+mdegree*10,180-mdegree*10,240, 249, 62,0xff);
            filledPieRGBA(*renderer,outPacman->x*80+30+38,outPacman->y*80+30+38,38,-180+mdegree*10,180-mdegree*10,240, 249, 62,0xff);
            *deg=2;
            break;
        case DIR_NONE:
            deg1=-(*deg)*90+mdegree*10;
            filledPieRGBA(*renderer,outPacman->x*80+30+38,outPacman->y*80+30+38,38,deg1,deg1+358-20*mdegree,240, 249, 62,0xff);
            break;
    }
}

void drawghost(SDL_Renderer *renderer,Direction dir,Ghost* ghost,int eye,int W1,int H1,int r,int g,int b){
    switch (dir){
        case DIR_UP:ghost->y=ghost->y-0.025+(((ghost->y-0.025)<=-1)*H1);
            if(ghost->y<=0 && ghost->y>=-1)
                Drawghost(renderer,ghost->x,ghost->y+H1,r,g,b,eye);
            break;
        case DIR_DOWN:ghost->y=ghost->y+0.025-(((ghost->y+0.025)>=H1)*H1);
            if(ghost->y<=H1 && ghost->y>=H1-1)
                Drawghost(renderer,ghost->x,ghost->y-H1,r,g,b,eye);
            break;
        case DIR_RIGHT:ghost->x=ghost->x+0.025-(((ghost->x+0.025)>=W1)*W1);
            if(ghost->x<=W1 && ghost->x>=W1-1)
                Drawghost(renderer,ghost->x-W1,ghost->y,r,g,b,eye);
            break;
        case DIR_LEFT:ghost->x=ghost->x-0.025+(((ghost->x-0.025)<=-1)*(W1));
            if(ghost->x<=0 && ghost->x>=-1)
                Drawghost(renderer, ghost->x+W1, ghost->y,r,g,b,eye);
            break;
    }
}

void Drawghost(SDL_Renderer *renderer, double x, double y, int r, int g, int b,int eye) {
    int moveyex=3*((eye%2==0)*(3-eye));
    int moveyey=3*((eye%2==1)*(eye-2));
    boxRGBA(renderer, x*80+30+15,y*80+30+24,x*80+48+30+15,y*80+45+30+24,r,g,b,0xff);
    filledPieRGBA(renderer,x*80+30+15+24,y*80+30+24,24,-180,0,r, g, b,0xff);
    filledTrigonRGBA(renderer,x*80+30+15,y*80+45+25+30,x*80+30+15+16,y*80+45+24+30,x*80+30+15,y*80+45+24+40,r, g, b,0xff);
    filledTrigonRGBA(renderer,x*80+30+15+16,y*80+45+24+30,x*80+30+15+32,y*80+45+24+30,x*80+30+15+24,y*80+45+24+40,r, g, b,0xff);
    filledTrigonRGBA(renderer,x*80+30+15+32,y*80+45+24+30,x*80+30+15+48,y*80+45+24+30,x*80+30+15+48,y*80+45+24+40,r, g, b,0xff);
    filledCircleRGBA(renderer,x*80+30+24+6,y*80+30+20,6,0xff,0xff,0xff,0xff);
    filledCircleRGBA(renderer,x*80+30+24+25,y*80+30+20,6,0xff,0xff,0xff,0xff);
    filledCircleRGBA(renderer,x*80+30+24+6+moveyex,y*80+30+20+moveyey,3,0,0,0,0xff);
    filledCircleRGBA(renderer,x*80+30+24+25+moveyex,y*80+30+20+moveyey,3,0,0,0,0xff);
}

int main(int argc, char* argv[]) {
    char *filename="res\\map.txt";
    int i,j;
    Map outMap;
    Game outGame;
    Pacman outPacman;
    Ghost outGhosts[4];
    outGame.ghosts=4;
    initiateGame(filename,&outMap,&outGame,&outPacman,outGhosts);

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, outMap.width*80+60,outMap.height*80+60,SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }
    SDL_Event e;
    float mdegree=0;
    float degreearr[81];
    for(i=0;i<41;i++){
        degreearr[i]=mdegree;
        mdegree+=0.1;}
        mdegree-=0.1;
    for(i=41;i<81;i++){
        mdegree-=0.1;
        degreearr[i]=mdegree; }
    int counter=20;
    int flag=1;
    clock_t clock0 = clock();
    int b4dir=(outPacman.dir+(outPacman.dir%2==0)*2)%4;
    SDL_PollEvent(&e);
    while( e.type!=SDL_KEYDOWN || e.key.keysym.sym!=SDLK_s ){
        SDL_PollEvent(&e);
        if( e.key.keysym.sym==SDLK_q || e.type==SDL_QUIT ){
            SDL_Quit();
            exit(1); }
        SDL_RenderSetScale(renderer,1.5,1.5);
        boxRGBA(renderer,0,0,outMap.width*80+60,outMap.height*80+60,79, 9, 24,200);
        filledPieRGBA(renderer,140,152,24,40,330,226, 216, 68,0xff);
        stringRGBA(renderer,190,140,"PRESS S TO START",0xff,0xff,0xff,0xff);
        stringRGBA(renderer,195,165,"PRESS Q TO QUIT",0xff,0xff,0xff,0xff);
        SDL_RenderPresent(renderer);
        SDL_RenderSetScale(renderer,1,1);
    }
    while(e.type!=SDL_QUIT) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_PollEvent(&e);
        mdegree=degreearr[counter];
        if(flag)
            counter++;
        if(counter>80)
            counter=0;
        boxRGBA(renderer,30,30,outMap.width*80+30,outMap.height*80+30,56, 54, 54,0xff);
        for(i=0;i<outMap.height;i++){
            for(j=0;j<outMap.width;j++){
                if(outMap.cells[j][i]==CELL_BLOCK)
                    boxRGBA(renderer,j*80+30,i*80+30,(j+1)*80+30,(i+1)*80+30,0xaa,0xaa,0xaa,0xff);
                if(outMap.cells[j][i]==CELL_CHERRY)
                    filledCircleRGBA(renderer,j*80+40+30,i*80+40+30,15,188, 22, 111,0xff);
                if(outMap.cells[j][i]==CELL_PINEAPPLE)
                    filledCircleRGBA(renderer,j*80+40+30,i*80+40+30,30,244, 238, 48 ,0xff);
                if(outMap.cells[j][i]==CELL_CHEESE) {
                    filledTrigonRGBA(renderer,j*80+30+10,i*80+30+60,j*80+30+70,i*80+30+60,j*80+30+30,i*80+30+20,249, 243, 204,0xff);
                    filledCircleRGBA(renderer,j*80+30+30,i*80+50+30,8, 239, 233, 62,0xff);
                    filledCircleRGBA(renderer,j*80+30+50,i*80+50+30,5,239, 233, 62,0xff); }
            }}
        double pacx=floor(outPacman.x+0.001);
        double pacy=floor(outPacman.y+0.001);
        if(fabsl(outPacman.x-pacx)<0.01 && fabsl(outPacman.y-pacy)<0.01 ){
            outPacman.x=pacx;
            outPacman.y=pacy;
            if ( e.key.keysym.sym == SDLK_UP) {
                flag=1;
                Direction dirr=decidePacman(&outMap, &outPacman, ACTION_UP);
                if(dirr==-1)
                    flag=0;
                outPacman.dir=dirr;
                drawPac(dirr,&renderer,&outPacman,outMap.height,outMap.width,mdegree,&b4dir);
            }
            else if ( e.key.keysym.sym == SDLK_DOWN) {
                flag=1;
                Direction dirr=decidePacman(&outMap, &outPacman, ACTION_DOWN);
                if(dirr==-1)
                    flag=0;
                outPacman.dir=dirr;
                drawPac(dirr,&renderer,&outPacman,outMap.height,outMap.width,mdegree,&b4dir);
        }
            else if ( e.key.keysym.sym == SDLK_RIGHT) {
                flag=1;
                Direction dirr=decidePacman(&outMap, &outPacman, ACTION_RIGHT);
                if(dirr==-1)
                    flag=0;
                outPacman.dir=dirr;
                drawPac(dirr,&renderer,&outPacman,outMap.height,outMap.width,mdegree,&b4dir);
        }
            else if ( e.key.keysym.sym == SDLK_LEFT) {
                flag=1;
                Direction dirr=decidePacman(&outMap, &outPacman, ACTION_LEFT);
                if(dirr==-1)
                    flag=0;
                outPacman.dir=dirr;
                drawPac(dirr,&renderer,&outPacman,outMap.height,outMap.width,mdegree,&b4dir);
        }
            else{
                 flag=0;
                 Direction dirr=decidePacman(&outMap, &outPacman,ACTION_IDLE);
                 drawPac(dirr,&renderer,&outPacman,outMap.height,outMap.width,mdegree,&b4dir);
         }}
        else{
            flag=1;
            drawPac(outPacman.dir,&renderer,&outPacman,outMap.height,outMap.width,mdegree,&b4dir);
    }
        checkEatables(&outMap,&outGame,&outPacman,outGhosts);
        double ghostx[4];
        double ghosty[4];
        int r[4]={226,242,186,209};
        int g[4]={13,186,242,185};
        int b[4]={102,233,237,133};
        for(i=0;i<4;i++) {
            int eye=outGhosts[i].dir;
             ghostx[i]=floor(outGhosts[i].x+0.001);
             ghosty[i]=floor(outGhosts[i].y+0.001);
            int r1=r[i];
            int g1=g[i];
            int b1=b[i];
            if(outGhosts[i].blue==true){
                r1=1;
                g1=4;
                b1=178; }
            if(fabsl(outGhosts[i].x-ghostx[i])<0.01 && fabsl(outGhosts[i].y-ghosty[i])<0.01 ){
                outGhosts[i].x=ghostx[i];
                outGhosts[i].y=ghosty[i];
                outGhosts[i].dir=decideGhost(&outMap,&outGhosts[i],&outPacman,&outGhosts[0]);
                while(outGhosts[i].dir==-1)
                    outGhosts[i].dir=decideGhost(&outMap,&outGhosts[i],&outPacman,&outGhosts[0]);
                drawghost(renderer,outGhosts[i].dir,&outGhosts[i],eye,outMap.width,outMap.height,r1,g1,b1);}
            else{
                drawghost(renderer,outGhosts[i].dir,&outGhosts[i],eye,outMap.width,outMap.height,r1,g1,b1);
            }
            Drawghost(renderer,outGhosts[i].x,outGhosts[i].y,r1,g1,b1,eye);
            checkGhostCollision(&outPacman,&outGhosts[i]);
            checkGhostState(&outGhosts[i]);
        }
        boxRGBA(renderer,0,0,outMap.width*80+30,30,0, 0,0,0xff);
        boxRGBA(renderer,0,outMap.height*80+30,outMap.width*80+60,outMap.height*80+60,0, 0,0,0xff);
        boxRGBA(renderer,0,0,30,outMap.height*80+30,0, 0,0,0xff);
        boxRGBA(renderer,outMap.width*80+30,0,outMap.width*80+60,outMap.height*80+60,0, 0,0,0xff);
        for(i=0;i<outPacman.health;i++){
            filledPieRGBA(renderer,i*20+15,15,10,20,340,229, 11, 11,0xff); }
        char score[10];
        char time1[10];
        sprintf(score,"score:%d",outGame.score);
        stringRGBA(renderer,60*outMap.width,10,score,0xff,0xff,0xff,0xff);

        clock_t clock1= clock();
        sprintf(time1,"time:%.2f",(((double)clock1- clock0)/(1.0*CLOCKS_PER_SEC)));
        stringRGBA(renderer,20*outMap.width,10,time1,0xff,0xff,0xff,0xff);

        stringRGBA(renderer,100,outMap.height*80+40,"P:pause",0xff,0xff,0xff,0xff);
        stringRGBA(renderer,500,outMap.height*80+40,"Q:quit",0xff,0xff,0xff,0xff);

        if( e.key.keysym.sym==SDLK_p ){

            boxRGBA(renderer,0,0,outMap.width*80+30,outMap.height*80+30,0, 0,0,200);
            stringRGBA(renderer,350,210,"PAUSED",0xff,0xff,0xff,0xff);
            stringRGBA(renderer,250,230,"press any other key to continue",0xff,0xff,0xff,0xff);
            while( e.type!=SDL_KEYDOWN||e.key.keysym.sym==SDLK_p ){
                SDL_PollEvent(&e);
                if(e.type==SDL_QUIT)
                    SDL_Quit();
                SDL_RenderPresent(renderer);
               }}
        if( e.key.keysym.sym==SDLK_q ){
            SDL_Quit();
            exit(1);
        }
       if(isGameFinished(&outGame,&outPacman)){
           SDL_RenderSetScale(renderer,2,2);
           if(outGame.cheeses==0){
               boxRGBA(renderer,0,0,outMap.width*80+30,outMap.height*80+30,0, 0,0,200);
               stringRGBA(renderer,150,100,"YOU WON",0xff,0xff,0xff,0xff);}
           else{
               boxRGBA(renderer,0,0,outMap.width*80+30,outMap.height*80+30,0, 0,0,200);
               stringRGBA(renderer,150,100,"GAME OVER",0xff,0xff,0xff,0xff);}
           while(e.type!=SDL_KEYDOWN || e.key.keysym.sym!=SDLK_q  ){
               if(e.type==SDL_QUIT)
                   SDL_Quit();
               SDL_PollEvent(&e);
               SDL_RenderPresent(renderer);
               }
           SDL_Quit();
           return 0;
       }
    SDL_RenderPresent(renderer);
    SDL_Delay(10);}
    SDL_Quit();
    return 0;
}