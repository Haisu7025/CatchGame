#ifndef ALGTHM_H
#define ALGTHM_H
#include "QList"

#define MAX_MAP_SIZE 30

#define FTG 0
#define BLOCK 1
#define MOUSE 2
#define CAT 3
class Node
{
  public:
    Node *father;
    Node(int x, int y, int State);
    void load(int x, int y, int State);
    void setGH(int g, int h);
    int getState();
    int getGH() { return g + h; }
    int getG() { return g; }
    int getH() { return h; }
    int getX() { return x; }
    int getY() { return y; }

  private:
    int x, y;
    int g, h;
    int State;
};

class StateNode
{
public:
    StateNode *father;
    StateNode(int catx,int caty,int mousex,int mousey);
    int bfc,bfm;
    int catx, caty, mousex, mousey;
    int level;
    int get_key(){
        return (level%3)*10000+(catx*20+caty)*20+mousex*20+mousey;
    }

    bool isLeaf();
};

class Algthm
{
  public:
    Algthm(int x, int y);
    Algthm(int x, int y, int array[MAX_MAP_SIZE][MAX_MAP_SIZE]);
    Node *getEle(int x, int y);
    void AStarSearch(Node *s, Node *e);
    void AStarUnitSearch(QList<Node *> *OpenLs, QList<Node *> *CloseLs, Node *n, Node *target);
    QList<Node*> get_path(){
        return *Path;
    }

    void down_spread(StateNode *e);
    void construct_tree_for_cat();
    void construct_tree_for_mouse();

    void VsSearch(int a[], int b[]);
    void get_next_move_for_mouse(int catpos[],int mousepos[], int *tar);




  private:
    Node *nmap[MAX_MAP_SIZE][MAX_MAP_SIZE];
    int rangex, rangey;

    // A*
    QList<Node *> *Path;
    int getMahattanDistance(int curx, int cury, int targetx, int targety);

    // Vs
    QMap<int,StateNode *> *Tree;

};

#endif // ALGTHM_H
