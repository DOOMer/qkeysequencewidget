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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>

#include "qkeysequencewidget.h"

class Widget : public QWidget
{
Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:

public Q_SLOTS:
    void enableWidget1(bool enable);
    void visibleWidget1(bool visible);
    void changeClearButtonPos(int pos);
    void keySequenceChanged(const QKeySequence &seq);
    void keyNotSupported();
    void changeClearIcon();

private:
    QVBoxLayout *verticalMain;
    QHBoxLayout *horizontal_1;
    QHBoxLayout *horizontal_2;
    QHBoxLayout *horizontal_3;
    QHBoxLayout *horizontal_4;

    QLabel *labOne;
    QLabel *labOneClearBtn;

    QKeySequenceWidget *keyWidget;
    QKeySequenceWidget *keyWidget2;

    QCheckBox *checkBoxEnable1;
    QCheckBox *checkBoxVisible1;    

    QComboBox *combo1;

    QPushButton *changeClrBtnIcon;
};

#endif // WIDGET_H
