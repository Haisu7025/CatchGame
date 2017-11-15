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



class AdState{
public:
    AdState* father;
    int cat_pos,mouse_pos,level;
    int benefit;
    AdState(int cat_pos, int mouse_pos, int level){
        father = NULL;
        this->cat_pos = cat_pos;
        this->mouse_pos = mouse_pos;
        this->level = level;
        benefit = 0;
    }
    bool isequal(AdState *s){
        return s->cat_pos==cat_pos && s->mouse_pos==mouse_pos;
    }
    bool isleaf(){
        return cat_pos == mouse_pos;
    }
};

class Algthm
{
  public:
    Algthm(int x, int y);
    Algthm(int x, int y, int array[MAX_MAP_SIZE][MAX_MAP_SIZE]);
    Node *getEle(int x, int y);

    Node *nmap[MAX_MAP_SIZE][MAX_MAP_SIZE];
    int rangex, rangey;

    // A*
    QList<Node *> *Path;
    int getMahattanDistance(int curx, int cury, int targetx, int targety);
    void AStarSearch(Node *s, Node *e);
    void AStarUnitSearch(QList<Node *> *OpenLs, QList<Node *> *CloseLs, Node *n, Node *target);
    QList<Node*> get_path(){
        return *Path;
    }

    // Adversarial Search
    QList<AdState*> *Tree;
    void AdvSearch(int cat_pos_start, int mouse_pos_start);
    void spread(AdState *cur);
    void get_next_move(int* cat_pos, int* mouse_pos, int *nm);
};

#endif // ALGTHM_H
