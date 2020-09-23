////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Character to glyph index mapping table
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

namespace
{
struct Format0
{
    static Format0 parse(std::uint32_t offset, const std::vector<std::uint8_t>& data);

    std::uint16_t format   = 0;
    std::uint16_t length   = 0;
    std::uint16_t language = 0;
    std::vector<std::uint8_t> glyph_id_array; // 256 size
};

struct Format4
{
    static Format4 parse(std::uint32_t offset, const std::vector<std::uint8_t>& data);

    std::uint16_t format         = 0;
    std::uint16_t length         = 0;
    std::uint16_t language       = 0;
    std::uint16_t seg_count_x2   = 0;
    std::uint16_t search_range   = 0;
    std::uint16_t entry_selector = 0;
    std::uint16_t range_shift    = 0;
    std::vector<std::uint16_t> end_code; //[segcount]
    std::uint16_t reserved_pad = 0;
    std::vector<std::uint16_t> start_code;      //[segcount]
    std::vector<std::int16_t> id_delta;         //[segcount]
    std::vector<std::uint16_t> id_range_offset; //[segcount]
    std::vector<std::uint16_t> glyph_id_array;
};

struct Format6
{
    static Format6 parse(std::uint32_t offset, const std::vector<std::uint8_t>& data);

    std::uint16_t format      = 0;
    std::uint16_t length      = 0;
    std::uint16_t language    = 0;
    std::uint16_t first_code  = 0;
    std::uint16_t entry_count = 0;
    std::vector<std::uint16_t> glyph_id_array; //[entrycount]
};

GlyphMap::GlyphIndexMap parse_glyphs(const Format0& table);
GlyphMap::GlyphIndexMap parse_glyphs(const Format4& table);
GlyphMap::GlyphIndexMap parse_glyphs(const Format6& table);

GlyphMap::GlyphIndexMap parse_glyphs(const GlyphMap table, const std::vector<std::uint8_t>& data)
{
    constexpr std::uint16_t unicode_engiding_id              = 3;
    constexpr std::array<std::uint16_t, 3> supported_formats = {0, 4, 6};

    auto unicode_platform = [unicode_engiding_id](const EncodingRecord& record) {
        return record.platform_id == PlatformId::Unicode && record.encoding_id == unicode_engiding_id;
    };

    auto it = std::find_if(table.encoding_records.begin(), table.encoding_records.end(), unicode_platform);

    if (it == table.encoding_records.end()) {
        GlyphMap::GlyphIndexMap();
    }

    std::uint16_t format = utils::big_endian_value<std::uint16_t>(data.begin() + it->offset, data.end());

    const bool supported = std::any_of(supported_formats.begin(), supported_formats.end(), [format](std::uint16_t f) {
        return f == format;
    });

    if (!supported) {
        return GlyphMap::GlyphIndexMap();
    }

    switch (format) {
        case 0: return parse_glyphs(Format0::parse(it->offset, data));
        case 4: return parse_glyphs(Format4::parse(it->offset, data));
        case 6: return parse_glyphs(Format6::parse(it->offset, data));
    }

    return GlyphMap::GlyphIndexMap();
}

} // namespace

