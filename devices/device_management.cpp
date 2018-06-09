#include <sstream>
#include <ios>

#include "device_management.hpp"

#include "../utils/utils.hpp"

device_base::device_base(size_t device_id)
: power(0)
, fan(0)
, temperature(0)
, device_id(device_id)
{
}

device_base::~device_base()
{
    
}

size_t device_base::id() const
{
    return device_id;
}


void device_base::read_state()
{
    do_read_state();
}


double device_base::get_power() const
{
    return power;
}


double device_base::get_fan() const
{
    return fan;
}


double device_base::get_temperature() const
{
    return temperature;
}


void device_base::process_action(device_action const & action)
{
    do_process_action(action);
}

