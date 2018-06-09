#include "controllers.hpp"

#include <stddef.h>
#include "device_action.hpp"
#include "device_management.hpp"

power_equlizer::power_equlizer(double min_power, double max_power, double min_temperature, double max_temperature)
: min_power(min_power), max_power(max_power), min_temperature(min_temperature), max_temperature(max_temperature)
{}

void power_equlizer::process_device(device_base * device)
{
    device->read_state();

    device_action action;
    action.fan = 0;
    action.power = 0;

    if(device->get_power() < min_power && device->get_temperature() < max_temperature)
        action.power = 1;
    else if (device->get_power() > max_power)
        action.power = -1;

    if(device->get_temperature() < min_temperature)
        action.fan = -1;
    else if(device->get_temperature() > max_temperature)
        action.fan = device->get_temperature() - max_temperature;
    else if(device->get_temperature() > (min_temperature + max_temperature) * 0.5)
        action.fan = 1;

    if(action.power > 0 && action.fan < 0)
        action.fan = 0;

    device->process_action(action);
}
