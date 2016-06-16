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
 * @file   Frontend.cpp
 * @author Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>
 * @date   Wed Sep 30 12:57:11 2009
 *
 * @brief
 *
 *
 */

#include "Frontend.h"

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "ConfigFile.h"

using namespace std;

static Frontend msFrontend;
map<pthread_t, Frontend*> *Frontend::mpFrontends = NULL;
static bool initialized = false;

/**
 *
 */
void Frontend::Init(Communicator *c) {
#if 1
    const char *config_file;
#ifdef _CONFIG_FILE
    if((config_file = getenv("CONFIG_FILE")) == NULL)//getenv函数的功能是查找环境变量的内容
        config_file = _CONFIG_FILE;
#else
	config_file = "gvirtus.properties";
#endif
    ConfigFile *cf = new ConfigFile(config_file);
    string communicator;
#ifndef _WIN32
    char *tmp;
	if((tmp = getenv("COMMUNICATOR")) != NULL)
        communicator = string(tmp);
    else
#endif
    communicator = cf->Get("communicator");
    mpCommunicator = Communicator::Get(communicator);
#else
    mpCommunicator = c;
#endif

    mpCommunicator->Connect();//这里包括了cocket中的connect（）函数
    mpInputBuffer = new Buffer();
    mpOutputBuffer = new Buffer();
    mpLaunchBuffer = new Buffer();
    mExitCode = -1;
    mpInitialized = true;
}

Frontend::~Frontend() {
//    if (mpFrontends != NULL) {
//        map<pthread_t, Frontend*>::iterator it;
//        for(it = mpFrontends->begin(); it != mpFrontends->end(); it++) {
//            delete it->second;
//        }
//    }
//    else {
//        mpCommunicator->Close();
//        delete mpCommunicator;
//    }
}

     /**
     * Retrieves the single instance of the Frontend class.
     *
     * @param register_var
     *
     * @return The instance of the Frontend class.
     */
Frontend * Frontend::GetFrontend(Communicator *c) {
    if (mpFrontends == NULL)
        mpFrontends = new map<pthread_t, Frontend*>();
    
    /*
     *  syscall() 执行一个系统调用，根据指定的参数number和所有系统调用的汇编语言接口来确定调用哪个系统调用。
       系统调用所使用的符号常量可以在头文件<sys/syscll.h>里面找到。
       根据tid号来决定使用哪一个Frontend对象
     */
    pid_t tid = syscall(SYS_gettid);
    if (mpFrontends->find(tid) != mpFrontends->end())
           return mpFrontends->find(tid)->second;
    
    else {
        Frontend* f = new Frontend();
        if (!f->initialized()) {
            try {
                f->Init(c);
                mpFrontends->insert(make_pair(tid, f));
            } catch (const char *e) {
                cerr << "Error: cannot create Frontend ('" << e << "')" << endl;
            }
        }
        return f;
    }    
}

void Frontend::Execute(const char* routine, const Buffer* input_buffer) {
    if (input_buffer == NULL)
        input_buffer = mpInputBuffer;

    /* sending job */
    mpCommunicator->Write(routine, strlen(routine) + 1);	//mark 1 :routine是cuda的API名称

#ifdef ZEROMQ_REP_REQ
    char tmp[10];
    mpCommunicator->Read(tmp, 10);
    tmp[3] = '\0';
    cout<<"read ACK:"<<tmp<<endl;
#endif
    cout<<"routine send over"<<endl;
    input_buffer->Dump(mpCommunicator);		// mark 2
    cout<<"frontend input_buffer Dump over"<<endl;
    mpCommunicator->Sync();

    /* receiving output */
    //std::istream &in = mpCommunicator->GetInputStream();

    mpOutputBuffer->Reset();

    //Read阻塞在这里，等待后端执行完routine函数之后写回来一个mExitCode的值（Result->mExitCode）
    cout<<"frontend waiting for mExitCode ... "<<endl;
    mpCommunicator->Read((char *) & mExitCode, sizeof (int));
    cout<<" mExitCode get "<<endl;
#ifdef ZEROMQ_REP_REQ
    mpCommunicator->Write("ACK",3);
#endif
    size_t out_buffer_size;
    //Read一个size_t类型的数据，其值为零表明后端执行错误，否则其长度表示回传的执行结果
    cout<<"frontend waiting for execute recult ... "<<endl;
    mpCommunicator->Read((char *) & out_buffer_size, sizeof (size_t));
    cout<<" execute recult get "<<endl;
#ifdef ZEROMQ_REP_REQ
    mpCommunicator->Write("ACK",3);
#endif
    if (out_buffer_size > 0)
        mpOutputBuffer->Read<char>(mpCommunicator, out_buffer_size); 	//将会通过mpCommunictor->Read out_buffer_size大小的数据，存放在mpOutputBuffer中
}

void Frontend::Prepare() {
    mpInputBuffer->Reset();//主要是执行置零的工作
}
