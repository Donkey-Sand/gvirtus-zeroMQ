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
 * @file   Process.cpp
 * @author Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>
 * @date   Wed Sep 30 10:45:40 2009
 *
 * @brief
 *
 *
 */

#include "Process.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <dlfcn.h>

using namespace std;

static GetHandler_t LoadModule(const char *name) {
    char path[4096];
    if(*name == '/')
        strcpy(path, name);
    else
        sprintf(path, _PLUGINS_DIR "/lib%s-backend.so", name);//path的值为“_PLUGINS_DIR "/libcudart-backend.so"

    /*
     * dlopen()是一个强大的库函数。该函数将打开一个新库，并把它装入内存。
     * 当库被装入后，可以把 dlopen() 返回的句柄作为给 dlsym() 的第一个参数，以获得符号在库中的地址。
     * 使用这个地址，就可以获得库中特定函数的指针，并且调用装载库中的相应函数。
     */
    void *lib = dlopen(path, RTLD_LAZY);
    if(lib == NULL) {
        cerr << "Error loading " << path << ": " << dlerror() << endl;
        return NULL;
    }

    /*
     * init 将指向函数"HandlerInit()"在内存中的位置，可以 用来引用该函数
     */
    HandlerInit_t init = (HandlerInit_t) ((pointer_t) dlsym(lib, "HandlerInit"));
    if(init == NULL) {
        dlclose(lib);
        cerr << "Error loading " << name << ": HandlerInit function not found."
                << endl;
        return NULL;
    }

    if(init() != 0) {
        dlclose(lib);
        cerr << "Error loading " << name << ": HandlerInit failed."
                << endl;
        return NULL;
    }

    /*
     * dlsym的返回值为void* 指向函数的地址，供调用使用。
     * typedef uint64_t pointer_t;
     * 执行之后sym将指向GetHandler()函数的地址，可以使用sym来调用该函数
     */
    GetHandler_t sym = (GetHandler_t) ((pointer_t) dlsym(lib, "GetHandler"));
    if(sym == NULL) {
        dlclose(lib);
        cerr << "Error loading " << name << ": " << dlerror() << endl;
        return NULL;
    }

    cout << "Loaded module '" << name << "'." << endl;		//这里是执行时候输出到屏幕上的

    return sym;
}
/*
 * 该构造函数在执行前先调用了两个父类的构造构造函数
 */
Process::Process(const Communicator *communicator, vector<string> &plugins)
: Subprocess(), Observable() {
    mpCommunicator = const_cast<Communicator *> (communicator);
    mPlugins = plugins;
}

/*
 * 这是在执行结束之后在屏幕上输出的内容
 */
Process::~Process() {
    cout << "[Process " << GetPid() << "]: Destroyed." << endl;
}

void Process::Setup() {

}
#if 0

static bool getstring(Communicator *c, string & s) {
	cout<<endl;
    s = "";
    char ch = 0;
    /*
     * 这个循环从c->mpInput输入流中一个字符一个字符的读入，遇到结束符'\0'终止
     * 并且将结束之前的内容存放到字符串s中
     */
    while(c->Read(&ch, 1) == 1)
    {
        if(ch == 0) {
            return true;
        }
        s += ch;
        printf( "\t%d\t",ch );
    }
    return false;
}
#endif
/*
 * socket是以字节流的方式来传输数据的，zeromq是是帧为单位进行传输的，所以重写这个函数，用来处理zeromq的连接方式
 */
# define LEN 100
static bool getstring(Communicator *c, string & s) {
    s = "";
    char ch[LEN] = {0};
    /*
     * 这个循环从c->mpInput输入流中一个字符一个字符的读入，遇到结束符'\0'终止
     * 并且将结束之前的内容存放到字符串s中
     */
    int rec = c->Read(ch, LEN);
#ifdef ZEROMQ_REP_REQ
    c->Write("ACK",3);
#endif

    if(rec != 0)
    {
    	ch[rec] = '\0';
        s += ch;
        printf( "received:%s\n",ch );
        return true;
    }
    return false;
}
/*
 * 这是主处理申请的过程
 */
void Process::Execute(void * arg) {
    cout << "[Process " << GetPid() << "]: Started." << endl;

    /*
     * mPlugins内容应该只有一个，值为"cudart"
     * GetHandler_t是一个指向函数的指针，具体见定义
     */
    GetHandler_t h;
    for(vector<string>::iterator i = mPlugins.begin(); i != mPlugins.end();
            i++) {
        if((h = LoadModule((*i).c_str())) != NULL)//h是指向GetHandler()函数的地址的指针
            mHandlers.push_back(h());
    }
// -----2016-02-29-------

    string routine;
    Buffer * input_buffer = new Buffer();
    /*
     * 这个循环是不断的从mpCommunicator（一个TcpCommunicator类）的mpInput输入流中每次读入一个字符串，直到读到文件结束符EOF为止
     * 这个循环就是整个的处理总过程
     */
    int loop_count = 0; //Sandy 2016.05.17
    while (getstring(mpCommunicator, routine))//mpCommunicator此时的值应该为client，即包含客户信息的TcpCommunicator
    {
    	cout<<"Process loop :"<< loop_count++ <<endl; //Sandy 2016.05.17
    	cout<<"received request:"<<routine<<"."<<endl;
        input_buffer->Reset(mpCommunicator);	//mark 2 : Sandy
        cout<<"backend input_buffer Reset over"<<endl;
        Handler *h = NULL;
        for(vector<Handler *>::iterator i = mHandlers.begin();
                i != mHandlers.end(); i++) {
            if((*i)->CanExecute(routine)) {
                h = *i;		//h指向的应该是CudaRtHandler类型
                break;
            }
        }
        Result * result;	//这个是得到的执行结果，也是用来返回给前端用的
        if(h == NULL)
        {
            cout << "[Process " << GetPid() << "]: Requested unknown routine "
                    << routine << "." << endl;
            result = new Result(-1, new Buffer());//初始化mExitCode=-1，表示执行失败，前端会收到这个mExitCode的值
        } else
            result = h->Execute(routine, input_buffer);  //错误就在这里 2016.06.08

        result->Dump(mpCommunicator);	//mark 3
        cout<<"result Dump to frontend"<<endl;
        if (result->GetExitCode() != 0 && routine.compare("cudaLaunch"))
        {
            cout << "[Process " << GetPid() << "]: Requested '" << routine
                    << "' routine." << endl;
            cout << "[Process " << GetPid() << "]: Exit Code '"
                    << result->GetExitCode() << "'." << endl;
        }
        delete result;
    }
    delete input_buffer;
    Notify("process-ended");
    delete this;
}

