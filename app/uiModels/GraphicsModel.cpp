#include "GraphicsModel.h"

#include <QDebug>

#include <algorithm>

#include "details/GraphicController.h"
#include "qabstractitemmodel.h"
#include "qcolor.h"
#include "qpoint.h"

namespace {

QVector<QString> colors {
	"#e60049", "#0bb4ff", "#50e991", "#e6d800", "#9b19f5", "#ffa300", "#dc0ab4", "#b3d4ff", "#00bfa0",
	"#ea5545", "#f46a9b", "#ef9b20", "#edbf33", "#ede15b", "#bdcf32", "#87bc45", "#27aeef", "#b33dc6",
	"#e60049", "#0bb4ff", "#50e991", "#e6d800", "#9b19f5", "#ffa300", "#dc0ab4", "#b3d4ff", "#00bfa0",
	"#fd7f6f", "#7eb0d5", "#b2e061", "#bd7ebe", "#ffb55a", "#ffee65", "#beb9db", "#fdcce5", "#8bd3c7",
	"#115f9a", "#1984c5", "#22a7f0", "#48b5c4", "#76c68f", "#a6d75b", "#c9e52f", "#d0ee11", "#d0f400",
	"#d7e1ee", "#cbd6e4", "#bfcbdb", "#b3bfd1", "#a4a2a8", "#df8879", "#c86558", "#b04238", "#991f17",
	"#0000b3", "#0010d9", "#0020ff", "#0040ff", "#0060ff", "#0080ff", "#009fff", "#00bfff", "#00ffff",
	"#1984c5", "#22a7f0", "#63bff0", "#a7d5ed", "#e2e2e2", "#e1a692", "#de6e56", "#e14b31", "#c23728",
	"#ffb400", "#d2980d", "#a57c1b", "#786028", "#363445", "#48446e", "#5e569b", "#776bcd", "#9080ff",
	"#54bebe", "#76c8c8", "#98d1d1", "#badbdb", "#dedad2", "#e4bcad", "#df979e", "#d7658b", "#c80064",
	"#e27c7c", "#a86464", "#6d4b4b", "#503f3f", "#333333", "#3c4e4b", "#466964", "#599e94", "#6cd4c5",
};

QColor getColor(int n)
{
	if (n >= 0 && n < colors.size()) {
		return QColor(colors[n]);
	}
	return QColor(0, 0, 0);
}

}

namespace GraphicViewer::ui {

GraphicsModel::GraphicsModel(const std::shared_ptr<GraphicController>& controller,
                             QObject *parent)
    : QAbstractListModel{parent}
    , m_controller{controller}
{
	connect(m_controller.get(),
	        &GraphicController::graphicAdded,
	        this,
	        &GraphicsModel::graphicAdded);
	connect(m_controller.get(),
	        &GraphicController::addedData,
	        this,
	        &GraphicsModel::newData);
	connect(m_controller.get(),
	        &GraphicController::addedData,
	        this,
	        [this](){
		emit dataChanged(index(0), index(rowCount()-1), QVector<int>() << LastValueYRole);
	});

	for (const auto &graph : m_controller->graphicsIds()) {
		graphicAdded(graph);
	}
}

QVariant GraphicsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	const auto item = m_graphics[static_cast<std::size_t>(index.row())];

	auto graphic = m_controller->getById(item.id);
	if (!graphic) {
		return QVariant();
	}

	switch (role) {
	case NameRole:
		return QVariant::fromValue(graphic.value()->name());
	case DescriptionRole: return  QVariant::fromValue(graphic.value()->description());
	case VisibleRole: return QVariant::fromValue(item.visible);
	case LastValueXRole:
		return QVariant::fromValue(graphic.value()->getValueStorage().getLastPoint().time);
	case LastValueYRole:
		return QVariant::fromValue(QString("%1").arg(graphic.value()->getValueStorage().getLastPoint().value, 0, 'f', 3));
	case ColorRole:
		return QVariant::fromValue(item.color);
	default: return QVariant();
	}
}

bool GraphicsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid()) {
		return false;
	}

	switch (role) {
	case VisibleRole:
		m_graphics[static_cast<std::size_t>(index.row())].visible = value.toBool();
		emit visibleChanged();
		return true;
	default: return false;
	}
}

int GraphicsModel::rowCount(const QModelIndex &parent) const
{
	return m_graphics.count();
}

QHash<int, QByteArray> GraphicsModel::roleNames() const
{
	return QHash<int, QByteArray>{
		{ NameRole, "name" },
		{ DescriptionRole, "description" },
		{ VisibleRole, "visibleGraphic" },
		{ LastValueXRole, "lastValueX" },
		{ LastValueYRole, "lastValueY" },
		{ ColorRole, "color" },
	};
}

int GraphicsModel::count() const
{
	return m_graphics.count();
}

int GraphicsModel::maxDot() const
{
	return 100000;
}

void GraphicsModel::graphicAdded(QUuid id)
{
	beginResetModel();
	GraphicItem graphItem;

	graphItem.id = id;
	graphItem.color = getColor(m_graphics.size());
	m_graphics.append(graphItem);

	endResetModel();
}

void GraphicsModel::graphicRemoved(QUuid id)
{
//	m_graphics.erase(std::find(m_graphics.begin(), m_graphics.end(), [&id](GraphicItem item){
//	    return item.id == id;
//	}));

	emit dataChanged(index(0), index(m_graphics.size()));
}

}
