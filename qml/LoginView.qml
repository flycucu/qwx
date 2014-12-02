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
    property string skey: ""

    Text {
        id: titleText
        text: "微信"
        font.pixelSize: 22
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 42
    }

    Image {
        id: qrcodeImage
        source: "https://login.weixin.qq.com/qrcode/" + loginView.uuid + "?t=webwx"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: titleText.bottom
        anchors.topMargin: 31
    }

    Text {
        text: "请使用微信扫描二维码以登录"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: qrcodeImage.bottom
        anchors.topMargin: 38
    }

    Scan {
        id: scanObj
        onError: { console.log("ERROR:", strerror) }
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
        interval: 10000; running: true; repeat: true
        onTriggered: { scanQRcode() }
    }

    Cookie {
        id: cookieObj
        onInfoV1Changed: {
            loginView.uin = uin
            loginView.sid = sid
            statReportObj.post(loginView.uuid)
            initObj.post(loginView.uin, loginView.sid, ticket)
        }
        onInfoV2Changed: {
            loginView.uin = uin
            loginView.sid = sid
            loginView.skey = skey
            statReportObj.post(loginView.uuid)
            initObj.post(loginView.uin, loginView.sid, ticket)
        }
    }

    StatReport {
        id: statReportObj
    }

    Init {
        id: initObj
        onSkeyChanged: {
            if (skey != "") { loginView.skey = skey }
            syncObj.post(loginView.uin, loginView.sid, synckey)
            rootWindowStackView.clear()
            rootWindowStackView.push({
                item: Qt.resolvedUrl("NavigatorView.qml"),  
                properties: {uin: loginView.uin, 
                             sid: loginView.sid, 
                             skey: loginView.skey, 
                             initObj: initObj}})
        }
    }

    Sync {
        id: syncObj
    }
}
