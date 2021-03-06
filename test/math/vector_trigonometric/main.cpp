
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

#include <math/math.hpp>
#include <unit_test/suite.hpp>

using ::framework::math::vector3d;
using ::framework::math::vector4d;

using ::framework::math::pi;
using ::framework::math::quarter_pi;
using ::framework::math::tau;

class trigonometric_function_tests : public framework::unit_test::suite
{
public:
    trigonometric_function_tests() : suite("trigonometric_function_tests")
    {
        add_test([this]() { radians_function(); }, "radians_function");
        add_test([this]() { degrees_function(); }, "degrees_function");
        add_test([this]() { sin_function(); }, "sin_function");
        add_test([this]() { cos_function(); }, "cos_function");
        add_test([this]() { tan_function(); }, "tan_function");
        add_test([this]() { asin_function(); }, "asin_function");
        add_test([this]() { acos_function(); }, "acos_function");
        add_test([this]() { atan_function(); }, "atan_function");
        add_test([this]() { sinh_function(); }, "sinh_function");
        add_test([this]() { cosh_function(); }, "cosh_function");
        add_test([this]() { tanh_function(); }, "tanh_function");
        add_test([this]() { asinh_function(); }, "asinh_function");
        add_test([this]() { acosh_function(); }, "acosh_function");
        add_test([this]() { atanh_function(); }, "atanh_function");

        v4d = {180.0, 360.0, 90.0, 45.0};
        v3d = {45.0, 60.0, 180.0};
    }

private:
    void radians_function()
    {
        TEST_ASSERT(radians(v4d) == vector4d(pi, tau, pi / 2, pi / 4), "Radians function failed.");
    }

    void degrees_function()
    {
        TEST_ASSERT(degrees(radians(v4d)) == v4d, "Degrees function failed.");
    }

    void sin_function()
    {
        const vector4d sin_vector(sin(pi), sin(tau), sin(pi / 2), sin(pi / 4));
        TEST_ASSERT(almost_equal(sin(radians(v4d)), sin_vector), "Sin function failed.");
    }

    void cos_function()
    {
        const vector4d cos_vector(cos(pi), cos(tau), cos(pi / 2), cos(pi / 4));
        TEST_ASSERT(almost_equal(cos(radians(v4d)), cos_vector), "Cos function failed.");
    }

    void tan_function()
    {
        TEST_ASSERT(almost_equal(tan(radians(v3d)), sin(radians(v3d)) / cos(radians(v3d)), 1), "Tan function failed.");
    }

    void asin_function()
    {
        const vector4d asin_vector(asin(sin(pi)), asin(sin(tau)), pi / 2, pi / 4);
        TEST_ASSERT(almost_equal(asin(sin(radians(v4d))), asin_vector, 1), "Asin function failed.");
    }

    void acos_function()
    {
        TEST_ASSERT(almost_equal(acos(cos(radians(v4d))), vector4d(pi, 0, pi / 2, pi / 4)), "Acos function failed.");
    }

    void atan_function()
    {
        const vector3d result1 = atan(tan(radians(v3d)));
        const vector3d result2 = atan(sin(radians(v3d)), cos(radians(v3d)));

        TEST_ASSERT(almost_equal(result1, vector3d(quarter_pi, pi / 3, atan(tan(pi)))), "Atan from tan failed.");
        TEST_ASSERT(almost_equal(result2, vector3d(quarter_pi, pi / 3, pi), 1), "Atan from sin and cos failed.");
    }

    void sinh_function()
    {
        const vector3d sinh_vector(0.86867096148600953, 1.2493670505239751, 11.548739357257748);

        TEST_ASSERT(almost_equal(sinh(radians(v3d)), sinh_vector, 2), "Sinh function failed.");
    }

    void cosh_function()
    {
        const vector3d cosh_vector(1.3246090892520057, 1.6002868577023861, 11.591953275521519);
        TEST_ASSERT(almost_equal(cosh(radians(v3d)), cosh_vector, 1), "Cosh function failed.");
    }

    void tanh_function()
    {
        const vector3d tanh_vector = sinh(radians(v3d)) / cosh(radians(v3d));
        TEST_ASSERT(almost_equal(tanh(radians(v3d)), tanh_vector, 1), "Tanh function failed.");
    }

    void asinh_function()
    {
        TEST_ASSERT(almost_equal(asinh(sinh(radians(v3d))), vector3d(pi / 4, pi / 3, pi), 1), "Asinh function failed.");
    }

    void acosh_function()
    {
        TEST_ASSERT(almost_equal(acosh(cosh(radians(v3d))), vector3d(pi / 4, pi / 3, pi), 1), "Acosh function failed.");
    }

    void atanh_function()
    {
        TEST_ASSERT(almost_equal(atanh(tanh(radians(v3d))), vector3d(pi / 4, pi / 3, pi), 4), "Atanh function failed.");
    }

    vector4d v4d;
    vector3d v3d;
};

int main()
{
    return run_tests(trigonometric_function_tests());
}
