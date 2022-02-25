![](https://img.shields.io/badge/version-2.0.0-green.svg)   ![](https://img.shields.io/badge/By-Suyc323-orange.svg)  
![](https://img.shields.io/badge/State-Development-blue.svg)

PreRelease版本2.0.0 review1 预计在2022年3月3日发布

# XSuNet
A server-side framework for intelligent building cloud services.
## 2.0新特性

#### 动态多线程
所有的消息Server收到后会存入一个动态数组容器，服务器会根据负载情况启用多个线程从容器中拿取消息进行处理，负载上升时会增加启用的线程数（最多为3个），负载下降时会减少启用的线程数。当没有消息即0负载时，Server会将所有消息处理线程销毁，即Core模块进入休眠，直到Connect模块收到新的消息。

#### 过期包丢弃
服务器在处理信息Device发出的上报请求和远程控制端发出的控制指令等具有时效性的信息时，会记录最近的一个包的TIME作为Device或者Remote Controller的最近更新时间，如果收到的包的时间早于最近更新时间，将视作过期包直接予以丢弃。
*所有的消息都应该带有TIME属性（即消息的发出时间）。如果消息不带有TIME，并且服务器配置文件ServerSetting.ini中“StrictTimeChecks被设置为”true”，该消息将会直接被丢弃而不会进行处理。

#### 超大数据分包发送
服务器2.0版本起支持接受超过单次传输大小上限的数据分为多个包进行传送，目前该功能在2.0版本处于Beta阶段，存在出现问题和修改、删除的可能，请暂时不要依赖该功能。该功能将在2.1版本正式可用并在说明文档中更新。

## 用于搭建智能楼宇云服务端程序的XSuNet框架



### 数据驱动的对象同步控制

1.终端设备周期性通过调用远程API:”DEVICE_UPDATE_INFO”发送完整的设备属性(包含设备名称，上报变量和受控变量的当前状态)，以光感智能光照系统为例，如下：
{“API”:”DEVICE_UPDATE_INFO”,”ARGS”:{“DEVICE_NAME“:”LIGHT001“,”RES”:{“ILLUMINANCE”:20,”DEFAULT_THRESHOLD”:70},”CONTROLLED”:{“STATE”:0}}}

*这里ILLUMINANCE指光强传感器的实时数据

*这里DEFAULT_THRESHOLD指默认光感阈值，如果云端没有设置光感阈值，则按照消息包含的默认阈值判断灯光应当开启还是关闭。

*STATE指的是灯光的开闭状态

2.云端按照收到的数据判断终端设备应当处于什么状态，并将受控变量的应当变化后状态发送给终端设备，消息示例如下：

{CONTROL”:{“STATE”:1},TIME：}

3.终端设备根据收到来自云端的消息后，将受控变量同步到设备完成控制过程。需要注意的是，Device向Server发送一次信息上报后，Server不管是否对受控变量做出改变，都会发送2中示例的控制反馈信息，Device应当在收到2的消息或超时后向Server进行下一次数据上报。

### 远程控制端的对象查询
前端用户界面（App/WebApp）与Server的通讯同样遵循上述“数据驱动的对象同步控制机制“，但是由于前端用户界面需要访问所有Server下挂的设备信息，如果全部实时同步需要很大的数据量。因此，我们建议实时数据交换采用查询接口而非获取接口。

1.	查询接口
发送信息
{“API”:”FIND_DEVICE”,”ARGS”:{“DEVICE_NAME”:”LIGHT001”,”KEY”:”X45V45A54N42”}}
该条请求将获得对应Device的全部信息
{“API”:”FIND_DEVICES_BY_CLASS”,”ARGS”:{“DEVICE_CLASSNAME”:”LIGHT”,”KEY”:”X45V45A54N42”}}
该条请求获得对应class的全部Device的全部信息

2.	获取接口
{“API”:”GET_DEVICES”,”ARGS”:{“”KEY”:”X45V45A54N42”}}
该条请求获得Server下挂的所有Device的所有信息。

