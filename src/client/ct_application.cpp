//
// Created by RGAA on 2024/3/8.
//

#include "client/ct_application.h"

#include "client/ct_app_message.h"
#include <QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QElapsedTimer>
#include <QFile>
#include <QProcess>

#include "ui/app_menu.h"
#include "ui/app_stream_list.h"
#include "tc_common_new/log.h"
#include "tc_common_new/thread.h"
#include "ui/create_stream_dialog.h"
#include "client/ct_client_context.h"
#include "tc_qt_widget/widget_helper.h"
#include "ui/stream_content.h"
#include "ui/settings_content.h"
#include "ui/about_content.h"
#include "ui/no_margin_layout.h"
#include "client/ct_settings.h"
#include "tc_qt_widget/sized_msg_box.h"
#include "tc_qt_widget/widgetframe/mainwindow_wrapper.h"
#include "tc_dialog.h"

namespace tc
{

    Application::Application(const std::shared_ptr<ClientContext>& ctx, QWidget* parent) : QMainWindow(parent) {
        context_ = ctx;
        settings_ = Settings::Instance();
        resize(1515, 768);
        auto notifier = this->context_->GetMessageNotifier();
        (new MainWindowWrapper(notifier, this))->Setup(tr("GammaRay Client"));

        theme_ = new MainWindowPrivate(this);
        QString app_dir = qApp->applicationDirPath();
        QString style_dir = app_dir + "/resources/";
        theme_->AdvancedStyleSheet = new acss::QtAdvancedStylesheet(this);
        theme_->AdvancedStyleSheet->setStylesDirPath(style_dir);
        theme_->AdvancedStyleSheet->setOutputDirPath(app_dir + "/output");
        theme_->AdvancedStyleSheet->setCurrentStyle("qt_material");
        theme_->AdvancedStyleSheet->setCurrentTheme("light_blue");
        theme_->AdvancedStyleSheet->updateStylesheet();
        setWindowIcon(theme_->AdvancedStyleSheet->styleIcon());
        qApp->setStyleSheet(theme_->AdvancedStyleSheet->styleSheet());

        CreateLayout();
        Init();

    }

    Application::~Application() {
        delete theme_;
    }

    void Application::CreateLayout() {
        auto root_widget = new RoundRectWidget(0xffffff, 0, this);
        auto root_layout = new QHBoxLayout();
        WidgetHelper::ClearMargins(root_layout);
        int margin = 20;
        root_layout->setContentsMargins(0, margin, margin, margin);

        // 1. app menu
        content_widget_ = new QStackedWidget(this);
        content_widget_->setContentsMargins(0,0,0,0);
        content_widget_->setStyleSheet("border:none;background-color:#ffffff;");

        std::vector<AppItemDesc> menus = {
                {tr("GAMES"), ":/resources/image/ic_stream.svg"},
                {tr("SETTINGS"), ":/resources/image/ic_settings.svg"},
                //{tr("ABOUT"), ":/resources/image/ic_settings.svg"}
        };
        app_menu_ = new AppMenu(menus, this);
        app_menu_->SetOnItemClickedCallback([this](const QString& name, int idx) {
            content_widget_->setCurrentIndex(idx);
        });

        auto menu_layout = new NoMarginVLayout();
        menu_layout->addWidget(app_menu_);
        menu_layout->addStretch();

        auto lbl_version = new QLabel();
        lbl_version->setFixedWidth(app_menu_->width());
        lbl_version->setAlignment(Qt::AlignCenter);
        lbl_version->setText(Settings::Instance()->version_.c_str());
        menu_layout->addWidget(lbl_version);

        root_layout->addLayout(menu_layout);

        // 2. stream list

        // streams
        auto stream_content = new StreamContent(context_, this);
        content_widget_->addWidget(stream_content);
        stream_content_ = stream_content;

        // settings
        auto settings_content = new SettingsContent(context_, this);
        content_widget_->addWidget(settings_content);

        // about
        auto about_content = new AboutContent(context_, this);
        content_widget_->addWidget(about_content);

        root_layout->addWidget(content_widget_);
        root_widget->setLayout(root_layout);
        setCentralWidget(root_widget);

        content_widget_->setCurrentIndex(0);
    }

    void Application::Init() {
        msg_listener_ = context_->ObtainMessageListener();
    }

    void Application::changeEvent(QEvent* event) {
        if (event->type() == QEvent::ActivationChange) {
            qDebug() << "window state: " << isActiveWindow();
        }
    }

    void Application::closeEvent(QCloseEvent* event) {
//        auto msg_box = SizedMessageBox::MakeOkCancelBox(tr("Stop"), tr("Do you want to exit GammaRayClient ?"));
//        if (msg_box->exec() == 0) {
//            event->accept();
//        } else {
//            event->ignore();
//        }

        event->ignore();

        auto dlg = TcDialog::Make(tr("Stop"), tr("Do you want to exit GammaRayClient ?"), nullptr);
        dlg->SetOnDialogSureClicked([=, this]() {
            this->close();
        });
        dlg->show();

    }

}