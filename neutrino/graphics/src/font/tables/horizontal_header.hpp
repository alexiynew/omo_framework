////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Horizontal header table
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

#ifndef FRAMEWORK_GRAPHICS_SRC_FONT_TABLES_FONT_HORIZONTAL_HEADER_HPP
#define FRAMEWORK_GRAPHICS_SRC_FONT_TABLES_FONT_HORIZONTAL_HEADER_HPP

#include <graphics/src/font/types.hpp>
#include <vector>

namespace framework::graphics::details::font
{

struct HorizontalHeader
{
    static HorizontalHeader parse(const std::vector<std::uint8_t>& data);

    bool valid() const;

    std::uint16_t major_version       = 0;
    std::uint16_t minor_version       = 0;
    FWord ascender                    = 0;
    FWord descender                   = 0;
    FWord line_gap                    = 0;
    UFWord advance_width_max          = 0;
    FWord min_left_side_bearing       = 0;
    FWord min_right_side_bearing      = 0;
    FWord x_max_extent                = 0;
    std::int16_t caret_slope_rise     = 0;
    std::int16_t caret_slope_run      = 0;
    std::int16_t caret_offset         = 0;
    std::int16_t reserved1            = 0;
    std::int16_t reserved2            = 0;
    std::int16_t reserved3            = 0;
    std::int16_t reserved4            = 0;
    std::int16_t metric_data_format   = 0;
    std::uint16_t number_of_h_metrics = 0;
};

}

#endif
