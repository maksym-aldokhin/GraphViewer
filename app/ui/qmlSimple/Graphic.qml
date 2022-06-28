import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import ModelUtil 1.0
import Palette 1.0

Item {
	id: root

	property QtObject model // GraphicsModel

	enum GraphicMode {
		RectangleZoom,
		ScrollZoom,
		ViewAll
	}

	Column {
		spacing: 6

		anchors.fill: parent

		RowLayout {
			id: buttonRow

			spacing: 6

			width: root.width
			height: 16

			Button {
				Layout.preferredHeight: 16
				Layout.minimumWidth: 32

				text: "Reset"

				onReleased: chart.zoomReset()
			}

			Button {
				Layout.preferredHeight: 16
				Layout.minimumWidth: 32

				text: "Rectangle Zoom"

				onReleased: {
					internal.setGraphicMode(Graphic.GraphicMode.RectangleZoom);
				}
			}

			Button {
				Layout.preferredHeight: 16
				Layout.minimumWidth: 32

				text: "Scroll Zoom"

				onReleased: {
					internal.setGraphicMode(Graphic.GraphicMode.ScrollZoom);
				}
			}

			Button {
				Layout.preferredHeight: 16
				Layout.minimumWidth: 32

				text: "View all"

				onReleased: {
					internal.setGraphicMode(Graphic.GraphicMode.ViewAll);
				}
			}
		}

		ChartView {
			id: chart

			width: root.width
			height: root.height - buttonRow.height

			backgroundRoundness: 0
			theme: ChartView.ChartThemeDark

			animationOptions: ChartView.NoAnimation
			antialiasing: true
			legend.visible: false

			margins {
				top: 10
				bottom: 10
				left: 10
			}

			axes: [
				DateTimeAxis {
					id: xAxis
					format: "mm:ss:zzz"
				},
				ValueAxis {
					id: yAxis
					min: -50.0
					max: 50.0
				}
			]

			Component.onCompleted: {
				var seriesCount = root.model.count();
				console.log(seriesCount);
				for(var i = 0;i < seriesCount;i ++)
				{
					var nameRole = ModelUtil.getRoleByName("name", root.model);
					var series = chart.createSeries(ChartView.SeriesTypeLine, root.model.data(root.model.index(i, 0), nameRole), xAxis, yAxis);

					var visibleRole = ModelUtil.getRoleByName("visibleGraphic", root.model);
					series.pointsVisible = root.model.data(root.model.index(i, 0), visibleRole);

					var colorRole = ModelUtil.getRoleByName("color", root.model);
					series.color = root.model.data(root.model.index(i, 0), colorRole);
					series.useOpenGL = true;
				}
			}

			Rectangle {
				id: selectionZone

				visible: false

				color: "#AAAAAAAA"
			}

			MouseArea {
				id: rectangleZoomController

				anchors.fill: parent

				enabled: internal.graphicMode === Graphic.GraphicMode.RectangleZoom

				onDoubleClicked: chart.zoomReset();

				onPressed: {
					internal.startRectanglePositionX = mouseX;
					internal.startRectanglePositionY = mouseY;

					selectionZone.x = mouseX;
					selectionZone.y = mouseY;
				}

				onReleased: {
					var r = Qt.rect(selectionZone.x, selectionZone.y, selectionZone.width, selectionZone.height);
					chart.zoomIn(r);

					selectionZone.visible = false;
				}

				onPositionChanged: {
					if (mouseX >= internal.startRectanglePositionX) {
						if (mouseX > chart.x + chart.width) {
							selectionZone.width = chart.x + chart.width - internal.startRectanglePositionX;
						} else {
							selectionZone.width = mouseX - internal.startRectanglePositionX;
						}
					} else {
						if (mouseX < chart.x) {
							selectionZone.x = chart.x;
							selectionZone.width = internal.startRectanglePositionX - chart.x;
						} else {
							selectionZone.x = mouseX;
							selectionZone.width = internal.startRectanglePositionX - mouseX;
						}
					}
					if (mouseY >= internal.startRectanglePositionY) {
						if (mouseY > chart.y + chart.height) {
							selectionZone.height = chart.y + chart.height - internal.startRectanglePositionY;
						} else {
							selectionZone.height = mouseY - internal.startRectanglePositionY;
						}
					} else {
						if (mouseY < chart.y) {
							selectionZone.y = chart.y;
							selectionZone.height = internal.startRectanglePositionY - chart.y;
						} else {
							selectionZone.y = mouseY;
							selectionZone.height = internal.startRectanglePositionY - mouseY;
						}
					}

					selectionZone.visible = true;
				}
			}

			MouseArea {
				id: scrollZoomController

				anchors.fill: parent

				enabled: internal.graphicMode === Graphic.GraphicMode.ScrollZoom

				hoverEnabled: true

				onDoubleClicked: chart.zoomReset();
				onWheel: (wheel)=> {
					var lengthLeft = mouseX - chart.x;
					var lengthRight = chart.x + chart.width - mouseX;
					var lengthTop = mouseY - chart.y;
					var lengthButtom = chart.y + chart.height - mouseY;

					var sideRect = Math.min(lengthLeft, lengthRight, lengthTop, lengthButtom);

					if (wheel.angleDelta.y > 0) {
						var halfSideRect = sideRect / 2;
						var r = Qt.rect(mouseX - halfSideRect, mouseY - halfSideRect, sideRect, sideRect);
						chart.zoomIn(r);

					} else if (wheel.angleDelta.y < 0) {
						var side2Rect = sideRect * 2;
						var r = Qt.rect(mouseX - sideRect, mouseY - sideRect, side2Rect, side2Rect);
						chart.zoomOut(r);
					}
				}

				onPositionChanged: (mouse)=> {
					if (pressed) {
						var deltaX = internal.prevMousePositionX - mouseX;
						var deltaY = internal.prevMousePositionY - mouseY;

						if (deltaX < 0) {
							chart.scrollLeft(Math.abs(deltaX));
						}
						if (deltaX > 0) {
							chart.scrollRight(Math.abs(deltaX));
						}

						if (deltaY < 0) {
							chart.scrollUp(Math.abs(deltaY));
						}
						if (deltaY > 0) {
							chart.scrollDown(Math.abs(deltaY));
						}

						internal.prevMousePositionX = mouseX;
						internal.prevMousePositionY = mouseY;
					}
				}

				onPressed: {
					internal.prevMousePositionX = mouseX;
					internal.prevMousePositionY = mouseY;
					cursorShape = Qt.ClosedHandCursor;
				}

				onReleased: {
					cursorShape = Qt.ArrowCursor;
				}
			}
		}
	}

	Connections  {
		target: root.model

		onNewData: {
			var seriesCount = root.model.count();
			for(var i = 0;i < seriesCount;i ++)
			{
				var lastValueXRole = ModelUtil.getRoleByName("lastValueX", root.model);
				var lastValueYRole = ModelUtil.getRoleByName("lastValueY", root.model);
				chart.series(i).append(root.model.data(root.model.index(i, 0), lastValueXRole), root.model.data(root.model.index(i, 0), lastValueYRole));
				if (root.model.data(root.model.index(i, 0), lastValueXRole) > xAxis.max) {
					xAxis.max = root.model.data(root.model.index(i, 0), lastValueXRole);
				}

				internal.updateMinMaxVertical(root.model.data(root.model.index(i, 0), lastValueYRole));
				internal.updateMinMaxHorizontal(root.model.data(root.model.index(i, 0), lastValueXRole));
				internal.updateLimetPoint(i);
			}
		}

		onVisibleChanged: {
			var seriesCount = root.model.count();
			for(var i = 0;i < seriesCount;i ++)
			{
				var visibleGraphicRole = ModelUtil.getRoleByName("visibleGraphic", root.model);
				chart.series(i).visible = root.model.data(root.model.index(i, 0), visibleGraphicRole);
			}
		}
	}

	QtObject {
		id: internal

		property var maxViewX: new Date()
		property var minViewX: new Date()
		property real maxViewY: 0.0
		property real minViewY: 0.0

		property real startRectanglePositionX: 0
		property real startRectanglePositionY: 0

		property real prevMousePositionX: 0
		property real prevMousePositionY: 0

		property int graphicMode: Graphic.GraphicMode.ScrollZoom

		function setGraphicMode(mode) {
			graphicMode = mode;
			switch(mode) {
			case Graphic.GraphicMode.RectangleZoom:
				break;
			case Graphic.GraphicMode.ScrollZoom:
				break;
			case Graphic.GraphicMode.ViewAll:
				chart.zoomReset();
				atualizeGraphicBorders();
				break;
			}
		}

		function atualizeGraphicBorders() {
			if (graphicMode !== Graphic.GraphicMode.ViewAll) {
				return;
			}

			if (yAxis.max < maxViewY) {
				yAxis.max = maxViewY;
			}

			if (yAxis.min > minViewY) {
				yAxis.min = minViewY;
			}
		}

		function updateMinMaxVertical(v) {
			if (v > maxViewY) {
				maxViewY = v;
				atualizeGraphicBorders();
			} else if (v < minViewY) {
				minViewY = v;
				atualizeGraphicBorders();
			}
		}

		function updateMinMaxHorizontal(v) {

		}

		function updateLimetPoint(i) {
			var maxDot = root.model.maxDot();

			while (chart.series(i).count > maxDot) {
				chart.series(i).remove(0);
			}
		}
	}
}
