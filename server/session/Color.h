#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <nlohmann/json.hpp>

struct Color
{
    Color() : r(0), g(0), b(0) {};
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {};
    uint8_t r, g, b;
};

// Сериализация Color в JSON
inline void to_json(nlohmann::json &j, const Color &color)
{
    j = nlohmann::json{{"r", color.r}, {"g", color.g}, {"b", color.b}};
}

// Десериализация Color из JSON
inline void from_json(const nlohmann::json &j, Color &color)
{
    j.at("r").get_to(color.r);
    j.at("g").get_to(color.g);
    j.at("b").get_to(color.b);
}
#endif // COLOR_H