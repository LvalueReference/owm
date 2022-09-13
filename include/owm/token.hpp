#pragma once

#include <string_view>
#include <string>

namespace owm{
    enum class units{standart, metric, imperial};
    enum class lang{af, al, ar, az, bg, ca, cz, da, de, el, en, eu, fa, fi, fr, gl, he, hi, hr, hu, id,
                    it, ja, kr, la, lt, mk, no, nl, pl, pt, pt_br, ro, ru, sv, se, sk, sl, sp, es, sr,
                    th, tr, ua, uk, vi, zh_cn, zh_tw, zu};

    struct token{
        std::string units;
        std::string lang;
        std::string appid;

        explicit token(std::string_view, enum units = units::metric, enum lang = lang::en) noexcept;
    };
}