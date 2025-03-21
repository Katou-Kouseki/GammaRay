#include <iostream>

#include "app.h"
#include "settings/settings.h"
#include "context.h"
#include "tc_common_new/log.h"
#include "tc_common_new/dump_helper.h"
#include "tc_common_new/base64.h"
#include "tc_common_new/folder_util.h"
#include "gflags/gflags.h"

#include <QLockFile>
#include <QMessageBox>

using namespace tc;

DEFINE_int32(steam_app_id, 0, "steam app id");
DEFINE_bool(logfile, true, "log to file");
DEFINE_bool(isolate, false, "only use settings.toml, args below aren't be used");

// encoder
DEFINE_string(encoder_select_type, "auto", "auto/specify");
DEFINE_string(encoder_name, "nvenc", "nvenc/amf/ffmpeg");
DEFINE_string(encoder_format, "h264", "h264/h265");
DEFINE_int32(encoder_bitrate, 20, "encoder bitrate");
DEFINE_string(encoder_resolution_type, "origin", "origin/specify");
DEFINE_int32(encoder_width, 1280, "");
DEFINE_int32(encoder_height, 720, "");

// capture
DEFINE_bool(capture_audio, true, "");
DEFINE_string(capture_audio_type, "global", "hook/global");
DEFINE_bool(capture_video, true, "");
DEFINE_string(capture_video_type, "hook", "hook/global");

// network
DEFINE_bool(webrtc_enabled, true, "");
DEFINE_bool(websocket_enabled, true, "");
DEFINE_int32(network_listen_port, 20371, "");
DEFINE_bool(udp_kcp_enabled, true, "");
DEFINE_int32(udp_listen_port, 20381, "");

DEFINE_string(sig_server_address, "", "");
DEFINE_string(sig_server_port, "", "");
DEFINE_string(coturn_server_address, "", "");
DEFINE_string(coturn_server_port, "", "");

DEFINE_string(capture_audio_device, "", "capture audio device");

// application
DEFINE_string(app_game_path, "", "");
DEFINE_string(app_game_args, "", "");

DEFINE_bool(debug_block, false, "block the render process");
DEFINE_bool(mock_video, false, "use mocking video plugin");

DEFINE_string(device_id, "", "device id");
DEFINE_string(device_random_pwd, "", "device random pwd");

DEFINE_string(relay_server_host, "", "relay host");
DEFINE_string(relay_server_port, "", "relay port");

DEFINE_int32(panel_server_port, 0, "");

void UpdateSettings(Settings* settings) {
    if (FLAGS_steam_app_id > 0) {
        settings->app_.steam_app_.app_id_ = FLAGS_steam_app_id;
        settings->app_.steam_app_.steam_url_ = std::format("steam://rungameid/{}", FLAGS_steam_app_id);
    }

    // encoder
    if (FLAGS_encoder_select_type == "auto") {
        settings->encoder_.encoder_select_type_ = ECreateEncoderPolicy::kAuto;
    } else {
        settings->encoder_.encoder_select_type_ = ECreateEncoderPolicy::kSpecify;
    }

    if (FLAGS_encoder_name == "nvenc") {
        settings->encoder_.encoder_name_ = ECreateEncoderName::kNVENC;
    } else if (FLAGS_encoder_name == "amf") {
        settings->encoder_.encoder_name_ = ECreateEncoderName::kAMF;
    } else {
        settings->encoder_.encoder_name_ = ECreateEncoderName::kFFmpeg;
    }

    if (FLAGS_encoder_format == "h264") {
        settings->encoder_.encoder_format_ = Encoder::EncoderFormat::kH264;
    } else {
        settings->encoder_.encoder_format_ = Encoder::EncoderFormat::kHEVC;
    }

    settings->encoder_.bitrate_ = FLAGS_encoder_bitrate;

    if (FLAGS_encoder_resolution_type == "origin") {
        settings->encoder_.encode_res_type_ = Encoder::EncodeResolutionType::kOrigin;
    } else {
        settings->encoder_.encode_res_type_ = Encoder::EncodeResolutionType::kSpecify;
    }
    settings->encoder_.encode_width_ = FLAGS_encoder_width;
    settings->encoder_.encode_height_ = FLAGS_encoder_height;

    // capture
    settings->capture_.enable_audio_ = FLAGS_capture_audio;
    if (FLAGS_capture_audio_type == "global") {
        settings->capture_.capture_audio_type_ = Capture::CaptureAudioType::kAudioGlobal;
    } else {
        settings->capture_.capture_audio_type_ = Capture::CaptureAudioType::kAudioHook;
    }

    settings->capture_.enable_video_ = FLAGS_capture_video;
    if (FLAGS_capture_video_type == "global") {
        settings->capture_.capture_video_type_ = Capture::CaptureVideoType::kCaptureScreen;
    } else {
        settings->capture_.capture_video_type_ = Capture::CaptureVideoType::kVideoHook;
    }
    settings->capture_.capture_audio_device_ = Base64::Base64Decode(FLAGS_capture_audio_device);

    settings->transmission_.listening_port_ = FLAGS_network_listen_port;
    settings->transmission_.udp_enabled_ = FLAGS_udp_kcp_enabled;
    settings->transmission_.udp_listen_port_ = FLAGS_udp_listen_port;
    settings->transmission_.websocket_enabled_ = FLAGS_websocket_enabled;
    settings->transmission_.webrtc_enabled_ = FLAGS_webrtc_enabled;

    // app
    if (!FLAGS_app_game_path.empty()) {
        settings->app_.game_path_ = FLAGS_app_game_path;
    }
    if (!FLAGS_app_game_args.empty()) {
        settings->app_.game_arguments_ = FLAGS_app_game_args;
    }

    settings->block_debug_ = FLAGS_debug_block;
    settings->capture_.mock_video_ = FLAGS_mock_video;

    settings->device_id_ = FLAGS_device_id;
    settings->device_random_pwd_ = FLAGS_device_random_pwd;

    settings->relay_host_ = FLAGS_relay_server_host;
    settings->relay_port_ = FLAGS_relay_server_port;

    settings->panel_server_port_ = FLAGS_panel_server_port;

}

