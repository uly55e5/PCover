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
#ifndef SONGFILE_H
#define SONGFILE_H

#include <QObject>

class QFile;
namespace TagLib
{
class FileRef;
}
/**
	@author David Raug <d.rauh@freenet.de>
*/
class SongFile : public QObject
{
Q_OBJECT
public:
    SongFile(QString name, QObject *parent = 0);

    ~SongFile();
    QString artist();
    QString title();
    uint track();
    QString genre();
    QString comment();
    uint year();
    QString album();
    private:
    TagLib::FileRef * _tagFile;
};

#endif
