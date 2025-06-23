//
// Created by RGAA on 23/06/2025.
//

#ifndef GAMMARAY_RETRY_CONN_DIALOG_H
#define GAMMARAY_RETRY_CONN_DIALOG_H

#include "tc_qt_widget/tc_custom_titlebar_dialog.h"

namespace tc
{
    class Win10CircleLoadingWidget;
    class Win10HorizontalLoadingWidget;

    class RetryConnDialog : public TcCustomTitleBarDialog {
    public:
        RetryConnDialog(const QString &title, QWidget *parent = nullptr);
        void Exec();
        void Done();

    private:
        Win10CircleLoadingWidget* h_loading_widget_ = nullptr;
    };
}


#endif //GAMMARAY_RETRY_CONN_DIALOG_H
