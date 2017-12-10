#pragma one

#include "Particle.h"
#include "PN532_I2C.h"
#include "PN532.h"
#include "NfcAdapter.h"

#include <functional>

enum NFCClientState {
    ERROR_ALREADY_STARTED = -1,
    START_SUCCEED,
    STOPPED,
};

class NFCClient {
    public:

        typedef std::function<void(String)> NFCClientReadMessageHandler;

        NFCClient(NFCClientReadMessageHandler callback);

        int start();
        int stop();

    private:
        Timer* _timer;
        NFCClientReadMessageHandler callback;

        PN532_I2C _pn532_i2c;
        NfcAdapter _nfcAdapter;

        bool _readMessage();

        NfcTag _lastTag;

        bool _isRunning();

        void _timerCallback(void);

        volatile bool _isReadingNFCMessage;
};
