/*
 * gVirtuS -- A GPGPU transparent virtualization component.
 *
 * Copyright (C) 2009-2010  The University of Napoli Parthenope at Naples.
 *
 * This file is part of gVirtuS.
 *
 * gVirtuS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gVirtuS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gVirtuS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Written by: Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>,
 *             Department of Applied Science
 */

/**
 * @file   TcpCommunicator.cpp
 * @author Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>
 * @date   Thu Oct 8 12:08:33 2009
 *
 * @brief
 *
 *
 */

#include "TcpCommunicator.h"

# include <assert.h>
# include <string>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#else
#include <WinSock2.h>
static bool initialized = false;
#endif

#include <cstring>
#include <cstdlib>

using namespace std;

TcpCommunicator::TcpCommunicator(const std::string& communicator) {//传入的参数为"tcp://localhost:9988"
#ifdef _WIN32
	if(!initialized) {
		WSADATA data;
		if(WSAStartup(MAKEWORD(2, 2), &data) != 0)
			throw "Cannot initialized WinSock.";
		initialized = true;
	}
#endif

	zmqHostname = communicator;	//zeromq方式中只需要这一句就行了，下面的都是多余的,（唯一的用处是用来检验传入参数的格式是否正确）
	//与tcp不同，zeromq无法解析字符串"lcoalhost",所以要用"*"来代替
	//string::size_tpye pos = zmqHostname.find( "localhost", 0 );
	//s.replace(pos, 9, "*");

    const char *valueptr = strstr(communicator.c_str(), "://") + 3;//valueptr指向位置是"localhost:9988"的开头
    const char *portptr = strchr(valueptr, ':');//*portptr的值为":9988"
    if (portptr == NULL)
        throw "Port not specified.";
    /*
     * strtol函数用来将第一个参数（字符串型）转化为数字
     * mPort的值为9988
     */
    mPort = (short) strtol(portptr + 1, NULL, 10);
#ifdef _WIN32
    char *hostname = _strdup(valueptr);
#else
    char *hostname = strdup(valueptr);//strdup是字符串复制函数,*hostname的值为"localhost:9988"
#endif
    hostname[portptr - valueptr] = 0;//hostname的值变为了"localhost"
    mHostname = string(hostname);//mHostname表示服务器的主机IP地址
    struct hostent *ent = gethostbyname(hostname);//这是socket内容
    free(hostname);
    if (ent == NULL)
        throw "TcpCommunicator: Can't resolve hostname '" + mHostname + "'.";
    mInAddrSize = ent->h_length;//主机的IP地址的长度
    /*
     * mInAddr存储主机的IP地址，应该是网络字节序
     */
    mInAddr = new char[mInAddrSize];
    memcpy(mInAddr, *ent->h_addr_list, mInAddrSize);
}

TcpCommunicator::TcpCommunicator(const char *hostname, short port) {
    mHostname = string(hostname);
    struct hostent *ent = gethostbyname(hostname);
    if (ent == NULL)
        throw "TcpCommunicator: Can't resolve hostname '" + mHostname + "'.";
    mInAddrSize = ent->h_length;
    mInAddr = new char[mInAddrSize];
    memcpy(mInAddr, *ent->h_addr_list, mInAddrSize);
    mPort = port;
}

TcpCommunicator::TcpCommunicator(int fd, const char *hostname) {
    mSocketFd = fd;
    InitializeStream();
}

/*
 * Sandy 2016.05.17
 * 用来对zeromq方式进行初始化
 */
TcpCommunicator::TcpCommunicator(void* zmq, int fd,const char *hostname) {
    zeroSocketFd = zmq;
    mSocketFd = fd;
    InitializeStream();
}

TcpCommunicator::~TcpCommunicator() {
    delete[] mInAddr;
}

//2016.04.26 Sandy
//把通信方式 从socket修改为 zeromq
void TcpCommunicator::Serve() {
    //struct sockaddr_in socket_addr;
	void *context = zmq_ctx_new ();//新建一个zeromq 的环境
	if( NULL == context)
	{
		throw "**zmqCommunicator:Can't create zmq_context.";
	}
	printf( "create a new zeromq context...\n");
	 // Socket to talk to clients
	void *socket_fd = zmq_socket (context, ZMQ_PAIR);
	if( NULL == socket_fd)
	{
		throw "**zmqCommunicator:Can't create zmq_socket.";
	}
	printf( "create a new zeromq socket...\n");

	//int result = zmq_bind (socket_fd, "tcp://*:9988");//这里只是暂时的，应该把第二个参数修改为构造函数的传输参数
	int result = zmq_bind (socket_fd, zmqHostname.c_str() );//这里只是暂时的，应该把第二个参数修改为构造函数的传输参数
	 if( result != 0)
		throw "zmqCommunicator: Can't bind socket.";
	 printf( "bind zeromq socket on localhost:9988.\n");

	 zeroSocketFd = socket_fd; //Sandy 2016.05.17
	int fd = 0;
	size_t fd_len = sizeof(int);
	int rc = zmq_getsockopt( socket_fd,ZMQ_FD, &fd,&fd_len) ;
	assert( rc == 0 );

	//cout<<"File descriptor is"<<fd<<endl;
	//在tcp连接方式中mSocketFd 非常重要，因为涉及到了函数InitializeStream中流的初始化，如果失败一定是这个值不能用来初始化流
	//在zeromq方式中毫无用处
	 mSocketFd = fd;
}

