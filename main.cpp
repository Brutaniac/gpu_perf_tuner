#include <iostream>

#include "devices/device_management.hpp"
#include "devices/amd_rocm/amd_rocm_gpu.hpp"
#include "devices/controllers.hpp"


int main ()
{
    device_manager<amd_rocm::amd_rocm_spec> dm;
    
    power_equlizer pm(110, 120, 68, 72);
    
    for(auto const & dev : dm)
    {
        pm.process_device(dev);
    }
}

