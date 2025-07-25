//
// Created by RGAA on 2024/3/5.
//

#include "ws_stream_router.h"
#include "tc_common_new/data.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread_util.h"
#include "ws_plugin.h"
#include "tc_message.pb.h"

namespace tc
{

    void WsStreamRouter::OnOpen(std::shared_ptr<asio2::https_session> &sess_ptr) {
        WssRouter::OnOpen(sess_ptr);
    }

    void WsStreamRouter::OnClose(std::shared_ptr<asio2::https_session> &sess_ptr) {
        WssRouter::OnClose(sess_ptr);
    }

    void WsStreamRouter::OnMessage(std::shared_ptr<asio2::https_session>& sess_ptr, int64_t socket_fd, std::string_view data) {
        WssRouter::OnMessage(sess_ptr, socket_fd, data);
        auto plugin = Get<WsPlugin*>("plugin");
        auto msg = Data::Make(data.data(), data.size());
        plugin->OnClientEventCame(true, socket_fd, NetPluginType::kWebSocket, msg);
    }

    void WsStreamRouter::OnPing(std::shared_ptr<asio2::https_session> &sess_ptr) {
        WssRouter::OnPing(sess_ptr);
    }

    void WsStreamRouter::OnPong(std::shared_ptr<asio2::https_session> &sess_ptr) {
        WssRouter::OnPong(sess_ptr);
    }

    void WsStreamRouter::PostBinaryMessage(std::shared_ptr<Data> data) {
        if (!session_ || !session_->is_started()) {
            return;
        }

        auto tid = tc::GetCurrentThreadID();
        if (post_thread_id_ == 0) {
            post_thread_id_ = tid;
        }
        if (tid != post_thread_id_) {
            //LOGI("OH NO! Post binary message in thread: {}, but the last thread is: {}", tid, post_thread_id_);
        }

        session_->ws_stream().binary(true);
        queuing_message_count_++;
        session_->async_send(data->CStr(), data->Size(), [=, this](size_t byte_sent) {
            queuing_message_count_--;

            // report data size
            auto plugin = Get<WsPlugin*>("plugin");
            plugin->ReportSentDataSize(byte_sent);
        });
    }

    void WsStreamRouter::PostBinaryMessage(const std::string &data) {
        this->PostBinaryMessage(Data::From(data));
    }

    void WsStreamRouter::PostTextMessage(const std::string &data) {
        if (!session_ || !session_->is_started()) {
            return;
        }

        auto tid = tc::GetCurrentThreadID();
        if (post_thread_id_ == 0) {
            post_thread_id_ = tid;
        }
        if (tid != post_thread_id_) {
            LOGI("OH NO! Post text message in thread: {}, but the last thread is: {}", tid, post_thread_id_);
        }

        session_->ws_stream().text(true);
        queuing_message_count_++;
        session_->async_send(data, [=, this](size_t byte_sent) {
            queuing_message_count_--;

            // report data size
            auto plugin = Get<WsPlugin*>("plugin");
            plugin->ReportSentDataSize(byte_sent);
        });
    }
}
