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
        network();
    public:
        void request(std::string_view, params&&);
        std::string&& response() noexcept;
        const std::string& response() const noexcept;
    };
}