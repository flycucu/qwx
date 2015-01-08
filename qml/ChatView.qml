// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Rectangle {
    id: chatView
    width: parent.width; height: parent.height
    color: "white"

    property bool v2: false
    property string uin
    property string sid
    property string skey
    property string deviceId
    property string ticket
    property string fromUserName
    property string toUserName
    property string toNickName
    property var syncKey
    property bool quitRobot: true

    function moveToTheEnd() 
    {
        chatListView.positionViewAtIndex(chatListView.count - 1, ListView.End)
    }

    XiaoDouBi {
        id: xiaodoubiObj
        onContentChanged: {
            if (quitRobot) {
                return
            }
            content = "小逗比：" + content
            if (chatView.v2) {
                sendMsgObj.sendV2(chatView.uin,
                            chatView.sid,                                          
                            chatView.skey,
                            chatView.deviceId, 
                            chatView.fromUserName,                                 
                            chatView.toUserName,                                   
                            content,                                 
                            chatView.syncKey)                                      
            } else {
                sendMsgObj.send(chatView.uin,
                                chatView.sid,
                                chatView.skey,
                                chatView.deviceId,
                                chatView.fromUserName,
                                chatView.toUserName,
                                content,
                                chatView.syncKey)
            }

            chatListModel.append({"content": content,                
                                  "curUserName": chatView.fromUserName})           
            moveToTheEnd()
        }
    }

    Contact {                                                                      
        id: contactObj                                                             
        Component.onCompleted: {                                                   
            if (chatView.v2) {                                                       
                contactObj.postV2()                                                
            } else {                                                               
                contactObj.post()                                                  
            }                                                                      
        }                                                                          
    }

    Process {
        id: processObj
        program: "notify-send"
    }

    GetMsg {                                                                       
        id: getMsgObj
        fromUserName: chatView.fromUserName
        toUserName: chatView.toUserName
        onReceived: {
            if (content == "小逗比退下") {
                quitRobot = true
            } else if (content == "小逗比出来") {
                quitRobot = false
            }
            chatListModel.append({"content": content, 
                                  "curUserName": userName})
            moveToTheEnd()
            if (!quitRobot) { 
                xiaodoubiObj.get(content)
            }
        }
        onNewMsg: {
            if (fromUserName != chatView.fromUserName || 
            fromUserName != chatView.toUserName) {
                var nickName = ""
                if (chatView.fromUserName == fromUserName) {
                    nickName = contactObj.getNickName(toUserName)
                } else {
                    nickName = contactObj.getNickName(fromUserName)
                }
                processObj.arguments = [nickName, content, '--icon=dialog-information', '-t', '3000']
                processObj.start()
            }
        }
        onSyncKeyChanged: {
            chatView.syncKey = getMsgObj.syncKey
        }
    }                                                                              
                                                                                   
    Timer {                                                                        
        id: getMsgTimer                                                            
        interval: 1000; running: true; repeat: true; triggeredOnStart: true 
        onTriggered: {                                                             
            if (chatView.v2) {
                getMsgObj.postV2(chatView.uin, chatView.sid, chatView.skey, chatView.syncKey)
            } else {
                getMsgObj.post(chatView.uin, chatView.sid, chatView.skey, chatView.syncKey)
            }
        }                                                                          
    }

    SendMsg {
        id: sendMsgObj
    }

    ListModel {
        id: chatListModel
        Component.onCompleted: {
            chatListModel.clear()
        }

        ListElement { content: ""; curUserName: "" }
    }

    ListView {
        id: chatListView
        model: chatListModel
        width: parent.width; height: parent.height - chatHeader.height - 
        sendMsgTextField.height
        anchors.top: chatHeader.bottom
        spacing: 10
        delegate: Item {
            width: parent.width 
            height: chatText.contentHeight < fromUserHeadImage.height ? fromUserHeadImage.height : chatText.contentHeight
   
            HeadImg {
                id: fromUserHeadImgObj 
                userName: curUserName 
                onFilePathChanged: { 
                    fromUserHeadImage.imageSource = fromUserHeadImgObj.filePath 
                }
            }

            CircleImage {
                id: fromUserHeadImage
                width: 42; height: 42
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
            }

            Text {
                id: chatText
                text: content
                width: parent.width - fromUserHeadImage.width - 30 
                wrapMode: Text.WordWrap
                font.pixelSize: 11
                anchors.left: fromUserHeadImage.right
                anchors.leftMargin: 10
            }
        }
    }

    Rectangle {                                                            
        id: chatHeader                                                
        width: parent.width; height: 58                                    
        anchors.top: parent.top                                            
        color: "#20282a"                                                   

        Image {
            id: backImage
            source: "../images/back.png"
            width: 36; height: 36
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 19

            MouseArea {
                anchors.fill: parent
                onClicked: { navigatorStackView.pop() }
            }
        }

        Text {                                                             
            text: chatView.toNickName
            font.pixelSize: 22                                             
            anchors.verticalCenter: parent.verticalCenter                  
            anchors.left: backImage.right
            anchors.leftMargin: 19                                         
            color: "white"                                                 
        }                                                                  
    }

    TextField {
        id: sendMsgTextField
        width: parent.width - sendButton.width
        anchors.bottom: parent.bottom
    }

    Button {
        id: sendButton
        text: "发送"
        anchors.top: sendMsgTextField.top
        anchors.right: parent.right
        onClicked: {
            if (chatView.v2) {
                sendMsgObj.sendV2(chatView.uin,
                            chatView.sid, 
                            chatView.skey,
                            chatView.deviceId, 
                            chatView.fromUserName, 
                            chatView.toUserName, 
                            sendMsgTextField.text, 
                            chatView.syncKey)
            } else {
                sendMsgObj.send(chatView.uin,
                                chatView.sid,
                                chatView.skey,
                                chatView.deviceId,
                                chatView.fromUserName,
                                chatView.toUserName,
                                sendMsgTextField.text,
                                chatView.syncKey)
            }
            chatListModel.append({"content": sendMsgTextField.text, 
                                  "curUserName": chatView.fromUserName})
            if (sendMsgTextField.text == "小逗比出来") {
                quitRobot = false
                xiaodoubiObj.get(sendMsgTextField.text)
            } else if (sendMsgTextField.text == "小逗比退下") {
                quitRobot = true
            }
            sendMsgTextField.text = ""
            moveToTheEnd()
        }
    }
}
