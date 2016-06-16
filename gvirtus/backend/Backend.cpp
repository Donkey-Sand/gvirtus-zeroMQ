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

#include <vector>
#include <cstring>
#include <cstdio>

/**
 * @file   Backend.cpp
 * @author Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>
 * @date   Wed Sep 30 12:29:26 2009
 *
 * @brief
 *
 *
 */

#include "Backend.h"

#include <iostream>

#include "Process.h"
#include <dlfcn.h>
#include <string>
#include <cstring>

using namespace std;

Backend::Backend(vector<string> &plugins) {
    mPlugins = plugins;
}

void Backend::Start(Communicator * communicator) {
	/*
	 * 设置一系列参数，并执行socket的从socket()到listen()函数部分，等待前段的申请
	 */
    communicator->Serve();
    while (true) {
    	/*
    	 * Accept()的返回值是一个包含了客户地址信息的TcpCommunicator对象
    	 * const_cast为强制类型转换，*client指向Accept()返回的TcpCommunicator对象,
    	 * cilent很重要很重要，它应该是通信功能与处理功能的分割部分
    	 */
        Communicator *client =
                const_cast<Communicator *> (communicator->Accept());
        /*
         * 此时mPlugins数据成员的值为"cudart"
         * client->mSocketFd 是用来向客户socket线程传输数据用的句柄
         */
        Process *process = new Process(client, mPlugins);
        process->Start(NULL);//这是处理过程，对前端的请求都在这个过程中处理
    }
}

void Backend::EventOccurred(std::string& event, void* object) {
    std::cout << "EventOccurred: " << event << std::endl;
}
