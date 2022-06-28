#include "Graphics.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>

#include "details/GraphicController.h"
#include "details/Graphic.h"
#include "uiModels/GraphicsModel.h"
#include "ui/utility/ModelUtil.h"
#include "ui/utility/Palette.h"

Graphics::Graphics(const QList<QString> &names,
                   QObject *parent)
    : QObject{parent}
    , m_graphic{GraphicViewer::createGraphicController()}
{
	for (const auto &n : names) {
		m_graphic->addGraphic(GraphicViewer::createGraphic(n));
	}

	m_graphicModel = std::make_shared<GraphicViewer::ui::GraphicsModel>(m_graphic);

	m_engine = std::make_shared<QQmlApplicationEngine>();
	const QUrl url(QStringLiteral("qrc:/mainWindow/mainWindow.qml"));
	qmlRegisterSingletonType<ModelUtil>("ModelUtil", 1, 0, "ModelUtil", modelutil_create);
	qmlRegisterSingletonType<ModelUtil>("Palette", 1, 0, "Palette", palette_create);
	m_engine->rootContext()->setContextProperty("GraphicModel", m_graphicModel.get());
	m_engine->load(url);
}

void Graphics::update(const QMap<QString, double> &v)
{
	m_graphic->update(v);
}

void Graphics::update(const QMap<QUuid, double> &v)
{
	m_graphic->update(v);
}
