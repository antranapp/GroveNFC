#include "Particle.h"
#include "NFCClient.h"

NFCClient::NFCClient(NFCClientReadMessageHandler callback_):
    _pn532_i2c(Wire),
    _nfcAdapter(_pn532_i2c),
    callback(std::move(callback_)),
    _isReadingNFCMessage(0) {

    _timer = new Timer(1000, &NFCClient::_timerCallback, *this, false);
}

int NFCClient::start() {
    if (_isRunning()) {
        return NFCClientState::ERROR_ALREADY_STARTED;
    }

    _nfcAdapter.begin();
    _timer->reset();

    return NFCClientState::START_SUCCEED;
}

int NFCClient::stop() {
    _timer->stop();
    return NFCClientState::STOPPED;
}

bool NFCClient::_readMessage() {
    _isReadingNFCMessage = true;

    if (_nfcAdapter.tagPresent()) {
        NfcTag tag = _nfcAdapter.read();
        if (tag.getUidLength() > 0) {
            _lastTag = tag;
            _isReadingNFCMessage = false;
            return true;
        }
    }

    _isReadingNFCMessage = false;
    return false;
}

bool NFCClient::_isRunning() {
    return _timer->isActive();
}

void NFCClient::_timerCallback() {
    if (_isReadingNFCMessage) {
        return;
    }

    if (!_readMessage()) {
        return;
    }

    Serial.println("\n---\n** FOUND TAG **");

    if (callback) {
        callback(_lastTag.getUidString());
    }
}
