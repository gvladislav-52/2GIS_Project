import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
Rectangle
{
    color: "gray"
    property var button_vector_name: ["Открыть", "Старт", "Пауза", "Отмена"]
    ColumnLayout
    {
        anchors.fill: parent
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: parent.height * 0.2
            Layout.preferredWidth: parent.width * 0.9
            color: "transparent"

            ProgressBar {
                id: progressBar
                anchors.fill: parent
                value: file_proc.Progress;
            }

            Text {
                anchors.centerIn: parent
                text:
                {
                    if(progressBar.value !== 1)
                        return "Cчитывание файла: " + Math.round(progressBar.value * 100) + "%"
                    else
                        return "Считывание окончено!";
                }
                font.pixelSize: parent.height * 0.1
                color: "white"
            }
        }

        Repeater
        {
            model: button_vector_name.length
            Button {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight: parent.height * 0.1
                Layout.preferredWidth: parent.width * 0.8
                text: button_vector_name[index]

                background: Rectangle {
                    color: parent.pressed ? "#696969" : (parent.hovered ? "darkblue" : "blue")
                    radius: parent.height * 0.1
                    border.color: "black"
                    border.width: 1
                }

                onClicked:
                {
                    switch(index)
                    {
                    case 0:
                        file_proc.chooseFileAndPrintName()
                        break;
                    }
                }
            }
        }

        // Button {
        //     Layout.alignment: Qt.AlignHCenter
        //     Layout.preferredHeight: parent.height * 0.1
        //     Layout.preferredWidth: parent.width * 0.8
        //     text: "Открыть"

        //     background: Rectangle {
        //         color: parent.pressed ? "#696969" : (parent.hovered ? "darkblue" : "blue")
        //         radius: parent.height * 0.1
        //     }
        // }
        // Button
        // {
        //     Layout.alignment: Qt.AlignHCenter
        //     Layout.preferredHeight: parent.height * 0.1
        //     Layout.preferredWidth: parent.width * 0.8
        //     text: "Старт"
        // }
        // Button
        // {
        //     Layout.alignment: Qt.AlignHCenter
        //     Layout.preferredHeight: parent.height * 0.1
        //     Layout.preferredWidth: parent.width * 0.8
        //     text: "Пауза"
        // }

        // Button
        // {
        //     Layout.alignment: Qt.AlignHCenter
        //     Layout.preferredHeight: parent.height * 0.1
        //     Layout.preferredWidth: parent.width * 0.8
        //     text: "Отмена"
        // }
    }

}
