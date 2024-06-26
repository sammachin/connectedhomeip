/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include "PigweedLogger.h"
#include "pigweed/RpcService.h"
#include <cmsis_os2.h>

namespace chip {
namespace rpc {
class PigweedLoggerMutex : public ::chip::rpc::Mutex
{

public:
    PigweedLoggerMutex() {}
    void Lock() override
    {
        osMutexId_t * sem = PigweedLogger::GetMutex();
        if (sem)
        {
            osMutexAcquire(*sem, osWaitForever);
        }
    }
    void Unlock() override
    {
        osMutexId_t * sem = PigweedLogger::GetMutex();
        if (sem)
        {
            osMutexRelease(*sem);
        }
    }
};

extern PigweedLoggerMutex logger_mutex;

} // namespace rpc
} // namespace chip
