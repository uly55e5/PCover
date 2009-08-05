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
#include "sizesettings.h"
#include "cover.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
#include <QColorDialog>

SizeSettings::SizeSettings(Cover * cover, QWidget *parent)
        : QWidget(parent)
{
    _cover = cover;
    if (_cover == 0)
        close();
    createLayout();
    init();
}


SizeSettings::~SizeSettings()
{}

void SizeSettings::createLayout()
{
    setWindowTitle(tr("Größe und Farbe"));
    _mainLayout = new QVBoxLayout(this);

    _coverSizeLayout = new QHBoxLayout;

    _coverSizeLabel = new QLabel(tr("Covergröße"));
    _coverSizeBox = new QSpinBox;

    _coverSizeLayout->addWidget(_coverSizeLabel);
    _coverSizeLayout->addWidget(_coverSizeBox);

    _mainLayout->addLayout(_coverSizeLayout);

    _coverColorLayout = new QHBoxLayout;

    _coverColorLabel = new QLabel(tr("Hintergrundfarbe"));
    _coverColorPreview = new QPushButton;

    _coverColorLayout->addWidget(_coverColorLabel);
    _coverColorLayout->addWidget(_coverColorPreview);

    _mainLayout->addLayout(_coverColorLayout);

    _singleCoverSizeLayout = new QHBoxLayout;

    _singleCoverSizeLabel = new QLabel(tr("Einzelcovergröße"));
    _singleCoverSizeAutoBox = new QCheckBox(tr("automatisch"));
    _singleCoverSizeWidthBox = new QSpinBox;
    _singleCoverSizeHeightBox = new QSpinBox;
    _singleCoverSizeChainBox = new QCheckBox(tr("Quadrat"));

    _singleCoverSizeLayout->addWidget(_singleCoverSizeLabel);
    _singleCoverSizeLayout->addWidget(_singleCoverSizeWidthBox);
    _singleCoverSizeLayout->addWidget(_singleCoverSizeHeightBox);
    _singleCoverSizeLayout->addWidget(_singleCoverSizeChainBox);

    _mainLayout->addLayout(_singleCoverSizeLayout);
    _mainLayout->addWidget(_singleCoverSizeAutoBox);

    _singleCoverAlphaLayout = new QHBoxLayout;

    _singleCoverAlphaLabel = new QLabel(tr("Transparenz"));
    _singleCoverAlphaBox = new QSpinBox;

    _singleCoverAlphaLayout->addWidget(_singleCoverAlphaLabel);
    _singleCoverAlphaLayout->addWidget(_singleCoverAlphaBox);

    _mainLayout->addLayout(_singleCoverAlphaLayout);

    connect(_coverColorPreview,SIGNAL(clicked()),this,SLOT(setCoverColor()));
    connect(_coverSizeBox,SIGNAL(valueChanged(int)),_cover,SLOT(setCoverSize(int)));
    connect(_singleCoverAlphaBox,SIGNAL(valueChanged(int)),_cover,SLOT(setSingleCoverAlpha(int)));
    connect(_singleCoverSizeWidthBox, SIGNAL(valueChanged(int)),
            this, SLOT(setSingleCoverSizeWidth(int)));
    connect(_singleCoverSizeHeightBox,SIGNAL(valueChanged(int)),
            this, SLOT(setSingleCoverSizeHeight(int)));
    connect(_singleCoverSizeAutoBox,SIGNAL(toggled(bool)),
            _cover, SLOT(setAutoSingleCoverSize(bool)));
    connect(_singleCoverSizeAutoBox,SIGNAL(toggled(bool)),
            _singleCoverSizeWidthBox, SLOT(setDisabled(bool)));
    connect(_singleCoverSizeAutoBox,SIGNAL(toggled(bool)),
            _singleCoverSizeHeightBox, SLOT(setDisabled(bool)));
    connect(_singleCoverSizeAutoBox,SIGNAL(toggled(bool)),
            _singleCoverSizeChainBox, SLOT(setDisabled(bool)));
    connect(_singleCoverSizeAutoBox,SIGNAL(toggled(bool)),
            _singleCoverSizeChainBox, SLOT(setChecked(bool)));
    connect(_singleCoverSizeChainBox,SIGNAL(toggled(bool)),
            _singleCoverSizeHeightBox, SLOT(setDisabled(bool)));
    connect(_cover,SIGNAL(coverChanged()),this,SLOT(init()));

}

void SizeSettings::init()
{
    _singleCoverAlphaBox->setRange(0,100);
    _singleCoverAlphaBox->setValue(_cover->singleCoverAlpha());
    _singleCoverSizeWidthBox->setRange(0,10000);
    _singleCoverSizeHeightBox->setRange(0,10000);
    _coverSizeBox->setRange(0,10000);
    _coverSizeBox->setValue(_cover->coverSize());
    QPalette pal = _coverColorPreview->palette();
    pal.setColor(QPalette::Button,_cover->backgroundColor());
    _coverColorPreview->setPalette(pal);
    QSize size = _cover->singleCoverSize();
    _singleCoverSizeWidthBox->setValue(size.width());
    _singleCoverSizeHeightBox->setValue(size.height());
    _singleCoverSizeAutoBox->setChecked(_cover->autoSingleCoverSize());
}

void SizeSettings::setCoverColor()
{
    QColor color = QColorDialog::getColor();
    QPalette pal = _coverColorPreview->palette();
    pal.setColor(QPalette::Button,color);
    _coverColorPreview->setPalette(pal);
    _cover->setBackgroundColor(color);
}

void SizeSettings::setSingleCoverSizeWidth(int val)
{
    if ( val == _cover->singleCoverSize().width())
        return;
    if (_singleCoverSizeChainBox->isChecked())
        _cover->setSingleCoverSize(val,val);
    else
        _cover->setSingleCoverSize(val,_cover->singleCoverSize().height());
    _singleCoverSizeHeightBox->setValue(_cover->singleCoverSize().height());
}

void SizeSettings::setSingleCoverSizeHeight(int val)
{
    if ( val == _cover->singleCoverSize().height())
        return;
    else
        _cover->setSingleCoverSize(_cover->singleCoverSize().width(),val);
    _singleCoverSizeWidthBox->setValue(_cover->singleCoverSize().width());
}
