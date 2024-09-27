#pragma once

#include "window.hpp"
#include <memory>

enum class VsyncInterval {
    Off = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3,
};

class EventLoop {
public:
    EventLoop(std::unique_ptr<Window> app) : app(std::move(app))
    {
    }

    virtual void run(VsyncInterval vsyncInterval=VsyncInterval::_1);

public:
    std::unique_ptr<Window> app;
};