/*
     OpenDCP: Builds Digital Cinema Packages
     Copyright (c) 2010-2011 Terrence Meiczinger, All Rights Reserved

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QDir>
#include "dialogj2kconversion.h"

DialogJ2kConversion::DialogJ2kConversion(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint);

    connect(buttonClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonStop, SIGNAL(clicked()), this, SLOT(abort()));
}

void DialogJ2kConversion::init(int imageCount, int threadCount)
{
    QString labelText;

    currentCount = 0;
    done         = 0;
    cancelled    = 0;
    totalCount   = imageCount;

    progressBar->reset();
    progressBar->setMinimum(0);
    progressBar->setMaximum(totalCount);

    labelText.sprintf("Conversion using %d threads(s)",threadCount);
    labelThreadCount->setText(labelText);

    setButtons(1);
}

void DialogJ2kConversion::step()
{
    QString labelText;

    if (done == 1 && cancelled == 0) {
        currentCount = totalCount;
    }

    labelText.sprintf("Completed %d of %d",currentCount,totalCount);
    labelTotal->setText(labelText);
    progressBar->setValue(currentCount);

    currentCount++;
}

void DialogJ2kConversion::finished()
{
    done = 1;
    setButtons(0);
    step();
}

void DialogJ2kConversion::abort()
{
    setButtons(0);
    cancelled = 1;
    emit cancel();
}

void DialogJ2kConversion::setButtons(int state)
{
    if (state == 0) {
        buttonClose->setEnabled(true);
        buttonStop->setEnabled(false);
    } else {
        buttonClose->setEnabled(false);
        buttonStop->setEnabled(true);
    }
}