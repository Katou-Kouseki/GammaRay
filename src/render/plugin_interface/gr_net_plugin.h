//
// Created by RGAA on 21/11/2024.
//

#ifndef GAMMARAY_GR_NET_PLUGIN_H
#define GAMMARAY_GR_NET_PLUGIN_H

#include "gr_plugin_interface.h"

namespace tc
{

    enum class NetPluginType {
        kWebSocket,
        kUdpKcp,
        kWebRtcDirect,
        kWebRtc
    };

    class NetSyncInfo {
    public:
        int64_t socket_fd_{0};
        std::string device_id_{};
        std::string stream_id_{};
    };

    class GrNetPlugin : public GrPluginInterface {
    public:
        GrNetPlugin();
        virtual ~GrNetPlugin() override;

        // Serialized proto message from Renderer
        // to see format details in tc_message_new/tc_message.proto
        // such as : message VideoFrame { ... }
        // you can send it to any clients
        //                       -> client 1
        // Renderer Messages ->  -> client 2
        //                       -> client 3
        virtual void PostProtoMessage(const std::string& msg);

        // Serialized proto message from Renderer
        // to a specific stream
        virtual bool PostTargetStreamProtoMessage(const std::string& stream_id, const std::string& msg);

        // messages from remote(client) -> this plugin -> process it
        // client 1 ->
        // client 2 ->  -> Renderer
        // client 3 ->
        void OnClientEventCame(bool is_proto, int64_t socket_fd, const NetPluginType& nt_plugin_type, const std::string& msg);

        virtual bool IsOnlyAudioClients();

        virtual int ConnectedClientSize();

        virtual void SyncInfo(const NetSyncInfo& info);

    protected:
        NetSyncInfo sync_info_{};

    };

}

#endif //GAMMARAY_GR_NET_PLUGIN_H
