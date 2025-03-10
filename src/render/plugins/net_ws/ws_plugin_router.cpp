//
// Created by RGAA on 2024/3/5.
//

#include "ws_plugin_router.h"
#include "tc_common_new/data.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread_util.h"
#include "ws_plugin.h"
#include "tc_message.pb.h"

namespace tc
{

    void WsPluginRouter::OnOpen(std::shared_ptr<asio2::http_session> &sess_ptr) {
        WsRouter::OnOpen(sess_ptr);

        // for testing
        auto m = new tc::Message();
        m->set_type(MessageType::kSyncPanelInfo);
        auto info = m->SerializeAsString();

    }

    void WsPluginRouter::OnClose(std::shared_ptr<asio2::http_session> &sess_ptr) {
        WsRouter::OnClose(sess_ptr);
    }

    void WsPluginRouter::OnMessage(std::shared_ptr<asio2::http_session>& sess_ptr, int64_t socket_fd, std::string_view data) {
        WsRouter::OnMessage(sess_ptr, socket_fd, data);
        auto plugin = Get<WsPlugin*>("plugin");
        auto msg = std::string(data.data(), data.size());
        plugin->OnClientEventCame(true, socket_fd, NetPluginType::kWebSocket, msg);
    }

    void WsPluginRouter::OnPing(std::shared_ptr<asio2::http_session> &sess_ptr) {
        WsRouter::OnPing(sess_ptr);
    }

    void WsPluginRouter::OnPong(std::shared_ptr<asio2::http_session> &sess_ptr) {
        WsRouter::OnPong(sess_ptr);
    }

    void WsPluginRouter::PostBinaryMessage(const std::shared_ptr<Data> &data) {
        this->PostBinaryMessage(data->AsString());
    }

    void WsPluginRouter::PostBinaryMessage(const std::string &data) {
        if (!session_ || !session_->is_started()) {
            return;
        }
        session_->post_queued_event([=, this]() {
            auto tid = tc::GetCurrentThreadID();
            if (post_thread_id_ == 0) {
                post_thread_id_ = tid;
            }
            if (tid != post_thread_id_) {
                LOGI("OH NO! Post binary message in thread: {}, but the last thread is: {}", tid, post_thread_id_);
            }

            session_->ws_stream().binary(true);
            queued_message_count_++;
            session_->async_send(data, [=, this](size_t byte_sent) {
                queued_message_count_--;
            });
        });
    }

    bool WsPluginRouter::IsVideoEnabled() {
        return enable_video_;
    }

    void WsPluginRouter::PostTextMessage(const std::string &data) {
        if (!session_ || !session_->is_started()) {
            return;
        }
        session_->post_queued_event([=, this]() {
            auto tid = tc::GetCurrentThreadID();
            if (post_thread_id_ == 0) {
                post_thread_id_ = tid;
            }
            if (tid != post_thread_id_) {
                LOGI("OH NO! Post text message in thread: {}, but the last thread is: {}", tid, post_thread_id_);
            }

            session_->ws_stream().text(true);
            queued_message_count_++;
            session_->async_send(data, [=, this](size_t byte_sent) {
                queued_message_count_--;
            });
        });
    }
}
