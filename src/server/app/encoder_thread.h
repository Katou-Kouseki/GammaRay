//
// Created by RGAA on 2023-12-24.
//

#ifndef TC_APPLICATION_ENCODER_THREAD_H
#define TC_APPLICATION_ENCODER_THREAD_H

#include <memory>
#include <functional>

namespace tc
{

    class Thread;
    class VideoEncoder;
    class Data;
    class Image;
    class File;
    class Context;
    class Settings;

    class EncoderThread {
    public:
        static std::shared_ptr<EncoderThread> Make(const std::shared_ptr<Context>& ctx);

        explicit EncoderThread(const std::shared_ptr<Context>& ctx);
        ~EncoderThread() = default;

        void Encode(const std::shared_ptr<Data>& data, int width, int height, uint64_t frame_index);
        void Encode(const std::shared_ptr<Image>& image, uint64_t frame_index);
        void Encode(int64_t adapter_uid, uint64_t handle, int width, int height, int format, uint64_t frame_index);
        void Exit();

    private:
        Settings* settings_ = nullptr;
        std::shared_ptr<Thread> enc_thread_ = nullptr;
        std::shared_ptr<VideoEncoder> video_encoder_ = nullptr;
        std::shared_ptr<Context> context_ = nullptr;

        int frame_width_ = 0;
        int frame_height_ = 0;

        // debug
        std::shared_ptr<File> debug_file_ = nullptr;
    };

}

#endif //TC_APPLICATION_ENCODER_THREAD_H
