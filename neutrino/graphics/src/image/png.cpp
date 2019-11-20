/// @file
/// @brief Png image implementation.
/// @author Fedorov Alexey
/// @date 05.04.2019

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

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <vector>

#include <common/crc.hpp>
#include <common/types.hpp>
#include <common/zlib.hpp>
#include <graphics/src/image/png.hpp>

namespace
{
using framework::int32;
using framework::uint16;
using framework::uint32;
using framework::uint8;
using framework::usize;
using framework::graphics::color_t;
using framework::graphics::details::image::image_info;

constexpr usize signature_length = 8;
constexpr usize pass_count       = 7;

std::vector<uint8> read_bytes(std::ifstream& in, usize count)
{
    std::vector<uint8> data(count);

    in.read(reinterpret_cast<char*>(data.data()), count);

    if (!in) {
        return std::vector<uint8>();
    }

    return data;
}

template <typename T, typename B>
inline constexpr T big_endian_value(const B* buffer) noexcept
{
    constexpr uint32 size = sizeof(T);

    uint8 tmp[size];
    for (uint32 i = 0; i < size; ++i) {
        tmp[i] = (reinterpret_cast<const uint8*>(buffer))[size - i - 1];
    }

    return *(reinterpret_cast<T*>(tmp));
}

#pragma region chunk

struct chunk_t
{
    enum class type_t : uint32
    {
        undefined = 0,
        IHDR      = 0x49484452,
        PLTE      = 0x504c5445,
        IDAT      = 0x49444154,
        IEND      = 0x49454e44,
        cHRM      = 0x6348524d,
        gAMA      = 0x67414d41,
        iCCP      = 0x69434350,
        sBIT      = 0x73424954,
        sRGB      = 0x73524742,
        bKGD      = 0x624b4744,
        hIST      = 0x68495354,
        tRNS      = 0x74524e53,
        pHYs      = 0x70485973,
        sPLT      = 0x73504c54,
        tIME      = 0x74494d45,
        iTXt      = 0x69545874,
        tEXt      = 0x74455874,
        zTXt      = 0x7a545874,
    };

    uint32 length = 0;
    type_t type   = type_t::undefined;
    uint32 crc    = 0;

    std::vector<uint8> data;

    static chunk_t read(std::ifstream& in);

    bool is_critical() const;
    bool valid() const;
};

chunk_t chunk_t::read(std::ifstream& in)
{
    chunk_t c;

    char buffer[4];

    in.read(buffer, 4);
    c.length = big_endian_value<uint32>(buffer);

    in.read(buffer, 4);
    c.type = big_endian_value<chunk_t::type_t>(buffer);

    if (c.length > 0) {
        c.data = read_bytes(in, c.length);
    }

    in.read(buffer, 4);
    c.crc = big_endian_value<uint32>(buffer);

    return c;
}

bool chunk_t::is_critical() const
{
    return (((static_cast<uint32>(type) >> 24) & 0xFF) & 0x20) == 0;
}

bool chunk_t::valid() const
{
    framework::utils::crc32 crc_calk;

    crc_calk.update(big_endian_value<uint32>(reinterpret_cast<const char*>(&type)));
    crc_calk.update(begin(data), end(data));

    return crc_calk.current_value() == crc;
}

#pragma endregion chunk

#pragma region file header

enum class color_type_t : uint8
{
    greyscale       = 0,
    truecolor       = 2,
    indexed         = 3,
    greyscale_alpha = 4,
    truecolor_alpha = 6,
};

enum class compression_method_t : uint8
{
    deflate_inflate = 0,
};

enum class filter_method_t : uint8
{
    adaptive = 0,
};

enum class interlace_method_t : uint8
{
    no    = 0,
    adam7 = 1,
};

struct file_header_t
{
    uint32 width                            = 0;
    uint32 height                           = 0;
    uint8 bit_depth                         = 0;
    color_type_t color_type                 = color_type_t::greyscale;
    compression_method_t compression_method = compression_method_t::deflate_inflate;
    filter_method_t filter_method           = filter_method_t::adaptive;
    interlace_method_t interlace_method     = interlace_method_t::no;

