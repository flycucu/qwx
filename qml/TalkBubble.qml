// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

import QtQuick 2.0

Item {
    id: talkBubble
    property string text 

    Canvas {
        id: canvas
        width: 320
        height: 280

        property color strokeStyle:  Qt.darker(fillStyle, 1.3)
        property color fillStyle: "#14aaff" // blue
        property int lineWidth: lineWidthCtrl.value
        property bool fill: true
        property bool stroke: true
        property real alpha: 1.0
        property real scale : 2.3
        property real rotate : 0.0

        antialiasing: true

        onLineWidthChanged:requestPaint();
        onFillChanged:requestPaint();
        onStrokeChanged:requestPaint();

        onPaint: {
            var ctx = canvas.getContext('2d');
            var originX = 75
            var originY = 75

            ctx.save();
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.translate(originX, originX);
            ctx.strokeStyle = canvas.strokeStyle;
            ctx.fillStyle = canvas.fillStyle;
            ctx.lineWidth = canvas.lineWidth;

            ctx.translate(originX, originY)
            ctx.rotate(canvas.rotate);
            ctx.scale(canvas.scale, canvas.scale);
            ctx.translate(-originX, -originY)

            ctx.beginPath();
            ctx.moveTo(75,25);
            ctx.quadraticCurveTo(25,25,25,62.5);
            ctx.quadraticCurveTo(25,100,50,100);
            ctx.quadraticCurveTo(50,120,30,125);
            ctx.quadraticCurveTo(60,120,65,100);
            ctx.quadraticCurveTo(125,100,125,62.5);
            ctx.quadraticCurveTo(125,25,75,25);
            ctx.closePath();

            if (canvas.fill)
                ctx.fill();
            if (canvas.stroke)
                ctx.stroke();

            ctx.fillStyle = "white";
            ctx.font = "bold 6px sans-serif";
            // TODO: multiline wrap
            ctx.fillText(talkBubble.text, 40, 70);
            ctx.restore();
        }
    }
}
