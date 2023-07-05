#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>

constexpr auto MAX_BITS = 119;

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: crcrem <data length> <generative polynomial>" << std::endl;
        return 0;
    }

    const auto len_data = std::stoi(argv[1]);
    const auto gp_str = std::string(argv[2]);

    const auto len_gp = gp_str.length();
    if (len_gp < 4 || len_gp > 9)
    {
        std::cout << "Please specify a generative polynomial of a length within [4, 9]." << std::endl;
        return 0;
    }

    const auto gp = std::bitset<MAX_BITS>(gp_str);
    for (size_t i = 0; i < len_data; ++i)
    {
        auto remainder = std::bitset<MAX_BITS>(1 << (len_gp + i));

        for (ptrdiff_t j = i + 1; j >= 0; --j)
        {
            if (remainder[len_gp + j - 1] == true)
                remainder ^= gp << j;
        }

        remainder &= (1 << (len_gp - 1)) - 1;

        std::cout << std::setfill('0') << std::setw(2) << std::hex
                  << remainder.to_ullong() << '\t';
    }

    std::cout << std::endl;
}
