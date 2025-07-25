//
// Created by RGAA on 23/04/2025.
//

#include "gr_account_manager.h"
#include "gr_settings.h"
#include "tc_common_new/log.h"
#include "gr_workspace.h"

namespace tc
{

    GrAccountManager::GrAccountManager(const std::shared_ptr<GrContext>& ctx) {
        context_ = ctx;
        settings_ = GrSettings::Instance();
    }

    Result<bool, GrAccountError> GrAccountManager::IsDeviceInfoOk() {
        auto device_id = settings_->GetDeviceId();
        auto device_random_pwd = settings_->GetDeviceRandomPwd();
        auto device_safety_pwd = settings_->GetDeviceSecurityPwd();

        if (device_id.empty() || device_random_pwd.empty()) {
            LOGE("Check device info error, device id is empty.");
            return TRError(GrAccountError::kGrAccountDeviceInfoEmpty);
        }

        return true;
    }

}