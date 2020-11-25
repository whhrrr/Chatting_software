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

*** 

*** 

###### 建立连接与收发消息：

1、从控件中获取IP地址及端口，调用GetDlgItem()->GetWindowTextW函数。使用USES_CONVERSION宏来转换CString为char*

> USES_CONVERSION是ALT中的一个宏定义用于编码转换。要想使用这个宏需要加上头文件#include<atlcon.h> USES_CONVERSION从堆栈上分配内存，直到调用它的函数返回。该内存不会被释放，如果在一个循环中这个宏被反复调用会导致stackoverflow.



`客户端`需要重写Socket类，在控件连接按钮的操作函数上生成一个新的CMySocket对象创建套接字调用Connect去连接。连接成功会调用Connect函数后会回调OnConnect函数。在界面上显示信息。发送函数会通过Send函数发送给服务端然后将自身发送的信息显示到列表框(MFCClientDlg.cpp中实现)。接收函数主要是会通过创建的CMySocket调用回调函数OnReceive，通过格式转换将接收到的信息显示到客户端。

`服务端`需要重写2个类：因为服务端有两类Socket,一类是服务器serversocket，一类是每来一个连接的socket。在server端启动按钮处理函数中创建服务器Socket对象创建套接字。进行连接。进行连接之后创建新的Socket对象与服务器进行通信。调用Accept开始接收连接。发送消息控件处理函数与客户端类似。

***

###### 自动回复

在客户端重写的Socket类中重写了OnReceive函数负责接收服务端发来的信息产生回调。如果自动回复控件被勾选那么出发自动恢复处理程序。通过调用客户端Send函数向服务端发送编辑框内自动回复信息(CMySocket.cpp中实现)

***

###### 颜色更改及保存配置信息

在客户端和服务端中存在颜色设置选项，那么需要使用GetWindowTextW拿到控件的颜色选择。调用SetTextColor()函数改变字体颜色。保存配置信息需要在初始化中添加处理配置文件函数，如果处理没有配置文件就设置名称为默认名称。如果配置文件存在那么就设置控件中内容为获取的内容。保存昵称控件作用为修改昵称。首先需要保证控件中内容不为空。如果确认那么就将配置信息写入配置文件。

***

###### 断开连接

断开连接首先就是把m_client、m_server、m_chat资源回收。将资源重新置为NULL。然后显示到列表框中。三者实际上就是通信中调用的中间支持者。

###### 快捷打开以及快捷键使用

使用ShellExecute可以支持快捷打开exe文件

快捷键使用主要是对按键按下时的处理。

示例代码：

```cpp


if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        return TRUE;
    }
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
    {
        return TRUE;
    }
    //添加快捷键 ctrl + x 退出对话框
    if (pMsg->message == WM_KEYDOWN)
    {
        if (GetKeyState(VK_CONTROL) < 0)    //ctrl键是否按下
        {
            if (pMsg->wParam == 'X')
            {
                CDialog::OnOK();        //退出
}}}
```

总结：客户端与服务端的通信最重要的是回调函数接发信息。主要的实现除了初始化的基本流程之外主要是对C++中面向对象性质的理解。例如不论是接收信息还是发送信息都需要创建的对象去调用函数才能完成。例如在Server端用一个m_server接收一个连接请求就会重新创建一个Socket对象m_chat去进行接发消息。而m_server只是用来接收信息。在客户端中不论是收发消息还是创建连接都会用m_client对象去调用函数。

不足：其实对于MFC中控件的使用还是不太熟悉。在视频和帮助文档的帮助下才能完成。需要通过MFC的学习了解通信的基本流程，熟悉开发的流程。
