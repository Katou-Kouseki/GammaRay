//
// Created by RGAA on 15/11/2024.
//

#ifndef GAMMARAY_MEDIA_RECORDER_PLUGIN_H
#define GAMMARAY_MEDIA_RECORDER_PLUGIN_H

#include "plugin_interface/gr_encoder_plugin.h"

namespace tc
{

    class AmfEncoderPlugin : public GrEncoderPlugin {
    public:

        std::string GetPluginName() override;
        std::string GetVersionName() override;
        uint32_t GetVersionCode() override;

        bool CanEncodeTexture() override;
        void On1Second() override;
        bool OnCreate(const tc::GrPluginParam &param) override;
        bool OnDestroy() override;
        void InsertIdr() override;
        bool IsWorking() override;

        bool Init(const EncoderConfig& config) override;
        void Encode(ID3D11Texture2D* tex2d, uint64_t frame_index) override;
        void Encode(const std::shared_ptr<Image>& i420_image, uint64_t frame_index) override;
        void Exit() override;

    };

}

extern "C" __declspec(dllexport) void* GetInstance();

void* GetInstance() {
    static tc::AmfEncoderPlugin plugin;
    return (void*)&plugin;
}


#endif //GAMMARAY_UDP_PLUGIN_H
