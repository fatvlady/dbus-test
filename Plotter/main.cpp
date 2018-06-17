#include "arrow.h"
#include "arrow_adaptor.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtDBus/QDBusConnection>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    scene.setSceneRect(-10, -100, 1000, 200);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    Arrow *arrow = new Arrow();
    scene.addItem(arrow);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animation tracker"));
    view.resize(1000, 200);
    view.show();

    new ArrowInterfaceAdaptor(arrow);
    QDBusConnection connection = QDBusConnection::sessionBus();

    if (!connection.registerService("org.fatvlady.Test"))
    {
        throw std::runtime_error("Fatal: org.fatvlady.Test service is held by another process.");
    }
    if (!connection.registerObject("/Arrow", arrow))
    {
        throw std::runtime_error("Fatal: /Arrow object is held by another process.");
    }

    return a.exec();
}
