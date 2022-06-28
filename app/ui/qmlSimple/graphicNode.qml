import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import Palette 1.0

Item {
	id: root

	property string garphicName: ""
	property string garphicDescription: ""
	property real lastValue: 0.0
	property bool visibleState: true

	implicitHeight: internal.mode === GraphicNode.Mode.Small ? title.implicitHeight : title.implicitHeight + legendLoader.height

	enum Mode {
		Small,
		Big
	}

	Rectangle {
		id: title

		implicitHeight: 28
		implicitWidth: root.width

		color: Palette.color2()

		RowLayout {
			anchors{
				left: parent.left
				right: parent.right
				verticalCenter: parent.verticalCenter

				leftMargin: 6
				rightMargin: 6
			}

			Rectangle {
				height: 16
				width: 16

				radius: height / 2

				color: model.color
			}

			Text {
				Layout.fillWidth: true
				Layout.fillHeight: true

				text: name

				Component.onCompleted: {
					console.log(name);
				}
			}
		}

		MouseArea {
			id: arrowButton

			anchors {
				right: parent.right
				verticalCenter: parent.verticalCenter
				rightMargin: 6
			}

			width: 16
			height: 16

			onReleased: {
				if (internal.mode === GraphicNode.Mode.Small) {
					internal.mode = GraphicNode.Mode.Big;
				} else if (internal.mode === GraphicNode.Mode.Big) {
					internal.mode = GraphicNode.Mode.Small;
				}
			}

			Image {
				anchors.fill: parent

				visible: internal.mode === GraphicNode.Mode.Small

				source: "../src/down_arrow.png"
			}

			Image {
				anchors.fill: parent

				visible: internal.mode === GraphicNode.Mode.Big

				source: "../src/up_arrow.png"
			}
		}

		Image {
			id: infoIcon

			visible: garphicDescription != ""

			anchors {
				right: arrowButton.left
				verticalCenter: parent.verticalCenter
				rightMargin: 6
			}

			width: 16
			height: 16


			source: "../src/information.png"

			MouseArea {
				anchors.fill: parent

				onReleased: infoPopup.open()
			}

			Popup {
				id: infoPopup

				x: infoIcon.width
				y: infoIcon.height / 2

				width: 200
				height: 100

				closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

				background: Rectangle {
					color: Palette.color2()

					layer.enabled: true
					layer.effect: DropShadow {
						transparentBorder: true
						radius: 4
						samples: 4
					}
				}

				Text {
					anchors.fill: parent
					text: root.garphicDescription
				}
			}
		}
	}

	Loader {
		id: legendLoader

		anchors{
			top: title.bottom
			left: parent.left
			right: parent.right
		}

		active: internal.mode === GraphicNode.Mode.Big

		sourceComponent: legendComponent
	}

	Component {
		id: legendComponent

		Rectangle {
			id: legend

			color: Palette.color3()

			anchors {
				right: parent.right
				left: parent.left
			}

			implicitHeight: 40

			GridLayout {
				anchors {
					fill: parent
					topMargin: 3
					bottomMargin: 3
					rightMargin: 3
					leftMargin: 3
				}

				rows: 2
				columns: 2


				Rectangle {
					Layout.fillHeight: true
					Layout.fillWidth: true
					Layout.columnSpan: 2
					Layout.rowSpan: 1
					Layout.row: 0
					Layout.column: 0

					color: "transparent"

					CheckBox {
						id: visibleState

						anchors {
							verticalCenter: parent.verticalCenter
							right: parent.right
							left: parent.left
						}

						height: 18

						text: "Visible"

						checked: true
						tristate: false

						indicator: Rectangle {
							implicitWidth: 16
							implicitHeight: 16
							x: control.leftPadding
							y: parent.height / 2 - height / 2
							radius: 3
							border.color: visibleState.down ? Palette.color4() : Palette.color5()

							Rectangle {
								width: 12
								height: 12
								x: 2
								y: 2
								radius: 2
								color: visibleState.down ? Palette.color4() : Palette.color5()
								visible: visibleState.checked
							}
						}

						onReleased: {
							root.visibleState = checked;
						}
					}
				}

				Rectangle {
					Layout.fillHeight: true
					Layout.fillWidth: true
					Layout.columnSpan: 1
					Layout.rowSpan: 1
					Layout.row: 1
					Layout.column: 0

					color: "transparent"

					Text {
						anchors{
							verticalCenter: parent.verticalCenter
							right: parent.right
							left: parent.left
						}
						text: qsTr("lastValue")
					}
				}

				Rectangle {
					Layout.fillHeight: true
					Layout.fillWidth: true
					Layout.columnSpan: 1
					Layout.rowSpan: 1
					Layout.row: 1
					Layout.column: 1

					color: Palette.color2()
					Text {
						id: lastValue
						anchors{
							verticalCenter: parent.verticalCenter
							right: parent.right
							left: parent.left
						}

						horizontalAlignment: Text.AlignRight

						text: root.lastValue
					}
				}
			}
		}
	}

	QtObject {
		id: internal

		property int mode: GraphicNode.Mode.Small
	}
}
