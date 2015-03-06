// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import cn.com.isoft.qwx 1.0
import "global.js" as Global

Item {
    id: navigatorView
    width: parent.width; height: parent.height

    LogOut {
        id: logOutObj
    }

    Component.onDestruction: {
        if (Global.v2) {
            logOutObj.getV2();
        } else {
            logOutObj.get();
        }
        console.log("Bye ;-)");
    }

    Process {                                                                   
        id: processObj                                                          
        program: "notify-send"                                                  
    }

    Weather {
        id: weatherObj
        onWeatherChanged: {
            processObj.arguments = [qsTr("energy saving and emission reduction"), report, '--icon=dialog-information', '-t', '13000'];
            processObj.start();
        }
    }

    IpCity {
        id: ipCityObj
        Component.onCompleted: {
            ipCityObj.get();
        }
        onCityChanged: {
            weatherObj.get(city);
        }
    }

    Sync {
        id: syncObj
        onSyncKeyChanged: {
            Global.syncKey = syncObj.syncKey;
            doMonitor();
        }
        Component.onCompleted: {
            if (Global.v2) {
                syncObj.postV2(Global.uin, Global.sid, Global.skey, Global.initSyncKey);
            } else {
                syncObj.post(Global.uin, Global.sid, Global.skey, Global.initSyncKey);
            }
        }
    }

    StatusNotify {
        id: statusNotifyObj
        Component.onCompleted: {
            if (Global.v2) {
                statusNotifyObj.postV2(Global.uin, Global.sid, Global.skey, Global.deviceId, Global.loginUserName);
            } else {
                statusNotifyObj.post(Global.uin, Global.sid, Global.skey, Global.deviceId, Global.loginUserName);
            }
        }
    }

    function doMonitor() 
    {
        if (Global.v2) {
            monitorObj.getV2(Global.uin, Global.sid, Global.skey, Global.deviceId, Global.syncKey);
        } else {
            monitorObj.get(Global.uin, Global.sid, Global.skey, Global.deviceId, Global.syncKey);
        }
    }

    Monitor {
        id: monitorObj
        onNoNewMsg: {
            rootWindow.title = qsTr("WeChat Qt frontend");
        }
        onNewMsg: {
            Global.monitorNewMsg();
        }
    }

    Timer {                                                                        
        id: monitorTimer                                                              
        interval: 6000; running: true; repeat: true 
        onTriggered: {
            doMonitor();
        }
    }

    HeadImg {
        id: loginUserHeadImg
        v2: Global.v2 
        userName: Global.loginUserName
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
                    title: qsTr("WeChat")
                    iconSource: "images/messages.png"
                    WXView {}
                }

                IconTab {
                    title: qsTr("Contact")
                    iconSource: "images/contacts.png"
                    ContactListView {}
                }

                IconTab {
                    title: qsTr("Me")
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
                    text: qsTr("WeChat")
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
