#include "XmppPacket.hpp"
#include "../XmppUtils.hpp"
#include <string>
#include <vector>

//---------------------------------------------------------------------------
namespace espiot::xmpp::tcp {
//---------------------------------------------------------------------------
XmppPacket::XmppPacket(std::vector<uint8_t>& data) : data(data) {}

XmppPacket::XmppPacket(std::wstring& data) : data(data.begin(), data.end()) {}
XmppPacket::XmppPacket(std::string& data) : data(data.begin(), data.end()) {}

int XmppPacket::get_send_length() {
    return static_cast<int>(data.size());
}

const uint8_t* XmppPacket::get_data() {
    return data.data();
}

std::vector<uint8_t>& XmppPacket::get_data_vec() {
    return data;
}

const std::vector<uint8_t>& XmppPacket::get_data_vec() const {
    return data;
}

std::wstring XmppPacket::to_wstring() const {
    return wstring_convert_from_bytes(data);
}

std::string XmppPacket::to_string() const {
    return std::string(data.begin(), data.end());
}

std::size_t XmppPacket::size() const {
    return data.size();
}

void XmppPacket::resize(std::size_t newSize) {
    data.resize(newSize);
}
//---------------------------------------------------------------------------
} // namespace espiot::xmpp::tcp
//---------------------------------------------------------------------------
