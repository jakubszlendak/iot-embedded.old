#include "nodecontainer.h"
#include <stdexcept>

NodeContainer::NodeContainer(QObject *parent) : QObject(parent)
{

}

SensorNode *NodeContainer::getSensor(const QString &name)
{
        if(sensor_nodes_.contains(name))
            return sensor_nodes_[name];
        else throw new std::runtime_error("Cannot find node with given name");
}

BrokerNode *NodeContainer::getBroker(const QString &name)
{
    if(broker_nodes_.contains(name))
        return broker_nodes_[name];
    else throw new std::runtime_error("Cannot find node with given name");
}

ConnectivityNode *NodeContainer::getConnectivityNode(const QString &name)
{
    if(connectivity_nodes_.contains(name))
        return connectivity_nodes_[name];
    else throw new std::runtime_error("Cannot find node with given name");
}

SensorNodeFactory *NodeContainer::getSensorFactory(const QString &name)
{
    if(sensor_node_factories_.contains(name))
        return sensor_node_factories_[name];
    else throw new std::runtime_error("Node Factory of given name not registered.");
}

BrokerNodeFactory *NodeContainer::getBrokerFactory(const QString &name)
{
    if(broker_node_factories_.contains(name))
        return broker_node_factories_[name];
    else throw new std::runtime_error("Node Factory of given name not registered.");

}

ConnectivityNodeFactory *NodeContainer::getConnectivityFactory(const QString &name)
{
    if(connectivity_node_factories_.contains(name))
        return connectivity_node_factories_[name];
    else throw new std::runtime_error("Node Factory of given name not registered.");

}

#include "plugin/sensor/system_telemetry/SystemTelemetrySensorFactory.h"
#include "plugin/rest/RestEndpointFactory.h"
bool NodeContainer::loadNodeFactory(QString &file_name)
{
    if(file_name.startsWith("test")) {
        QString name = file_name;
        name.remove("test_lib");
        name.remove(".so");
        NodeFactory* nf;
        if(name=="restendpoint") {
//            nf = new RestEndpointFactory();
            factories_.insert(nf->getNodeClassName(), nf);
        }

        if(name=="systemtelemetrysensor") {
//            nf = new SystemTelemetrySensorFactory();
            factories_.insert(nf->getNodeClassName(), nf);
        }
    }
    // do PluginLoader stuff here
}

bool NodeContainer::loadNodeFactoryTestSet()
{
//    NodeFactory *sts_factory = new SystemTelemetrySensorFactory(this);
//    factories_.insert(sts_factory->getNodeClassName(), sts_factory);
    /// debug function



}

void NodeContainer::registerNode(SensorNode *node)
{
    if(sensor_nodes_.contains(node->getName()))
        throw new std::runtime_error("Node of given name already exists.");
    else
        sensor_nodes_.insert(node->getName(), node);
}

void NodeContainer::registerNode(BrokerNode *node)
{
    if(broker_nodes_.contains(node->getName()))
        throw new std::runtime_error("Node of given name already exists.");
    else
        broker_nodes_.insert(node->getName(), node);
}

void NodeContainer::registerNode(ConnectivityNode *node)
{
    if(connectivity_nodes_.contains(node->getName()))
        throw new std::runtime_error("Node of given name already exists.");
    else
        connectivity_nodes_.insert(node->getName(), node);
}




