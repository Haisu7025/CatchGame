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

StateNode::StateNode(int catx, int caty, int mousex, int mousey)
{
    this->catx = catx;
    this->caty = caty;
    this->mousex = mousex;
    this->mousey = mousey;
    bfc = bfm = 0;
    level = 0;
}

bool StateNode::isLeaf()
{
    return (catx == mousex && caty == mousey);
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
                        else
                        {
                            continue;
                        }
                    }
                    else
                    {
                        OpenLs->append(nmap[i][j]);
                        nmap[i][j]->father = n;
                    }
                }
            }
        }
    }
}

void Algthm::down_spread(StateNode *e)
{
    int curx, cury;
    if(e->level%3==0 || e->level%3==2){
        // cat's turn to move
        curx = e->catx;
        cury = e->caty;
    }
    else{
        // mouse's turn to move
        curx = e->mousex;
        cury = e->mousey;
    }

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
                if (nmap[i][j]->getState()==BLOCK){
                    continue;
                }
                StateNode *t;
                if(e->level%3==0 || e->level%3==2){
                    // cat's turn to move
                    t = new StateNode(i, j, e->mousex, e->mousey);
                }
                else{
                    // mouse's turn to move
                    t = new StateNode(e->catx,e->caty,i,j);
                }
                t->father = e;
                t->level = t->father->level + 1;
                QMap<int,StateNode *>::iterator it = Tree->find(t->get_key());
                if(it!=Tree->end()){
                    // already exists in Tree
                    continue;
                }
                Tree->insert(t->get_key(),t);
                //inside range
                if (e->isLeaf())
                {
                    // Reach Leaf Node
                    e->bfc = e->level;
                    e->bfm = e->level;
                    // backward
                    StateNode *temp = t;
                    int back_c_flag, back_h_flag;
                    while (true)
                    {
                        back_c_flag = 0;
                        back_h_flag = 0;
                        switch (temp->level % 3)
                        {
                        case 0:
                        case 1:
                            // MAX for cat, MIN for mouse
                            if (temp->bfc > temp->father->bfc)
                            {
                                temp->father->bfc = temp->bfc;
                            }
                            else
                            {
                                back_c_flag = 1;
                            }
                            if (temp->bfm < temp->father->bfm)
                            {
                                temp->father->bfm = temp->bfm;
                            }
                            else
                            {
                                back_h_flag = 1;
                            }
                            break;
                        case 2:
                            // MIN for cat, MAX for mouse
                            if (temp->bfc < temp->father->bfc)
                            {
                                temp->father->bfc = temp->bfc;
                            }
                            else
                            {
                                back_c_flag = 1;
                            }
                            if (temp->bfm > temp->father->bfm)
                            {
                                temp->father->bfm = temp->bfm;
                            }
                            else
                            {
                                back_h_flag = 1;
                            }
                            break;
                        default:
                            break;
                        }
                        if (back_c_flag && back_h_flag)
                        {
                            // dont change any more
                            break;
                        }
                        temp = temp->father;
                    }
                }
                else{
                    down_spread(t);
                }
            }
        }
    }
}

void Algthm::VsSearch(int a[], int b[])
{
    Tree = new QMap<int,StateNode*>();
    StateNode *root = new StateNode(a[0],a[1],b[0],b[1]);
    down_spread(root);
}

void Algthm::get_next_move_for_mouse(int catpos[], int mousepos[], int *tar){
    int key = 20000+(catpos[0]*20+catpos[1])*20+mousepos[0]*20+mousepos[1];
    QMap<int,StateNode *>::iterator it = Tree->find(key);
    QMap<int,StateNode *>::iterator i;
    int MAX = -1;
    StateNode *target=NULL;
    for(i=Tree->begin();i!=Tree->end();i++){
        // mouse want to escape as long as possible
        if(i.value()->father->get_key()==it.value()->get_key()){
            // i is current child
            if(i.value()->bfm>=MAX){
                target = i.value();
                MAX=i.value()->bfm;
            }
        }
    }
    tar[0]=target->mousex;
    tar[1]=target->mousey;
}
