// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.2
import QtQuick.Controls 1.1
import cn.com.isoft.qwx 1.0
import "global.js" as Global

Item {
    id: loginView
    width: parent.width; height: parent.height

    property string uuid
    property string tip: "1"

    Text {
        id: titleText
        text: Global.v2 ? qsTr("WeChat") + " V2" : qsTr("WeChat")
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
        id: tipText
        text: qsTr("Loading QRcode ...")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: qrcodeImage.bottom
        anchors.topMargin: 38
    }

    Scan {
        id: scanObj
        onError: { console.log("ERROR:", strerror) }
        onScanedButWaitConfirm: {
            console.log("scanned but waiting for confirm...");
            tipText.text = qsTr("Please confirm on your mobile");
            loginView.tip = "0";
            statReportObj.firstRequestSuccess(loginView.uuid);
            statReportObj.secondRequestStart(loginView.uuid);
        }
        onScanedAndConfirmed: {
            console.log("confirmed!");
            tipText.text = qsTr("Confirmed then waiting for login");
            scanTimer.stop();
            if (Global.v2) {
                cookieObj.getV2(redirect_uri);
            } else {
                cookieObj.get(redirect_uri);
            }
        }
    }

    function scanQRcode() { 
        if (qrcodeImage.status == Image.Ready) {
            tipText.text = Global.v2 ? 
                                qsTr("Please again scan the QRcode to login") : 
                                qsTr("Please scan the QRcode to login");
            scanObj.get(loginView.uuid, loginView.tip);
        }
    }

    Timer {
        id: scanTimer
        interval: 1000; running: true; repeat: true; triggeredOnStart: true
        onTriggered: { scanQRcode() }
    }

    Cookie {
        id: cookieObj
        onInfoChanged: {
            Global.uin = uin
            Global.sid = sid
            Global.ticket = ticket
            if (Global.v2) {
                statReportObj.postV2(loginView.uuid)
                initObj.postV2(Global.uin, Global.sid, Global.ticket)
            } else {
                statReportObj.post(loginView.uuid)
                initObj.post(Global.uin, Global.sid, Global.ticket)
            }
        }
        onSwitchToV2: {
            Global.v2 = true;
            rootWindowStackView.clear();
            rootWindowStackView.push({
                item: Qt.resolvedUrl("SplashView.qml")});
        }
    }

    StatReport {
        id: statReportObj
    }

    Init {
        id: initObj
        onSkeyChanged: {
            if (skey != "")
                Global.skey = skey;

            Global.deviceId = initObj.deviceId;
            Global.loginUserName = initObj.loginUserName;
            Global.loginNickName = initObj.loginNickName;
            Global.initContactList = initObj.contactList;
            Global.initSyncKey = syncKey;
            rootWindowStackView.clear();
            rootWindowStackView.push({item: Qt.resolvedUrl("NavigatorView.qml")});
        }
    }
}
