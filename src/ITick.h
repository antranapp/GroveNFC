#pragma once

class ITick {
    public:
        virtual int tick(int status) = 0;
        virtual ~ITick() {}
};
