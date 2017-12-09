#pragma once

class ITick {
    public:
        virtual int tick() = 0;
        virtual ~ITick() {}
};
