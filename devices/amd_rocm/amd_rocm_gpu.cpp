#include <regex>
#include <iostream>

#include "amd_rocm_gpu.hpp"

#include <boost/format.hpp>


namespace amd_rocm
{

    
void amd_rocm_spec::read_state(std::string const & state, double & power, double & fan, double & temperature)
{
    std::regex 
          r_power("Average GPU Power:\\s*([0-9.]+)\\s*W")
        , r_fan("Fan Level:\\s*([0-9]+)\\s*")
        , r_temperature("Temperature:\\s*([0-9.]+)\\s*[cC]")
        , r_memory_freq_begin("Supported GPU Memory clock frequencies on.*")
        , r_power_level("GPU Clock Level:\\s*(\\d+)")
        , r_max_power_level("zhM\\s*[0-9.]*\\s*:([0-9]+)\\s*:")
        ;
    
    std::smatch match_results;
    
    if(!std::regex_search(state, match_results, r_power))
        throw std::logic_error("Could not find power information in the status line");
    double pwr = std::stod(match_results[1].str());
    
    if(!std::regex_search(state, match_results, r_fan))
        throw std::logic_error("Could not find fan information in the status line");
    double fn = std::stod(match_results[1].str()) / 255;

    if(!std::regex_search(state, match_results, r_temperature))
        throw std::logic_error("Could not find temperature in the status line");
    double temp = std::stod(match_results[1].str());
    
    if(!std::regex_search(state, match_results, r_memory_freq_begin))
        throw std::logic_error("Could not find GPU supported memory in the status line");
    
    std::string reverse (std::make_reverse_iterator(match_results[0].first), state.rend());
    
    if(!std::regex_search(reverse, match_results, r_max_power_level))
        throw std::logic_error("Could not find GPU max power level in the status line");
    max_power_level = std::stoi(std::string(std::make_reverse_iterator(match_results[1].second), std::make_reverse_iterator(match_results[1].first)));
    
    if(!std::regex_search(state, match_results, r_power_level))
        throw std::logic_error("Could not find current power level in the status line");
    power_level = std::stod(match_results[1].str());


    power = pwr;
    fan = fn;
    temperature = temp;
}

std::string amd_rocm_spec::process_action(size_t device_id, device_action const & action, double fan, double temperature )
{
    if(temperature > normal_temperature)
    {
        std::cerr << "Error: " << "Device " << device_id << " overheating detected. Sharp throttle." << std::endl;
        return boost::str(
                boost::format(set_state()) 
                % device_id 
                % 0 
                % int(255 * normal_fan) 
            );
    }
    
    if(fan > maximal_fan)
    {
        std::cerr << "Error: " << "Device " << device_id << " fan overspinning detected. Throttling." << std::endl;
        return boost::str(
                boost::format(set_state()) 
                % device_id 
                % (power_level > 0 ? power_level - 1 : 0)
                % int(255 * normal_fan) 
            );
    }

    
    fan = std::min(1.0, fan *( 1 + 0.1 * action.fan ));
    
    power_level = std::min( max_power_level, power_level + action.power);
    
    std::cout << "Info: " << "Device " << device_id << " setting fan: " << fan << " power_level: " << power_level << std::endl;
    
    return boost::str(
            boost::format(set_state()) 
            % device_id 
            % power_level
            % int(255 * fan) 
        );
}


}

