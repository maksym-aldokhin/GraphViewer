#include "GraphicController.h"
#include "qdatetime.h"

namespace GraphicViewer {

namespace impl {

class GraphicControllerImpl : public GraphicController
{
	Q_OBJECT

public:
	std::optional<QUuid> addGraphic(const GraphicPtr &) override;
	void removeGraphicById(QUuid) override;
	QVector<GraphicPtr> graphics() const override;
	QVector<QUuid> graphicsIds() const override;
	std::optional<GraphicPtr> getById(QUuid)const override;

	void update(const QMap<QString, double> &) override;
	void update(const QMap<QUuid, double> &) override;

private:
	QVector<QUuid> m_graphicSubsequence;
	QMap<QUuid, GraphicPtr> m_graphics;
};

std::optional<QUuid> GraphicControllerImpl::addGraphic(const GraphicPtr &v)
{
	for (const auto &graph : qAsConst(m_graphics)) {
		if (graph == v) {
			return std::nullopt;
		}
	}

	m_graphicSubsequence.append(v->id());
	m_graphics.insert(v->id(), v);

	emit graphicAdded(v->id());

	return v->id();
}

void GraphicControllerImpl::removeGraphicById(QUuid id)
{
	if (!m_graphics.contains(id)) {
		return;
	}

	m_graphics.remove(id);

	emit graphicRemoved(id);
}

QVector<GraphicPtr> GraphicControllerImpl::graphics() const
{
	QVector<GraphicPtr> res(m_graphics.size());

	for (const auto &graph : m_graphicSubsequence) {
		if (m_graphics.contains(graph)) {
			res.append(m_graphics[graph]);
		}
	}

	return res;
}

QVector<QUuid> GraphicControllerImpl::graphicsIds() const
{
	return m_graphicSubsequence;
}

std::optional<GraphicPtr> GraphicControllerImpl::getById(QUuid id) const
{
	if (m_graphics.contains(id)) {
		return m_graphics[id];
	}
	return std::nullopt;
}

void GraphicControllerImpl::update(const QMap<QString, double> &v)
{
	for (auto it = v.begin(); it != v.end(); ++it) {
		for (auto &graph : m_graphics) {
			if (graph->name() == it.key()) {
				graph->addPoint(it.value());
			}
		}
	}
	emit addedData();
}

void GraphicControllerImpl::update(const QMap<QUuid, double> &v)
{
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (m_graphics.contains(it.key())) {
			m_graphics[it.key()]->addPoint(it.value());
		}
	}
	emit addedData();
}

} // impl

std::shared_ptr<GraphicController> createGraphicController()
{
	return std::make_shared<impl::GraphicControllerImpl>();
}

} // GraphicViewer

#include "GraphicController.moc"
