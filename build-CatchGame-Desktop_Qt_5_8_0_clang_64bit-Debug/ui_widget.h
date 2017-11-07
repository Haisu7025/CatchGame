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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *quit_b;
    QPushButton *start_b;
    QLabel *label;
    QWidget *page_2;
    QPushButton *back_b;
    QWidget *gridLayoutWidget;
    QGridLayout *gl;
    QPushButton *back_b_2;
    QWidget *page_3;

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
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        quit_b = new QPushButton(page);
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
        start_b = new QPushButton(page);
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
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 150, 381, 101));
        label->setFont(font1);
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        back_b = new QPushButton(page_2);
        back_b->setObjectName(QStringLiteral("back_b"));
        back_b->setGeometry(QRect(460, 360, 151, 41));
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
        gridLayoutWidget = new QWidget(page_2);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(50, 50, 321, 301));
        gl = new QGridLayout(gridLayoutWidget);
        gl->setSpacing(6);
        gl->setContentsMargins(11, 11, 11, 11);
        gl->setObjectName(QStringLiteral("gl"));
        gl->setContentsMargins(0, 0, 0, 0);
        back_b_2 = new QPushButton(page_2);
        back_b_2->setObjectName(QStringLiteral("back_b_2"));
        back_b_2->setGeometry(QRect(80, 360, 151, 41));
        back_b_2->setFont(font);
        back_b_2->setStyleSheet(QLatin1String("QPushButton {\n"
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
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        stackedWidget->addWidget(page_3);

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        quit_b->setText(QApplication::translate("Widget", "QUIT", Q_NULLPTR));
        start_b->setText(QApplication::translate("Widget", "START GAME", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; color:#ffffff;\">Catch Me if You Can</span></p><p align=\"center\"><span style=\" font-size:24pt; color:#ffffff;\">v0.1</span></p></body></html>", Q_NULLPTR));
        back_b->setText(QApplication::translate("Widget", "BACK", Q_NULLPTR));
        back_b_2->setText(QApplication::translate("Widget", "RUN!", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
