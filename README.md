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
