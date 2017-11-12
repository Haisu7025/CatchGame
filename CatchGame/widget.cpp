#include "widget.h"
#include "ui_widget.h"
#include "QMouseEvent"
#include "QTime"
#include "QMessageBox"

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

    connect(ui->rand_b,SIGNAL(clicked(bool)),this,SLOT(rand_slot()));
    connect(ui->back_b, SIGNAL(clicked(bool)), this, SLOT(back_slot()));

    connect(ui->run_b,SIGNAL(clicked(bool)),this,SLOT(play_slot()));
    connect(ui->solve_b,SIGNAL(clicked(bool)),this,SLOT(solve_slot()));
    connect(ui->back_b_gp,SIGNAL(clicked(bool)),this,SLOT(back_gp_slot()));

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
    gen_map(5,5);

    connect(ui->cat_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));
    connect(ui->mouse_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));
    connect(ui->wall_b,SIGNAL(clicked(bool)),this,SLOT(pick_icon_slot()));

    connect(ui->col_set,SIGNAL(valueChanged(int)),this,SLOT(change_size_slot(int)));
    connect(ui->row_set,SIGNAL(valueChanged(int)),this,SLOT(change_size_slot(int)));

    connect(ui->mousemove,SIGNAL(clicked(bool)),this,SLOT(check_slot()));
    connect(ui->catrush,SIGNAL(clicked(bool)),this,SLOT(check_slot()));

}

void Widget::reset_game(){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cmap[i][j]=0;
            cgmap[i][j]=0;
            button_group[i][j]->deleteLater();
            play_b_group[i][j]->deleteLater();
        }
    }
    Path.clear();
    cat_pos[0]=cat_pos[1]=mouse_pos[0]=mouse_pos[1]=0;
    row=0;col=0;

    disconnect(ui->col_set,SIGNAL(valueChanged(int)),this,SLOT(change_size_slot(int)));
    disconnect(ui->row_set,SIGNAL(valueChanged(int)),this,SLOT(change_size_slot(int)));
    ui->row_set->setValue(5);
    ui->col_set->setValue(5);

    ui->mousemove->setChecked(false);
    ui->catrush->setChecked(false);
}

void Widget::gen_map(int row, int col)
{
    this->row=row;
    this->col=col;
    QFont font;
    int sizex = 280/row, sizey = 225/col;
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
                                  min-height: "+QString::number(sizex)+"px;                             \
                                  min-width: "+QString::number(sizey)+"px;                              \
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
    cat_pos[0]=m;
    cat_pos[1]=n;
}

void Widget::set_mouse(int m, int n){
    button_group[m][n]->setIcon(QIcon(QPixmap(":/new/prefix2/mouse.png")));
    cmap[m][n]=2;
    mouse_pos[0]=m;
    mouse_pos[1]=n;
}

void Widget::set_wall(int m, int n){
    button_group[m][n]->setIcon(QIcon(QPixmap(":/new/prefix2/wall1.png")));
    cmap[m][n]=1;
}

void Widget::set_blank(int m, int n){
    button_group[m][n]->setIcon(QIcon());
    cmap[m][n]=0;
}

void Widget::gen_play_map(){
    int sizex = 300/row, sizey = 250/col;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            play_b_group[i][j] = new QPushButton();
            play_b_group[i][j]->setParent(ui->gameplay);
            play_b_group[i][j]->setObjectName(QString::number(i*100+j));
            play_b_group[i][j]->setStyleSheet("QPushButton {                    \
                                  color: white;                                 \
                                  border-image: url(:/pics/button.png);         \
                                  border-width: 12px;                           \
                                  min-height: "+QString::number(sizex)+"px;                             \
                                  min-width: "+QString::number(sizey)+"px;                              \
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
            connect(play_b_group[i][j],SIGNAL(clicked(bool)),this,SLOT(move_map_slot()));
            ui->gl_gp->addWidget(play_b_group[i][j], i, j);
            switch (cmap[i][j]) {
            case 1:
                play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/wall1.png")));
                break;
            case 2:
                play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/mouse.png")));
                break;
            case 3:
                play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/cat.png")));
            default:
                break;
            }
        }
    }
}

