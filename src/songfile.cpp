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
#include "songfile.h"

#include "taglib/fileref.h"
#include "taglib/tag.h"

#include <QFile>
#include <QtDebug>

SongFile::SongFile(QString name, QObject *parent)
 : QObject(parent)
{
    char * fileName = "";
    if (QFile::exists(name))
    {
        _tagFile = new TagLib::FileRef(name.toUtf8().data());
        qDebug() << name << "existiert";
    }
    else qDebug() << name << "existiert nicht";
}


SongFile::~SongFile()
{
    delete _tagFile;
}

QString SongFile::artist()
{
    QString artist;
    artist =  TStringToQString(_tagFile->tag()->artist());
    qDebug() << artist;
    return artist;
}
QString SongFile::title()
{
    QString title;
    TagLib::String s = _tagFile->tag()->title();
    title =  TStringToQString(_tagFile->tag()->title());
    qDebug() << title;
    return title;
}
uint SongFile::year()
{
    uint year;
    year =  _tagFile->tag()->year();
    qDebug() << year;
    return year;
}
QString SongFile::album()
{
    QString title;
    title =  TStringToQString(_tagFile->tag()->album());
    qDebug() << title;
    return title;
}
QString SongFile::comment()
{
    QString title;
    title =  TStringToQString(_tagFile->tag()->comment());
    qDebug() << title;
    return title;
}
QString SongFile::genre()
{
    QString title;
    title =  TStringToQString(_tagFile->tag()->genre());
    qDebug() << title;
    return title;
}
uint SongFile::track()
{
    uint track;
    track =  _tagFile->tag()->track();
    qDebug() << track;
    return track;
}
