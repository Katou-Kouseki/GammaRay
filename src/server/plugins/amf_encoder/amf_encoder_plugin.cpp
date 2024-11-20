//
// Created RGAA on 15/11/2024.
//

#include "amf_encoder_plugin.h"
#include "plugin_interface/gr_plugin_events.h"
#include "video_encoder_vce.h"
#include "amf_encoder_defs.h"

namespace tc
{

    std::string AmfEncoderPlugin::GetPluginName() {
        return kAmfPluginName;
    }

    std::string AmfEncoderPlugin::GetVersionName() {
        return "1.1.0";
    }

    uint32_t AmfEncoderPlugin::GetVersionCode() {
        return 110;
    }

    bool AmfEncoderPlugin::CanEncodeTexture() {
        return true;
    }

    void AmfEncoderPlugin::On1Second() {

    }

    bool AmfEncoderPlugin::OnCreate(const tc::GrPluginParam &param) {
        return true;
    }

    bool AmfEncoderPlugin::OnDestroy() {
        return true;
    }

    void AmfEncoderPlugin::InsertIdr() {
        GrEncoderPlugin::InsertIdr();
    }

    bool AmfEncoderPlugin::IsWorking() {
        return init_success_ && plugin_enabled_ && video_encoder_;
    }

    bool AmfEncoderPlugin::Init(const EncoderConfig& config) {
        GrEncoderPlugin::Init(config);
        video_encoder_ = std::make_shared<VideoEncoderVCE>(config.adapter_uid_);
        init_success_ = video_encoder_->Initialize(config);
        return init_success_;
    }

    void AmfEncoderPlugin::Encode(ID3D11Texture2D* tex2d, uint64_t frame_index) {
        if (IsWorking()) {
            video_encoder_->Encode(tex2d, frame_index);
        }
    }

    void AmfEncoderPlugin::Encode(const std::shared_ptr<Image>& i420_image, uint64_t frame_index) {

    }

    void AmfEncoderPlugin::Exit() {

    }

}