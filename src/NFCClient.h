#pragma one

#include "Particle.h"
#include "PN532_I2C.h"
#include "PN532.h"
#include "NfcAdapter.h"

enum NFCClientState {
    ERROR_ALREADY_STARTED = -1,
    START_SUCCEED,
    STOPPED,
};

typedef void(NFCClientReadMessageHandler)(String);

class NFCClient {
    public:
        NFCClient(NFCClientReadMessageHandler* readMessageHandler);
        NFCClient();
        int start();
        int stop();

    private:
        Timer* _timer;
        NFCClientReadMessageHandler* _readMessageHandler;

        PN532_I2C pn532_i2c;
        NfcAdapter nfcAdapter;

        String readMessage();

        String _lastTagID;

        bool isRunning();

        void timerCallback(void);

        volatile uint8_t _isReadingNFCMessage;
};
