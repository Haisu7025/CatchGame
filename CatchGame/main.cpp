#include "widget.h"
#include <QApplication>

#include "QDebug"
#include "algthm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    //    int arr[10][10]={{0,0,0,0,0},{0,0,1,1,0},{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    //    Algthm *alg=new Algthm(5,5,arr);
    //    alg->AStarSearch(alg->getEle(0,0),alg->getEle(2,3));
    //    return 0;
    return a.exec();
}
