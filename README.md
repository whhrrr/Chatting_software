##### 尝试基于MFC创建的聊天软件
软件基于VS2019中MFC模板进行创建
***
服务端和客户端的端口和IP地址都由初始化设定。采用`TCP`连接。在初始化函数中设定。
***
服务端：Server端设置基础的IP地址及端口，用来连接Client客户端。

服务端需要创建两个Socket函数用来通信。因为其中的一个Socket函数只能用来接收客户端发送的信息请求，但是却不会应答这个发送的信息请求。需要重新创建一个Socket去应答这个请求。因为需要服务端接收端都能接收发送消息，所以需要重写接收和发送函数用来满足特定的发送接收请求。
不论是接收函数还是发送函数都需要在发送信息的时候将丛控件内的信息进行编码转换，并按一定格式发送。

服务端发送消息函数CMFCChatServerDlg::OnBnClickedStartBtn()：首先使用`GetDlgItem`获取文本框中的内容保存到创建好的strTmpMsg中。使用宏定义将消息格式转化为char类型指针保存到新创建的变量中发送给客户端。发送客户端后需要设定格式并将自己发送的信息显示到对话框中。发送信息后需要调用GetDlgItem来将发送框中的内容进行清空。完成消息发送。

***
客户端：Client端设置初始端口，用来连接Server端
客户端同样需要创建单独的Socket通信来接受或发送Server端的信息。


***
通用函数：获取当前时间函数，如果在发送消息的过程中加上发送消息的时间，那么需要获取系统当前时间。

如果发送消息需要标准化格式，包括`时间` + `信息` + `消息`。给两个发送函数的cpp文件中都添加上一个发送消息标准化的函数
> 简易版本网络通信
##### C++实现Socket编程---异步非阻塞Socket封装类CSsyncSocket

    使用MSDN去查看类：https://msdn.microsoft.com/zh-cn/?query=
1、CAsyncSocket::Create()，使用#include<afxsock.h>头文件，用AfxSocketInit()初始化。
2、`异步非阻塞`    ???
3、重写一个类，客户端和服务端
4、收到Socket事间之后，只是简单地回调CAsyncSocket::OnReceive()等虚函数，所以CAsuncSocket的派生类，只需要在这些虚函数里添加发送和接收代码
5、客户方在使用CAsyncSocket::Connect()时，往往返回一个WSAEWOULDBLOCK的错误(其他函数调用也是如此)。 实际上这不应该算作一个错误，它是Socket提醒我们，由于你使用了非阻塞Socket方式，所以(连接)操作需要时间，不能瞬间建立。
6 、事实上，我们可以在Connect()调用之后等待CAsyncSocket::OnConnect()事件被触发，CAsyncSocket::OnConnect()是要表明Socket要么连接成功了，要么连接彻底失败了。至此，我们在CAsyncSocket::OnConnect()被调用之后就知道是否Socket连接成功了，还是失败了

7 、特别注意：难点，那就是在客户方调用Connect()连接服务方，那么服务方如何Accept()，以建立连接的问题。简单的做法就是在监听的Socket收到OnAccept()时，用一个新的CAsyncSocket对象去建立连接



服务端需要重写2个类：因为服务端有两类Socket,一类是服务器serversocket，一类是每来一个连接的socket

*** 

*** 

###### 建立连接：

`服务端`创建一个对象用来传递等待连接的信息。调用Accept用来接收信息。接收到信息之后创建一个CChatSocket对象用来接发消息。然后刷新控件

`客户端`接收建立连接函数`void CmySocket::OnConnect(int nErrorCode)`。创建一个客户端对象dlg并与创建的连接进行通信。如果创建成功调用OnSend函数发送信息提示连接成功

***

###### 收发消息

***

###### 自动回复

***

###### 颜色更改及保存配置信息

***

###### 断开连接

