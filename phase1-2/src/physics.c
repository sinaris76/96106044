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

void insert_queue(int vertex, int *front, int *rear, int queue[10000][3], int root, int mainroot) {
    int i,Root=0;
    if(*front == -1)
        *front = 0;
    *rear = *rear+1;
    queue[*rear][0] = vertex ;
    queue[*rear][2] = root;
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

int delete_queue(int *front, int (*queue)[3]) {
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

int BFS(int root, int destin, int *edges, const Map *map,int* levelcount) {
    int i,j;
    *levelcount=0;
    int mainroot=root;
    int front=-1,rear=-1;
    int state[10000]={0};
    int queue[10000][3]={0};
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
                    int start=queue[rear][2];
                    while(start!=queue[0][1]){
                        for(j=0;j<=rear;j++){
                            if(start==queue[j][0]){
                                start=queue[j][2];}
                        }
                        (*levelcount)++;
                    }
                    (*levelcount)++;
                    return queue[rear][1];
                }}}}
}

Direction finddir(const Map *map, int *edges, Ghost *ghost, int node1, int node2, int *level0) {
    if(node1==node2){
        int dir=(int)(((double)rand()/RAND_MAX)*5+1);
        if(dir==5)
            dir=-1;
        if(dir==1) {
            if (map->cells[(int)(ghost->x)][(int)ghost->y-1+((int)ghost->y-1<0)*map->height]==CELL_BLOCK )
                dir=-1; }
        if(dir==2) {
            if (map->cells[(int)(ghost->x)+1-((int)ghost->x+1>=map->width)*map->width][(int)(ghost->y)]==CELL_BLOCK )
                dir=-1; }
        if(dir==3) {
            if (map->cells[(int)(ghost->x)][(int)ghost->y+1-((int)ghost->y+1>=map->height)*map->height]==CELL_BLOCK)
                dir=-1; }
        if(dir==4) {
            if (map->cells[(int)(ghost->x)-1+((int)ghost->x-1<0)*map->width][(int)ghost->y]==CELL_BLOCK)
                dir=-1; }
        return (Direction)dir;}

    if(BFS(node1,node2,edges,map,level0)==(node1+1)%map->width+(node1/map->width)*map->width){
        return DIR_RIGHT;}
    if(BFS(node1,node2,edges,map,level0)==(node1-1)%map->width+(node1/map->width)*map->width){
        return DIR_LEFT;}
    if(BFS(node1,node2,edges,map,level0)==(node1+map->width)-(node1+map->width>=map->width*map->height)*map->width*map->height){
        return DIR_DOWN;}
    if(BFS(node1,node2,edges,map,level0)==(node1-map->width)+(node1-map->width<0)*map->height*map->width){
        return DIR_UP;}
}

int convert2node(const Map *map, double y, double x, int flag) {
    if(map->cells[(int)x][(int)y]==CELL_BLOCK && flag==1)
        return -1;
    else
        return (((int)y)*map->width+(int)x);
}
int pinkynode(const Map *map, Pacman *pacman, int i) {
    if(pacman->y+i*(pacman->dir%2==1)*(pacman->dir-2)>=map->height ||pacman->x-i*(pacman->dir%2==0)*(pacman->dir-3)>=map->width )
        return -2;
    if(pacman->y+i*(pacman->dir%2==1)*(pacman->dir-2)<0 ||pacman->x-i*(pacman->dir%2==0)*(pacman->dir-3)<0 )
        return -2;
    return convert2node(map,pacman->y+i*(pacman->dir%2==1)*(pacman->dir-2),pacman->x-i*(pacman->dir%2==0)*(pacman->dir-3),1);
}

Direction decideGhost(const Map *map, Ghost *ghost, Pacman *pacman, Ghost *blinky) {
    int ghostx =(int)ghost->x;
    int ghosty=(int)ghost->y;
    int level=0;
    Direction Dir;
    if(ghost->x==ghostx && ghost->y==ghosty ){
        int* edges=malloc(10000*10000*sizeof(int));
        makegraph(map,edges);
        int ghostnode=convert2node(map,ghost->y,ghost->x,0);
        int pacnode=convert2node(map,pacman->y,pacman->x,0);
        int ghoststartnode=convert2node(map,ghost->startY,ghost->startX,0);
        if(ghost->type==BLINKY ){
            if(ghost->blue==false){
                Dir=finddir(map,edges,ghost,ghostnode,pacnode,&level);
                free(edges);
                return Dir;
            }
            else{
                Dir=finddir(map,edges,ghost,ghostnode,ghoststartnode,&level);
                free(edges);
                return Dir;
            }}
        if(ghost->type==PINKY){
            if(ghost->blue==false){
                if( pinkynode(map,pacman,4)==-2){
                    Dir=finddir(map,edges,ghost,ghostnode,pacnode,&level);
                    free(edges);
                    return Dir; }
                if(pinkynode(map,pacman,1)==-1){
                    Dir=finddir(map,edges,ghost,ghostnode,pacnode,&level);
                    free(edges);
                    return Dir;}
                if(pinkynode(map,pacman,2)==-1){
                    Dir=finddir(map,edges,ghost,ghostnode,pinkynode(map,pacman,1),&level);
                    free(edges);
                    return Dir;}
                if(pinkynode(map,pacman,3)==-1){
                    Dir=finddir(map,edges,ghost,ghostnode,pinkynode(map,pacman,2),&level);
                    free(edges);
                    return Dir;}
                if(pinkynode(map,pacman,4)==-1){
                    Dir=finddir(map,edges,ghost,ghostnode,pinkynode(map,pacman,3),&level);
                    free(edges);
                    return Dir;}
                Dir=finddir(map,edges,ghost,ghostnode,pinkynode(map,pacman,4),&level);
                free(edges);
                return Dir;
            }
            else{
                Dir=finddir(map,edges,ghost,ghostnode,ghoststartnode,&level);
                free(edges);
                return Dir;}
        }
        else return DIR_UP;
    }}

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