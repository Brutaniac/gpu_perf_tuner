#ifndef DEVICE_MANAGEMENT_H
#define DEVICE_MANAGEMENT_H

#include <vector>
#include "device_action.hpp"

class device_base
{
public:
    device_base(size_t device_id);
    virtual ~device_base();
    size_t id() const;

    void read_state();

    double get_power() const;
    double get_fan() const;
    double get_temperature() const;

    void process_action(device_action const & action);
protected:
    double power;
    double fan;
    double temperature;

private:
    size_t device_id;
    virtual void do_read_state() = 0;
    virtual void do_process_action(device_action const & action) = 0;
};


template<class DeviceSpecification>
class device : public device_base
{
public:
    device(size_t device_id);
private:
    virtual void do_read_state();
    virtual void do_process_action(device_action const & action);

    DeviceSpecification device_spec;
};


template<class DeviceSpecification>
class device_manager
{
public:
    device_manager();
    ~device_manager();

    std::vector<device_base*>::iterator begin( );
    std::vector<device_base*>::iterator   end( );
private:
    std::vector<device_base*> devices;
};

template<class DeviceSpecification>
std::vector<device_base*>::iterator begin(device_manager<DeviceSpecification> const & dm);

template<class DeviceSpecification>
std::vector<device_base*>::iterator end(device_manager<DeviceSpecification> const & dm);

#include "device_management.tcc"


#endif /* DEVICE_MANAGEMENT_H */

