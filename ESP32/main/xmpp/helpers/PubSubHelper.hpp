#pragma once

#include "../INonConstEventListener.hpp"
#include "../XmppClient.hpp"
#include "../messages/Message.hpp"
#include <tinyxml2.h>

#define BMP180
// #define MQ2
#define SPEAKER
// #define RELAY
// #define PHOTORESISTOR

//---------------------------------------------------------------------------
namespace espiot::xmpp::helpers {
//---------------------------------------------------------------------------
enum PubSubHelperState {
    PUB_SUB_HELPER_NOT_STARTED,
    PUB_SUB_HELPER_REQUESTING_NODES,
    PUB_SUB_HELPER_CREATING_NODES,
    PUB_SUB_HELPER_DONE
};

class PubSubHelper : public INonConstEventListener<messages::Message> {
    private:
    std::shared_ptr<xmpp::XmppClient> client;
    PubSubHelperState state;

    void setState(PubSubHelperState state);

    void discoverNodes();
    void createNodes();
    void onDiscoverNodesReply(messages::Message& event);
    void onCreateNodeReply(messages::Message& event);

    std::string genDiscoverNodesMessage();
    std::string genPublishUiNodeMessage();
    tinyxml2::XMLElement* genFieldNode(tinyxml2::XMLDocument& doc, const char* var, const char* type, const char* value, const char* label);
    tinyxml2::XMLElement* genNodePublishConfig(tinyxml2::XMLDocument& doc);
    tinyxml2::XMLElement* genNodeConfig(tinyxml2::XMLDocument& doc);
    /**
     * Generates a new PEP node.
     **/
    tinyxml2::XMLElement* genPublishItemNode(tinyxml2::XMLDocument& doc, const char* nodeName, const char* itemId);

    public:
    static const std::string XMPP_IOT_SENSOR_TEMP;
    static const std::string XMPP_IOT_SENSOR_BAR;
    static const std::string XMPP_IOT_SENSOR_MQ2;
    static const std::string XMPP_IOT_SENSOR_PHOTORESISTOR;
    static const std::string XMPP_IOT_SENSORS;
    static const std::string XMPP_IOT_ACTUATORS;
    static const std::string XMPP_IOT_ACTUATOR_LED;
    static const std::string XMPP_IOT_ACTUATOR_SPEAKER;
    static const std::string XMPP_IOT_ACTUATOR_RELAY;
    static const std::string XMPP_IOT_UI;
    static const std::string XMPP_IOT_NAMESPACE;

    void publishSensorNode(const std::string& node, const std::string& value, const std::string& unit, const std::string& type);
    void publishActuatorNode(const std::string& node, const std::string& value, const std::string& unit, const std::string& type);
    void publishTempNode(double temp);
    void publishPressureNode(int32_t pressure);
    void publishMq2Node(int32_t val);
    void publishPhotoresistorNode(int32_t val);
    void publishRelayNode(bool on);
    void publishLedNode(bool on);
    void publishSpeakerNode(bool on);
    void requestNodeConfigMessage(const std::string& nodeName);
    void createNode(const std::string& nodeName);
    void deleteNode(const std::string& nodeName);
    void subscribeToNode(const std::string& nodeName);

    PubSubHelper(std::shared_ptr<xmpp::XmppClient> client);

    PubSubHelperState getState();

    void start();

    void event(messages::Message& event) override;
};
//---------------------------------------------------------------------------
} // namespace espiot::xmpp::helpers
//---------------------------------------------------------------------------