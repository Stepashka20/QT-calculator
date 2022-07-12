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
   double calculate_result();
   void print_result();
   double result;
   QString operation;
   double last_number;
   bool history_exists = false;
   bool next_clear_screen = false;
   bool equal_pressed = false;
   bool waiting_for_operand = true;
   void delete_last_character();
private slots:
    void number_was_clicked(QAbstractButton*btn);
    void operation_pressed(QAbstractButton*btn);
    void on_equal_button_clicked();
    void on_clear_all_button_clicked();
    void on_dot_button_clicked();
    void on_delete_last_number_button_clicked();
    void on_negate_button_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
