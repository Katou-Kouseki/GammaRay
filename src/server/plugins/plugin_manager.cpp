//
// Created by RGAA on 15/11/2024.
//

#include "plugin_manager.h"
#include "tc_common_new/log.h"
#include <QDir>
#include <QFile>
#include <QApplication>
#include "plugin_interface/gr_plugin_interface.h"
#include "plugin_event_router.h"

typedef void *(*FnGetInstance)();

namespace tc
{

    std::shared_ptr<PluginManager> PluginManager::Make(const std::shared_ptr<Context> &ctx) {
        return std::make_shared<PluginManager>(ctx);
    }

    PluginManager::PluginManager(const std::shared_ptr<Context> &ctx) {
        this->context_ = ctx;
        this->evt_router_ = std::make_shared<PluginEventRouter>(ctx);
    }

    void PluginManager::LoadAllPlugins() {
        QDir pluginDir(QCoreApplication::applicationDirPath() + R"(/gr_plugins)");
        QStringList filters;
        filters << QString("*%1").arg(".dll");
        pluginDir.setNameFilters(filters);

        auto entryInfoList = pluginDir.entryInfoList();
        for (const auto &info: entryInfoList) {
            auto lib = new QLibrary(QCoreApplication::applicationDirPath() + R"(/gr_plugins/)" + info.fileName());
            if (lib->isLoaded()) {
                LOGI("{} is loaded.", info.fileName().toStdString().c_str());
                continue;
            }

            if (lib->load()) {
                auto func = (FnGetInstance) lib->resolve("GetInstance");
                if (func) {
                    auto plugin = (GrPluginInterface *) func();
                    if (plugin) {
                        auto plugin_name = plugin->GetPluginName();
                        if (plugins_.contains(plugin_name)) {
                            LOGE("{} repeated loading.", plugin_name);
                            lib->unload();
                            lib->deleteLater();
                            lib = nullptr;
                            continue;
                        }

                        // create it
                        // todo: load config
                        plugin->OnCreate(GrPluginParam {
                            .cluster_ = {},
                        });

                        plugins_.insert({plugin_name, plugin});
                        libs_.insert({plugin_name, lib});

                        LOGI("{} version: {}", plugin->GetPluginName(), plugin->GetVersionName());
                    } else {
                        LOGE("{} object create failed.", info.fileName().toStdString().c_str());
                        lib->unload();
                        lib->deleteLater();
                        lib = nullptr;
                    }
                } else {
                    LOGE("{} cannot find symbol.", info.fileName().toStdString().c_str());
                    lib->unload();
                    lib->deleteLater();
                    lib = nullptr;
                }
            } else {
                LOGE("{} load failed. error message: {}", info.fileName().toStdString().c_str(), lib->errorString().toStdString().c_str());
                lib->deleteLater();
                lib = nullptr;
            }
        }
    }

    void PluginManager::RegisterPluginEventsCallback() {
        VisitPlugins([=, this](GrPluginInterface* plugin) {
            plugin->RegisterEventCallback([=, this](const std::shared_ptr<GrPluginBaseEvent>& event) {
                evt_router_->ProcessPluginEvent(event);
            });
        });
    }

    void PluginManager::ReleaseAllPlugins() {
        for (auto &[k, plugin]: plugins_) {
            plugin->OnStop();
            plugin->OnDestroy();
        }
        for (auto &[k, lib]: libs_) {
            lib->unload();
            lib->deleteLater();
        }
        plugins_.clear();
        libs_.clear();
    }

    void PluginManager::ReleasePlugin(const std::string &name) {

    }

    GrPluginInterface *PluginManager::GetPluginByName(const std::string &name) {
        for (auto& [k, plugin]: plugins_) {
            if (k == name) {
                return plugin;
            }
        }
        return nullptr;
    }

    void PluginManager::VisitPlugins(const std::function<void(GrPluginInterface *)>&& visitor) {
        for (const auto &[k, plugin]: plugins_) {
            if (visitor && plugin->IsPluginEnabled()) {
                visitor(plugin);
            }
        }
    }

    void PluginManager::On1Second() {
        LOGI("On1Second...");
        VisitPlugins([=, this](GrPluginInterface* plugin) {
            LOGI("On1Second...{}", plugin->GetPluginName());
            plugin->On1Second();
        });
    }

    void PluginManager::DumpPluginInfo() {
        LOGI("====> Total plugins: {}", plugins_.size());
        int index = 1;
        VisitPlugins([&](GrPluginInterface *plugin) {
            LOGI("Plugin {}. {} Version name:{}, Version code: {}", index++, plugin->GetPluginName(),
                 plugin->GetVersionName(), plugin->GetVersionCode());
        });
    }

}