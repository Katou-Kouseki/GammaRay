//
// Created by RGAA on 22/11/2024.
//

#ifndef GAMMARAY_GR_MONITOR_CAPTURE_PLUGIN_H
#define GAMMARAY_GR_MONITOR_CAPTURE_PLUGIN_H

#include "gr_plugin_interface.h"
#include "tc_capture_new/win/desktop_capture/monitor_util.h"

namespace tc
{
    class Image;
    class Data;

    class GrMonitorCapturePlugin : public GrPluginInterface {
    public:
        GrMonitorCapturePlugin();

        bool OnCreate(const tc::GrPluginParam &param) override;
        bool OnDestroy() override;

        // target: monitor
        virtual bool StartCapturing();
        virtual void StopCapturing();
        bool IsMonitorTarget();

        virtual std::vector<CaptureMonitorInfo> GetCaptureMonitorInfo();
        virtual int GetCapturingMonitorIndex();
        virtual void SetCaptureMonitor(int index, const std::string& name);
        virtual void SetCaptureFps(int fps);
        virtual std::string GetCapturingMonitorName();

    protected:
        bool is_monitor_target_ = false;
    };
}

#endif //GAMMARAY_GR_MONITOR_CAPTURE_PLUGIN_H