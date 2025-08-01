//
// Created by RGAA on 17/08/2024.
//

#ifndef GAMMARAYPC_FLOAT_SUB_CONTROL_PANEL_H
#define GAMMARAYPC_FLOAT_SUB_CONTROL_PANEL_H

#include "base_widget.h"
#include <QPainter>

namespace tc
{
    class SwitchButton;
    class SubControlPanel : BaseWidget {
    public:
        explicit SubControlPanel(const std::shared_ptr<ClientContext>& ctx, QWidget* parent = nullptr);
        void paintEvent(QPaintEvent *event) override;

    private:
        void RequestCtrlAltDelete();
        void UpdateStatus(const MsgClientFloatControllerPanelUpdate& msg) override;
        void RequestRefreshDesktop();
    private:
        SwitchButton* clibpboard_btn_ = nullptr;
    };

}

#endif //GAMMARAYPC_FLOAT_SUB_CONTROL_PANEL_H
