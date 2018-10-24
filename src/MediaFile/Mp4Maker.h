﻿/*
 * MIT License
 *
 * Copyright (c) 2016 xiongziliang <771730766@qq.com>
 *
 * This file is part of ZLMediaKit(https://github.com/xiongziliang/ZLMediaKit).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MP4MAKER_H_
#define MP4MAKER_H_

#ifdef ENABLE_MP4V2

#include <mutex>
#include <memory>
#include <mp4v2/mp4v2.h>
#include "Player/PlayerBase.h"
#include "Util/util.h"
#include "Util/logger.h"
#include "Util/TimeTicker.h"
#include "Util/TimeTicker.h"

using namespace std;
using namespace ZL::Util;
using namespace ZL::Player;

namespace ZL {
namespace MediaFile {

class Mp4Info
{
public:
	time_t ui64StartedTime; //GMT标准时间，单位秒
	time_t ui64TimeLen;//录像长度，单位秒
	off_t ui64FileSize;//文件大小，单位BYTE
	string strFilePath;//文件路径
	string strFileName;//文件名称
	string strFolder;//文件夹路径
	string strUrl;//播放路径
	string strAppName;//应用名称
	string strStreamId;//流ID
	string strVhost;//vhost
};
class Mp4Maker {
public:
	typedef std::shared_ptr<Mp4Maker> Ptr;
	Mp4Maker(const string &strPath,
			 const string &strVhost ,
			 const string &strApp,
			 const string &strStreamId,
			 const PlayerBase::Ptr &pPlayer);
	virtual ~Mp4Maker();
	//时间戳：参考频率1000
	void inputH264(void *pData, uint32_t ui32Length, uint32_t ui32TimeStamp, int iType);
	//时间戳：参考频率1000
	void inputAAC(void *pData, uint32_t ui32Length, uint32_t ui32TimeStamp);
private:
	MP4FileHandle _hMp4 = MP4_INVALID_FILE_HANDLE;
	MP4TrackId _hVideo = MP4_INVALID_TRACK_ID;
	MP4TrackId _hAudio = MP4_INVALID_TRACK_ID;
	PlayerBase::Ptr _pPlayer;
	string _strPath;
	string _strFile;
	string _strFileTmp;
	Ticker _ticker;
	SmoothTicker _mediaTicker[2];

	void createFile();
	void closeFile();
	void _inputH264(void *pData, uint32_t ui32Length, uint32_t ui64Duration, int iType);
	void _inputAAC(void *pData, uint32_t ui32Length, uint32_t ui64Duration);

	string _strLastVideo;
	string _strLastAudio;

	uint32_t _ui32LastVideoTime = 0;
	uint32_t _ui32LastAudioTime = 0;
	int _iLastVideoType = 0;

	Mp4Info _info;
};

} /* namespace MediaFile */
} /* namespace ZL */

#endif ///ENABLE_MP4V2

#endif /* MP4MAKER_H_ */
