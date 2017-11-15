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


void Algthm::AdvSearch(int cat_pos_start, int mouse_pos_start){
    Tree = new QList<AdState*>();
    AdState *s = new AdState(cat_pos_start, mouse_pos_start, 0);
    spread(s);
}

void Algthm::spread(AdState *cur){
    int cpsx = cur->cat_pos/20, cpsy = cur->cat_pos%20;
    int mpsx = cur->mouse_pos/20, mpsy = cur->mouse_pos%20;
    Tree->append(cur);
    if(cur->level%2 == 0){
        // cat move 2 units
        for(int i=0;i<rangex;i++){
            for(int j=0;j<rangey;j++){
                if(abs(i-cpsx)+abs(j-cpsy)==2 && nmap[i][j]->getState()!=BLOCK){
                    // moving target point
                    int exi_flag=0;
                    for(int p=0;p<Tree->length();p++){
                        if(Tree->at(p)->cat_pos==20*i+j && Tree->at(p)->mouse_pos==cur->mouse_pos){
                            if(Tree->at(p)->father==NULL){
                                exi_flag = 1;
                                break;
                            }
                            if(Tree->at(p)->father->isequal(cur)){
                                exi_flag = 1;
                                break;
                            }
                        }
                    }
                    if(exi_flag){
                        continue;
                    }
                    AdState *s = new AdState(i*20+j,cur->mouse_pos,cur->level+1);
                    s->father = cur;
                    if(s->isleaf()){
                        s->benefit = s->level; // benefit is the round num
                        int be = s->benefit;
                        AdState *tmp=s;
                        while(1){
                            if(tmp->father==NULL){
                                break;
                            }
                            tmp = tmp->father;
                            if(tmp->level%2){
                                // Mouse to move - MAX level
                                if(tmp->benefit==0 || be>tmp->benefit){
                                    tmp->benefit = be;
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                // Cat to move - MIN level
                                if(tmp->benefit==0 || be<tmp->benefit){
                                    tmp->benefit = be;
                                }
                                else{
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        spread(s);
                    }
                }
            }
        }
    }
    else{
        // mouse move 1 unit
        for(int i=0;i<rangex;i++){
            for(int j=0;j<rangey;j++){
                if(abs(i-mpsx)+abs(j-mpsy)==1 && nmap[i][j]->getState()!=BLOCK){
                    // moving target point
                    int exi_flag=0;
                    for(int p=0;p<Tree->length();p++){
                        if(Tree->at(p)->cat_pos==cur->cat_pos && Tree->at(p)->mouse_pos==i*20+j){
                            if(Tree->at(p)->father==NULL){
                                exi_flag = 1;
                                continue;
                            }
                            if(Tree->at(p)->father->isequal(cur)){
                                exi_flag = 1;
                                break;
                            }
                        }
                    }
                    if(exi_flag){
                        continue;
                    }
                    AdState *s = new AdState(cur->cat_pos,i*20+j,cur->level+1);
                    s->father = cur;
                    if(s->isleaf()){
                        s->benefit = s->level; // benefit is the round num
                        int be = s->benefit;
                        AdState *tmp=s;
                        while(1){
                            if(tmp->father==NULL){
                                break;
                            }
                            tmp = tmp->father;
                            if(tmp->level%2){
                                // Mouse to move - MAX level
                                if(tmp->benefit==0 || be>tmp->benefit){
                                    tmp->benefit = be;
                                }
                                else{
                                    break;
                                }
                            }
                            else{
                                // Cat to move - MIN level
                                if(tmp->benefit==0 || be<tmp->benefit){
                                    tmp->benefit = be;
                                }
                                else{
                                    break;
                                }
                            }
                        }
                    }
                    else{
                        spread(s);
                    }
                }
            }
        }
    }
}

void Algthm::get_next_move(int *cat_pos, int *mouse_pos, int *nm){
    AdState *tmp = new AdState(cat_pos[0]*20+cat_pos[1], mouse_pos[0]*20+mouse_pos[1], 0);
    AdState *t=NULL;
    int MAX = -1;
    for(int i=0;i<Tree->length();i++){
        if(Tree->at(i)->father!=NULL && Tree->at(i)->father->isequal(tmp) && Tree->at(i)->father->level%2==1){
            if(Tree->at(i)->benefit>MAX){
                MAX = Tree->at(i)->benefit;
                t = Tree->at(i);
            }
        }
    }
    nm[0] = t->mouse_pos/20;
    nm[1] = t->mouse_pos%20;
}
