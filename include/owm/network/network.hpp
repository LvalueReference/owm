#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"

#include <string>
#include <string_view>

#include "misc/params.hpp"

namespace owm{
    class network{
    private:
        curlpp::Easy _handle;
        std::string _response;
    public:
        void request(std::string_view, params&&);
        std::string response() && noexcept;
    };
}