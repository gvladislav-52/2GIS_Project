#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include "file_processing.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    File_processing fp;

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("file_proc", &fp);
    engine.load(url);


    //fp.chooseFileAndPrintName();

    return app.exec();
}