void Widget::pick_map_slot(){
    int p=QObject::sender()->objectName().toInt();
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
                set_wall(i,j);
                break;
            case 2:
                set_mouse(i,j);
                break;
            case 3:
                set_cat(i,j);
            default:
                break;
            }
        }
    }
}

void Widget::check_slot(){
    if(ui->mousemove->isChecked() && ui->catrush->isChecked()){
        dynamic_cast<QCheckBox*>(QObject::sender())->setChecked(false);
        QMessageBox::about(NULL,"ERROR","Can't Activate Both Mode");
    }
}

void Widget::play_slot(){
    game_mode=0;
    if(ui->mousemove->isChecked()){
        game_mode=1;
    }
    if(ui->catrush->isChecked()){
        game_mode=2;
    }
    ui->stackedWidget->setCurrentIndex(2);
    gen_play_map();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cgmap[i][j]=cmap[i][j];
        }
    }
    al = new Algthm(row,col,cmap);
    switch (game_mode) {
    case 0:
        al->AStarSearch(al->getEle(cat_pos[0],cat_pos[1]),al->getEle(mouse_pos[0],mouse_pos[1]));
        Path = al->get_path();
        req_move = Path.length()+row*col/15;
        ui->req_move_l->setText("<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">"+QString::number(Path.length()+row*col/15)+"</span></p></body></html>");
        ui->cur_move_l->setText("<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">"+QString::number(0)+"</span></p></body></html>");
        break;
    case 1:
        al->VsSearch(cat_pos,mouse_pos);
    case 2:
        break;
    }
    cur_cat_pos[0]=cat_pos[0];
    cur_cat_pos[1]=cat_pos[1];

    cur_mouse_pos[0]=mouse_pos[0];
    cur_mouse_pos[1]=mouse_pos[1];
}

void Widget::solve_slot(){
    switch (game_mode) {
    case 0:
        if(cur_move!=0){
            // Alredy move
            QMessageBox::about(NULL, "ERROR", "Already Move Cat!");
        }
        else{
            for(int i=0;i<Path.length();i++){
                play_b_group[cur_cat_pos[0]][cur_cat_pos[1]]->setIcon(QIcon());
                cur_cat_pos[0]=Path.at(i)->getX();
                cur_cat_pos[1]=Path.at(i)->getY();
                play_b_group[cur_cat_pos[0]][cur_cat_pos[1]]->setIcon(QIcon(QPixmap(":/new/prefix2/cat.png")));
                QTime t;
                t.start();
                while(t.elapsed()<300)
                    QCoreApplication::processEvents();
            }
            QMessageBox::information(NULL,"End","Problem Solved!",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            reset_game();
            ui->stackedWidget->setCurrentIndex(0);
        }
        break;

    case 1:
        break;
    }
}

void Widget::cat_move(int curx, int cury){
    cgmap[cur_cat_pos[0]][cur_cat_pos[1]]=0;
    play_b_group[cur_cat_pos[0]][cur_cat_pos[1]]->setIcon(QIcon());
    cur_cat_pos[0]=curx;
    cur_cat_pos[1]=cury;
    cgmap[cur_cat_pos[0]][cur_cat_pos[1]]=CAT;
    play_b_group[cur_cat_pos[0]][cur_cat_pos[1]]->setIcon(QIcon(QPixmap(":/new/prefix2/cat.png")));
    cur_move++;
}

void Widget::mous_move(int curx, int cury){
    cgmap[cur_mouse_pos[0]][cur_mouse_pos[1]]=0;
    play_b_group[cur_mouse_pos[0]][cur_mouse_pos[1]]->setIcon(QIcon());
    cur_mouse_pos[0]=curx;
    cur_mouse_pos[1]=cury;
    cgmap[cur_mouse_pos[0]][cur_mouse_pos[1]]=CAT;
    play_b_group[cur_mouse_pos[0]][cur_mouse_pos[1]]->setIcon(QIcon(QPixmap(":/new/prefix2/mouse.png")));
}

void Widget::move_map_slot(){
    int p = QObject::sender()->objectName().toInt();
    int curx = p/100, cury = p%100;
    switch (game_mode) {
    case 0:
        if(cgmap[curx][cury]==CAT){
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    if(abs(i-curx)+abs(j-cury)==1 && (cgmap[i][j]==FTG || cgmap[i][j]==MOUSE)){
                        if(cgmap[i][j]==MOUSE){
                            cgmap[i][j]=-2;
                            continue;
                        }
                        if(i-curx==1){
                            //up
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/down.png")));
                        }
                        if(curx-i==1){
                            //down
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/up.png")));
                        }
                        if(j-cury==1){
                            //right
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/right.png")));
                        }
                        if(cury-j==1){
                            //left
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/left.png")));
                        }
                        cgmap[i][j]=-1;
                        continue;
                    }
                    play_b_group[i][j]->setEnabled(false);
                }
            }
        }
        else if(cgmap[curx][cury]==-1){
            cat_move(curx,cury);
            ui->cur_move_l->setText("<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">"+QString::number(cur_move)+"</span></p></body></html>");
            if(cur_move>req_move){
                QMessageBox::about(NULL,"Fail","You Fail!");
                ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 2);
            }
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    play_b_group[i][j]->setEnabled(true);
                    if(cgmap[i][j]==-1){
                        cgmap[i][j]=0;
                        play_b_group[i][j]->setIcon(QIcon());
                    }
                }
            }
        }
        else if(cgmap[curx][cury]==-2){
            QMessageBox::about(NULL,"Victory","You Win!\nRequired Move:"+QString::number(req_move)+"\nYour Move:"+QString::number(cur_move));
            reset_game();
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 2);
        }
        break;

    case 1:
        if(cgmap[curx][cury]==CAT){
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    if(abs(i-curx)+abs(j-cury)==1 && (cgmap[i][j]==FTG || cgmap[i][j]==MOUSE)){
                        if(cgmap[i][j]==MOUSE){
                            cgmap[i][j]=-2;
                        }
                        if(i-curx==1){
                            //up
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/down.png")));
                        }
                        if(curx-i==1){
                            //down
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/up.png")));
                        }
                        if(j-cury==1){
                            //right
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/right.png")));
                        }
                        if(cury-j==1){
                            //left
                            play_b_group[i][j]->setIcon(QIcon(QPixmap(":/new/prefix2/left.png")));
                        }
                        cgmap[i][j]=-1;
                        continue;
                    }
                    play_b_group[i][j]->setEnabled(false);
                }
            }
        }
        else if(cgmap[curx][cury]==-1){
            cat_move(curx,cury);
            ui->cur_move_l->setText("<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">"+QString::number(cur_move)+"</span></p></body></html>");
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    play_b_group[i][j]->setEnabled(true);
                    if(cgmap[i][j]==-1){
                        cgmap[i][j]=0;
                        play_b_group[i][j]->setIcon(QIcon());
                    }
                }
            }

            //Mouse Move
            if(cur_move%2==0){
                int target[2];
                al->get_next_move_for_mouse(cur_cat_pos,cur_mouse_pos,target);
                mous_move(target[0],target[1]);

            }
        }
        else if(cgmap[curx][cury]==-2){
            QMessageBox::about(NULL,"Victory","You Win!\nRequired Move:"+QString::number(req_move)+"\nYour Move:"+QString::number(cur_move));
            reset_game();
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 2);
        }
        break;

    }

}

void Widget::back_gp_slot(){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            play_b_group[i][j]->deleteLater();
        }
    }
    reset_game();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 2);
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
