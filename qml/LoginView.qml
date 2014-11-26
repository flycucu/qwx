// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0

Item {
    id: loginView
    width: parent.width; height: parent.height

    property string uuid: ""
    property string tip: "1"
    property string uin: ""
    property string sid: ""

    UUID {
        id: uuidObj
        onError: {
            console.log("ERROR: 获取UUID失败!")
        }
        onUuidChanged: {
            loginView.uuid = uuid
            qrcodeImage.source = "https://login.weixin.qq.com/qrcode/" + uuid + "?t=webwx"
            qrcodeImage.visible = true                     
            scanQRcode()
            scanTimer.start()
        }
    }

    Image {
        id: qrcodeImage
        visible: false
    }

    Scan {
        id: scanObj
        onError: {
            console.log("ERROR:", strerror)
            console.log("DEBUG: 等待扫描 ...")
        }
        onScanedButWaitConfirm: {
            console.log("DEBUG: 已扫描等待确认 ...")
            loginView.tip = "0"
            statReportObj.firstRequestSuccess(loginView.uuid)
            statReportObj.secondRequestStart(loginView.uuid)
        }
        onScanedAndConfirmed: {
            console.log("DEBUG: 已确认")
            scanTimer.stop()
            cookieObj.get(redirect_uri)
        }
    }

    function scanQRcode() { scanObj.get(loginView.uuid, loginView.tip) }

    Timer {
        id: scanTimer
        interval: 16000; running: false; repeat: true
        onTriggered: { scanQRcode() }
    }

    Cookie {
        id: cookieObj
        onInfoChanged: {
            loginView.uin = uin
            loginView.sid = sid
            statReportObj.post(loginView.uuid)
            initObj.post(loginView.uin, loginView.sid)
        }
    }

    StatReport {
        id: statReportObj
    }

    Init {
        id: initObj
        onSkeyChanged: {
            modContactObj.post(loginView.uin, loginView.sid)
            contactObj.post()                                                      
            //----------------------------------------------------------------- 
            // TODO: only for test                                                 
            headImgObj.get("sirtoozee")                                            
            statusNotifyObj.post(loginView.uin, loginView.sid, "sirtoozee")
            //----------------------------------------------------------------- 
            stackView.clear()                                                      
            stackView.push({item: Qt.resolvedUrl("ContactListView.qml"),           
                            properties: {modContactObj: modContactObj,             
                                         uin: loginView.uin, 
                                         sid: loginView.sid, 
                                         skey: skey}})
        }
    }

    ModContact {
        id: modContactObj
    }

    Contact {
        id: contactObj
    }

    HeadImg {
        id: headImgObj
    }

    StatusNotify {
        id: statusNotifyObj
    }
}
