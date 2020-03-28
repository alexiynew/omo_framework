/// @file
/// @brief OpenGL texture.
/// @author Fedorov Alexey
/// @date 16.04.2019

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

#ifndef FRAMEWORK_GRAPHICS_TEXTURE_HPP
#define FRAMEWORK_GRAPHICS_TEXTURE_HPP

#include <common/types.hpp>

namespace framework::graphics
{
enum class min_filter
{
    nearest,
    linear,
    nearest_mipmap_nearest,
    linear_mipmap_nearest,
    nearest_mipmap_linear,
    linear_mipmap_linear,
};

enum class mag_filter
{
    nearest,
    linear,
};

enum class wrap_s
{
    clamp_to_edge,
    mirrored_repeat,
    repeat,
};

enum class wrap_t
{
    clamp_to_edge,
    mirrored_repeat,
    repeat,
};

class texture
{
public:
    texture(min_filter minf = min_filter::linear,
            mag_filter magf = mag_filter::linear,
            wrap_s ws       = wrap_s::repeat,
            wrap_t wt       = wrap_t::repeat);

    void load(int32 width, int32 height, const void* data);

    // void alloc();
    // void subload();

    void bind();
    void unbind();

    framework::uint32 texture_id() const;
    framework::int32 texture_unit() const;

private:
    framework::uint32 m_texture_id = 0;
};

} // namespace framework::graphics

#endif
