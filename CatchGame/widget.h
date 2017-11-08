#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractButton>
#include <QPushButton>
#include "QPropertyAnimation"
#include "algthm.h"

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

  void init_widget_look();
  void bind_slots();
  void create_move_animation(QAbstractButton *obj, QPoint target);

protected:
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent *event);

private:
  Ui::Widget *ui;
  bool mMoveing;
  QPoint mMovePosition;
  QPropertyAnimation *anim;
  QPushButton *button_group[MAX_MAP_SIZE][MAX_MAP_SIZE];

  // Game Set
  int row, col;
  int cmap[MAX_MAP_SIZE][MAX_MAP_SIZE];
  bool cat_picked, mouse_picked;
  bool mouse_move, cat_rush;

  void gen_map(int row, int col);
  void rand_gen_cmap();

  void set_cat(int m, int n);
  void set_mouse(int m, int n);
  void set_wall(int m, int n);
  void set_blank(int m, int n);

  void shrink_out(QWidget *w);
  void shrink_in(QWidget *w);
  void shrink_out_and_quit(QWidget *w);

private slots:
  void start_slot();
  void pick_map_slot();
  void pick_icon_slot();
  void change_size_slot(int csize);

  void rand_slot();
  void quit_slot();
  void back_slot();
};

#endif // WIDGET_H