const Communicator * const TcpCommunicator::Accept() const
{

	/*
	void *context_ack = zmq_init (1);
	// Socket to talk to clients
	void *server_socket = zmq_socket (context_ack, ZMQ_PAIR);
	//void *server_socket = zmq_socket (context_ack, ZMQ_REP);
	//void *responder = zmq_socket (context_ack, ZMQ_STREAM);
	assert( NULL != server_socket);
	int bind_result = zmq_bind (server_socket, "tcp://*:8888");
	assert( 0 == bind_result);
	printf("binding on port 8888.\nwaiting client send message...\n");

    //Sandy 2016.05.12
    //程序阻塞在这里，等待客户端的连接
    printf("waiting for client...\n");
    char buf[15];
    buf[0] = '\0';
    int recult_rec = zmq_recv (server_socket, buf, 15, 0);
    assert( recult_rec != -1 );
	printf ("Received Hello string=[%s] length=%d\n",buf,recult_rec);

	zmq_close (server_socket);
	zmq_term (context_ack);
	*/

    /*
     * 第二个参数貌似毫无用处？？
     */
	int client_socket_fd = mSocketFd;
    //return new TcpCommunicator(client_socket_fd,"219.219.216.211");
    return new TcpCommunicator(zeroSocketFd,client_socket_fd,"219.219.216.211");
}

/*
 * 这个函数是客户端的socket代码，包含了客户端socket的联系建立过程
 * 这个函数只会由在前端的TcpCommunicator类会调用，用来与后端建立连接
 */
void TcpCommunicator::Connect() {
	void *context = zmq_ctx_new ();//新建一个zeromq 的环境
	assert (context);
	//void *context_ack = zmq_ctx_new ();//新建一个zeromq 的环境
	//assert (context_ack);

	// Socket to talk to clients
	void *socket_frontend = zmq_socket (context, ZMQ_PAIR);
	//void *socket_frontend = zmq_socket (context, ZMQ_STREAM);
	//void *socket_frontend_ack = zmq_socket (context_ack, ZMQ_PAIR);
	if( NULL == socket_frontend)
	{
		throw "**TcpCommunicator:Can't create zmq_socket.";
	}
	//int result = zmq_connect (socket_frontend, "tcp://219.219.216.211:9988");
	int result = zmq_connect (socket_frontend, zmqHostname.c_str() );
	//int result_ack = zmq_connect (socket_frontend_ack, "tcp://219.219.216.211:8888");
	if( result != 0)
	{
		throw "TcpCommunicator : cannot connect to zmq_socket.";
	}
	printf( "zeromq socket connected.\n");

	//向服务器端发送与一条消息，以确定是否连接成功
	//Sandy 2016.05.12
	/*
	  char buffer[]="hello Server";
	  printf ("Sending request...\n" );
	  int result_send = zmq_send (socket_frontend_ack, buffer, sizeof(buffer)+1, 0);	//sizeof求得的值是不包括的最后的'\0'的，因此要加一
	  assert( result_send != -1);
	  printf("send over\n");
	  zmq_close (socket_frontend_ack);
	  zmq_ctx_destroy (context_ack);
	  */
	//下面这段代码在zeromq通信方式中毫无用处
    int fd = 0;
	size_t fd_len = sizeof(int);
	int rc = zmq_getsockopt( socket_frontend,ZMQ_FD, &fd,&fd_len) ; //fd用来存储socket_frontend的文件描述符(file descriptor)
	assert( rc == 0 );
	cout<<"File descriptor is"<<fd<<endl;
    mSocketFd = fd ;  //Sandy 2016.05.17
    zeroSocketFd = socket_frontend;

    InitializeStream();		//在这里，因为客户端只会调用到Connect()这一个函数，所以，必须在这里初始化流文件

}

/*
 * 这个函数应该用来关闭zeroMQ的socket连接，但是gvirtus单线程运行过程中应该永远都不应该关闭掉连接，所以这个一段dead code,所以就不写函数体了
 */
void TcpCommunicator::Close() {
}
/*
 * 从输入流mpInput中读入size大小的数据，放入到buffer中
 */
#if 0
size_t TcpCommunicator::Read(char* buffer, size_t size) {
	mpInput->read(buffer, size);//read()是流自带函数
	if (mpInput->bad() || mpInput->eof())
		return 0;
    return size;
}
#endif

size_t TcpCommunicator::Read(char* buffer, size_t size) {
	int result = zmq_recv(zeroSocketFd, buffer, size, 0);
    if (result == -1)
        return 0;
    return result;
}
size_t TcpCommunicator::Write(const char* buffer, size_t size) {
	int result = zmq_send(zeroSocketFd, buffer, size, 0);
	if( result == -1 )
		return 0;
    return size;
}
#if 0

