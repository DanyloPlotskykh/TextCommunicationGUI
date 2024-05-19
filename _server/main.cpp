// #include <QCoreApplication>
#include "server.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Server>("com.example.server", 1, 0, "Server");

    Server s;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("backend", &s);

    const QUrl url(QStringLiteral("../../_server/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}