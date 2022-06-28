#pragma once

#include <QObject>
#include <QString>
#include <QList>

#include <memory>

#if defined(GRAPH_VIEWER_TEST_MODE)
#  define GraphViewer_EXPORT Q_DECL_EXPORT
#else
#  define GraphViewer_EXPORT Q_DECL_IMPORT
#endif

class QQmlApplicationEngine;

namespace GraphicViewer {

class GraphicController;

namespace ui {

class GraphicsModel;

}

}

class GraphViewer_EXPORT Graphics : public QObject
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

