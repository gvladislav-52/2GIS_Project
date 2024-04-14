#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include "file_processing.h"
#include "file_thread.h"
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    File_processing fileProcessing;
    qDebug() << "Id main-thread: " << QThread::currentThreadId();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Main.qml"));

    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("file_proc", &fileProcessing);
    qmlRegisterType<File_processing>("com.example", 1, 0, "File_processing");
    engine.load(url);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    return app.exec();
}