size_t TcpCommunicator::Write(const char* buffer, size_t size) {
    mpOutput->write(buffer, size);
    return size;
}

#endif



void TcpCommunicator::Sync() {
    //mpOutput->flush(); //表示将缓冲区内的内容发送出去，修改为zeromq通信方式之后要修改为将之前的帧发送出去 Sandy 2016.06.08
}

void TcpCommunicator::InitializeStream() {
	cout<<"Function InitializeStream called.."<<endl;		//Sandy
#ifdef _WIN32
        FILE *i = _fdopen(mSocketFd, "r");
	FILE *o = _fdopen(mSocketFd, "w");
	mpInputBuf = new filebuf(i);
	mpOutputBuf = new filebuf(o);
#else
	mpInputBuf = new __gnu_cxx::stdio_filebuf<char>(mSocketFd, ios_base::in);		//???????  __gnu_cxx是一个名字空间
	mpOutputBuf = new __gnu_cxx::stdio_filebuf<char>(mSocketFd, ios_base::out);		//?????
	//mpInputBuf = new __gnu_cxx::stdio_filebuf<char>(  ((FILE *)zeroSocketFd ), ios_base::in);		//zeromq
	//mpOutputBuf = new __gnu_cxx::stdio_filebuf<char>( ((FILE *)zeroSocketFd ), ios_base::out);		//zeromq
#endif
	mpInput = new istream(mpInputBuf);		//????
	mpOutput = new ostream(mpOutputBuf);	//?????
	cout<<"Function InitializeStream Over."<<endl;	//Sandy
}

//2016.04.26 Sandy
#if 0
void TcpCommunicator::Serve() {
    struct sockaddr_in socket_addr;


    if ((mSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw "**TcpCommunicator: Can't create socket.";

    memset((char *) &socket_addr, 0, sizeof(struct sockaddr_in));

    socket_addr.sin_family = AF_INET;//设置通信协议为IPv4
    socket_addr.sin_port = htons(mPort);//设置端口号,htons表示把16位值从主机字节序转换成网络字节序
    socket_addr.sin_addr.s_addr = INADDR_ANY;//把IP地址设置为本机IP地址

    /*
     * 设置socket选项，SO_REUSEADDR （BOOL型？）    允许套接口和一个已在使用中的地址捆绑（参见bind()）
     */
    char on = 1;
    setsockopt(mSocketFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));

    /*
     * 绑定
     */
    int result = bind(mSocketFd, (struct sockaddr *) & socket_addr,
            sizeof (struct sockaddr_in));
     if( result != 0)
        throw "TcpCommunicator: Can't bind socket.";

     /*
      * 侦听，Listen函数使socket处于被动的监听模式，并为该socket建立一个输入数据队列，5代表最多有5个等待的申请
      */
    if (listen(mSocketFd, 5) != 0)
        throw "AfUnixCommunicator: Can't listen from socket.";
}
#endif
//2016.04.26 Sandy
#if 0
const Communicator * const TcpCommunicator::Accept() const {
    unsigned client_socket_fd;
    struct sockaddr_in client_socket_addr;
#ifndef _WIN32
    unsigned client_socket_addr_size;
#else
	int client_socket_addr_size;
#endif
    client_socket_addr_size = sizeof (struct sockaddr_in);
    if ((client_socket_fd = accept(mSocketFd,
            (sockaddr *) & client_socket_addr,
            &client_socket_addr_size)) == 0)
        throw "TcpCommunicator: Error while accepting connection.";
    else
    {
    	cout<<"received connect request from:"<<inet_ntoa(client_socket_addr.sin_addr)<<endl;
    }

    /*
     * client_socket_fd是用来处理数据传输的socket句柄
     * client_socket_addr是客户程序的地址信息
     * client_socket_addr.sin_addr是客户程序的IP地址
     * inet_ntoa();//将long类型的网络字节序转换成IP地址字符串
     */
    return new TcpCommunicator(client_socket_fd,
            inet_ntoa(client_socket_addr.sin_addr));
}
#endif
//Sandy 2016.04.26
#if 0
void TcpCommunicator::Connect() {
    struct sockaddr_in remote;

    if ((mSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw "TcpCommunicator: Can't create socket.";

    remote.sin_family = AF_INET;
    remote.sin_port = htons(mPort);
    memcpy(&remote.sin_addr, mInAddr, mInAddrSize);

    if (connect(mSocketFd, (struct sockaddr *) & remote,
            sizeof (struct sockaddr_in)) != 0)
        throw "TcpCommunicator: Can't connect to socket.";
    else
    {
    	cout<<"connected with "<<inet_ntoa(remote.sin_addr)<<endl;
    }
    InitializeStream();		//在这里，因为客户端只会调用到Connect()这一个函数，所以，必须在这里初始化流文件
}
#endif
