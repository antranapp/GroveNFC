#pragma once

#include "ITick.h"
#include "NFCClient.h"

enum NFCManagerStatus {
    AUTHENTICATED = 0,
    NOT_AUTHENTICATED
};

class NFCManager {
    public:
        NFCManager();

        void setup();
        bool tick(NFCManagerStatus status);

    private:
        NFCClient* _nfcClient;

        void _nfcClientCallback(String tag);
};