    static file_header_t read(std::ifstream& in);

    bool valid() const;
    usize samples_per_pixel() const;
    usize bits_per_pixel() const;
    usize bytes_per_pixel() const;

    image_info get_image_info() const;
};

file_header_t file_header_t::read(std::ifstream& in)
{
    auto c = chunk_t::read(in);
    if (c.type != chunk_t::type_t::IHDR || !c.valid()) {
        return file_header_t();
    }

    file_header_t h;
    h.width              = big_endian_value<uint32>(&c.data[0]);
    h.height             = big_endian_value<uint32>(&c.data[4]);
    h.bit_depth          = c.data[8];
    h.color_type         = static_cast<color_type_t>(c.data[9]);
    h.compression_method = static_cast<compression_method_t>(c.data[10]);
    h.filter_method      = static_cast<filter_method_t>(c.data[11]);
    h.interlace_method   = static_cast<interlace_method_t>(c.data[12]);

    return h;
}

bool file_header_t::valid() const
{
    auto valid_bit_depth = [=]() {
        switch (color_type) {
            case color_type_t::greyscale:
                return (bit_depth == 1 || bit_depth == 2 || bit_depth == 4 || bit_depth == 8 || bit_depth == 16);
            case color_type_t::truecolor: return (bit_depth == 8 || bit_depth == 16);
            case color_type_t::indexed: return (bit_depth == 1 || bit_depth == 2 || bit_depth == 4 || bit_depth == 8);
            case color_type_t::greyscale_alpha: return (bit_depth == 8 || bit_depth == 16);
            case color_type_t::truecolor_alpha: return (bit_depth == 8 || bit_depth == 16);
        }
        return false;
    };

    bool valid = true;

    valid &= valid_bit_depth();
    valid &= compression_method == compression_method_t::deflate_inflate;
    valid &= filter_method == filter_method_t::adaptive;
    valid &= (interlace_method == interlace_method_t::no || interlace_method == interlace_method_t::adam7);

    return valid;
}

usize file_header_t::samples_per_pixel() const
{
    switch (color_type) {
        case color_type_t::greyscale: return 1;
        case color_type_t::truecolor: return 3;
        case color_type_t::indexed: return 1;
        case color_type_t::greyscale_alpha: return 2;
        case color_type_t::truecolor_alpha: return 4;
    }

    return 0;
}

usize file_header_t::bits_per_pixel() const
{
    return samples_per_pixel() * bit_depth;
}

usize file_header_t::bytes_per_pixel() const
{
    return (samples_per_pixel() * bit_depth + 7) / 8;
}

image_info file_header_t::get_image_info() const
{
    return image_info{static_cast<int32>(width), static_cast<int32>(height), true};
}

bool check_signature(const std::vector<uint8>& data)
{
    constexpr std::array<uint8, signature_length> signature = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};

    if (data.size() < signature.size()) {
        return false;
    }

    for (uint32 i = 0; i < signature.size(); ++i) {
        if (data[i] != signature[i]) {
            return false;
        }
    }

    return true;
}

#pragma endregion

#pragma region pass info

struct pass_info
{
    struct position_t
    {
        usize x;
        usize y;
    };

    struct offset_t
    {
        usize x;
        usize y;
    };

    pass_info(usize w, usize h, usize b, position_t p, offset_t o)
        : width(w), height(h), bytes_per_scanline(b), position(p), offset(o)
    {}

    const usize width;
    const usize height;
    const usize bytes_per_scanline;
    const position_t position;
    const offset_t offset;
};

