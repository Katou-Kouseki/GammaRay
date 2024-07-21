//
// Created by RGAA  on 2024/2/12.
//

#ifndef TC_APPLICATION_CONTROL_EVENT_REPLAYER_WIN_H
#define TC_APPLICATION_CONTROL_EVENT_REPLAYER_WIN_H

#include <memory>
#include "tc_message.pb.h"
#include "tc_capture_new/capture_message.h"

namespace tc
{

    class WinEventReplayer {
    public:
        void HandleMessage(const std::shared_ptr<Message>& message);
        void HandleKeyEvent(const tc::KeyEvent& event);
        void HandleMouseEvent(const tc::MouseEvent& event);
        void ReplayMouseEvent(int monitor_index, float x_ratio, float y_ratio, int buttons, int data);
        void UpdateCaptureMonitorInfo(const CaptureMonitorInfoMessage& msg);

    private:
        bool IsKeyPermitted(uint32_t vk);
        void ResetKey();
        void ReplayKeyEvent(uint16_t scancode, bool extend, const tc::KeyEvent& event);
        void MockKeyEvent(uint16_t scancode);

    private:
        // capturing monitors
        std::vector<CaptureMonitorInfo> monitors_;
        bool current_key_status_map[256] = {false, };
        bool control_pressed_ = false;
        bool menu_pressed_ = false;
        bool delete_pressed_ = false;
        bool shift_pressed_ = false;
        bool win_pressed_ = false;
    };
}


#endif //TC_APPLICATION_CONTROL_EVENT_REPLAYER_WIN_H
