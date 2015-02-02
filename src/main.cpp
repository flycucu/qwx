// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QtQml>
#include <QtQuick/QQuickView>

#include "globaldeclarations.h"
#include "qtsingleapplication/QtSingleApplication"
#include "qwxuuid.h"
#include "scan.h"
#include "cookie.h"
#include "statreport.h"
#include "init.h"
#include "sync.h"
#include "contact.h"
#include "headimg.h"
#include "statusnotify.h"
#include "sendmsg.h"
#include "monitor.h"
#include "getmsg.h"
#include "circleimage.h"
#include "process.h"
#include "xiaodoubi.h"
#include "chatlog.h"

int main(int argc, char* argv[]) 
{                                                                        
    QtSingleApplication app(argc, argv);
    if (app.isRunning()) return 0;
    app.setApplicationName(CODE_NAME);
    app.setApplicationVersion(APPLICATION_VERSION);

    qmlRegisterType<QwxUUID>("cn.com.isoft.qwx", 1, 0, "QwxUUID");
    qmlRegisterType<Scan>("cn.com.isoft.qwx", 1, 0, "Scan");
    qmlRegisterType<Cookie>("cn.com.isoft.qwx", 1, 0, "Cookie");
    qmlRegisterType<StatReport>("cn.com.isoft.qwx", 1, 0, "StatReport");
    qmlRegisterType<Init>("cn.com.isoft.qwx", 1, 0, "Init");
    qmlRegisterType<Sync>("cn.com.isoft.qwx", 1, 0, "Sync");
    qmlRegisterType<Contact>("cn.com.isoft.qwx", 1, 0, "Contact");
    qmlRegisterType<HeadImg>("cn.com.isoft.qwx", 1, 0, "HeadImg");
    qmlRegisterType<StatusNotify>("cn.com.isoft.qwx", 1, 0, "StatusNotify");
    qmlRegisterType<SendMsg>("cn.com.isoft.qwx", 1, 0, "SendMsg");
    qmlRegisterType<Monitor>("cn.com.isoft.qwx", 1, 0, "Monitor");
    qmlRegisterType<GetMsg>("cn.com.isoft.qwx", 1, 0, "GetMsg");
    qmlRegisterType<CircleImage>("cn.com.isoft.qwx", 1, 0, "CircleImage");
    qmlRegisterType<Process>("cn.com.isoft.qwx", 1, 0, "Process");
    qmlRegisterType<XiaoDouBi>("cn.com.isoft.qwx", 1, 0, "XiaoDouBi");
    qmlRegisterType<ChatLog>("cn.com.isoft.qwx", 1, 0, "ChatLog");

    QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml")); 
    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel); 
    if (!window) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }
    window->show();

    return app.exec();
}
