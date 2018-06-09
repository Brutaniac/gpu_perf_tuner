#include "utils.hpp"

#include <array>
#include <memory>

namespace os
{

std::string exec(const char* cmd)
{
    size_t const buf_len = 128;
    std::array<char, buf_len> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    
    if (!pipe)
        throw std::runtime_error(std::string("Cannot execute the command: ") + cmd);
        
    while (!feof(pipe.get())) 
    {
        if (fgets(buffer.data(), buf_len, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

std::string exec(std::string const & cmd)
{
    return exec(cmd.c_str());
}

}