// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: navigatorView
    width: parent.width; height: parent.height

    property string uin
    property string sid
    property string skey
    property var syncKey
    property var initObj

    Sync {
        id: syncObj
        Component.onCompleted: {
            syncObj.post(navigatorView.uin, navigatorView.sid, navigatorView.syncKey)
        }
    }

    Monitor {
        id: monitorObj
    }

    Timer {                                                                        
        id: getMsgTimer                                                              
        interval: 8000; running: true; repeat: true                              
        onTriggered: {
            monitorObj.get(navigatorView.uin, navigatorView.sid, syncObj.syncKey)
        }                                              
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
                        uin: navigatorView.uin
                        sid: navigatorView.sid
                        skey: navigatorView.skey
                        loginUserName: navigatorView.initObj.loginUserName
                        initObj: navigatorView.initObj
                    }
                }

                IconTab {
                    title: "通讯录"
                    iconSource: "images/contacts.png"
                    ContactListView {
                        uin: navigatorView.uin 
                        sid: navigatorView.sid 
                        skey: navigatorView.skey 
                        loginUserName: navigatorView.initObj.loginUserName 
                    }
                }

                IconTab {
                    title: "我"
                    iconSource: navigatorView.initObj.loginHeadImgUrl
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
                            anchors.topMargin: 10
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
