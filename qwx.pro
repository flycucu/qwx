QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)

lessThan(QT_VER_MAJ, 5) | lessThan(QT_VER_MIN, 2) {
	error(qwx is only tested under Qt 5.2!)
}

QT += qml quick network xml
QMAKE_CXXFLAGS += -std=c++11 -Werror
!android: !ios: !blackberry: qtHaveModule(widgets): QT += widgets
TARGET = qwx
CODECFORSRC = UTF-8

include(src/src.pri)

OTHER_FILES += \
    qml/main.qml    \
    qml/SplashView.qml  \
    qml/LoginView.qml   \
    qml/NavigatorView.qml   \
    qml/IconTab.qml \
    qml/WXView.qml  \
    qml/ChatView.qml    \
    qml/TalkBubble.qml  \
    qml/ContactListView.qml \
    qml/IView.qml \
    qml/global.js

RESOURCES += \
    resources.qrc

!isEmpty(QWX_DEBUG) {
    DEFINES += QWX_DEBUG
    QMAKE_CXXFLAGS += -g
}

unix {
    #VARIABLES
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    BINDIR = $$PREFIX/bin
    DATADIR = $$PREFIX/share

    DEFINES += PREFIX=\\\"$$PREFIX\\\"
    DEFINES += TARGET=\\\"$$TARGET\\\"
    DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"

    #MAKE INSTALL
    INSTALLS += target desktop icon

    target.path = $$BINDIR

    desktop.path = $$DATADIR/applications
    desktop.files += $${TARGET}.desktop

    icon.path = $$DATADIR/icons/hicolor/64x64/apps
    icon.files += images/$${TARGET}.png
}
