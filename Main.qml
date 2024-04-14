import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import com.example 1.0

ApplicationWindow {
    visible: true
    width: 600
    height: 300
    title: "Histogram"
    File_processing {
        id: fileProcessor
    }


    Rectangle
    {
        anchors.fill: parent
        color: "black"
    }

    RowLayout
    {
        anchors.fill: parent
    Histogram
    {
        Layout.preferredWidth: parent.width *0.7
        Layout.preferredHeight: parent.height
    }
    Bar_buttons
    {
        Layout.fillWidth: true
        Layout.preferredHeight: parent.height
    }
    }
}
