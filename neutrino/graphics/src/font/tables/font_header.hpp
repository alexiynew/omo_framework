////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Font header table
/// @author Fedorov Alexey
/// @date 18.09.2020
////////////////////////////////////////////////////////////////////////////////

// =============================================================================
// MIT License
//
// Copyright (c) 2017-2019 Fedorov Alexey
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// =============================================================================

#ifndef FRAMEWORK_GRAPHICS_SRC_FONT_TABLES_FONT_HEADER_HPP
#define FRAMEWORK_GRAPHICS_SRC_FONT_TABLES_FONT_HEADER_HPP

#include <graphics/src/font/types.hpp>
#include <vector>

namespace framework::graphics::details::font
{

struct FontHeader
{
    static FontHeader parse(const std::vector<std::uint8_t>& data);

    bool valid() const;

    std::uint16_t major_version        = 0;
    std::uint16_t minor_version        = 0;
    Fixed font_revision                = 0;
    std::uint32_t check_sum_adjustment = 0;
    std::uint32_t magic_number         = 0;
    std::uint16_t flags                = 0;
    std::uint16_t units_per_em         = 0;
    DateTime created                   = 0;
    DateTime modified                  = 0;
    std::int16_t x_min                 = 0;
    std::int16_t y_min                 = 0;
    std::int16_t x_max                 = 0;
    std::int16_t y_max                 = 0;
    std::uint16_t mac_style            = 0;
    std::uint16_t lowest_rec_ppem      = 0;
    std::int16_t font_direction_hint   = 0;
    std::int16_t index_to_loc_format   = 0;
    std::int16_t glyph_data_format     = 0;
};

}

#endif 