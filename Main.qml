import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 600
    height: 300
    title: "Histogram"

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
