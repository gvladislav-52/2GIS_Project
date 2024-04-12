import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
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
        RowLayout {
            anchors.fill: parent
            Repeater {
                model: file_proc.Top_CountWords_inFile.length
                Rectangle {
                    Layout.preferredWidth: parent.width * 0.05
                    Layout.preferredHeight: file_proc.Top_CountWords_inFile[index] * parent.height * 0.01
                    Layout.alignment: Qt.AlignBottom
                    color: "green"
                    border.color: "black"

                    Text {
                        anchors
                        {
                            bottom: parent.top
                            horizontalCenter: parent.horizontalCenter
                        }

                        text: file_proc.Top_CountWords_inFile[index]
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
            clip: true
            RowLayout {
                anchors.fill: parent

                Repeater {
                    model: file_proc.Top_Words_inFile.length

                    Text {
                        Layout.alignment: Qt.AlignVCenter
                        text: file_proc.Top_Words_inFile[index]
                        color: "white"
                        rotation: -90
                        font.bold: true
                        font.pixelSize: parent.height * 0.15
                        Layout.preferredWidth: parent.width * 0.05
                    }
                }
            }
        }
        }
}