std::vector<pass_info> get_pass_info(const file_header_t& header)
{
    switch (header.interlace_method) {
        case interlace_method_t::adam7: {
            std::array<usize, pass_count> widths = {
            (header.width + 7) / 8,
            (header.width + 3) / 8,
            (header.width + 3) / 4,
            (header.width + 1) / 4,
            (header.width + 1) / 2,
            (header.width + 0) / 2,
            (header.width + 0) / 1,
            };

            std::vector<pass_info> info = {
            pass_info(widths[0], (header.height + 7) / 8, (widths[0] * header.bits_per_pixel() + 7) / 8, {0, 0}, {8, 8}),
            pass_info(widths[1], (header.height + 7) / 8, (widths[1] * header.bits_per_pixel() + 7) / 8, {4, 0}, {8, 8}),
            pass_info(widths[2], (header.height + 3) / 8, (widths[2] * header.bits_per_pixel() + 7) / 8, {0, 4}, {4, 8}),
            pass_info(widths[3], (header.height + 3) / 4, (widths[3] * header.bits_per_pixel() + 7) / 8, {2, 0}, {4, 4}),
            pass_info(widths[4], (header.height + 1) / 4, (widths[4] * header.bits_per_pixel() + 7) / 8, {0, 2}, {2, 4}),
            pass_info(widths[5], (header.height + 1) / 2, (widths[5] * header.bits_per_pixel() + 7) / 8, {1, 0}, {2, 2}),
            pass_info(widths[6], (header.height + 0) / 2, (widths[6] * header.bits_per_pixel() + 7) / 8, {0, 1}, {1, 2}),
            };

            return info;
        }
        case interlace_method_t::no:
            return {
            pass_info(header.width, header.height, (header.width * header.bits_per_pixel() + 7) / 8, {0, 0}, {1, 1})};
    }

    return std::vector<pass_info>();
}

#pragma endregion

#pragma region filter reconstruction

template <typename In, typename Out>
inline void reconstruct_sub(In first, In last, In a, Out x)
{
    while (first != last) {
        *x++ = static_cast<uint8>((static_cast<int32>(*a++) + *first++) & 0xFF);
    }
}

template <typename In, typename Out>
inline void reconstruct_up(In first, In last, In b, Out x)
{
    while (first != last) {
        *x++ = static_cast<uint8>((static_cast<int32>(*b++) + *first++) & 0xFF);
    }
}

template <typename In, typename Out>
inline void reconstruct_average(In first, In last, In a, In b, Out x)
{
    while (first != last) {
        *x++ = static_cast<uint8>((((static_cast<int32>(*a++) + *b++) >> 1) + *first++) & 0xFF);
    }
}

uint8 paeth_predictor(uint8 a, uint8 b, uint8 c)
{
    const int32 p  = static_cast<uint8>((static_cast<int32>(a) + b - c) & 0xFF);
    const int32 pa = static_cast<uint8>(abs(p - a) & 0xFF);
    const int32 pb = static_cast<uint8>(abs(p - b) & 0xFF);
    const int32 pc = static_cast<uint8>(abs(p - c) & 0xFF);

    if (pa <= pb && pa <= pc) {
        return a;
    } else if (pb <= pc) {
        return b;
    } else {
        return c;
    }
}

template <typename In, typename Out>
inline void reconstruct_peath(In first, In last, In a, In b, In c, Out x)
{
    while (first != last) {
        *x++ = static_cast<uint8>((static_cast<int32>(paeth_predictor(*a++, *b++, *c++)) + *first++) & 0xFF);
    }
}

enum class filter_type_t : uint8
{
    none    = 0,
    sub     = 1,
    up      = 2,
    average = 3,
    peath   = 4
};

