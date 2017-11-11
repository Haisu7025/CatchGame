#include "algthm.h"
#include "QtMath"

Node::Node(int x, int y, int State)
{
    this->x = x;
    this->y = y;
    this->State = State;
    g = 0;
    h = 0;
}

void Node::load(int x, int y, int State)
{
    this->x = x;
    this->y = y;
    this->State = State;
}

void Node::setGH(int g, int h)
{
    this->g = g;
    this->h = h;
}

int Node::getState()
{
    return State;
}


StateNode::StateNode(int catx, int caty, int mousex, int mousey){
    this->catx=catx;
    this->caty=caty;
    this->mousex=mousex;
    this->mousey=mousey;
    bfc = bfm = 0;
}

bool StateNode::isLeaf(){
    return (catx==mousex && caty==mousey);
}

Algthm::Algthm(int x, int y)
{
    rangex = x;
    rangey = y;
    for (int i = 0; i < rangex; i++)
    {
        for (int j = 0; j < rangey; j++)
        {
            nmap[i][j] = new Node(i, j, FTG);
        }
    }
}

Algthm::Algthm(int x, int y, int array[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    rangex = x;
    rangey = y;
    for (int i = 0; i < rangex; i++)
    {
        for (int j = 0; j < rangey; j++)
        {
            nmap[i][j] = new Node(i, j, array[i][j]);
        }
    }
}

int Algthm::getMahattanDistance(int curx, int cury, int targetx, int targety)
{
    return abs(curx - targetx) + abs(cury - targety);
}

Node *Algthm::getEle(int x, int y)
{
    return nmap[x][y];
}

void Algthm::AStarSearch(Node *s, Node *e)
{
    QList<Node *> *OpenLs = new QList<Node *>();
    QList<Node *> *ClosLs = new QList<Node *>();
    Path = new QList<Node *>();
    OpenLs->append(s);
    while (1)
    {
        int min = 100;
        Node *tn = NULL;
        for (int i = 0; i < OpenLs->length(); i++)
        {
            int f = OpenLs->at(i)->getGH();
            if (f <= min)
            {
                min = f;
                tn = OpenLs->at(i);
            }
        }
        AStarUnitSearch(OpenLs, ClosLs, tn, e);
        if (tn == e)
        {
            break;
        }
    }
    Node *temp = e;
    Path->append(temp);
    while (1)
    {
        if (temp->father != s)
        {
            temp = temp->father;
            Path->push_front(temp);
        }
        else
        {
            break;
        }
    }
}

void Algthm::AStarUnitSearch(QList<Node *> *OpenLs, QList<Node *> *ClosLs, Node *n, Node *target)
{
    int curx = n->getX(), cury = n->getY();
    int tarx = target->getX(), tary = target->getY();
    OpenLs->removeOne(n);
    ClosLs->append(n);
    for (int i = curx - 1; i <= curx + 1; i++)
    {
        for (int j = cury - 1; j <= cury + 1; j++)
        {
            if (i == curx && j == cury)
            {
                continue;
            }
            if (abs(i - curx) + abs(j - cury) == 2)
            {
                continue;
            }
            if (i >= 0 && i < rangex && j >= 0 && j < rangey)
            {
                //inside range
                int t;
                if (ClosLs->indexOf(nmap[i][j]) >= 0)
                {
                    continue;
                }
                if (nmap[i][j]->getState() == FTG || nmap[i][j]->getState() == MOUSE)
                {
                    nmap[i][j]->setGH(n->getG() + 1, getMahattanDistance(i, j, tarx, tary));
                    if ((t = OpenLs->indexOf(nmap[i][j])) >= 0)
                    {
                        if (OpenLs->at(t)->getGH() >= nmap[i][j]->getGH())
                        {
                            nmap[i][j]->father = n;
                            OpenLs->replace(t, nmap[i][j]);
                        }
                        else{
                            continue;
                        }
                    }
                    else{
                        OpenLs->append(nmap[i][j]);
                        nmap[i][j]->father = n;
                    }
                }
            }
        }
    }
}

void Algthm::down_spread(StateNode *e){
    int curx,cury;
    switch (new_level) {
    case CAT:
        curx = e->catx;
        cury = e->caty;
        for (int i = curx - 1; i <= curx + 1; i++)
        {
            for (int j = cury - 1; j <= cury + 1; j++)
            {
                if (i == curx && j == cury)
                {
                    continue;
                }
                if (abs(i - curx) + abs(j - cury) == 2)
                {
                    continue;
                }
                if (i >= 0 && i < rangex && j >= 0 && j < rangey)
                {
                    StateNode *t = new StateNode(i,j,e->mousex,e->mousey);
                    Tree->append(t);
                    t->father = e;
                    t->level = t->father->level+1;
                    //inside range
                    if(e->isLeaf()){
                        // Reach Leaf Node
                        e->bfc = 1;
                        e->bfm = 1;
                    }
                    // backward
                    StateNode *temp=t;
                    while(true){
                        switch (temp->level%3) {
                        case 0:
                        case 1:
                            // MAX for cat, MIN for mouse
                            if(temp->bfc>temp->father->bfc){
                                temp->father->bfc = temp->bfc;
                            }
                            if(temp->bfm<temp->father->bfm){
                                temp->father->bfm = temp->bfm;
                            }
                            break;
                        case 2:
                            // MIN for cat, MAX for mouse
                            if(temp->bfc<temp->father->bfc){
                                temp->father->bfc = temp->bfc;
                            }
                            if(temp->bfm>temp->father->bfm){
                                temp->father->bfm = temp->bfm;
                            }
                            break;
                        default:
                            break;
                        }
                        temp = temp->father;
                    }
                }
            }
        }
        break;
    case MOUSE:
        curx = e->mousex;
        cury = e->mousey;
        break;
    default:
        break;
    }
}

void Algthm::VsSearch(Node *s, Node *e){
    new_level=CAT;
}
