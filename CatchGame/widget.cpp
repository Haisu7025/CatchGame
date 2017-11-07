#include "widget.h"
#include "ui_widget.h"
#include "QMouseEvent"

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
}

void Widget::bind_slots()
{
    connect(ui->start_b, SIGNAL(clicked(bool)), this, SLOT(start_slot()));

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

    gen_map(5, 5);
    connect(ui->cat_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));
    connect(ui->mouse_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));
    connect(ui->wall_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));

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

void Widget::pick_map_slot(){
    int p=QObject::sender()->objectName().toInt();
    int m=p/100,n=p%100;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(cmap[i][j]==-2){
                cmap[i][j]=0;
            }
        }
    }
    cmap[m][n]=-2;
}

void Widget::pick_icon_slot(){
    if(QObject::sender()==ui->cat_b){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(cmap[i][j]==3){
                    button_group[i][j]->setIcon(QIcon());
                    cmap[i][j]=0;
                }
                if(cmap[i][j]==-2){
                    button_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/cat.png")));
                    cmap[i][j]=3;
                }
            }
        }
        return;
    }
    if(QObject::sender()==ui->mouse_b){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(cmap[i][j]==2){
                    button_group[i][j]->setIcon(QIcon());
                    cmap[i][j]=0;
                }
                if(cmap[i][j]==-2){
                    button_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/mouse.png")));
                    cmap[i][j]=2;
                }
            }
        }
        return;
    }
    if(QObject::sender()==ui->wall_b){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(cmap[i][j]==-2){
                    button_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/wall.png")));
                    cmap[i][j]=0;
                    return;
                }
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
