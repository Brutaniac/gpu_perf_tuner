#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP

class device_base;

class power_equlizer {
public:
    power_equlizer(double min_power, double max_power, double min_temperature, double max_temperature);

    void process_device(device_base * device);
private:
    double const min_power, max_power, min_temperature, max_temperature;
};

#endif /* CONTROLLERS_HPP */