void PrintInputArgs() {
    LOGI("--------------In args begin--------------");
    LOGI("steam_app_id: {}", FLAGS_steam_app_id);
    LOGI("logfile: {}", FLAGS_logfile);
    LOGI("encoder_select_type: {}", FLAGS_encoder_select_type);
    LOGI("encoder_name: {}", FLAGS_encoder_name);
    LOGI("encoder_format: {}", FLAGS_encoder_format);
    LOGI("encoder_bitrate: {}", FLAGS_encoder_bitrate);
    LOGI("encoder_resolution_type: {}", FLAGS_encoder_resolution_type);
    LOGI("encoder_width: {}", FLAGS_encoder_width);
    LOGI("encoder_height: {}", FLAGS_encoder_height);
    LOGI("capture_audio: {}", FLAGS_capture_audio);
    LOGI("capture_audio_type: {}", FLAGS_capture_audio_type);
    LOGI("capture_video: {}", FLAGS_capture_video);
    LOGI("capture_video_type: {}", FLAGS_capture_video_type);
    LOGI("websocket enabled: {}", FLAGS_websocket_enabled);
    LOGI("webrtc enabled: {}", FLAGS_webrtc_enabled);
    LOGI("network_listen_port: {}", FLAGS_network_listen_port);
    LOGI("udp_listen_port: {}", FLAGS_udp_listen_port);
    LOGI("capture audio device: {}", Base64::Base64Decode(FLAGS_capture_audio_device));
    LOGI("app_game_path: {}", FLAGS_app_game_path);
    LOGI("app_game_args: {}", FLAGS_app_game_args);
    LOGI("block debug: {}", FLAGS_debug_block);
    LOGI("mock video: {}", FLAGS_mock_video);
    LOGI("sig server address: {}", FLAGS_sig_server_address);
    LOGI("sig server port: {}", FLAGS_sig_server_port);
    LOGI("coturn server address: {}", FLAGS_coturn_server_address);
    LOGI("coturn server port: {}", FLAGS_coturn_server_port);
    LOGI("device id: {}", FLAGS_device_id);
    LOGI("device random pwd: {}", FLAGS_device_random_pwd);
    LOGI("panel server port: {}", FLAGS_panel_server_port);
    LOGI("udp listen port: {}", FLAGS_udp_listen_port);
    LOGI("relay host: {}", FLAGS_relay_server_host);
    LOGI("relay port: {}", FLAGS_relay_server_port);
    LOGI("--------------In args end----------------");
}

std::shared_ptr<QLockFile> g_instance_lock = nullptr;
bool CanWeRun(const QString& lock_path) {
    g_instance_lock = std::make_shared<QLockFile>(lock_path);
    bool is_locked = g_instance_lock->isLocked();
//    if (!is_locked) {
//        return true;
//    }
    (void)is_locked;
    if (!g_instance_lock->tryLock(1000)) {
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // dump
    CaptureDump();

    // 1. load from config.toml
    auto settings = Settings::Instance();
    settings->LoadSettings("settings.toml");
    if (!FLAGS_isolate) {
        UpdateSettings(settings);
    }

    // Log
    std::cout << "logfile: " << FLAGS_logfile << std::endl;
    auto log_file_path = std::format("{}/gr_logs/gammaray_render_{}.log",
         QString::fromStdWString(FolderUtil::GetCurrentFolderPath()).toStdString(), settings->transmission_.listening_port_);
    Logger::InitLog(log_file_path, FLAGS_logfile);

    PrintInputArgs();

    auto settings_str = settings->Dump();
    LOGI("\n" + settings_str);

    //settings->block_debug_ = true;
    if (settings->block_debug_) {
        MessageBoxA(0, 0, 0, 0);
    }

    auto lock_name = std::format("gammaray_render_lock_{}", settings->transmission_.listening_port_);
    QString lock_path = QDir::temp().absoluteFilePath(lock_name.c_str());
    auto can_we_run = CanWeRun(lock_path);
    if (!can_we_run) {
        LOGE("We can't run because of already running instance!");
        QString reason = "Already locked at: " + lock_path;
        QMessageBox::critical(nullptr, "Start render failed!", reason);
        return -1;
    }

    // start application
    tc::AppParams params = {};
    auto app = tc::Application::Make(params);
    app->Init(argc, argv);
    app->CaptureControlC();
    return app->Run();
}
