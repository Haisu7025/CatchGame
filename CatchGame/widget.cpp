#include "widget.h"
#include "ui_widget.h"
#include "QMouseEvent"
#include "QTime"

#define DEBUG 1

#if DEBUG
#include "QDebug"
#endif

Widget::Widget(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Widget)
{
    shrink_in(this);
    ui->setupUi(this);

    setMouseTracking(true);

    init_widget_look();
    bind_slots();
    ui->start_b->setFlat(true);
    ui->quit_b->setFlat(true);
}

void Widget::init_widget_look()
{
    this->setWindowFlags(Qt::FramelessWindowHint); //去掉标题栏
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/new/prefix1/timg.jpeg").scaled(this->size())));
    this->setPalette(palette);
    ui->stackedWidget->setCurrentIndex(0);

    gen_map(5,5);
}

void Widget::bind_slots()
{
    connect(ui->start_b, SIGNAL(clicked(bool)), this, SLOT(start_slot()));
    connect(ui->rand_b,SIGNAL(clicked(bool)),this,SLOT(rand_slot()));
    connect(ui->quit_b, SIGNAL(clicked(bool)), this, SLOT(quit_slot()));
    connect(ui->back_b, SIGNAL(clicked(bool)), this, SLOT(back_slot()));
}

void Widget::create_move_animation(QAbstractButton *obj, QPoint target)
{
    anim = new QPropertyAnimation(obj, "pos");
    anim->setDuration(2000);
    anim->setStartValue(QPoint(obj->geometry().x(), obj->geometry().y()));
    anim->setEndValue(target);
    anim->setEasingCurve(QEasingCurve::OutCubic);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start_slot()
{
    ui->stackedWidget->setCurrentIndex(1);

    connect(ui->cat_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));
    connect(ui->mouse_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));
    connect(ui->wall_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));

    connect(ui->col_set,SIGNAL(valueChanged(int)),this,SLOT(change_size_slot(int)));
    connect(ui->row_set,SIGNAL(valueChanged(int)),this,SLOT(change_size_slot(int)));

}

void Widget::gen_map(int row, int col)
{
    this->row=row;
    this->col=col;
    QFont font;
    int sizex = 225/row, sizey = 290/col;
    font.setFamily("Papyrus");  
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cmap[i][j]=0;
            button_group[i][j] = new QPushButton();
            button_group[i][j]->setParent(ui->gameset);
            button_group[i][j]->setObjectName(QString::number(i*100+j));
            button_group[i][j]->setStyleSheet("QPushButton {                    \
                                  color: white;                                 \
                                  border-image: url(:/pics/button.png);         \
                                  border-width: 12px;                           \
                                  min-height: "+QString::number(sizey)+"px;                             \
                                  min-width: "+QString::number(sizex)+"px;                              \
                                  border:2px groove gray;                       \
                                  border-radius:10px;                           \
                                  }                                             \
                                  QPushButton:pressed {                         \
                                  color: lightgray;                             \
                                  border-image: url(:/pics/button-pressed.png); \
                                  padding-top: -10px;                           \
                                  padding-bottom: -16px;                        \
                                  }                                             \
                                  QPushButton:hover {                           \
                                  border-width: 12px;                           \
                                  padding: -12px 0px;                           \
                                  min-height: 25px;                             \
                                  min-width: 60px;                              \
                                  border:3px groove gray;                       \
                                  border-radius:10px;                           \
                                  }");
            button_group[i][j]->setFont(font);
            connect(button_group[i][j],SIGNAL(clicked(bool)),this,SLOT(pick_map_slot()));
            ui->gl->addWidget(button_group[i][j], i, j);
        }
    }
}

void Widget::rand_gen_cmap(){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cmap[i][j]=0;
            button_group[i][j]->setIcon(QIcon());
        }
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    cmap[qrand()%row][qrand()%col]=3;
    cmap[qrand()%row][qrand()%col]=2;
    for(int i=0;i<qrand()%10+row*col/5;i++){
        int m=qrand()%10,n=qrand()%10;
        if(cmap[m][n]>0){
            i--;
            continue;
        }
        cmap[m][n]=1;
    }
}

void Widget::set_cat(int m, int n){
    button_group[m][n]->setIcon(QIcon(QPixmap(":/new/prefix2/cat.png")));
    cmap[m][n]=3;
}

void Widget::set_mouse(int m, int n){
    button_group[m][n]->setIcon(QIcon(QPixmap(":/new/prefix2/mouse.png")));
    cmap[m][n]=2;
}

void Widget::set_wall(int m, int n){
    button_group[m][n]->setIcon(QIcon(QPixmap(":/new/prefix2/wall1.png")));
    cmap[m][n]=1;
}

void Widget::set_blank(int m, int n){
    button_group[m][n]->setIcon(QIcon());
    cmap[m][n]=0;
}

void Widget::pick_map_slot(){
    int p=QObject::sender()->objectName().toInt();
    int blank_flag=0;
    int m=p/100,n=p%100;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(cmap[i][j]==-2){
                if(i*100+j==p){
                    // click self again:blank it
                    continue;
                }
                cmap[i][j]=0;
            }
        }
    }
    if(cmap[m][n]==-2){
        set_blank(m,n);
        return;
    }
    cmap[m][n]=-2;
}

void Widget::pick_icon_slot(){
    if(QObject::sender()==ui->cat_b){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(cmap[i][j]==3){
                    set_blank(i,j);
                }
                if(cmap[i][j]==-2){
                    set_cat(i,j);
                }
            }
        }
        return;
    }
    if(QObject::sender()==ui->mouse_b){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(cmap[i][j]==2){
                    set_blank(i,j);
                }
                if(cmap[i][j]==-2){
                    set_mouse(i,j);
                }
            }
        }
        return;
    }
    if(QObject::sender()==ui->wall_b){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(cmap[i][j]==-2){
                    set_wall(i,j);
                    return;
                }
            }
        }
    }

}

void Widget::change_size_slot(int csize){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(button_group[i][j]!=NULL){
                button_group[i][j]->deleteLater();
            }
        }
    }
    if(QObject::sender()==ui->row_set){
        row = csize;
        gen_map(row,col);
    }
    if(QObject::sender()==ui->col_set){
        col = csize;
        gen_map(row,col);
    }
}

void Widget::rand_slot(){
    rand_gen_cmap();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            switch (cmap[i][j]) {
            case 1:
                button_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/wall1.png")));
                break;
            case 2:
                button_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/mouse.png")));
                break;
            case 3:
                button_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/cat.png")));
            default:
                break;
            }
        }
    }
}

void Widget::quit_slot()
{
    shrink_out_and_quit(this);
}

void Widget::back_slot()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void Widget::shrink_in(QWidget *w)
{
    QPropertyAnimation *animation = new QPropertyAnimation(w, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void Widget::shrink_out(QWidget *w)
{
    QPropertyAnimation *animation = new QPropertyAnimation(w, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}

void Widget::shrink_out_and_quit(QWidget *w)
{
    QPropertyAnimation *animation = new QPropertyAnimation(w, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), w, SLOT(close()));
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing && (event->buttons() && Qt::LeftButton) && (event->globalPos() - mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos() - mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}
