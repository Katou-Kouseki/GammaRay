//
// Created by RGAA on 2023-12-22.
//

#ifndef TC_APPLICATION_APP_MANAGER_FACTORY_H
#define TC_APPLICATION_APP_MANAGER_FACTORY_H

#include <memory>

namespace tc
{

    class RdContext;
    class AppManager;

    class AppManagerFactory {
    public:

        static std::shared_ptr<AppManager> Make(const std::shared_ptr<RdContext>& ctx);

    };

}

#endif //TC_APPLICATION_APP_MANAGER_FACTORY_H
