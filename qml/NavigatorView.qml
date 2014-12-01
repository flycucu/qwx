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
    property var initObj

    Monitor {
        id: monitorObj
    }

    Timer {                                                                        
        id: getMsgTimer                                                              
        interval: 8000; running: true; repeat: true                              
        onTriggered: {
            monitorObj.get(navigatorView.uin, navigatorView.sid)
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

                Tab {
                    title: "微信"
                    source: "../images/messages.png"
                    WXView {
                        uin: navigatorView.uin
                        sid: navigatorView.sid
                        skey: navigatorView.skey
                        loginUserName: navigatorView.initObj.loginUserName
                        initObj: navigatorView.initObj
                    }
                }

                Tab {
                    title: "通讯录"
                    source: "../images/contacts.png"
                    ContactListView {
                        uin: navigatorView.uin 
                        sid: navigatorView.sid 
                        skey: navigatorView.skey 
                        loginUserName: navigatorView.initObj.loginUserName 
                    }
                }

                Tab {
                    title: "我"
                    source: navigatorView.initObj.loginHeadImgUrl
                    IView {}
                }

                style: TabViewStyle {
                    frameOverlap: 1 
                    tab: Rectangle {
                        color: "white"
                        implicitWidth: 100
                        implicitHeight: 60

                        // FIXME: how to use image in Tab?
                        Image {
                            anchors.centerIn: parent
                            source: styleData.source
                            width: 30; height: 30
                        }

                        Text {
                            anchors.centerIn: parent
                            text: styleData.title
                            color: styleData.selected ? "#45c01a" : "#9b9b9b"
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
