/***************************************************************************
 *   Copyright (C) 2007 by David Raug   *
 *   d.rauh@freenet.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "texttools.h"
#include "cover.h"

#include <QPushButton>
#include <QFontDialog>
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>

TextTools::TextTools(Cover * cover, QWidget *parent)
        : QWidget(parent)
{
    _cover = cover;
    createLayout();
}


TextTools::~TextTools()
{}

void TextTools::createLayout()
{
    _mainLayout = new QVBoxLayout(this);

    _addTextButton = new QPushButton(tr("Neuer Text"));

    _fontColorLayout = new QHBoxLayout;

    _fontColorLabel = new QLabel(tr("Farbe"));
    _fontColorButton = new QPushButton;

    _fontColorLayout->addWidget(_fontColorLabel);
    _fontColorLayout->addWidget(_fontColorButton);

    _fontButton = new QPushButton(tr("Zeichen"));

    _mainLayout->addWidget(_addTextButton);
    _mainLayout->addLayout(_fontColorLayout);
    _mainLayout->addWidget(_fontButton);

    connect(_fontButton,SIGNAL(clicked()), this, SLOT(setFont()));
    connect(_fontColorButton,SIGNAL(clicked()), this , SLOT(setColor()));
    connect(_addTextButton, SIGNAL(clicked()), this , SLOT(addText()));
}

void TextTools::createActions()
{
}

void TextTools::setFont()
{
    QGraphicsTextItem * item = _cover->selectedTextItem();
    if (item == 0)
    {
        QMessageBox::warning(this,"Kein Text markiert","Es wurde kein Text ausgewählt.");
        return;
    }
    bool * ok;
    QFont font = item->font();
    item->setFont(QFontDialog::getFont(ok,font));
}

void TextTools::setColor()
{
    QGraphicsTextItem * item = _cover->selectedTextItem();
    if (item == 0)
    {
        QMessageBox::warning(this,"Kein Text markiert","Es wurde kein Text ausgewählt.");
        return;
    }
    QColor color = QColorDialog::getColor();
    item->setDefaultTextColor(color);
    QPalette pal = _fontColorButton->palette();
    pal.setColor(QPalette::Button,color);
    _fontColorButton->setPalette(pal);
}

void TextTools::addText()
{
    _cover->addText();
}