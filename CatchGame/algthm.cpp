#include "algthm.h"
#include "QtMath"

Node::Node(int x, int y, int State){
    this->x=x;
    this->y=y;
    this->State=State;
    g=0;
    h=0;
}

void Node::load(int x, int y, int State){
    this->x=x;
    this->y=y;
    this->State=State;
}

void Node::setGH(int g, int h){
    this->g=g;
    this->h=h;
}

int Node::getState(){
    return State;
}

Algthm::Algthm(int x, int y)
{
    rangex=x;
    rangey=y;
    for(int i=0;i<rangex;i++){
        for(int j=0;j<rangey;j++){
            nmap[i][j]=new Node(i,j,FTG);
        }
    }
}

Algthm::Algthm(int x, int y ,int array[MAX_MAP_SIZE][MAX_MAP_SIZE]){
    rangex=x;
    rangey=y;
    for(int i=0;i<rangex;i++){
        for(int j=0;j<rangey;j++){
            nmap[i][j] = new Node(i,j,array[i][j]+10000);
        }
    }
}

int Algthm::getMahattanDistance(int curx, int cury, int targetx, int targety){
    return abs(curx-targetx)+abs(cury-targety);
}

Node* Algthm::getEle(int x, int y){
    return nmap[x][y];
}

void Algthm::AStarSearch(Node *s, Node *e){
    QList<Node*> *OpenLs = new QList<Node*>();
    QList<Node*> *ClosLs = new QList<Node*>();

    OpenLs->append(s);
    while(1){
        int min=100;
        Node *tn=NULL;
        for(int i=0;i<OpenLs->length();i++){
            int f=OpenLs->at(i)->getGH();
            if(f<min){
                min=f;
                tn=OpenLs->at(i);
            }
        }
        AStarUnitSearch(OpenLs,ClosLs,tn,e);
    }
}

void Algthm::AStarUnitSearch(QList<Node*> *OpenLs, QList<Node*> *ClosLs, Node *n, Node *target){
    int curx=n->getX(),cury=n->getY();
    int tarx=target->getX(),tary=target->getY();
    OpenLs->removeOne(n);
    ClosLs->append(n);
    for(int i=curx-1;i<=curx+1;i++){
        for(int j=cury-1;j<=cury+1;j++){
            if(i==curx && j==cury){
                continue;
            }
            if(abs(i-curx)+abs(j-cury)==2){
                continue;
            }
            if(i>=0 && i<=rangex && j>=0 && j<=rangey){
                //inside range
                int t;
                if(ClosLs->indexOf(nmap[i][j])>=0){
                    continue;
                }
                if(nmap[i][j]->getState()==FTG){
                    nmap[i][j]->father=n;
                    nmap[i][j]->setGH(n->getG()+1,getMahattanDistance(i,j,tarx,tary));
                    if((t=OpenLs->indexOf(nmap[i][j]))>=0){
                        if(OpenLs->at(t)->getGH()>=nmap[i][j]->getGH()){
                            OpenLs->replace(t,nmap[i][j]);
                        }
                    }
                    OpenLs->append(nmap[i][j]);
                }
            }
        }
    }
}
