#include <sstream>

#include <boost/format.hpp>

#include "../utils/utils.hpp"

#include "device_management.hpp"


template<class DeviceSpecification>
device<DeviceSpecification>::device(size_t device_id)
: device_base(device_id)
{}


template<class DeviceSpecification>
void device<DeviceSpecification>::do_read_state()
{
    std::string command = boost::str(boost::format(DeviceSpecification::read_state()) % id());
    std::string const result = os::exec(command);

    device_spec.read_state(result, power, fan, temperature);
}


template<class DeviceSpecification>
void device<DeviceSpecification>::do_process_action(device_action const & action)
{
    std::string command = device_spec.process_action(id(), action, fan, temperature);
    os::exec(command);
}


template<class DeviceEnumerator>
device_manager<DeviceEnumerator>::device_manager()
{
    std::string device_nums = os::exec( DeviceEnumerator::enum_devices() );
    std::istringstream istr(device_nums);

    while(true)
    {
        size_t dev_num;
        istr >> dev_num;
        if(!istr.good())
            break;
        devices.push_back(new device<DeviceEnumerator>(dev_num));
    }
}


template<class DeviceEnumerator>
device_manager<DeviceEnumerator>::~device_manager()
{
    for(auto dev : devices)
        delete dev;
}


template<class DeviceEnumerator>
std::vector<device_base*>::iterator device_manager<DeviceEnumerator>::begin( )
{
    return devices.begin();
}


template<class DeviceEnumerator>
std::vector<device_base*>::iterator device_manager<DeviceEnumerator>::end( )
{
    return devices.end();
}


template<class DeviceSpecification>
std::vector<device_base*>::iterator begin(device_manager<DeviceSpecification> const & dm)
{
    return dm.begin();
}

template<class DeviceSpecification>
std::vector<device_base*>::iterator end(device_manager<DeviceSpecification> const & dm)
{
    return dm.end();
}

