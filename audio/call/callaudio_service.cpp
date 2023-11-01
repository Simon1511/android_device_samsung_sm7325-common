/*
 * Copyright (C) 2023 The LineageOS Project
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

#include <android-base/properties.h>
#include <android-base/logging.h>
#include <binder/ProcessState.h>
#include <android/hardware/audio/7.0/IDevicesFactory.h>

using android::IBinder;
using android::base::GetProperty;
using android::base::SetProperty;
using android::sp;
using ::android::hardware::hidl_string;

int main() {
    android::ProcessState::self()->setThreadPoolMaxThreadCount(1);
    android::ProcessState::self()->startThreadPool();
    sp<::android::hardware::audio::V7_0::IDevice> audioDevice;

    LOG(ERROR) << "Passing parameter";

    if (!audioDevice) {
        ::android::hardware::audio::V7_0::IDevicesFactory::getService()->openDevice(
            "primary", [&](::android::hardware::audio::V7_0::Result, const sp<::android::hardware::audio::V7_0::IDevice>& result) {
                    audioDevice = result;
        });
    }

    if (audioDevice != nullptr) {
        std::string value = "0x02";//GetProperty("vendor.calls.slotid", "-1");
        audioDevice->setParameters({}, {{"g_call_sim_slot", value}});
        LOG(ERROR) << "Parameter passed";
    }

    audioDevice->close();

    SetProperty("vendor.calls.finished", "1");

    return 0;
}
