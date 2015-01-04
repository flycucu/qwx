// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: navigatorView
    width: parent.width; height: parent.height

    property bool v2: false
    property string uin
    property string sid
    property string skey
    property string deviceId
    property string ticket
    property string loginUserName
    property var syncKey
    property var initObj

    Sync {
        id: syncObj
        Component.onCompleted: {
            if (navigatorView.v2) {
                syncObj.postV2(navigatorView.uin, navigatorView.sid, navigatorView.skey, navigatorView.syncKey)
            } else {
                syncObj.post(navigatorView.uin, navigatorView.sid, navigatorView.skey, navigatorView.syncKey)
            }
        }
    }

    StatusNotify {
        id: statusNotifyObj
        Component.onCompleted: {
            if (navigatorView.v2) {
                statusNotifyObj.postV2(navigatorView.uin, navigatorView.sid, navigatorView.skey, navigatorView.deviceId, navigatorView.loginUserName)
            } else {
                statusNotifyObj.post(navigatorView.uin, navigatorView.sid, navigatorView.skey, navigatorView.deviceId, navigatorView.loginUserName)
            }
        }
    }

    Monitor {
        id: monitorObj
    }

    Timer {                                                                        
        id: monitorTimer                                                              
        interval: 3000; running: true; repeat: true; triggeredOnStart: true 
        onTriggered: {
            monitorObj.get(navigatorView.uin, navigatorView.sid, navigatorView.skey, navigatorView.deviceId, syncObj.syncKey)
        }
    }

    HeadImg {
        id: loginUserHeadImg
        v2: navigatorView.v2                                             
        userName: navigatorView.loginUserName
    }

    StackView {
        id:navigatorStackView
        anchors.fill: parent
        initialItem: Item {
            TabView {
                id: navigatorTabView
                width: parent.width; height: parent.height - navigatorHeader.height
                tabPosition: Qt.BottomEdge
                anchors.top: navigatorHeader.bottom

                IconTab {
                    title: "微信"
                    iconSource: "images/messages.png"
                    WXView {
                        v2: navigatorView.v2
                        uin: navigatorView.uin
                        sid: navigatorView.sid
                        skey: navigatorView.skey
                        deviceId: navigatorView.deviceId
                        ticket: navigatorView.ticket
                        loginUserName: navigatorView.loginUserName
                        syncKey: syncObj.syncKey
                        initObj: navigatorView.initObj
                    }
                }

                IconTab {
                    title: "通讯录"
                    iconSource: "images/contacts.png"
                    ContactListView {
                        v2: navigatorView.v2
                        uin: navigatorView.uin 
                        sid: navigatorView.sid 
                        skey: navigatorView.skey
                        deviceId: navigatorView.deviceId
                        ticket: navigatorView.ticket 
                        loginUserName: navigatorView.loginUserName 
                        syncKey: syncObj.syncKey
                    }
                }

                IconTab {
                    title: "我"
                    iconSource: loginUserHeadImg.filePath
                    IView {}
                }

                style: TabViewStyle {
                    frameOverlap: 1 
                    tab: Rectangle {
                        color: "white"
                        implicitWidth: 100
                        implicitHeight: 60

                        CircleImage {
                            id: iconImage
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            anchors.topMargin: 3
                            imageSource: navigatorTabView.getTab(styleData.index).iconSource
                            width: 30; height: 30
                        }

                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: iconImage.bottom
                            anchors.topMargin: 3
                            text: styleData.title
                            color: styleData.selected ? "#45c01a" : "#9b9b9b"
                            font.pixelSize: 12
                        }
                    }
                    frame: Rectangle { color: "white" }
                }
            }
        
            Rectangle {
                id: navigatorHeader 
                width: parent.width; height: 58
                anchors.top: parent.top
                color: "#20282a"
                                                                                   
                Text { 
                    text: "微信"
                    font.pixelSize: 22
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 19
                    color: "white"
                }
            }
        }
    }
}
