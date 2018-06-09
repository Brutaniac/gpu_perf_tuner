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

    int exit_code = -1;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), [&exit_code](FILE * f){ exit_code = pclose(f); });
    
    if (!pipe)
        throw std::runtime_error(std::string("Cannot execute the command: ") + cmd);
        
    while (!feof(pipe.get())) 
    {
        if (fgets(buffer.data(), buf_len, pipe.get()) != nullptr)
            result += buffer.data();
    }
    
    pipe.reset();
    
    if( exit_code != 0)
        throw std::runtime_error(std::string("Process exit code was error for command: ") + cmd);
    
    return result;
}

std::string exec(std::string const & cmd)
{
    return exec(cmd.c_str());
}

}