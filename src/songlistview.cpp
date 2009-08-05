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
#include "songlistview.h"
#include "m3uplaylist.h"

#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


SongListView::SongListView(QWidget *parent)
 : QWidget(parent)
{
    _playlist = 0;
    createLayout();
}

SongListView::SongListView(M3UPlaylist * list, QWidget *parent)
    : QWidget(parent)
{
    _playlist = list;
    createLayout();
    updateSonglist();
}


SongListView::~SongListView()
{
}

const QString SongListView::s_formatToolTip=trUtf8("Folgende Zeichenfolgen werden ersetzt:\n%a\tKünstler\n%c\tKommentar\n%D\tLänge\n%F\tDatei\n%g\tGenre\n%l\tAlbum\n%s\tTitel\n%t,%tt\tTitelnummer (aus Datei)\n%T,%TT\tTitelnummer\n%y\tJahr\n\\t\tTabulator");

void SongListView::createLayout()
{

    _format = "%TT. \"%s\" - %a: %D";
    _formatLabel = new QLabel(trUtf8("Format: "),this);

    _formatEdit = new QLineEdit(_format);
    _formatEdit->setToolTip(s_formatToolTip);

    _listLabel = new QLabel();

    _addToCoverButton = new QPushButton(tr("<- Cover"));

    _mainLayout = new QVBoxLayout(this);
    _editLayout = new QHBoxLayout();
    _editLayout->addWidget(_formatLabel);
    _editLayout->addWidget(_formatEdit);
    _mainLayout->addLayout(_editLayout);
    _mainLayout->addWidget(_addToCoverButton);
    _mainLayout->addWidget(_listLabel);
    _mainLayout->addStretch();

    connect(_formatEdit,SIGNAL(textChanged(const QString &)), this, SLOT(setFormat(QString)));
    connect(_addToCoverButton, SIGNAL(clicked()), this, SLOT(addToCoverClicked()));
}

void SongListView::addToCoverClicked()
{
    emit addToCover(_listLabel->text());
}

void SongListView::setFormat(QString format)
{
    _format = format;
    updateSonglist();
}

void SongListView::setPlaylist(M3UPlaylist * list)
{
    _playlist = list;
    updateSonglist();
}

void SongListView::updateSonglist()
{
    _playlist->setListFormat(_format);
    _listLabel->setText(_playlist->formattedSonglist());
    emit songlistChanged();
}




