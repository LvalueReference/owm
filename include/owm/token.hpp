#pragma once

#include <string_view>
#include <string>
#include <variant>

namespace owm{
    enum class units{standard, metric, imperial};
    enum class lang{af, al, ar, az, bg, ca, cz, da, de, el, en, eu, fa, fi, fr, gl, he, hi, hr, hu, id,
                    it, ja, kr, la, lt, mk, no, nl, pl, pt, pt_br, ro, ru, sv, se, sk, sl, sp, es, sr,
                    th, tr, ua, uk, vi, zh_cn, zh_tw, zu};

    struct token{
        const std::string m_units;
        const std::string m_lang;
        const std::string m_appid;

        token(std::string_view, enum units = units::standard, enum lang = lang::en) noexcept;
        token(std::string_view, std::variant<enum units, enum lang>) noexcept;
    };
}