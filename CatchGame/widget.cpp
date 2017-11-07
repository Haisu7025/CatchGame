#include "widget.h"
#include "ui_widget.h"
#include "QMouseEvent"

#define DEBUG 1

#if DEBUG
#include "QDebug"
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
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

void Widget::init_widget_look(){
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/timg.jpeg").scaled(this->size())));
    this->setPalette(palette);

}

void Widget::bind_slots(){
    connect(ui->start_b,SIGNAL(clicked(bool)),this,SLOT(start_slot()));

    connect(ui->quit_b,SIGNAL(clicked(bool)),this,SLOT(quit_slot()));
    connect(ui->back_b,SIGNAL(clicked(bool)),this,SLOT(back_slot()));
}

void Widget::create_move_animation(QAbstractButton *obj,QPoint target){
    anim = new QPropertyAnimation(obj,"pos");
    anim->setDuration(2000);
    anim->setStartValue(QPoint(obj->geometry().x(),obj->geometry().y()));
    anim->setEndValue(target);
    anim->setEasingCurve(QEasingCurve::OutCubic);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::start_slot(){
    ui->stackedWidget->setCurrentIndex(1);
    gen_map(5,5);
}

void Widget::gen_map(int row, int col){
    QFont font;
    font.setFamily("Papyrus");
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            button_group[i][j] = new QPushButton();
            button_group[i][j]->setStyleSheet("QPushButton {                                \
                                  color: white;                                 \
                                  border-image: url(:/pics/button.png);         \
                                  border-width: 12px;                           \
                                  min-height: 50px;                             \
                                  min-width: 55px;                              \
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
            ui->gl->addWidget(button_group[i][j],i,j);
        }
    }

}

void Widget::quit_slot(){
    shrink_out_and_quit(this);
}

void Widget::back_slot(){
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}

void Widget::shrink_in(QWidget *w){
    QPropertyAnimation *animation = new QPropertyAnimation(w, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void Widget::shrink_out(QWidget *w){
    QPropertyAnimation *animation = new QPropertyAnimation(w, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
}

void Widget::shrink_out_and_quit(QWidget *w){
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
    if (mMoveing && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}
