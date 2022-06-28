#include "ValueStorage.h"

namespace GraphicViewer {

ValueStorage::ValueStorage(QDateTime startTime,
                           QObject *parent)
    : QObject{parent}
    , m_startTime{startTime}
{

}

void ValueStorage::addPoint(double value, QDateTime time)
{
	updateMaxValue(value);
	updateMinValue(value);

	const auto deltaTime = time.toMSecsSinceEpoch() - m_startTime.toMSecsSinceEpoch();
	//TODO add maximum points in storage
	m_points.push_back({value, QDateTime::fromMSecsSinceEpoch(deltaTime)});

	while (m_points.size() > 1) {
		m_points.removeFirst();
	}
}

QVector<Point> ValueStorage::getPoints() const
{
	return m_points;
}

Point ValueStorage::getLastPoint() const
{
	if (m_points.isEmpty()) {
		return {0.0, QDateTime{}};
	}

	return m_points.last();
}

double ValueStorage::maxValue() const
{
	return m_maxValue;
}

double ValueStorage::minValue() const
{
	return m_minValue;
}

void ValueStorage::updateMaxValue(double v)
{
	if (m_points.empty()) {
		m_maxValue = v;
		return;
	}

	if (v > m_maxValue) {
		m_maxValue = v;
	}
}

void ValueStorage::updateMinValue(double v)
{
	if (m_points.empty()) {
		m_minValue = v;
		return;
	}

	if (v < m_minValue) {
		m_minValue = v;
	}
}

} // GraphicViewer
