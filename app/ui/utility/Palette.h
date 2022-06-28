#pragma once

#include <QObject>
#include <QColor>
#include <QJSEngine>
#include <QQmlEngine>

class Palette : public QObject
{
	Q_OBJECT
public:
	explicit Palette(QObject *parent = nullptr);

	Q_INVOKABLE QColor color1() const;
	Q_INVOKABLE QColor color2() const;
	Q_INVOKABLE QColor color3() const;
	Q_INVOKABLE QColor color4() const;
	Q_INVOKABLE QColor color5() const;

};

QObject *palette_create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

