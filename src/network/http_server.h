#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "tc_3rdparty/http/httplib.h"

#include <thread>
#include <memory>

namespace tc
{

    class Context;
    class HttpHandler;

    class HttpServer
    {
    public:
        explicit HttpServer(const std::shared_ptr<Context>& ctx);
        ~HttpServer();

        void Start();
        void Exit();

    private:

        std::shared_ptr<Context> context_ = nullptr;
        std::shared_ptr<httplib::SSLServer> server_ = nullptr;
        std::shared_ptr<HttpHandler> http_handler_ = nullptr;

        std::thread server_thread_;

    };

}

#endif // HTTP_SERVER_H
