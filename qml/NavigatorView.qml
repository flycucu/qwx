// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: navigatorView
    width: parent.width; height: parent.height

    property string uin: ""
    property string sid: ""
    property string skey: ""
    property string loginUserName: ""
    property var initObj

    GetMsg {
        id: getMsgObj
    }

    Timer {                                                                        
        id: getMsgTimer                                                              
        interval: 8000; running: true; repeat: true                              
        onTriggered: {
            getMsgObj.post(navigatorView.uin, navigatorView.sid)
        }                                              
    }

    TabView {
        id: navigatorTabView
        width: parent.width; height: parent.height - navigatorHeader.height
        tabPosition: Qt.BottomEdge
        anchors.top: navigatorHeader.bottom

        Tab {
            title: "微信"
            WXView {
                uin: navigatorView.uin
                sid: navigatorView.sid
                skey: navigatorView.skey
                loginUserName: navigatorView.loginUserName
                initObj: navigatorView.initObj
            }
        }

        Tab {                                                                      
            title: "通讯录"                                                        
            ContactListView {                                                      
                uin: navigatorView.uin                                             
                sid: navigatorView.sid                                             
                skey: navigatorView.skey                                           
                loginUserName: navigatorView.loginUserName 
            }                                                                      
        }

        Tab {
            title: "我"
            IView {}
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
