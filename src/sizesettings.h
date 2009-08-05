/***************************************************************************
 *   Copyright (C) 2007 by David Rauh   *
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
#ifndef SIZESETTINGS_H
#define SIZESETTINGS_H

#include <QWidget>
class Cover;

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QSpinBox;
class QPushButton;
class QCheckBox;

/**
	@author David Rauh <dave@bolivien>
*/
class SizeSettings : public QWidget
{
    Q_OBJECT
public:
    SizeSettings(Cover * cover, QWidget *parent = 0);

    ~SizeSettings();
    public slots:
        void init();
    private slots:
        void setCoverColor();
        void setSingleCoverSizeWidth(int val);
        void setSingleCoverSizeHeight(int val);
    private:
        void createLayout();

        Cover * _cover;

        QVBoxLayout * _mainLayout;

        QHBoxLayout * _coverSizeLayout;
        QHBoxLayout * _coverColorLayout;
        QHBoxLayout * _singleCoverSizeLayout;
        QHBoxLayout * _singleCoverAlphaLayout;

        QLabel * _coverSizeLabel;
        QLabel * _coverColorLabel;
        QLabel * _singleCoverSizeLabel;
        QLabel * _singleCoverAlphaLabel;

        QSpinBox * _coverSizeBox;
        QSpinBox * _singleCoverSizeWidthBox;
        QSpinBox * _singleCoverSizeHeightBox;
        QSpinBox * _singleCoverAlphaBox;

        QCheckBox * _singleCoverSizeChainBox;
        QCheckBox * _singleCoverSizeAutoBox;

        QPushButton * _coverColorPreview;
};

#endif
