/// @file
/// @brief Contains common math constants.
/// @author Fedorov Alexey
/// @date 06.05.2017

// =============================================================================
// MIT License
//
// Copyright (c) 2017-2018 Fedorov Alexey
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

#ifndef FRAMEWORK_MATH_DETAILS
#error You should include math/math.hpp instead of constants.hpp
#endif

#ifndef FRAMEWORK_MATH_DETAILS_CONSTANTS_HPP
#define FRAMEWORK_MATH_DETAILS_CONSTANTS_HPP

#include <common/types.hpp>

namespace framework
{
namespace math
{
/// @addtogroup math_predefined_constants
/// @{

/// @brief Predefined constant
/// @{
constexpr float64 deg_to_rad = 0.017453292519943295769236907684886127134428718885417254560;
constexpr float64 rad_to_deg = 57.29577951308232087679815481410517033240547246656432154916;

constexpr float64 pi                = 3.141592653589793238462643383279502884197169399375105820974;
constexpr float64 tau               = 6.283185307179586476925286766559005768394338798750211641949;
constexpr float64 half_pi           = 1.570796326794896619231321691639751442098584699687552910487;
constexpr float64 three_over_two_pi = 4.712388980384689857693965074919254326295754099062658731462;
constexpr float64 quarter_pi        = 0.785398163397448309615660845819875721049292349843776455243;
constexpr float64 one_over_pi       = 0.318309886183790671537767526745028724068919291480912897495;
constexpr float64 one_over_two_pi   = 0.159154943091895335768883763372514362034459645740456448747;
constexpr float64 two_over_pi       = 0.636619772367581343075535053490057448137838582961825794990;
constexpr float64 four_over_pi      = 1.273239544735162686151070106980114896275677165923651589981;
constexpr float64 two_over_root_pi  = 1.128379167095512573896158903121545171688101258657997713688;
constexpr float64 one_over_root_two = 0.707106781186547524400844362104849039284835937688474036588;
constexpr float64 root_half_pi      = 1.253314137315500251207882642405522626503493370304969158314;
constexpr float64 root_two_pi       = 2.506628274631000502415765284811045253006986740609938316629;
constexpr float64 root_pi           = 1.772453850905516027298167483341145182797549456122387128213;

constexpr float64 root_two   = 1.414213562373095048801688724209698078569671875376948073176;
constexpr float64 root_three = 1.732050807568877293527446341505872366942805253810380628055;
constexpr float64 root_five  = 2.236067977499789696409173668731276235440618359611525724270;

constexpr float64 ln_two       = 0.693147180559945309417232121458176568075500134360255254120;
constexpr float64 ln_ten       = 2.302585092994045684017991454684364207601101488628772976033;
constexpr float64 ln_ln_two    = -0.36651292058166432701243915823266946945426344783710526305;
constexpr float64 root_ln_four = 1.177410022515474691011569326459699637747385689385820538522;

constexpr float64 third        = 0.333333333333333333333333333333333333333333333333333333333;
constexpr float64 two_thirds   = 0.666666666666666666666666666666666666666666666666666666666;
constexpr float64 golden_ratio = 1.618033988749894848204586834365638117720309179805762862135;

constexpr float64 e     = 2.718281828459045235360287471352662497757247093699959574966;
constexpr float64 euler = 0.577215664901532860606512090082402431042159335939923598805;
/// @}

/// @}

} // namespace math

} // namespace framework

#endif
