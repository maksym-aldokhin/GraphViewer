#pragma once

#include <QObject>
#include <QString>
#include <QList>

#include <memory>

class QQmlApplicationEngine;

namespace GraphicViewer {

class GraphicController;

namespace ui {

class GraphicsModel;

}

}

class Graphics : public QObject
{
	Q_OBJECT
public:
	explicit Graphics(const QList<QString> &names,
	                  QObject *parent = nullptr);

	void update(const QMap<QString, double> &);
	void update(const QMap<QUuid, double> &);

private:
	std::shared_ptr<GraphicViewer::GraphicController> m_graphic;
	std::shared_ptr<GraphicViewer::ui::GraphicsModel> m_graphicModel;
	std::shared_ptr<QQmlApplicationEngine> m_engine;
};

