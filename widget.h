#ifndef WIDGET_H
#define WIDGET_H

#include "qabstractbutton.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
   void number_pressed(QAbstractButton*btn);
   void operation_pressed(QAbstractButton*btn);
   double calculate_result();
   void print_result();
   double result;
   QString operation;
   double last_number;
   bool history_exists = false;
   bool next_clear_screen = false;
   bool equal_pressed = false;
   bool waiting_for_operand = true;

private slots:
    void buttonWasClicked(QAbstractButton*btn);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
