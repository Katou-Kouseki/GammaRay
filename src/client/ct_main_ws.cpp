//
// Created by RGAA on 2023-12-26.
//

#include <QApplication>
#include <QSurfaceFormat>
#include <QFontDatabase>
#include <QMessageBox>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "thunder_sdk.h"
#include "client/ct_client_context.h"
#include "client/ct_workspace.h"
#include "client/ct_application.h"
#include "tc_common_new/md5.h"
#include "tc_common_new/log.h"
#include "client/ct_settings.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <QDir>
#include "client/ui/sized_msg_box.h"

using namespace tc;

std::string g_host_;
int g_port_ = 0;

void ParseCommandLine(QApplication& app) {
    QCommandLineParser parser;
    parser.setApplicationDescription("GammaRay Client");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption opt_host("host", "Host", "xx.xx.xx.xx", "");
    parser.addOption(opt_host);

    QCommandLineOption opt_port("port", "Port", "9999", "0");
    parser.addOption(opt_port);

    QCommandLineOption opt_audio("audio", "Audio enabled", "value", "0");
    parser.addOption(opt_audio);

    QCommandLineOption opt_clipboard("clipboard", "Clipboard", "value", "0" );
    parser.addOption(opt_clipboard);

    QCommandLineOption opt_ignore_mouse("ignore_mouse", "Ignore mouse event", "value", "0");
    parser.addOption(opt_ignore_mouse);

    QCommandLineOption opt_device_id("device_id", "Device id", "value", "");
    parser.addOption(opt_device_id);


    parser.process(app);

    g_host_ = parser.value(opt_host).toStdString();
    g_port_ = parser.value(opt_port).toInt();
    //g_port_ = 9090;

    auto settings = tc::Settings::Instance();
    settings->remote_address_ = g_host_;
    auto audio_on = parser.value(opt_audio).toInt();
    settings->audio_on_ = (audio_on == 1);

    auto clipboard_on = parser.value(opt_clipboard).toInt();
    settings->clipboard_on_ = (clipboard_on == 1);
    settings->ignore_mouse_event_ = parser.value(opt_ignore_mouse).toInt() == 1;

    settings->device_id_ = parser.value(opt_device_id).toStdString();

    LOGI("host: {}", g_host_);
    LOGI("port: {}", g_port_);
    LOGI("audio on: {}", settings->audio_on_);
    LOGI("clipboard on: {}", settings->clipboard_on_);
    LOGI("ignore mouse event: {}", settings->ignore_mouse_event_);
    LOGI("device id: {}", settings->device_id_);
}

bool PrepareDirs(const QString& base_path) {
    std::vector<QString> dirs = {
        "gr_logs", "gr_data"
    };

    bool result = true;
    for (const QString& dir : dirs) {
        auto target_dir_path = base_path + "/" + dir;
        QDir target_dir(target_dir_path);
        if (target_dir.exists()) {
            continue;
        }
        if (!target_dir.mkpath(target_dir_path)) {
            result = false;
            LOGI("Make path failed: {}", target_dir_path.toStdString());
        }
    }
    return result;
}

int main(int argc, char** argv) {
#ifdef WIN32
    //CaptureDump();
#endif

#ifdef __APPLE__
    QSurfaceFormat fmt;
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    fmt.setVersion(3, 3);
    fmt.setSwapInterval(1);
    QSurfaceFormat::setDefaultFormat(fmt);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
#endif

    Logger::InitLog("GammaRayClientInner.log", true);

    QApplication app(argc, argv);
    ParseCommandLine(app);
    // font
#if 0
    auto id = QFontDatabase::addApplicationFont(":/resources/font/quixotic-1.otf");
    qDebug() << "font family : " << QFontDatabase::applicationFontFamilies(id) ;

    QFont font;
    font.setPointSize(10);
    qApp->setFont(font);
#endif

    PrepareDirs(app.applicationDirPath());

    auto host = g_host_;
    auto port = g_port_;
    if (host.empty() || port <= 0 || port >= 65535) {
        auto msg_box = SizedMessageBox::MakeOkBox("Error Params", "You must give valid HOST & PORT");
        msg_box->exec();
        return -1;
    }

    auto name = g_host_ + "_" + MD5::Hex(host).substr(0, 10);
    auto ctx = std::make_shared<ClientContext>(name);
    ctx->Init(true);
    static Workspace ws(ctx, ThunderSdkParams {
            .ssl_ = false,
            .enable_audio_ = true,
            .enable_video_ = true,
            .enable_controller_ = false,
            .ip_ = host,
            .port_ = port,
            .req_path_ = "/media?only_audio=0",
#if defined(WIN32)
            .client_type_ = ClientType::kWindows,
#elif defined(ANDROID)
            .client_type_ = ClientType::kAndroid,
#endif
    });
    ws.setWindowTitle(QMainWindow::tr("GammaRay Game Streamer"));
    ws.resize(1280, 768);
    ws.show();

    HHOOK keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, [](int code, WPARAM wParam, LPARAM lParam) -> LRESULT {
        auto kbd_struct = (KBDLLHOOKSTRUCT *)lParam;
        if (code >= 0 && ws.IsActiveNow()) {
            bool down = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);
            if (kbd_struct->vkCode == VK_LWIN || kbd_struct->vkCode == VK_RWIN) {
                ws.SendWindowsKey(kbd_struct->vkCode, down);
                return 1; // ignore it , send to remote
            }

            // Tab was sent in video_widget_event.cpp, and the ALT + TAB are pressed together, sending the TAB here.
            if (kbd_struct->vkCode == VK_TAB && (GetKeyState(VK_LMENU) < 0 || GetKeyState(VK_RMENU) < 0)) {
                ws.SendWindowsKey(kbd_struct->vkCode, down);
                return 1;
            }
        }
        return CallNextHookEx(nullptr, code, wParam, lParam);
    }, nullptr, 0);

    auto r = app.exec();
    UnhookWindowsHookEx(keyboardHook);
    return r;
}