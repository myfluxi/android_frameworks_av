/*******************************************************************************
--                                                                            --
--                    CedarX Multimedia Framework                             --
--                                                                            --
--          the Multimedia Framework for Linux/Android System                 --
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                         Softwinner Products.                               --
--                                                                            --
--                   (C) COPYRIGHT 2011 SOFTWINNER PRODUCTS                   --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _CDX_RECORDER_H_
#define _CDX_RECORDER_H_

enum cdx_video_source {
    CDX_VIDEO_SOURCE_DEFAULT,
    CDX_VIDEO_SOURCE_CAMERA,
    CDX_VIDEO_SOURCE_GRALLOC_BUFFER,
    CDX_VIDEO_SOURCE_PUSH_BUFFER,
};

#ifndef __OS_LINUX
int CDXRecorder_Create(void **inst);
void CDXRecorder_Destroy(void *recorder);

typedef struct CDXRecorderBsInfo
{
	int  bs_count;
	int  total_size;
	char *bs_data[4];
	int  bs_size[4];
}CDXRecorderBsInfo;

typedef enum RawPacketType
{
	RawPacketTypeVideo = 0,
	RawPacketTypeAudio,

	RawPacketTypeVideoExtra = 128,
	RawPacketTypeAudioExtra
}RawPacketType;

typedef struct RawPacketHeader
{
	int  stream_type;
	int  size;
	long long pts;
}__attribute__((packed)) RawPacketHeader;

typedef struct CdxRecorderWriterCallbackInfo {
	void *parent;
	int (*writer)(void *parent, CDXRecorderBsInfo *bs_info);
}CdxRecorderWriterCallbackInfo;

typedef struct CDXRecorder
{
	void *context;
	int  (*control)(void *Recorder, int cmd, unsigned int para0, unsigned int para1);
}CDXRecorder;

#else
int CDXRecorder_Init();
int CDXRecorder_Exit();
int CDXRecorder_Control(int cmd, unsigned int para0, unsigned int para1);

#endif

#endif	// _CDX_RECORDER_H_

#ifdef __cplusplus
}
#endif /* __cplusplus */