namespace framework::graphics::details::font
{

CharacterToGlyphIndexMappingTable CharacterToGlyphIndexMappingTable::parse(const std::vector<std::uint8_t>& data)
{
    constexpr size_t record_size = 8;

    CharacterToGlyphIndexMappingTable table;
    table.version    = utils::big_endian_value<std::uint16_t>(data.begin(), data.end());
    table.num_tables = utils::big_endian_value<std::uint16_t>(data.begin() + 2, data.end());

    table.encoding_records.reserve(table.num_tables);

    auto from = std::next(data.begin(), 4);
    for (size_t i = 0; i < table.num_tables; ++i) {

        EncodingRecord record;
        record.platform_id = utils::big_endian_value<PlatformId>(from, data.end());
        record.encoding_id = utils::big_endian_value<std::uint16_t>(from + 2, data.end());
        record.offset      = utils::big_endian_value<std::uint32_t>(from + 4, data.end());

        table.encoding_records.push_back(record);
        std::advance(from, record_size);
    }

    table.glyphs = parse_glyphs(table, data);

    return table;
}

CharacterToGlyphIndexMappingTable::CharToGlyphIndexMap CharacterToGlyphIndexMappingTable::parse_glyphs(
const CharacterToGlyphIndexMappingTable table,
const std::vector<std::uint8_t>& data)
{}

CharacterToGlyphIndexMappingTable::CharToGlyphIndexMap CharacterToGlyphIndexMappingTable::parse_glyphs(
const CharacterToGlyphIndexMappingTable::Format0&)
{
    throw std::runtime_error("Implement this");
}

CharacterToGlyphIndexMappingTable::CharToGlyphIndexMap CharacterToGlyphIndexMappingTable::parse_glyphs(
const CharacterToGlyphIndexMappingTable::Format4&)
{
    throw std::runtime_error("Implement this");
}

CharacterToGlyphIndexMappingTable::CharToGlyphIndexMap CharacterToGlyphIndexMappingTable::parse_glyphs(
const CharacterToGlyphIndexMappingTable::Format6&)
{
    throw std::runtime_error("Implement this");
}

CharacterToGlyphIndexMappingTable::Format0 CharacterToGlyphIndexMappingTable::Format0::parse(
std::uint32_t offset,
const std::vector<std::uint8_t>& data)
{
    constexpr size_t glyphs_count = 256;

    auto from = std::next(data.begin(), offset);

    Format0 table;
    table.format   = utils::big_endian_value<std::uint16_t>(from, data.end());
    table.length   = utils::big_endian_value<std::uint16_t>(from + 2, data.end());
    table.language = utils::big_endian_value<std::uint16_t>(from + 4, data.end());
    table.glyph_id_array.reserve(glyphs_count);

    std::advance(from, 6);
    for (size_t i = 0; i < glyphs_count; ++i) {
        table.glyph_id_array.push_back(utils::big_endian_value<std::uint8_t>(from + i, data.end()));
    }

    return table;
}

CharacterToGlyphIndexMappingTable::Format4 CharacterToGlyphIndexMappingTable::Format4::parse(
std::uint32_t offset,
const std::vector<std::uint8_t>& data)
{
    auto from = std::next(data.begin(), offset);

    Format4 table;
    table.format         = utils::big_endian_value<std::uint16_t>(from, data.end());
    table.length         = utils::big_endian_value<std::uint16_t>(from + 2, data.end());
    table.language       = utils::big_endian_value<std::uint16_t>(from + 4, data.end());
    table.seg_count_x2   = utils::big_endian_value<std::uint16_t>(from + 6, data.end());
    table.search_range   = utils::big_endian_value<std::uint16_t>(from + 8, data.end());
    table.entry_selector = utils::big_endian_value<std::uint16_t>(from + 10, data.end());
    table.range_shift    = utils::big_endian_value<std::uint16_t>(from + 12, data.end());

    std::advance(from, 14);

    const size_t seg_count = table.seg_count_x2 / 2;

    table.end_code.reserve(seg_count);
    for (size_t i = 0; i < seg_count; ++i) {
        table.end_code.push_back(utils::big_endian_value<std::uint16_t>(from, data.end()));
        std::advance(from, 2);
    }

    table.reserved_pad = utils::big_endian_value<std::uint16_t>(from, data.end());
    std::advance(from, 2);

    table.start_code.reserve(seg_count);
    for (size_t i = 0; i < seg_count; ++i) {
        table.start_code.push_back(utils::big_endian_value<std::uint16_t>(from, data.end()));
        std::advance(from, 2);
    }

    table.id_delta.reserve(seg_count);
    for (size_t i = 0; i < seg_count; ++i) {
        table.id_delta.push_back(utils::big_endian_value<std::int16_t>(from, data.end()));
        std::advance(from, 2);
    }

    table.id_range_offset.reserve(seg_count);
    for (size_t i = 0; i < seg_count; ++i) {
        table.id_range_offset.push_back(utils::big_endian_value<std::uint16_t>(from, data.end()));
        std::advance(from, 2);
    }

    size_t dist = std::distance(from, std::next(data.begin(), offset + table.length));

    size_t count = dist / 2;

    size_t count2 = 0;
    for (size_t i = 0; i < seg_count; ++i) {
        size_t c = table.end_code[i] - table.start_code[i];
        count2 += c;
    }

    if (count || count2) {
    }

    return table;
}

CharacterToGlyphIndexMappingTable::Format6 CharacterToGlyphIndexMappingTable::Format6::parse(
std::uint32_t,
const std::vector<std::uint8_t>&)
{
    return Format6();
}

} // namespace framework::graphics::details::font