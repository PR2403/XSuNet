![](https://img.shields.io/badge/Development-3.0Alpha-green.svg)  ![](https://img.shields.io/badge/Release-2.0LTS-green.svg)  ![](https://img.shields.io/badge/By-Suyc323-orange.svg)

长期支持版本2.0 LTS 已发布！

查看3.0源码以了解我的最新开发进展和XSuNet的新功能特性，但是3.0Alpha版本目前不具有运行可用性，请不要下载编译使用。

# XSuNet
A SocketConnector-side framework for intelligent building cloud services.

用于搭建智能楼宇云服务的服务端程序框架

## Gen3新特性

### 分布式负载均衡服务器

![image](https://github.com/Suyc323/XSuNet/blob/XSuNet3-master/Images/XSuNetOriginFramework.png)





## 为什么使用XSuNet

### 数据驱动的对象同步控制

1.终端设备周期性通过调用远程API:”DEVICE_UPDATE_INFO”发送完整的设备属性(包含设备名称，上报变量和受控变量的当前状态)，以光感智能光照系统为例，如下：

```
{"API":"DEVICE_UPDATE_INFO","ARGS":{"DEVICE_NAME":"LIGHT001","RES":{"ILLUMINANCE":20,"DEFAULT_THRESHOLD":70},"CONTROLLED":{"STATE":0}},"TIME"："2022-2-7 10:00"}
```

*这里ILLUMINANCE指光强传感器的实时数据:

*这里DEFAULT_THRESHOLD指默认光感阈值，如果云端没有设置光感阈值，则按照消息包含的默认阈值判断灯光应当开启还是关闭。

*STATE指的是灯光的开闭状态

2.云端按照收到的数据判断终端设备应当处于什么状态，并将受控变量的应当变化后状态发送给终端设备，消息示例如下：

```
{"CONTROL":{"STATE":1},"TIME"："2022-2-7 10:00"}
```

3.终端设备根据收到来自云端的消息后，将受控变量同步到设备完成控制过程。需要注意的是，Device向Server发送一次信息上报后，Server不管是否对受控变量做出改变，都会发送2中示例的控制反馈信息，Device应当在收到2的消息或超时后向Server进行下一次数据上报。

### 远程控制端的对象查询
前端用户界面（App/WebApp）与Server的通讯同样遵循上述“数据驱动的对象同步控制机制“，但是由于前端用户界面需要访问所有Server下挂的设备信息，如果全部实时同步需要很大的数据量。因此，我建议实时数据交换采用查询接口而非获取接口。

1.	查询接口

```
{"API":"Client_FIND_DEVICE","ARGS":{"DEVICE_NAME":"LIGHT001","KEY":"X45V45A54N42"}}
```

该条请求将获得对应Device的全部信息

```
{"API":"Client_FIND_DEVICES_BY_CLASS","ARGS":{"DEVICE_CLASSNAME":"LIGHT","KEY":"X45V45A54N42"}}
```

该条请求获得对应class的全部Device的全部信息

2.	获取接口

```
{"API":"Client_GET_DEVICES","ARGS":{"KEY":"X45V45A54N42"}}
```

该条请求获得Server下挂的所有Device的所有信息。

### 逻辑功能使用Lua脚本语言
当C++语言开发的XSuNet服务器主体收到Device上报的数据更新后，会将数据信息传递给用户定义的Lua脚本进行逻辑判断得出控制变量的最终值，并通过控制变量信息返回给Device完成控制过程。
支持上层逻辑业务功能使用脚本语言实现可以使得拓展修改无需更改XSuNet的源码内容和重新编译，仅需修改Scrpts文件夹下的Lua脚本即可。Lua作为一种胶水语言，能很好的辅助C++完成逻辑业务，同时这一特性也为未来将加入的热更新和热拔插功能提供了框架支持。
