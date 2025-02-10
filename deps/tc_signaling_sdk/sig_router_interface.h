#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>
#include "rtc_context.h"
#include "sig_params.h"

namespace tc {

using OnSigMessageCallback = std::function<void(const std::string& sig)>;

class MessageNotifier;
class MessageListener;

class SigRouterInterface {
public:
	explicit SigRouterInterface(const std::shared_ptr<RtcContext>& ctx) {
		rtc_ctx_ = ctx;
		msg_notifier_ = rtc_ctx_->GetMessageNotifier();
		msg_listener_ = msg_notifier_->CreateListener();
	}

	virtual void Init(const SignalingParam& params) = 0;
	virtual void Start() = 0;
	virtual void Exit() = 0;
	virtual void SendSigMessage(const std::string& sig_name, const std::string& token, const std::string& msg) = 0;
	virtual void SendHeartBeat() = 0;
	virtual bool IsAlive() = 0;

	void RegisterSigMesssageCallback(OnSigMessageCallback&& cbk) {
		sig_msg_cbk_ = std::move(cbk);
	}

protected:
	std::shared_ptr<RtcContext> rtc_ctx_ = nullptr;
	std::shared_ptr<MessageNotifier> msg_notifier_ = nullptr;
	std::shared_ptr<MessageListener> msg_listener_ = nullptr;
	OnSigMessageCallback sig_msg_cbk_;
	SignalingParam sig_params_;

};

}