std::tuple<std::vector<uint8>::iterator, std::vector<uint8>::iterator> reconstruct_pass(std::vector<uint8>::iterator in,
                                                                                        std::vector<uint8>::iterator out,
                                                                                        const pass_info& pass,
                                                                                        usize bytes_per_pixel)
{
    const usize bytes_in_row = (pass.bytes_per_scanline + bytes_per_pixel);
    std::vector<uint8> res(bytes_in_row * (pass.height + 1), 0);

    auto res_a = next(res.begin(), bytes_in_row);
    auto res_b = next(res.begin(), bytes_per_pixel);
    auto res_c = res.begin();
    auto res_x = next(res.begin(), bytes_in_row + bytes_per_pixel);

    for (usize h = 0; h < pass.height; ++h) {
        const filter_type_t ft = static_cast<filter_type_t>(*in++);

        auto last = next(in, pass.bytes_per_scanline);

        switch (ft) {
            case filter_type_t::none: std::copy(in, last, res_x); break;
            case filter_type_t::sub: reconstruct_sub(in, last, res_a, res_x); break;
            case filter_type_t::up: reconstruct_up(in, last, res_b, res_x); break;
            case filter_type_t::average: reconstruct_average(in, last, res_a, res_b, res_x); break;
            case filter_type_t::peath: reconstruct_peath(in, last, res_a, res_b, res_c, res_x); break;
        }

        advance(res_a, bytes_in_row);
        advance(res_b, bytes_in_row);
        advance(res_c, bytes_in_row);
        advance(res_x, bytes_in_row);
        in = last;
    }

    auto it = next(res.begin(), bytes_in_row + bytes_per_pixel);
    for (usize h = 0; h < pass.height; ++h) {
        auto last = next(it, pass.bytes_per_scanline);

        out = std::copy(it, last, out);

        advance(it, bytes_in_row);
    }

    return std::make_tuple(in, out);
}

std::vector<uint8> reconstruct(const file_header_t& header, std::vector<uint8>&& data)
{
    if (data.empty()) {
        return std::vector<uint8>();
    }

    std::vector<uint8> res(data.size(), 0);

    auto in  = data.begin();
    auto out = res.begin();
    for (const auto& pass : get_pass_info(header)) {
        std::tie(in, out) = reconstruct_pass(in, out, pass, header.bytes_per_pixel());
    }

    return res;
}

#pragma endregion

#pragma region unserialize

template <usize N>
constexpr uint8 sample(usize input)
{
    static_assert(N < 32);
    constexpr usize maxinput  = (1 << N) - 1;
    constexpr usize maxoutput = (1 << 8) - 1;
    return static_cast<uint8>(input * maxoutput / maxinput);
}

template <usize N, usize Size = (1 << N)>
constexpr std::array<uint8, Size> generate_samples()
{
    static_assert(N < 32);
    std::array<uint8, Size> res = {0};

    for (usize input = 0; input < Size; input++) {
        res[input] = sample<N>(input);
    }

    return res;
}

using sample_tuple_t = std::tuple<color_t, std::vector<uint8>::iterator>;

template <color_type_t ColorType, uint8 BitDepth>
inline sample_tuple_t get_color(std::vector<uint8>::iterator in);

template <>
inline sample_tuple_t get_color<color_type_t::greyscale, 8>(std::vector<uint8>::iterator in)
{
    const uint8 c = *in++;
    return std::make_tuple(color_t(c, c, c, 0xFF), in);
}

template <>
inline sample_tuple_t get_color<color_type_t::greyscale, 16>(std::vector<uint8>::iterator in)
{
    const uint8 c = *in++;
    in++;
    return std::make_tuple(color_t(c, c, c, 0xFF), in);
}

template <>
inline sample_tuple_t get_color<color_type_t::truecolor, 8>(std::vector<uint8>::iterator in)
{
    const uint8 r = *in++;
    const uint8 g = *in++;
    const uint8 b = *in++;

    return std::make_tuple(color_t(r, g, b, 0xFF), in);
}

template <>
inline sample_tuple_t get_color<color_type_t::truecolor, 16>(std::vector<uint8>::iterator in)
{
    const uint8 r = *in++;
    in++;
    const uint8 g = *in++;
    in++;
    const uint8 b = *in++;
    in++;

    return std::make_tuple(color_t(r, g, b, 0xFF), in);
}

