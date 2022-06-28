#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QtMath>

#include "details/GraphicController.h"
#include "details/Graphic.h"

#include "qdebug.h"
#include "qobject.h"
#include "uiModels/GraphicsModel.h"
#include "ui/utility/ModelUtil.h"
#include "ui/utility/Palette.h"

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);

	auto controller = GraphicViewer::createGraphicController();
	controller->addGraphic(GraphicViewer::createGraphic("test1", "log text1"));
	controller->addGraphic(GraphicViewer::createGraphic("test2", "log text2"));
	controller->addGraphic(GraphicViewer::createGraphic("test3"));
	controller->addGraphic(GraphicViewer::createGraphic("test4", "log text4"));
	controller->addGraphic(GraphicViewer::createGraphic("test5", "log text5"));
	controller->addGraphic(GraphicViewer::createGraphic("test6"));

	double points{0.0};

	QTimer timer;
	QObject::connect(&timer,
	                 &QTimer::timeout,
	                 [controller, &points](){
		const auto ids = controller->graphicsIds();

		QMap<QUuid, double> newData;

		newData.insert(ids[0], qSin(qDegreesToRadians(points + M_PI_4)) * 80);
		newData.insert(ids[1], qSin(qDegreesToRadians(points)) * 15);
		newData.insert(ids[2], qCos(qDegreesToRadians(points)) * 100);
		newData.insert(ids[3], qSin(qDegreesToRadians(points * 2)) * 10);
		newData.insert(ids[4], qCos(qDegreesToRadians(points)) * 10 + 50);
		newData.insert(ids[5], qCos(qDegreesToRadians(points * 4)) *20 - 80);
		points += 1;


		controller->update(newData);
	});

	auto model = GraphicViewer::ui::GraphicsModel(controller);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/mainWindow/mainWindow.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
	                 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

	qmlRegisterSingletonType<ModelUtil>("ModelUtil", 1, 0, "ModelUtil", modelutil_create);
	qmlRegisterSingletonType<ModelUtil>("Palette", 1, 0, "Palette", palette_create);
	engine.rootContext()->setContextProperty("GraphicModel", &model);
	engine.load(url);
	timer.start(10);

	return app.exec();
}
