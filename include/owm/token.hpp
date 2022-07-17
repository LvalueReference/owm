#pragma once

#include <string_view>
#include <string>

namespace owm{
    enum class units{standart, metric, imperial};
    enum class lang{af, al, ar, az, bg, ca, cz, da, de, el, en, eu, fa, fi, fr, gl, he, hi, hr, hu, id,
                    it, ja, kr, la, lt, mk, no, nl, pl, pt, pt_br, ro, ru, sv, se, sk, sl, sp, es, sr,
                    th, tr, ua, uk, vi, zh_cn, zh_tw, zu};

    class token{
    private:
        units _units;
        lang _lang;
        std::string _token;
    public:
        token(std::string_view, units = units::metric, lang = lang::en) noexcept;
        std::string get_units() const noexcept;
        std::string get_lang() const noexcept;
        std::string get_token() const noexcept;
    };
}