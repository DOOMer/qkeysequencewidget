/******************************************************************************
Copyright (c) 2010, Artem Galichkin <doomer3d@gmail.com>
All rights reserved.

BSD License Usage

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

*******************************************************************************

GNU General Public License Usage

Alternatively, this file may be used under the terms of the GNU
General Public License version 3.0 as published by the Free Software
Foundation and appearing in the file LICENSE.GPL included in the
packaging of this file. Please review the following information to
ensure the GNU General Public License version 3.0 requirements will be
met: http://www.gnu.org/copyleft/gpl.html.

*******************************************************************************/

#include "widget.h"

#include <QDebug>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    resize(320, 120);
    setWindowTitle("QKeySequenceWidget Demo");

    keyWidget = new QKeySequenceWidget(QKeySequence("Ctrl+Space"), QString("Undefined keys"), this);

    // labels for displaying keysequences
    labOne = new QLabel(this);
    keySequenceChanged(keyWidget->keySequence());

    // labels for clearbutton combobox
    labOneClearBtn = new QLabel("Clear Button is:", this);

    // checkboxes for enable | disable keyWidgets
    checkBoxEnable1 = new QCheckBox(QString("One enabled"), this);
    checkBoxEnable1->setChecked(keyWidget->isEnabled());

    // checkboxes for set visible keyWidgets
    checkBoxVisible1 = new QCheckBox(QString("Visible"), this);
    checkBoxVisible1->setChecked(true);

    // comboboxes for clearbuttons states
    combo1 = new QComboBox(this);

    // utem of list clearbuttons states
    QStringList itemList;
    itemList << "No Show" << "Show Left" << "Show Right";

    combo1->addItems(itemList);
    combo1->setCurrentIndex(static_cast<int>(keyWidget->clearButtonShow()));

    // chane cleearbutton icon
    changeClrBtnIcon = new QPushButton("Change Icon");
//    spacerLeft = new QSpacerItem();
//    spacerRisght = new QSpacerItem();

    // horizontal layout 1a - for keyWidget & label
    horizontal_1 = new QHBoxLayout;
    horizontal_1->addWidget(labOne);
    horizontal_1->addWidget(keyWidget);

    // horizontal layout 1b - for checkboxes
    horizontal_2 = new QHBoxLayout;
    horizontal_2->addWidget(checkBoxEnable1);
    horizontal_2->addWidget(checkBoxVisible1);

    // horizontal layout 1c - for combobox
    horizontal_3 = new QHBoxLayout;
    horizontal_3->addWidget(labOneClearBtn);
    horizontal_3->addWidget(combo1);

    //
    horizontal_4 = new QHBoxLayout;
    horizontal_4->addSpacing(80);
    horizontal_4->addWidget(changeClrBtnIcon);
    horizontal_4->addSpacing(80);

    // create vertical layout
    verticalMain = new QVBoxLayout(this);

    // add horizontal layouts to vertical
    verticalMain->addLayout(horizontal_1);
    verticalMain->addLayout(horizontal_2);
    verticalMain->addLayout(horizontal_3);
    verticalMain->addLayout(horizontal_4);

    // set main layout
    setLayout(verticalMain);

    keyWidget2 = new QKeySequenceWidget;

    // connecting to slots
    connect(checkBoxEnable1, SIGNAL(toggled(bool)), this, SLOT(enableWidget1(bool)));
    connect(checkBoxVisible1, SIGNAL(toggled(bool)), this, SLOT(visibleWidget1(bool)));    
    connect(combo1, SIGNAL(currentIndexChanged(int)), this, SLOT(changeClearButtonPos(int)));
    connect(keyWidget, SIGNAL(keySequenceChanged(QKeySequence)), this, SLOT(keySequenceChanged(QKeySequence)));
    connect(keyWidget, SIGNAL(keyNotSupported()), this, SLOT(keyNotSupported()));
    connect(changeClrBtnIcon, SIGNAL(clicked()), this, SLOT(changeClearIcon()));

    keyWidget->setToolTip("Blah-Blah");
}


void Widget::enableWidget1(bool enable)
{
    keyWidget->setEnabled(enable);
}


void Widget::visibleWidget1(bool visible)
{
    keyWidget->setVisible(visible);
}

void Widget::changeClearButtonPos(int pos)
{
    keyWidget->setClearButtonShow(static_cast<QKeySequenceWidget::ClearButtonShow>(pos));
}

void Widget::keySequenceChanged(const QKeySequence &seq)
{
    if (seq.isEmpty() == false)
    {
        labOne->setText(seq.toString());
    }
    else
    {
        labOne->setText(keyWidget->noneText());
    }
}

void Widget::keyNotSupported()
{
    QMessageBox msg;
    msg.setWindowTitle("Message");
    msg.setText("This pressed key is not supported!");
    msg.setIcon(QMessageBox::Information);
    msg.exec();
}

void Widget::changeClearIcon()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Icon", QString(), "PNG Images (*.png);;All Files (*.*)");

    if (fileName.isEmpty() != true)
    {
        keyWidget->setClearButtonIcon(QIcon(fileName));
    }
}
