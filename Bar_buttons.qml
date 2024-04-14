import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle
{
    color: "gray"
    property var button_vector_name: ["Открыть", "Старт", "Пауза", "Отмена"]
    property var button_color: ["blue","green","green","red"]
    property var button_hover_color: ["darkblue","darkgreen","darkgreen","darkred"]
    property var button_pause: button_vector_name[2]
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

        Rectangle
        {
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: parent.height * 0.05
            Layout.preferredWidth: parent.width * 0.8
            color: "lightgray"
            border.color: "black"
            radius: parent.height * 0.01
            Text
            {
                anchors
                {
                    left: parent.left
                    leftMargin: parent.width * 0.025
                    verticalCenter: parent.verticalCenter
                }

                text: "file: " + file_proc.Filename;
                font.pixelSize: parent.height * 0.5
            }
            clip: true
        }

        Repeater
        {
            model: button_vector_name.length
            Button {
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight: parent.height * 0.1
                Layout.preferredWidth: parent.width * 0.8
                Text
                {
                    id: button_text
                    anchors.centerIn: parent
                    text: if(index !== 2) return button_vector_name[index]
                            else return button_pause;
                    color: "white"
                    font.bold: true
                    font.pixelSize: parent.height * 0.25
                }

                background: Rectangle {
                    color: parent.pressed ? "#696969" : (parent.hovered ? button_hover_color[index] : button_color[index])
                    radius: parent.height * 0.1
                    border.color: "black"
                    border.width: 1
                }

                onClicked:
                {
                    switch(index)
                    {
                    case 0:
                        file_proc.openFuntion()
                        break;
                    case 1:
                        button_pause = button_vector_name[2];
                        file_proc.startFunction()
                        break;
                    case 2:
                        file_proc.setPause()
                        file_proc.getPause()? button_pause = "Продолжить" : button_pause = button_vector_name[index]
                        break;
                    case 3:
                        file_proc.setCancel();
                        file_proc.cancelFunction();
                        button_pause = button_vector_name[2];
                        break;
                    }
                }
            }
        }
    }
}
