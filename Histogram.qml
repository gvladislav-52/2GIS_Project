import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    property var histogramModel: [50,20,30,40,60,25,35,45,55,70,80,90,10,15,65]

        property var wordVector: ["apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon", "mango", "nectarine", "orange", "pear", "quince"]

        ColumnLayout
        {
            anchors.fill: parent
        Rectangle
        {
            id: histogram
            color: "white"
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.fillHeight: true
            border.color: "black"
            border.width: 5
        RowLayout {
            anchors.fill: parent
            Repeater {
                model: histogramModel.length
                Rectangle {
                    Layout.preferredWidth: parent.width * 0.05
                    Layout.preferredHeight: histogramModel[index] * parent.height * 0.01
                    Layout.alignment: Qt.AlignBottom
                    color: "green"
                    border.color: "black"

                    Text {
                        anchors
                        {
                            bottom: parent.top
                            horizontalCenter: parent.horizontalCenter
                        }

                        text: histogramModel[index]
                        color: "black"
                    }
                }
            }
        }
        }

        Rectangle {
            color: "black"
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 0.15

            RowLayout {
                anchors.fill: parent

                Repeater {
                    model: histogramModel.length

                    Text {
                        Layout.alignment: Qt.AlignVCenter
                        text: wordVector[index]
                        color: "white"
                        rotation: -90
                        font.bold: true
                        font.pixelSize: parent.height * 0.1
                        Layout.preferredWidth: parent.width * 0.05
                    }
                }
            }
        }
        }
}
