#ifndef ALGTHM_H
#define ALGTHM_H
#include "QList"

#define MAX_MAP_SIZE 10

#define FTG 10000
#define BLOCK 10001
#define MOUSE 10002
#define CAT 10003
class Node
{
public:
    Node* father;
    Node(int x, int y, int State);
    void load(int x, int y, int State);
    void setGH(int g,int h);
    int getState();
    int getGH() {return g+h;}
    int getG(){return g;}
    int getX() {return x;}
    int getY() {return y;}
private:
    int x,y;
    int g,h;
    int State;
};

class Algthm
{
public:
    Algthm(int x, int y);
    Algthm(int x, int y, int array[MAX_MAP_SIZE][MAX_MAP_SIZE]);
    Node* getEle(int x, int y);
    void AStarSearch(Node *s, Node *e);
    void AStarUnitSearch(QList<Node*> *OpenLs, QList<Node*> *CloseLs, Node *n, Node *target);

private:
    Node* nmap[MAX_MAP_SIZE][MAX_MAP_SIZE];
    QList<Node*> *path;
    int rangex,rangey;

    int getMahattanDistance(int curx, int cury, int targetx, int targety);
};

#endif // ALGTHM_H
