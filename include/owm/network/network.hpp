#include "curlpp/Easy.hpp"
#include "curlpp/Options.hpp"

#include <string>
#include <string_view>

#include "misc/params.hpp"

namespace owm{
    class network{
    private:
        curlpp::Easy m_handle;
        std::string  m_response;
    public:
        void request(const std::string&, params&&);
        [[nodiscard]] std::string&& response() && noexcept;
    };
}