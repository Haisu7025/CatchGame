/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *welcome;
    QPushButton *quit_b;
    QPushButton *start_b;
    QLabel *label;
    QWidget *gameset;
    QPushButton *back_b;
    QWidget *gridLayoutWidget;
    QGridLayout *gl;
    QPushButton *run_b;
    QFrame *line;
    QSlider *row_set;
    QSlider *col_set;
    QPushButton *rand_b;
    QPushButton *cat_b;
    QPushButton *mouse_b;
    QPushButton *wall_b;
    QCheckBox *mousemove;
    QLabel *label_2;
    QCheckBox *catrush;
    QLabel *label_3;
    QWidget *gameplay;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gl_gp;
    QPushButton *back_b_gp;
    QPushButton *solve_b;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *cur_move_l;
    QLabel *req_move_l;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(691, 441);
        Widget->setAutoFillBackground(true);
        Widget->setStyleSheet(QStringLiteral(""));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 691, 441));
        stackedWidget->setFrameShape(QFrame::Box);
        stackedWidget->setFrameShadow(QFrame::Plain);
        welcome = new QWidget();
        welcome->setObjectName(QStringLiteral("welcome"));
        quit_b = new QPushButton(welcome);
        quit_b->setObjectName(QStringLiteral("quit_b"));
        quit_b->setGeometry(QRect(490, 210, 151, 41));
        QFont font;
        font.setFamily(QStringLiteral("Papyrus"));
        font.setItalic(false);
        quit_b->setFont(font);
        quit_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        start_b = new QPushButton(welcome);
        start_b->setObjectName(QStringLiteral("start_b"));
        start_b->setGeometry(QRect(490, 150, 151, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Papyrus"));
        start_b->setFont(font1);
        start_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        label = new QLabel(welcome);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 150, 381, 101));
        label->setFont(font1);
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        stackedWidget->addWidget(welcome);
        gameset = new QWidget();
        gameset->setObjectName(QStringLiteral("gameset"));
        back_b = new QPushButton(gameset);
        back_b->setObjectName(QStringLiteral("back_b"));
        back_b->setGeometry(QRect(480, 360, 151, 41));
        back_b->setFont(font);
        back_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        gridLayoutWidget = new QWidget(gameset);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(60, 20, 381, 331));
        gl = new QGridLayout(gridLayoutWidget);
        gl->setSpacing(1);
        gl->setContentsMargins(11, 11, 11, 11);
        gl->setObjectName(QStringLiteral("gl"));
        gl->setContentsMargins(0, 0, 0, 0);
        run_b = new QPushButton(gameset);
        run_b->setObjectName(QStringLiteral("run_b"));
        run_b->setGeometry(QRect(60, 360, 151, 41));
        run_b->setFont(font);
        run_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        line = new QFrame(gameset);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(430, 10, 61, 361));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        row_set = new QSlider(gameset);
        row_set->setObjectName(QStringLiteral("row_set"));
        row_set->setGeometry(QRect(480, 40, 160, 22));
        row_set->setMinimum(5);
        row_set->setMaximum(15);
        row_set->setOrientation(Qt::Horizontal);
        col_set = new QSlider(gameset);
        col_set->setObjectName(QStringLiteral("col_set"));
        col_set->setGeometry(QRect(480, 80, 160, 22));
        col_set->setMinimum(5);
        col_set->setMaximum(15);
        col_set->setOrientation(Qt::Horizontal);
        rand_b = new QPushButton(gameset);
        rand_b->setObjectName(QStringLiteral("rand_b"));
        rand_b->setGeometry(QRect(480, 290, 151, 41));
        rand_b->setFont(font);
        rand_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        cat_b = new QPushButton(gameset);
        cat_b->setObjectName(QStringLiteral("cat_b"));
        cat_b->setGeometry(QRect(480, 130, 41, 41));
        cat_b->setFont(font);
        cat_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix2/cat.png"), QSize(), QIcon::Normal, QIcon::Off);
        cat_b->setIcon(icon);
        mouse_b = new QPushButton(gameset);
        mouse_b->setObjectName(QStringLiteral("mouse_b"));
        mouse_b->setGeometry(QRect(540, 130, 41, 41));
        mouse_b->setFont(font);
        mouse_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix2/mouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        mouse_b->setIcon(icon1);
        wall_b = new QPushButton(gameset);
        wall_b->setObjectName(QStringLiteral("wall_b"));
        wall_b->setGeometry(QRect(600, 130, 41, 41));
        wall_b->setFont(font);
        wall_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix2/wall.png"), QSize(), QIcon::Normal, QIcon::Off);
        wall_b->setIcon(icon2);
        mousemove = new QCheckBox(gameset);
        mousemove->setObjectName(QStringLiteral("mousemove"));
        mousemove->setGeometry(QRect(500, 199, 20, 21));
        label_2 = new QLabel(gameset);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(520, 190, 101, 41));
        label_2->setFont(font1);
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setFrameShadow(QFrame::Plain);
        catrush = new QCheckBox(gameset);
        catrush->setObjectName(QStringLiteral("catrush"));
        catrush->setGeometry(QRect(500, 230, 20, 21));
        label_3 = new QLabel(gameset);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(520, 220, 101, 41));
        label_3->setFont(font1);
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setFrameShadow(QFrame::Plain);
        stackedWidget->addWidget(gameset);
        gameplay = new QWidget();
        gameplay->setObjectName(QStringLiteral("gameplay"));
        gridLayoutWidget_2 = new QWidget(gameplay);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(20, 20, 441, 381));
        gl_gp = new QGridLayout(gridLayoutWidget_2);
        gl_gp->setSpacing(1);
        gl_gp->setContentsMargins(11, 11, 11, 11);
        gl_gp->setObjectName(QStringLiteral("gl_gp"));
        gl_gp->setContentsMargins(0, 0, 0, 0);
        back_b_gp = new QPushButton(gameplay);
        back_b_gp->setObjectName(QStringLiteral("back_b_gp"));
        back_b_gp->setGeometry(QRect(480, 360, 151, 41));
        back_b_gp->setFont(font);
        back_b_gp->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        solve_b = new QPushButton(gameplay);
        solve_b->setObjectName(QStringLiteral("solve_b"));
        solve_b->setGeometry(QRect(480, 290, 151, 41));
        solve_b->setFont(font);
        solve_b->setStyleSheet(QLatin1String("QPushButton {\n"
"color: white;\n"
"border-image: url(:/pics/button.png);\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:2px groove gray;\n"
"border-radius:10px;\n"
"}\n"
"QPushButton:pressed {\n"
"color: lightgray;\n"
"border-image: url(:/pics/button-pressed.png); \n"
"padding-top: -10px;\n"
"padding-bottom: -16px;\n"
"}\n"
"QPushButton:hover {\n"
"border-width: 12px;\n"
"padding: -12px 0px;\n"
"min-height: 25px;\n"
"min-width: 60px;\n"
"border:3px groove gray;\n"
"border-radius:10px;\n"
"}"));
        label_4 = new QLabel(gameplay);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(470, 60, 151, 41));
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setFrameShadow(QFrame::Plain);
        label_5 = new QLabel(gameplay);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(470, 120, 151, 41));
        label_5->setFont(font1);
        label_5->setFrameShape(QFrame::NoFrame);
        label_5->setFrameShadow(QFrame::Plain);
        cur_move_l = new QLabel(gameplay);
        cur_move_l->setObjectName(QStringLiteral("cur_move_l"));
        cur_move_l->setGeometry(QRect(620, 60, 51, 41));
        cur_move_l->setFont(font1);
        cur_move_l->setFrameShape(QFrame::NoFrame);
        cur_move_l->setFrameShadow(QFrame::Plain);
        req_move_l = new QLabel(gameplay);
        req_move_l->setObjectName(QStringLiteral("req_move_l"));
        req_move_l->setGeometry(QRect(620, 120, 51, 41));
        req_move_l->setFont(font1);
        req_move_l->setFrameShape(QFrame::NoFrame);
        req_move_l->setFrameShadow(QFrame::Plain);
        stackedWidget->addWidget(gameplay);

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        quit_b->setText(QApplication::translate("Widget", "QUIT", Q_NULLPTR));
        start_b->setText(QApplication::translate("Widget", "START GAME", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; color:#ffffff;\">Catch Me if You Can</span></p><p align=\"center\"><span style=\" font-size:24pt; color:#ffffff;\">v0.1</span></p></body></html>", Q_NULLPTR));
        back_b->setText(QApplication::translate("Widget", "BACK", Q_NULLPTR));
        run_b->setText(QApplication::translate("Widget", "RUN!", Q_NULLPTR));
        rand_b->setText(QApplication::translate("Widget", "RANDOM", Q_NULLPTR));
        cat_b->setText(QString());
        mouse_b->setText(QString());
        wall_b->setText(QString());
        mousemove->setText(QString());
        label_2->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">Mouse Move ?</span></p></body></html>", Q_NULLPTR));
        catrush->setText(QString());
        label_3->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">Cat Rush ?</span></p></body></html>", Q_NULLPTR));
        back_b_gp->setText(QApplication::translate("Widget", "BACK", Q_NULLPTR));
        solve_b->setText(QApplication::translate("Widget", "SOLVE", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">CURRENT MOVE:</span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" color:#fefefe;\">REQUIRED MOVE:</span></p></body></html>", Q_NULLPTR));
        cur_move_l->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><br/></p></body></html>", Q_NULLPTR));
        req_move_l->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><br/></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
