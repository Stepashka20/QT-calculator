#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->numbersButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(number_was_clicked(QAbstractButton*)));
    connect(ui->operationsButtonsGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(operation_pressed(QAbstractButton*)));
    this->setWindowOpacity(0.95);
    this->setWindowTitle("Калькулятор");
    this->setWindowIcon(QIcon(":/resourses/img/calculator.png"));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::number_was_clicked(QAbstractButton* btn)
{
    if (ui->main_input->text()=="0" && btn->text()=="0") return;
    if (equal_pressed){
        equal_pressed = false;
        ui->main_input->setText("");
        ui->current_expression->setText("");
        history_exists = false;
    }
    if (ui->main_input->text()=="0" || !waiting_for_operand ) ui->main_input->setText("");
    if (!waiting_for_operand) waiting_for_operand = true;
    if (next_clear_screen) next_clear_screen = false;

    ui->main_input->setText(ui->main_input->text()+btn->text());
//    qInfo() << btn->property("type").toString() ;
//    QString prop = btn->property("type").toString();
}


void Widget::operation_pressed(QAbstractButton *btn)
{
    if (ui->main_input->text().endsWith(".")) delete_last_character();
    qInfo() << history_exists;
    if (history_exists){
        double result = calculate_result();
        ui->main_input->setText(QString::number(result));
        ui->current_expression->setText(QString::number(result)+" "+btn->text()+" ");
    }
    operation = btn->text();
    last_number = ui->main_input->text().toDouble();
    ui->current_expression->setText(QString::number((double)last_number)+" "+operation);
    waiting_for_operand = false;
    equal_pressed = false;
    history_exists = true;
}

double Widget::calculate_result()
{
    double result = 0.0;
    if (operation=="+"){
        result = last_number+ui->main_input->text().toDouble();
    } else if (operation=="-"){
        result = last_number-ui->main_input->text().toDouble();
    }else if (operation=="×"){
        result = last_number*ui->main_input->text().toDouble();
    }else if (operation=="÷"){
        result = (last_number / ui->main_input->text().toDouble());
    }
    return result;
}

void Widget::print_result()
{
    ui->current_expression->setText(QString::number((double)last_number)+" "+operation+" "+ui->main_input->text()+" ="); 
    next_clear_screen = true;
    equal_pressed = true;
    ui->main_input->setText(QString::number(calculate_result()));

}

void Widget::delete_last_character()
{
    QString str = ui->main_input->text();
    str.chop(1);
    ui->main_input->setText(str);
}

void Widget::on_equal_button_clicked()
{
    if (ui->main_input->text().endsWith(".")) delete_last_character();
    if (ui->current_expression->text()!=""){
        print_result();
        history_exists = false;
    }
}


void Widget::on_clear_all_button_clicked()
{
    ui->main_input->setText("0");
    ui->current_expression->setText("");
    history_exists = false;
}


void Widget::on_dot_button_clicked()
{
    if (!ui->main_input->text().contains(".")){
        ui->main_input->setText(ui->main_input->text()+".");
    }
}


void Widget::on_delete_last_number_button_clicked()
{
    if (ui->main_input->text().length()==1){
        ui->main_input->setText("0");
    } else {
         delete_last_character();
    }

}


void Widget::on_negate_button_clicked()
{
    if (ui->main_input->text().endsWith(".")) delete_last_character();
    if (ui->main_input->text()!="0")
        ui->main_input->setText("-"+ui->main_input->text());
}

