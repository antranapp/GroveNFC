#include "Particle.h"
#include "NFCClient.h"

NFCClient::NFCClient(NFCClientReadMessageHandler* readMessageHandler):
    pn532_i2c(Wire),
    nfcAdapter(pn532_i2c),
    _readMessageHandler(readMessageHandler),
    _isReadingNFCMessage(0),
    _lastTagID("") {

    _timer = new Timer(1000, &NFCClient::timerCallback, *this, false);

    nfcAdapter.begin();
}

int NFCClient::start() {
    if (isRunning()) {
        return NFCClientState::ERROR_ALREADY_STARTED;
    }

    _timer->reset();

    return NFCClientState::START_SUCCEED;
}

int NFCClient::stop() {
    _timer->stop();
    return NFCClientState::STOPPED;
}

String NFCClient::readMessage() {
    _isReadingNFCMessage = 1;

    String tagID = "";
    if (nfcAdapter.tagPresent()) {
        NfcTag tag = nfcAdapter.read();
        tag.print();
        tagID = tag.getUidString();
    }

    _isReadingNFCMessage = 0;

    return tagID;
}

bool NFCClient::isRunning() {
    return _timer->isActive();
}

void NFCClient::timerCallback() {
    if (_isReadingNFCMessage) {
        return;
    }

    _lastTagID = readMessage();
    if (_lastTagID.length() > 0) {
        _readMessageHandler(_lastTagID);
    }
}