template <color_type_t ColorType, uint8 BitDepth>
inline std::vector<uint8>::iterator unserialize_pass(std::vector<uint8>::iterator in,
                                                     const pass_info& pass,
                                                     const file_header_t& header,
                                                     std::vector<color_t>& out)
{
    for (usize h = 0; h < pass.height; ++h) {
        usize pos = (header.height - 1 - (pass.position.y + pass.offset.y * h)) * header.width + pass.position.x;
        for (usize w = 0; w < pass.width; ++w) {
            std::tie(out[pos], in) = get_color<ColorType, BitDepth>(in);
            pos += pass.offset.x;
        }
    }

    return in;
}

template <uint8 BitDepth>
inline std::vector<uint8>::iterator unserialize_greyscale_pass(std::vector<uint8>::iterator in,
                                                               const pass_info& pass,
                                                               const file_header_t& header,
                                                               std::vector<color_t>& out)
{
    constexpr auto samples = generate_samples<BitDepth>();
    constexpr usize mask   = (1 << BitDepth) - 1;

    for (usize h = 0; h < pass.height; ++h) {
        usize pos  = (header.height - 1 - (pass.position.y + pass.offset.y * h)) * header.width + pass.position.x;
        uint8 byte = 0;
        for (usize w = 0, i = 0; w < pass.width; ++w, i = (i + BitDepth) % 8) {
            if (i == 0) {
                byte = *in++;
            }
            const uint8 color = samples[(byte >> ((8 - BitDepth) - i)) & mask];
            out[pos]          = color_t(color, color, color, 0xFF);

            pos += pass.offset.x;
        }
    }

    return in;
}

template <typename F>
inline std::vector<color_t> unserialize_impl(const file_header_t& header, std::vector<uint8>&& data, F pass_function)
{
    std::vector<color_t> res(header.width * header.height, color_t(uint32(0xFF0000FF)));

    auto in = data.begin();
    //    for (const auto& pass : get_pass_info(header)) {
    //        in = pass_function(in, pass, header, res);
    //    }

    const auto pass = get_pass_info(header);

    in = pass_function(in, pass[0], header, res);
    in = pass_function(in, pass[1], header, res);
    in = pass_function(in, pass[2], header, res);
    in = pass_function(in, pass[3], header, res);
    in = pass_function(in, pass[4], header, res);
    in = pass_function(in, pass[5], header, res);
    in = pass_function(in, pass[6], header, res);

    return res;
}

inline std::vector<color_t> unserialize_greyscale(const file_header_t& header, std::vector<uint8>&& data)
{
    if (data.empty()) {
        return std::vector<color_t>();
    }

    switch (header.bit_depth) {
        case 1: return unserialize_impl(header, std::move(data), unserialize_greyscale_pass<1>);
        case 2: return unserialize_impl(header, std::move(data), unserialize_greyscale_pass<2>);
        case 4: return unserialize_impl(header, std::move(data), unserialize_greyscale_pass<4>);
        case 8: return unserialize_impl(header, std::move(data), unserialize_pass<color_type_t::greyscale, 8>);
        case 16: return unserialize_impl(header, std::move(data), unserialize_pass<color_type_t::greyscale, 16>);
    }

    return std::vector<color_t>();
}

inline std::vector<color_t> unserialize_truecolor(const file_header_t& header, std::vector<uint8>&& data)
{
    if (data.empty()) {
        return std::vector<color_t>();
    }

    switch (header.bit_depth) {
        case 8: return unserialize_impl(header, std::move(data), unserialize_pass<color_type_t::truecolor, 8>);
        case 16: return unserialize_impl(header, std::move(data), unserialize_pass<color_type_t::truecolor, 16>);
    }

    return std::vector<color_t>();
}

