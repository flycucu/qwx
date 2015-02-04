// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0
import "global.js" as Global

Item {
    id: wxView
    width: parent.width; height: parent.height

    ListModel {
        id: wxListModel
        Component.onCompleted: {
            wxListModel.remove(0);
        } 
                                                                                   
        ListElement { wxUserName: ""; wxNickName: ""; wxContent: "" } 
    }

    Component.onCompleted: {
        Global.wxView = wxView;
        for (var i = 0; i < Global.initContactList.length; i++) {
            wxListModel.append({"wxUserName": Global.initContactList[i].userName, 
                                "wxNickName": Global.initContactList[i].nickName, 
                                "wxContent": ""});
        }
    }

    Contact {                                                                      
        id: contactObj                                                             
        Component.onCompleted: {                                                   
            if (Global.v2) {                                              
                contactObj.postV2()                                                
            } else {                                                               
                contactObj.post()                                                  
            }                                                                      
        }                                                                          
    }

    function doNewMsg() 
    {
        if (Global.v2) {
            getMsgObj.postV2(Global.uin, Global.sid, Global.skey, Global.syncKey);
        } else {
            getMsgObj.post(Global.uin, Global.sid, Global.skey, Global.syncKey);
        }
    }

    SendMsg {
        id: sendMsgObj
    }

    Process {                                                                      
        id: processObj                                                             
        program: "notify-send"                                                     
    }

    GetMsg {
        id: getMsgObj
        onSyncKeyChanged: {
            if (getMsgObj.syncKey.length == 0) {
                rootWindowStackView.clear(); 
                rootWindowStackView.push({item: Qt.resolvedUrl("SplashView.qml")});
                return;
            }
            Global.syncKey = getMsgObj.syncKey;
        }
        onNoMsg: {
            rootWindow.title = "微信Qt前端";
        }
        onNewMsg: {
            var isExist = false;
            var nickName = "";
            
            rootWindow.title = "微信Qt前端 - 有新消息";
            for (var i = 0; i < wxListModel.count; i++) {
                var userName = wxListModel.get(i).wxUserName;
                nickName = contactObj.getNickName(userName);
                if (userName == fromUserName || 
                    userName == toUserName) {
                    isExist = true;
                    wxListModel.get(i).wxContent = content;
                    wxListModel.move(i, 0, 1);
                    break;
                }
            }

            if (isExist == false) {
                if (Global.loginUserName == fromUserName) {
                    nickName = contactObj.getNickName(toUserName);
                    wxListModel.insert(0, {"wxUserName": toUserName, 
                                           "wxNickName": nickName});
                } else {
                    nickName = contactObj.getNickName(fromUserName);
                    wxListModel.insert(0, {"wxUserName": fromUserName, 
                                           "wxNickName": nickName});
                }
            }

            if (nickName != "") {
                processObj.arguments = [nickName, content, '--icon=dialog-information', '-t', '3000'];
                processObj.start();
            }

            if (content == "away") {
                Global.isAway = true;
            } else if (content == "back") {
                Global.isAway = false;
            } else if (content == "小逗比出来" ||
                       content == "robot come") {
                Global.isRobot = true;
            } else if (content == "小逗比退下" ||
                       content == "robot away") {
                Global.isRobot = false;
            }
            if (Global.isAway) {
                var awayMsg = "不在，请在滴声后留言[咖啡] 消息来自qwx https://github.com/xiangzhai/qwx 若打扰到您，请回复内容back，暂时屏蔽自动回复[阴险]";
                if (Global.v2) {
                    sendMsgObj.sendV2(Global.uin,
                            Global.sid,                                          
                            Global.skey,
                            Global.deviceId, 
                            toUserName,                                 
                            fromUserName,                                   
                            contactObj.getNickName(Global.loginUserName) + awayMsg,
                            Global.syncKey)                                      
                } else {
                    sendMsgObj.send(Global.uin,
                                Global.sid,
                                Global.skey,
                                Global.deviceId,
                                toUserName,
                                fromUserName,
                                contactObj.getNickName(Global.loginUserName) + awayMsg,
                                Global.syncKey)
                }
            }
        }
    }

    ListView {
        id: wxListView
        model: wxListModel
        anchors.fill: parent

        delegate: Item {
            width: parent.width; height: 60

            HeadImg {
                id: headImgObj
                v2: Global.v2
                userName: wxUserName
                onFilePathChanged: {
                    headImage.imageSource = headImgObj.filePath
                }
            }

            CircleImage {
                id: headImage
                width: 42; height: 42
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            Text {
                id: nickNameText
                text: wxNickName
                font.pixelSize: 13
                anchors.top: parent.top
                anchors.topMargin: 14
                anchors.left: headImage.right
                anchors.leftMargin: 11
            }

            Text {
                text: wxContent
                font.pixelSize: 11
                anchors.top: nickNameText.bottom
                anchors.topMargin: 6
                anchors.left: nickNameText.left
            }

            Rectangle {
                width: parent.width; height: 1
                color: "#dadada"
            }

            MouseArea {                                                        
                anchors.fill: parent                                           
                onClicked: {                                                   
                    navigatorStackView.push({                                  
                        item: Qt.resolvedUrl("ChatView.qml"),                  
                        properties: {                                          
                            fromUserName: Global.loginUserName,
                            toUserName: wxUserName,                    
                            toNickName: wxNickName}})                  
                }                                                              
            }
        }
    }
}
