/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_SERVERS_CAMERA_CAMERAMODULE_H
#define ANDROID_SERVERS_CAMERA_CAMERAMODULE_H

#include <hardware/camera.h>
#include <camera/CameraMetadata.h>
#include <utils/Mutex.h>

/* This needs to be increased if we can have more cameras */
#define MAX_CAMERAS_PER_MODULE 2


namespace android {
/**
 * A wrapper class for HAL camera module.
 *
 * This class wraps camera_module_t returned from HAL to provide a wrapped
 * get_camera_info implementation which CameraService generates some
 * camera characteristics keys defined in newer HAL version on an older HAL.
 */
class CameraModule {
public:
    CameraModule(camera_module_t *module);

    const hw_module_t* getRawModule();
    int getCameraInfo(int cameraId, struct camera_info *info);
    int getNumberOfCameras(void);
    int open(const char* id, struct hw_device_t** device);
    int openLegacy(const char* id, uint32_t halVersion, struct hw_device_t** device);
    int setCallbacks(const camera_module_callbacks_t *callbacks);
    bool isVendorTagDefined();
    void getVendorTagOps(vendor_tag_ops_t* ops);
    int setTorchMode(const char* camera_id, bool enable);

private:
    // Derive camera characteristics keys defined after HAL device version
    static void deriveCameraCharacteristicsKeys(uint32_t deviceVersion, CameraMetadata &chars);
    status_t filterOpenErrorCode(status_t err);

    camera_module_t *mModule;
    CameraMetadata mCameraCharacteristics[MAX_CAMERAS_PER_MODULE];
    camera_info mCameraInfo[MAX_CAMERAS_PER_MODULE];
    bool mCameraInfoCached[MAX_CAMERAS_PER_MODULE];
    Mutex mCameraInfoLock;
};

} // namespace android

#endif

