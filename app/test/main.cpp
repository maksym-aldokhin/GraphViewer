#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QtMath>
#include <memory>

#include "qdebug.h"
#include "qobject.h"

#include "public/Graphics.h"

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);

	const QList<QString> names {
		"test1",
		"test2",
		"test3",
		"test4",
		"test5",
		"test6",
	};

	auto controller = std::make_unique<Graphics>(names);

	double points{0.0};

	QTimer timer;
	QObject::connect(&timer,
	                 &QTimer::timeout,
	                 [&controller, &names, &points](){
		QMap<QString, double> newData;

		newData.insert(names[0], qSin(qDegreesToRadians(points + M_PI_4)) * 80);
		newData.insert(names[1], qSin(qDegreesToRadians(points)) * 15);
		newData.insert(names[2], qCos(qDegreesToRadians(points)) * 100);
		newData.insert(names[3], qSin(qDegreesToRadians(points * 2)) * 10);
		newData.insert(names[4], qCos(qDegreesToRadians(points)) * 10 + 50);
		newData.insert(names[5], qCos(qDegreesToRadians(points * 4)) *20 - 80);
		points += 1;


		controller->update(newData);
	});

	timer.start(10);

	return app.exec();
}
