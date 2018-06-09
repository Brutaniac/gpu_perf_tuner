#ifndef AMD_ROCM_GPU_HPP
#define AMD_ROCM_GPU_HPP

#include <string>
#include "../device_action.hpp"

namespace amd_rocm
{

struct amd_rocm_spec
{
    static std::string rocm_path()    { return "/opt/rocm/bin/"; }
    static std::string rocm_binary()  { return "rocm-smi"; }
    static std::string rocm_smi()     { return rocm_path() + rocm_binary(); }

    static std::string enum_devices() { return rocm_smi() + " -i | grep -i 67df | sed -r 's/GPU\\[([0-9]+)\\].*/\\1/g'"; }

    static std::string read_state()   { return rocm_smi() + " -d %i -t -f -c -s -P"; }
    static std::string set_state()    { return rocm_smi() + " -d %i --setsclk %i --setfan %i"; }

    static constexpr size_t const normal_power = 115;
    static constexpr double const normal_fan = 0.75;
    static constexpr double const maximal_fan = 0.85;
    static constexpr double const normal_temperature = 75;

    size_t max_power_level;
    size_t power_level;

    void read_state(std::string const & state, double & power, double & fan, double & temperature);
    std::string process_action(size_t device_id, device_action const & action, double fan, double temperature);
};

}

#endif /* AMD_ROCM_GPU_HPP */

