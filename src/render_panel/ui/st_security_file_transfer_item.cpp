//
// Created by RGAA on 30/04/2025.
//

#include "st_security_file_transfer_item.h"
#include "no_margin_layout.h"
#include "render_panel/gr_context.h"
#include "render_panel/gr_application.h"
#include "render_panel/gr_app_messages.h"
#include "render_panel/database/file_transfer_record.h"
#include "tc_common_new/client_id_extractor.h"
#include "tc_common_new/time_util.h"
#include "tc_common_new/uid_spacer.h"
#include "tc_common_new/file_util.h"
#include "tc_label.h"
#include <QLabel>
#include <QPushButton>

namespace tc
{

    const QString kDisplayPluginEnabled = "Enabled";
    const QString kDisplayPluginDisabled = "Disabled";

    StSecurityFileTransferItemWidget::StSecurityFileTransferItemWidget(const std::shared_ptr<GrApplication>& app,
                       const std::shared_ptr<FileTransferRecord>& item_info,
                       QWidget* parent) : QWidget(parent) {
        app_ = app;
        context_ = app->GetContext();
        item_info_ = item_info;

        this->setObjectName("StSecurityFileTransferItemWidget");
        this->setStyleSheet("#StSecurityFileTransferItemWidget {background:#ffffffff;}");

        auto root_layout = new NoMarginVLayout();

        auto content_layout = new NoMarginHLayout();
        root_layout->addStretch();
        root_layout->addLayout(content_layout);
        root_layout->addStretch();

        auto header_style = R"(font-weight: 500; padding-left: 3px; color: #333333;)";
        auto item_style = R"(font-weight: 500; padding-left: 3px; color: #555555;)";
        auto target_style = !item_info_->IsHeaderItem() ? item_style : header_style;

        {
            auto lbl = new TcLabel(this);
            if (!item_info_->IsHeaderItem()) {
                if (item_info_->success_) {
                    lbl->setStyleSheet(R"(font-weight: 700; padding-left: 8px; color: #33FF33;)");
                }
                else {
                    lbl->setStyleSheet(R"(font-weight: 700; padding-left: 8px; color: #FF3333;)");
                }
                lbl->setText(item_info_->success_ ? "Success" : "Failed");
            }
            else {
                lbl->setStyleSheet(R"(font-weight: 500; padding-left: 8px; color: #555555;)");
                lbl->SetTextId("id_result");
            }

            lbl->setFixedWidth(100);
            content_layout->addWidget(lbl);
        }

        {
            auto lbl = new TcLabel(this);
            lbl->setStyleSheet(target_style);
            if (!item_info_->IsHeaderItem()) {
                lbl->setText(TimeUtil::FormatTimestamp(item_info_->begin_).c_str());
            }
            else {
                lbl->SetTextId("id_start_time");
            }
            lbl->setFixedWidth(130);
            content_layout->addWidget(lbl);
        }

        {
            auto lbl = new TcLabel(this);
            lbl->setStyleSheet(target_style);
            if (!item_info_->IsHeaderItem()) {
                if (item_info_->end_ <= 0) {
                    lbl->setText("- - -");
                }
                else {
                    lbl->setText(TimeUtil::FormatTimestamp(item_info_->end_).c_str());
                }
            }
            else {
                lbl->SetTextId("id_end_time");
            }
            lbl->setFixedWidth(130);
            content_layout->addWidget(lbl);
        }

        {
            auto lbl = new TcLabel(this);
            lbl->setStyleSheet(target_style);
            if (!item_info_->IsHeaderItem()) {
                std::string visitor_device_id = ExtractClientId(item_info_->visitor_device_);
                lbl->setText(SpaceId(visitor_device_id).c_str());
            }
            else {
                lbl->SetTextId("id_visitor_device");
            }
            lbl->setFixedWidth(130);
            content_layout->addWidget(lbl, 1);
        }

        {
            auto lbl = new TcLabel(this);
            lbl->setStyleSheet(target_style);
            if (!item_info_->IsHeaderItem()) {
                lbl->setText(SpaceId(item_info_->target_device_).c_str());
            }
            else {
                lbl->SetTextId("id_target_device");
            }
            lbl->setFixedWidth(130);
            content_layout->addWidget(lbl, 1);
        }

        {
            auto lbl = new TcLabel(this);
            lbl->setStyleSheet(target_style);
            if (!item_info_->IsHeaderItem()) {
                lbl->setText(item_info_->direction_.c_str());
            }
            else {
                lbl->SetTextId("id_direction");
            }
            lbl->setFixedWidth(100);
            content_layout->addWidget(lbl, 1);
        }

        {
            auto lbl = new TcLabel(this);
            lbl->setStyleSheet(target_style);
            if (!item_info_->IsHeaderItem()) {
                auto filename = FileUtil::GetFileNameFromPath(item_info_->file_detail_);
                lbl->setText(filename.c_str());
            }
            else {
                lbl->SetTextId("id_file_name");
            }
            lbl->setFixedWidth(250);
            content_layout->addWidget(lbl);
        }

        content_layout->addSpacing(10);

        setLayout(root_layout);
    }

    void StSecurityFileTransferItemWidget::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        if (!item_info_->IsHeaderItem()) {
            QPen pen;
            pen.setStyle(Qt::PenStyle::DashDotDotLine);
            pen.setColor(0xdddddd);
            painter.setPen(pen);
            int offset = 2;
            painter.drawRoundedRect(QRect(offset, offset, this->width() - offset * 2, this->height() - offset * 2), 5, 5);

            if (enter_) {
                painter.setBrush(QBrush(0xf1f1f1));
            }
            else {
                painter.setBrush(QBrush(0xffffff));
            }
            painter.drawRoundedRect(QRect(offset, offset, this->width() - offset * 2, this->height() - offset * 2), 5, 5);
        }
        else {
            int offset = 2;
            painter.setPen(Qt::NoPen);
            painter.setBrush(QBrush(0xeeeeee));
            painter.drawRoundedRect(QRect(offset, offset, this->width() - offset * 2, this->height() - offset * 2), 5, 5);
        }
        QWidget::paintEvent(event);
    }

    void StSecurityFileTransferItemWidget::UpdateStatus() {
        if (!lbl_enabled_) {
            return;
        }



    }

    void StSecurityFileTransferItemWidget::UpdatePluginStatus(bool enabled) {
        if (enabled) {
            lbl_enabled_->setText(kDisplayPluginEnabled);
            lbl_enabled_->setStyleSheet(R"(font-weight: 700; color: #555555;)");
        }
        else {
            lbl_enabled_->setText(kDisplayPluginDisabled);
            lbl_enabled_->setStyleSheet(R"(font-weight: 700; color: #ff2200;)");
        }
    }

    void StSecurityFileTransferItemWidget::SwitchPluginStatusInner(bool enabled) {

    }

    void StSecurityFileTransferItemWidget::enterEvent(QEnterEvent *event) {
        enter_ = true;
        repaint();
    }

    void StSecurityFileTransferItemWidget::leaveEvent(QEvent *event) {
        enter_ = false;
        repaint();
    }

}