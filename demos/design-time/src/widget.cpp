/******************************************************************************
Copyright (c) 2010, Artem Galichkin <doomer3d@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->checkVisible->setChecked(true);
    ui->checkEnable->setChecked(ui->keyWidget->isEnabled());

    ui->comboBox->setCurrentIndex(ui->keyWidget->clearButtonShow());

    on_keyWidget_keySequenceChanged(ui->keyWidget->keySequence());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget::on_checkVisible_toggled(bool checked)
{
    ui->keyWidget->setVisible(checked);
}

void Widget::on_checkEnable_toggled(bool checked)
{
    ui->keyWidget->setEnabled(checked);
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    ui->keyWidget->setClearButtonShow(static_cast<QKeySequenceWidget::ClearButtonShow>(index));
}

void Widget::on_keyWidget_keyNotSupported()
{
    QMessageBox msg;
    msg.setWindowTitle("Message");
    msg.setText("This pressed key is not supported!");
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

void Widget::on_keyWidget_keySequenceChanged(QKeySequence seq)
{
    if (seq.isEmpty() == false)
    {
        ui->label->setText(seq.toString());
    }
    else
    {
        ui->label->setText(ui->keyWidget->noneText());
    }
}

void Widget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Icon", QString(), "PNG Images (*.png);;All Files (*.*)");

    if (fileName.isEmpty() != true)
    {
        ui->keyWidget->setClearButtonIcon(QIcon(fileName));
    }
}
