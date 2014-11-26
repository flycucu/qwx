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
    property var initObj

    TabView {
        id: navigatorTabView
        width: parent.width; height: parent.height - navigatorHeader.height
        tabPosition: Qt.BottomEdge
        anchors.top: navigatorHeader.bottom

        Tab {
            title: "微信"
            WXView {}
        }

        Tab {
            title: "通讯录"
            ContactListView {
                uin: navigatorView.uin
                sid: navigatorView.sid
                skey: navigatorView.skey
                initObj: navigatorView.initObj
            }
        }

        Tab {
            title: "我"
            IView {}
        }
    }

    Rectangle {                                                                    
        id: navigatorHeader                                                        
        width: parent.width; height: 80
        anchors.top: parent.top
                                                                                   
        Text { text: "微信" }                                                      
    }
}
