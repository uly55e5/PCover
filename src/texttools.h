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
#ifndef TEXTTOOLS_H
#define TEXTTOOLS_H

#include <QWidget>

class Cover;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
/**
	@author David Rauh <dave@bolivien>
*/
class TextTools : public QWidget
{
    Q_OBJECT
public:
    TextTools(Cover * cover, QWidget *parent = 0);

    ~TextTools();
    public slots:
        void setFont();
        void setColor();
        void addText();
    protected:
        void createLayout();
        void createActions();

        QVBoxLayout * _mainLayout;

        QHBoxLayout * _fontColorLayout;

        Cover * _cover;

        QPushButton * _fontButton;
        QPushButton * _fontColorButton;
        QPushButton * _addTextButton;

        QLabel * _fontColorLabel;
};

#endif
