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
#ifndef M3UPLAYLIST_H
#define M3UPLAYLIST_H

#include <QObject>
#include <QList>

class QFile;
class QString;
class QTime;

/**
    @author David Raug <d.rauh@freenet.de>
*/
class M3UPlaylist : public QObject
{

        Q_OBJECT

        typedef struct SongListItem
        {
            QString fileName;
            QString title;
            int length;
            bool exists;
        };
        typedef QList<SongListItem *> SongList;

    public:
        M3UPlaylist ( const QString & name,QObject *parent = 0 );
        M3UPlaylist ( QFile & file,QObject *parent = 0 );
        ~M3UPlaylist();
        void read ( QFile & file );
        QString name() const;

        QString fileNameForTrack ( uint track );
        int lengthForTrack ( uint track );
        QTime timeForTrack ( uint track );
        QString titleForTrack( uint track );
        bool fileForTrackExists( uint track );

        int size();
        QString dir();
        QString formattedSonglist ();
        QString twoDigitNumber ( int num );
        QString listFormat()const;
        void setListFormat(const QString & format);
    private:
        SongList _playList;
        QString _fileName;
        bool _extended;
        QString _listFormat;
};

#endif
