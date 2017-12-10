#include "NFCManager.h"
#include <functional>

NFCManager::NFCManager() {
    using namespace std::placeholders;

    _nfcClient = new NFCClient(std::bind(&NFCManager::_nfcClientCallback, this, _1));
}

void NFCManager::setup() {
    _nfcClient->start();
}

bool NFCManager::tick(NFCManagerStatus status) {

}

void NFCManager::_nfcClientCallback(String tag) {
    Serial.print(tag);
}
