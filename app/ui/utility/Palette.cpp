#include "Palette.h"

namespace {

static const QColor s_color1{"#535353"};
static const QColor s_color2{"#A1A1A1"};
static const QColor s_color3{"#E0E0E0"};
static const QColor s_color4{"#bdcf32"};
static const QColor s_color5{"#87bc45"};

}

Palette::Palette(QObject *parent)
    : QObject{parent}
{
}

QColor Palette::color1() const
{
	return s_color1;
}

QColor Palette::color2() const
{
	return s_color2;
}

QColor Palette::color3() const
{
	return s_color3;
}

QColor Palette::color4() const
{
	return s_color4;
}

QColor Palette::color5() const
{
	return s_color5;
}

QObject *palette_create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
	Q_UNUSED(jsEngine)
	return new Palette(qmlEngine);
}
