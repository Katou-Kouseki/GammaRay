//
// Created by RGAA on 2023-12-17.
//

#ifndef TC_APPLICATION_SETTINGS_H
#define TC_APPLICATION_SETTINGS_H

#include <string>
#include <map>

#include "tc_encoder_new/video_encoder_factory.h"
#include "tc_steam_manager_new/steam_entities.h"

namespace tc
{

    // description
    struct Description {
        std::string author_;
        std::string version_;
    };

    // encoder
    struct Encoder {

        enum EncoderFormat {
            kH264,
            kHEVC,
        };

        enum EncodeResolutionType {
            kOrigin,
            kSpecify,
        };

        ECreateEncoderPolicy encoder_select_type_;
        ECreateEncoderName encoder_name_;
        EncoderFormat encoder_format_;
        int bitrate_;
        EncodeResolutionType encode_res_type_;
        int encode_width_;
        int encode_height_;
    };

    // capture
    struct Capture {
        enum CaptureAudioType {
            kAudioHook,
            kAudioGlobal,
        };

        enum CaptureVideoType {
            kVideoHook,
            kCaptureScreen,
        };

    public:
        bool IsVideoHook() {
            return capture_video_type_ == CaptureVideoType::kVideoHook;
        }

        bool IsAudioHook() {
            return capture_audio_type_ == CaptureAudioType::kAudioHook;
        }

    public:
        bool enable_audio_;
        CaptureAudioType capture_audio_type_;
        bool enable_video_;
        CaptureVideoType capture_video_type_;
        bool send_video_frame_by_shm_;
    };

    // Transmission
    struct Transmission {
        enum NetworkType {
            kWebsocket,
            kQUIC,
            kWebRtc,
        };

        NetworkType network_type_;
        int listening_port_ = 8888;
    };

    // Application
    struct TargetApplication {

        enum InjectMethod {
            kEasyHook,
            kOBS,
        };

        enum EventReplayMode {
            kGlobal,
            kHookInner,
        };

        [[nodiscard]] bool IsGlobalReplayMode() const {
            return event_replay_mode_ == EventReplayMode::kGlobal;
        }

    public:
        std::string game_path_{};
        std::string game_arguments_{};
        bool hide_after_started_{};
        bool force_fullscreen_{};
        InjectMethod inject_method_{kEasyHook};
        SteamApp steam_app_;
        bool debug_enabled_{false};
        EventReplayMode event_replay_mode_;

    public:
        [[nodiscard]] bool IsSteamUrl() const {
            return game_path_.find("steam://") != std::string::npos;
        }
    };

    class Settings {
    public:

        static Settings* Instance() {
            static Settings inst;
            return &inst;
        }

        bool LoadSettings(const std::string& path);
        std::string Dump();
        uint32_t GetShmBufferSize() const;

    public:

        Description desc_;
        Encoder encoder_{};
        Capture capture_{};
        Transmission transmission_{};
        TargetApplication app_;

    };

}

#endif //TC_APPLICATION_SETTINGS_H