// inline std::vector<color_t> unserialize_indexed(const file_header_t& header, std::vector<uint8>&& data)
//{
//    if (data.empty()) {
//        return std::vector<color_t>();
//    }
//
//    switch (header.bit_depth) {
//        case 1: return unserialize_impl<color_type_t::indexed, 1>(header, std::move(data));
//        case 2: return unserialize_impl<color_type_t::indexed, 2>(header, std::move(data));
//        case 4: return unserialize_impl<color_type_t::indexed, 4>(header, std::move(data));
//        case 8: return unserialize_impl<color_type_t::indexed, 8>(header, std::move(data));
//    }
//
//    return std::vector<color_t>();
//}
//
// inline std::vector<color_t> unserialize_greyscale_alpha(const file_header_t& header, std::vector<uint8>&& data)
//{
//    if (data.empty()) {
//        return std::vector<color_t>();
//    }
//
//    switch (header.bit_depth) {
//        case 8: return unserialize_impl<color_type_t::greyscale_alpha, 8>(header, std::move(data));
//        case 16: return unserialize_impl<color_type_t::greyscale_alpha, 16>(header, std::move(data));
//    }
//
//    return std::vector<color_t>();
//}
//
// inline std::vector<color_t> unserialize_truecolor_alpha(const file_header_t& header, std::vector<uint8>&& data)
//{
//    if (data.empty()) {
//        return std::vector<color_t>();
//    }
//
//    switch (header.bit_depth) {
//        case 8: return unserialize_impl<color_type_t::truecolor_alpha, 8>(header, std::move(data));
//        case 16: return unserialize_impl<color_type_t::truecolor_alpha, 16>(header, std::move(data));
//    }
//
//    return std::vector<color_t>();
//}
//
inline std::vector<color_t> unserialize(const file_header_t& header, std::vector<uint8>&& data)
{
    switch (header.color_type) {
        case color_type_t::greyscale: return unserialize_greyscale(header, std::move(data));
        case color_type_t::truecolor:
            return unserialize_truecolor(header, std::move(data));
            //        case color_type_t::indexed: return unserialize_indexed(header, std::move(data));
            //       case color_type_t::greyscale_alpha: return unserialize_greyscale_alpha(header, std::move(data));
            //      case color_type_t::truecolor_alpha: return unserialize_truecolor_alpha(header, std::move(data));
        default: break;
    }

    return std::vector<color_t>();
}

#pragma endregion

} // namespace

namespace framework::graphics::details::image::png
{
load_result_t load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file) {
        return load_result_t();
    }

    auto signature = read_bytes(file, signature_length);
    if (!check_signature(signature)) {
        return load_result_t();
    }

    file_header_t header = file_header_t::read(file);
    if (!header.valid()) {
        return load_result_t();
    }

    std::vector<uint8> data;
    for (chunk_t chunk = chunk_t::read(file); file && chunk.type != chunk_t::type_t::IEND;
         chunk         = chunk_t::read(file)) {
        if (!chunk.valid() && chunk.is_critical()) {
            return load_result_t();
        }

        switch (chunk.type) {
            case chunk_t::type_t::PLTE: break;
            case chunk_t::type_t::IDAT: {
                data.insert(end(data), begin(chunk.data), end(chunk.data));
            } break;
            case chunk_t::type_t::IEND: break;
            case chunk_t::type_t::cHRM: break;
            case chunk_t::type_t::gAMA: break;
            case chunk_t::type_t::iCCP: break;
            case chunk_t::type_t::sBIT: break;
            case chunk_t::type_t::sRGB: break;
            case chunk_t::type_t::bKGD: break;
            case chunk_t::type_t::hIST: break;
            case chunk_t::type_t::tRNS: break;
            case chunk_t::type_t::pHYs: break;
            case chunk_t::type_t::sPLT: break;
            case chunk_t::type_t::tIME: break;
            case chunk_t::type_t::iTXt: break;
            case chunk_t::type_t::tEXt: break;
            case chunk_t::type_t::zTXt: break;
            default: break;
        }
    }

    std::vector<uint8> recontructed = reconstruct(header, utils::zlib::inflate(data));
    std::vector<color_t> image_data = unserialize(header, std::move(recontructed));

    return std::make_optional(std::make_tuple(header.get_image_info(), std::move(image_data)));
}

bool is_png(const std::string& filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    return check_signature(read_bytes(file, signature_length));
}

} // namespace framework::graphics::details::image::png
