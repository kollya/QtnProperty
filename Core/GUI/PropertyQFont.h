/*
   Copyright (c) 2012-1015 Alex Zhondin <qtinuum.team@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef PROPERTYFONT_H
#define PROPERTYFONT_H

#include "../Auxiliary/PropertyTemplates.h"
#include <QtGui/QFont>

class QTN_PE_CORE_EXPORT QtnPropertyQFontBase: public QtnSinglePropertyBase<QFont>
{
	Q_OBJECT
	QtnPropertyQFontBase(const QtnPropertyQFontBase& other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQFontBase(QObject *parent);

protected:
	// string conversion implementation
	bool fromStrImpl(const QString& str, bool edit) override;
	bool toStrImpl(QString& str) const override;

	P_PROPERTY_DECL_MEMBER_OPERATORS(QtnPropertyQFontBase)
};

P_PROPERTY_DECL_EQ_OPERATORS(QtnPropertyQFontBase, QFont)

class QTN_PE_CORE_EXPORT QtnPropertyQFontCallback: public QtnSinglePropertyCallback<QtnPropertyQFontBase>
{
	Q_OBJECT
	QtnPropertyQFontCallback(const QtnPropertyQFontCallback& other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQFontCallback(QObject *parent)
		: QtnSinglePropertyCallback<QtnPropertyQFontBase>(parent)
	{
	}

	P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQFontCallback, QtnPropertyQFontBase)
};

class QTN_PE_CORE_EXPORT QtnPropertyQFont: public QtnSinglePropertyValue<QtnPropertyQFontBase>
{
	Q_OBJECT
	QtnPropertyQFont(const QtnPropertyQFont& other) Q_DECL_EQ_DELETE;

public:
	explicit QtnPropertyQFont(QObject *parent)
		: QtnSinglePropertyValue<QtnPropertyQFontBase>(parent)
	{
	}

	static QString getPixelStr();
	static QString getPointStr();
	static QString getPreferDefaultStr();
	static QString getNoAntialiasStr();
	static QString getPreferAntialiasStr();
	static QString getFamilyLabel();
	static QString getFamilyDescription(const QString &owner_name);
	static QString getStyleLabel();
	static QString getStyleDescription(const QString &owner_name);
	static QString getSizeLabel();
	static QString getSizeDescription(const QString &owner_name);
	static QString getSizeUnitLabel();
	static QString getSizeUnitDescription(const QString &owner_name);
	static QString getBoldLabel();
	static QString getBoldDescription(const QString &owner_name);
	static QString getItalicLabel();
	static QString getItalicDescription(const QString &owner_name);
	static QString getUnderlineLabel();
	static QString getUnderlineDescription(const QString &owner_name);
	static QString getStrikeoutLabel();
	static QString getStrikeoutDescription(const QString &owner_name);
	static QString getKerningLabel();
	static QString getKerningDescription(const QString &owner_name);
	static QString getAntialiasingLabel();
	static QString getAntialiasingDescription(const QString &owner_name);

	P_PROPERTY_DECL_MEMBER_OPERATORS2(QtnPropertyQFont, QtnPropertyQFontBase)
};

#endif // PROPERTYFONT_H
