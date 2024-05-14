//
// Created by RGAA on 2024/1/25.
//

#ifndef TC_APPLICATION_MESSAGE_PROCESSOR_H
#define TC_APPLICATION_MESSAGE_PROCESSOR_H

#include <string>
#include <memory>
#include <string_view>
#include "tc_message.pb.h"

namespace tc
{
    class ControlEventReplayerWin;
    class Application;
    class Settings;
    class Data;
    class Statistics;
    class WsMediaRouter;

    class MessageProcessor {
    public :
        explicit MessageProcessor(const std::shared_ptr<Application>& app);
        void HandleMessage(const std::shared_ptr<WsMediaRouter>& router, std::string_view message_str);

    private:
        void ProcessHelloEvent(const std::shared_ptr<WsMediaRouter>& router, std::shared_ptr<Message>&& msg);
        void ProcessMouseEvent(std::shared_ptr<Message>&& msg);
        void ProcessKeyboardEvent(std::shared_ptr<Message>&& msg);
#if ENABLE_SHM
        void PostIpcMessage(std::shared_ptr<Data>&& data);
#endif
        void PostIpcMessage(const std::string& msg);
        void ProcessGamepadState(std::shared_ptr<Message>&& msg);
        void ProcessClientStatistics(std::shared_ptr<Message>&& msg);

    private:
        Settings* settings_ = nullptr;
        Statistics* statistics_ = nullptr;
        std::shared_ptr<Application> app_;
        std::shared_ptr<ControlEventReplayerWin> control_event_replayer_win_;
    };
}

#endif //TC_APPLICATION_MESSAGE_PROCESSOR_H
