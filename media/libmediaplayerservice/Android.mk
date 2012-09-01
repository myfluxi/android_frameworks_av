LOCAL_PATH:= $(call my-dir)

#
# libmediaplayerservice
#

include $(CLEAR_VARS)

LOCAL_SRC_FILES:=               \
    ActivityManager.cpp         \
    Crypto.cpp                  \
    MediaRecorderClient.cpp     \
    MediaPlayerService.cpp      \
    MetadataRetrieverClient.cpp \
    TestPlayerStub.cpp          \
    MidiMetadataRetriever.cpp   \
    MidiFile.cpp                \
    StagefrightPlayer.cpp       \
    StagefrightRecorder.cpp     \
    AmlPlayerMetadataRetriever.cpp

ifeq ($(BUILD_WITH_AMLOGIC_PLAYER),true)
    LOCAL_SRC_FILES +=AmSuperPlayer.cpp
    LOCAL_SRC_FILES +=AmlogicPlayer.cpp
    LOCAL_SRC_FILES +=AmlogicPlayerRender.cpp
    LOCAL_SRC_FILES +=AmlogicPlayerStreamSource.cpp
    LOCAL_SRC_FILES +=AmlogicPlayerStreamSourceListener.cpp
endif

LOCAL_SHARED_LIBRARIES :=     		\
	libcutils             			\
	libutils              			\
	libbinder             			\
	libvorbisidec         			\
	libsonivox            			\
	libmedia              			\
	libmedia_native       			\
	libcamera_client      			\
	libstagefright        			\
	libstagefright_omx    			\
	libstagefright_foundation       \
	libgui                          \
	libdl                           \
	libaah_rtp

LOCAL_STATIC_LIBRARIES := \
        libstagefright_nuplayer                 \
        libstagefright_rtsp                     \

LOCAL_C_INCLUDES :=                                               \
	$(call include-path-for, graphics corecg)                       \
	$(TOP)/frameworks/av/media/libstagefright/include               \
	$(TOP)/frameworks/av/media/libstagefright/rtsp                  \
	$(TOP)/frameworks/native/include/media/openmax                  \
	$(TOP)/external/tremolo/Tremolo                                 \

ifeq ($(BOARD_USES_QCOM_HARDWARE),true)
    LOCAL_STATIC_LIBRARIES += libmedia_helper
    LOCAL_C_INCLUDES += $(TOP)/frameworks/av/include/media
endif

ifeq ($(BUILD_WITH_AMLOGIC_PLAYER),true)
AMPLAYER_APK_DIR=$(TOP)/device/ainol/elf2/packages/LibPlayer/
LOCAL_C_INCLUDES +=\
        $(AMPLAYER_APK_DIR)/amplayer/player/include     \
        $(AMPLAYER_APK_DIR)/amplayer/control/include    \
        $(AMPLAYER_APK_DIR)/amadec/include      \
        $(AMPLAYER_APK_DIR)/amcodec/include     \
        $(AMPLAYER_APK_DIR)/amavutils/include     \
        $(AMPLAYER_APK_DIR)/amffmpeg/ \
	$(TOP)/device/ainol/elf2/include

LOCAL_SHARED_LIBRARIES += libui
LOCAL_SHARED_LIBRARIES +=libamplayer libamavutils
LOCAL_CFLAGS += -DBUILD_WITH_AMLOGIC_PLAYER=1
endif

LOCAL_MODULE:= libmediaplayerservice

include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))

