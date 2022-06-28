#pragma once

#include <QObject>
#include <QDateTime>
#include <QVector>

namespace GraphicViewer {

struct Point {
	const QDateTime time;
	const double value;

	Point(const double value_, const QDateTime time_)
	    : time(time_)
	    , value(value_)
	{
	}
};

class ValueStorage : public QObject
{
	Q_OBJECT
public:

	explicit ValueStorage(QDateTime startTime = QDateTime::currentDateTime(),
	                      QObject *parent = nullptr);
	void addPoint(double value, QDateTime time = QDateTime::currentDateTime());

	QVector<Point> getPoints() const;
	Point getLastPoint() const;
	double maxValue() const;
	double minValue() const;

private:
	void updateMaxValue(double v);
	void updateMinValue(double v);

	double m_maxValue;
	double m_minValue;
	const QDateTime m_startTime;

	QVector<Point> m_points;
};

} // GraphicViewer
