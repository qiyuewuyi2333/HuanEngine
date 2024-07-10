#include "util/ApplicationLocator.h"
namespace Huan {
    Application* ApplicationLocator::serviceInstance = nullptr;

    void ApplicationLocator::provide(Application* service) {
        ApplicationLocator::serviceInstance = service;
    }

    Application* ApplicationLocator::getInstance() {
        if (!serviceInstance) {
            throw std::runtime_error("Instance not provided.");
        }
        return serviceInstance;
    }
}
