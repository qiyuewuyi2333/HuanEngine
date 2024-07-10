#pragma once
#include "Huan/Application.h"

namespace Huan {
    class HUAN_API ApplicationLocator {
    public:
        static void provide(Application* service);
        static Application* getInstance();

    private:
        static Application* serviceInstance;
    };
}