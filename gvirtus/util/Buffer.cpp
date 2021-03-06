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
 * @file   Buffer.cpp
 * @author Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>
 * @date   Sun Oct 18 13:16:46 2009
 *
 * @brief
 *
 *
 */

#include "Buffer.h"

using namespace std;

Buffer::Buffer(size_t initial_size, size_t block_size) {
    mSize = initial_size;
    mBlockSize = block_size;
    mLength = 0;
    mOffset = 0;
    mpBuffer = NULL;
    mOwnBuffer = true;
    if (mSize == 0)
        mSize = 0;
    if ((mSize = (mSize / mBlockSize) * mBlockSize) == 0)
        mSize = mBlockSize;
    if ((mpBuffer = (char *) malloc(mSize)) == NULL)
        throw "Can't allocate memory.";
    mBackOffset = mLength;
}

Buffer::Buffer(const Buffer& orig) {
    mBlockSize = orig.mBlockSize;
    mLength = orig.mLength;
    mSize = orig.mLength;
    mOffset = orig.mOffset;
    mLength = orig.mLength;
    mOwnBuffer = true;
    if ((mpBuffer = (char *) malloc(mSize)) == NULL)
        throw "Can't allocate memory.";
    memmove(mpBuffer, orig.mpBuffer, mLength);
    mBackOffset = mLength;
}

Buffer::Buffer(istream & in) {
    in.read((char *) & mSize, sizeof (size_t));
    mBlockSize = BLOCK_SIZE;
    mLength = mSize;
    mOffset = 0;
    mOwnBuffer = true;
    if ((mpBuffer = (char *) malloc(mSize)) == NULL)
        throw "Can't allocate memory.";
    in.read(mpBuffer, mSize);
    mBackOffset = mLength;
}

Buffer::Buffer(char* buffer, size_t buffer_size, size_t block_size) {
    mSize = buffer_size;
    mBlockSize = block_size;
    mLength = mSize;
    mOffset = 0;
    mpBuffer = buffer;
    mOwnBuffer = false;
    mBackOffset = mLength;
}

Buffer::~Buffer() {
    if(mOwnBuffer)
        free(mpBuffer);
}
//这个重载被前端调用
void Buffer::Reset() {
    mLength = 0;
    mOffset = 0;
    mBackOffset = 0;
}

/*
 * 这个函数的功能：如果内存不够就重新分配？？？？？
 * 这个重载被后端调用
 */
void Buffer::Reset(Communicator *c)
{
    int recult = ( c->Read((char *) & mLength, sizeof (size_t)) );
#ifdef ZEROMQ_REP_REQ
    c->Write("ACK",3);
#endif
    if( 0 == recult)
    {
    	cout<<"read mLength error!"<<endl;
    }
    cout<<"read mLength="<<mLength<<endl;	//Sandy
    mOffset = 0;
    mBackOffset = mLength;
    if (mLength >= mSize) {
        mSize = (mLength / mBlockSize + 1) * mBlockSize;
        if ((mpBuffer = (char *) realloc(mpBuffer, mSize)) == NULL)//realloc重新分配内存
            throw "Can't reallocate memory.";
    }
    int rec = ( c->Read(mpBuffer, mLength) );

    if( 0 == rec )
    {
    	cout<<"read mpBuffer error ! "<<endl;
    }
    else
    {
    	cout<<"read data to input_buffer:"<<mpBuffer<<endl;//Sandy
    }

}

const char * const Buffer::GetBuffer() const {
    return mpBuffer;
}

size_t Buffer::GetBufferSize() const {
    return mLength;
}

void Buffer::Dump(Communicator * c) const {
    c->Write((char *) & mLength, sizeof (size_t));
#ifdef ZEROMQ_REP_REQ
    char tmp[10];
    c->Read(tmp, 10);
    tmp[3] = '\0';
    cout<<"read ACK:"<<tmp<<endl;
#endif
    c->Write(mpBuffer, mLength);

    c->Sync();//这个函数保证上面两个写在缓冲区的数据立刻被发送出去
}

