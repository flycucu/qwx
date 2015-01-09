SyncKey的BUG 1100
------------------

> http://www.blogjava.net/yongboy/archive/2014/03/05/410636.html
> http://www.langyeweb.com/Program/70.html 

## 第一步 POST https://wx(2).qq.com/cgi-bin/mmwebwx-bin/webwxinit?r=时间戳

```
{"BaseRequest":{"Uin":"Uin值","Sid":"Sid值","Skey":"","DeviceID":"e+随机数"}}
```

我们将返回（结果）保存到init.json[https://github.com/xiangzhai/qwx/blob/master/src/init.cpp#L96] 文件中。

init.json文件部分内容如下：

```
"SyncKey": {                                                                       
"Count": 4,                                                                        
"List": [{                                                                         
"Key": 1,                                                                          
"Val": 632103871                                                                   
}                                                                                  
,{                                                                                 
"Key": 2,                                                                          
"Val": 632104379                                                                   
}                                                                                  
,{                                                                                 
"Key": 3,                                                                          
"Val": 632104156                                                                   
}                                                                                  
,{                                                                                 
"Key": 1000,                                                                       
"Val": 1420698575                                                                  
}                                                                                  
]                                                                                  
}
```

将其定义为InitSyncKey只有4个，键值是1、2、3、1000


## 第二步 POST https://wx(2).qq.com/cgi-bin/mmwebwx-bin/webwxsync?sid=Sid值&r=时间戳

```
{"BaseRequest":{"Uin":Uin值,"Sid":"Sid值"},"SyncKey":{"Count":4,"List":[{"Key":1,"Val":632103871},{"Key":2,"Val":632104379},{"Key":3,"Val":632104156},{"Key":1000,"Val":1420698575}]},"rr":时间戳}
```

这里POST的json内容中用到的SyncKey就是第一步中返回内容中的。

我们再把返回保存到sync.json[https://github.com/xiangzhai/qwx/blob/master/src/sync.cpp#L79] 文件中。

sync.json部分内容如下：

```
"SyncKey": {                                                                       
"Count": 5,                                                                        
"List": [{                                                                         
"Key": 1,                                                                          
"Val": 632103871                                                                   
}                                                                                  
,{                                                                                 
"Key": 2,                                                                          
"Val": 632104349                                                                   
}                                                                                  
,{                                                                                 
"Key": 3,                                                                          
"Val": 632104156                                                                   
}                                                                                  
,{                                                                                 
"Key": 11,                                                                         
"Val": 632103861                                                                   
}                                                                                  
,{                                                                                 
"Key": 1000,                                                                       
"Val": 1420688851                                                                  
}                                                                                  
]                                                                                  
}
```

注意：与第一步不同，这里（返回）的SyncKey的个数变成了5，并且在后续的getmsg.cpp[https://github.com/xiangzhai/qwx/blob/master/src/getmsg.cpp#L53]
sendmsg.cpp[https://github.com/xiangzhai/qwx/blob/master/src/sendmsg.cpp#L103]
都是用的5个元素的SyncKey

## 疑惑、问题、1100来了

用“微信同步心跳”做为关键词Google，可以发现

> http://freezingsky.iteye.com/blog/2055502

当其返回不是window.synccheck={retcode:"0",selector:"0"}就需要再次回到第二步，
重新获得SyncKey！
但是POST的json内容中用到的SyncKey只有4个元素，即第一步的InitSyncKey，
我现在用的是5个SyncKey，弃掉Key值为11的元素。

不幸运的是我会得到window.synccheck={retcode:"1100",selector:"0"}一旦出现1100
心跳同步就失败了！无法接收、发送微信 https://github.com/xiangzhai/qwx/issues/8

