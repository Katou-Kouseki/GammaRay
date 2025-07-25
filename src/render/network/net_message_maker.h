//
// Created by RGAA on 2023-12-25.
//

#ifndef TC_APPLICATION_MESSAGEMAKER_H
#define TC_APPLICATION_MESSAGEMAKER_H

#include <string>
#include <memory>

#include "tc_message.pb.h"

namespace tc
{

    class Data;
    class RdApplication;

    class NetMessageMaker {
    public:

        static std::string MakeHelloMsg();
        static std::string MakeAckMsg();
        static std::string MakeHeartBeatMsg();
        static std::shared_ptr<Data> MakeOnHeartBeatMsg(const std::shared_ptr<RdApplication>& app, uint64_t index, int64_t timestamp);
        static std::shared_ptr<Data> MakeVideoFrameMsg(const tc::VideoType& vt, const std::shared_ptr<Data>& data,
                                             uint64_t frame_index, int frame_width, int frame_height, bool key,
                                             const std::string& display_name, int mon_left,
                                             int mon_top, int mon_right, int mon_bottom, const tc::EImageFormat& img_format, int mon_index = 0);
        static std::shared_ptr<Data> MakeAudioFrameMsg(const std::shared_ptr<Data>& data,
                                             int samples, int channels, int bits, int frame_size);

        static std::shared_ptr<Data> MakeCursorInfoSyncMsg(uint32_t x, uint32_t y, uint32_t hotspot_x, uint32_t hotspot_y, uint32_t width,
                                          uint32_t height, bool visable, const std::shared_ptr<Data>& data, uint32_t type);

        static std::shared_ptr<Data> MakeMonitorSwitched(const std::string& name, const int& mon_index);

    };

}
#endif //TC_APPLICATION_MESSAGEMAKER_H
