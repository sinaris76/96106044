#include "physics.h"
#include "game.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void makegraph(const Map *map, int *adj) {
    int i,j;
    int h=map->height;
    int w=map->width;
    for(i=0;i<w*h;i++){
        for(j=0;j<w*h;j++){
            *(adj+i*10000+j)=0;

        }}
    for(i=0;i<w*h;i++){
        if(map->cells[((i+1)%w+(i/w)*w)%w][((i+1)%w+(i/w)*w)/w]!=CELL_BLOCK)
            *(adj+i*10000+(i+1)%w+(i/w)*w)=1;
        if(map->cells[((i-1)%w+(i/w)*w)%w][((i-1)%w+(i/w)*w)/w]!=CELL_BLOCK)
            *(adj+i*10000+(i-1)%w+(i/w)*w)=1;
        if(map->cells[((i+w)-(i+w>=w*h))%w][((i+w)-(i+w>=w*h))/w]!=CELL_BLOCK)
            *(adj+i*10000+(i+w)-(i+w>=w*h)*w*h)=1;
        if(map->cells[((i-w)+(i-w<0)*h*w)%w][((i-w)+(i-w<0)*h*w)/w]!=CELL_BLOCK)
            *(adj+i*10000+(i-w)+(i-w<0)*h*w)=1;
    }
}

void insert_queue(int vertex, int *front, int *rear, int (*queue)[2], int root, int mainroot) {
    int i,Root=0;
    if(*front == -1)
        *front = 0;
    *rear = *rear+1;
    queue[*rear][0] = vertex ;
    if(vertex==root || root==mainroot){
        queue[*rear][1]=queue[*rear][0];
    }
    else{
        for(i=0;i<10000;i++){
            if(queue[i][0]==root)
                Root=i;
        }
        queue[*rear][1]= queue[Root][1]; }
}

int delete_queue(int *front, int (*queue)[2]) {
    int delete_item;
    delete_item = queue[*front][0];
    *front = *front+1;
    return delete_item;
}

int isEmpty_queue(int front, int rear) {
    if( front > rear)
        return 1;
    else
        return 0;
}

int BFS(int root, int destin, int *edges, const Map *map, int *levelcount) {
    int i;
    *levelcount=0;
    int mainroot=root;
    int front=-1,rear=-1;
    int state[10000]={0};
    int queue[10000][2]={0};
    insert_queue(root,&front,&rear,queue,root,mainroot);
    state[root] = 1;
    while(!isEmpty_queue(front,rear))
    {

        root = delete_queue(&front,queue);
        state[root] = 2;
        for(i=0; i<map->height*map->width; i++)
        {
            if( *(edges+root*10000+i) == 1 && state[i] == 0)
            {

                insert_queue(i,&front,&rear,queue,root,mainroot);
                state[i] = 1;
                if(i==destin){

                    for(i=0;i<rear;i++){
                        if(queue[i][1]==queue[rear][1])
                            *levelcount=*levelcount+1;
                    }
                    return queue[rear][1];
                }}}}
}

Direction decideGhost(const Map* map, Ghost* ghost) {


}

Direction decidePacman(const Map* map, Pacman* pacman, Action action) {
    int intpacmanx=pacman->x/1;
    int intpacmany=pacman->y/1;
    int dir;
    int w=map->width, h=map->height;
    Direction Dir;
    if(pacman->x==intpacmanx && pacman->y==intpacmany ){
        int a=(int)pacman->y+(pacman->dir-2);
        int b= (int)(pacman->x)-(pacman->dir-3);
        if(action==2){
            if (map->cells[(int)(pacman->x)][(int)pacman->y-1+(intpacmany-1<0)*h]==CELL_BLOCK )
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=1;
        }
        else if (action==6){
            if (map->cells[(int)(pacman->x)+1-(intpacmanx+1>=w)*w][(int)(pacman->y)]==CELL_BLOCK )
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=2;
        }
        else if(action==10){
            if (map->cells[(int)(pacman->x)][(int)pacman->y+1-(intpacmany+1>=h)*h]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=3;
        }
        else if(action==14){
            if (map->cells[(int)(pacman->x)-1+(intpacmanx-1<0)*w][(int)pacman->y]==CELL_BLOCK)
                if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
                    dir=-1;
                else
                    dir=pacman->dir;
            else
                dir=4;
        }
        else
        if((pacman->dir%2==1 && map->cells[(int)(pacman->x)][a+(a<0)*h-(a>=h)*h]==CELL_BLOCK)||(pacman->dir%2==0 && map->cells[b+(b<0)*w-(b>=w)*w][(int)pacman->y]==CELL_BLOCK))
            dir=-1;
        else
            dir=pacman->dir;
    }
    Dir=dir;
    return Dir;
}