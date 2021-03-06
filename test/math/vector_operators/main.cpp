
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

using ::framework::float32;
using ::framework::float64;
using ::framework::int32;

using ::framework::math::vector2b;
using ::framework::math::vector2f;
using ::framework::math::vector2i;
using ::framework::math::vector2u;
using ::framework::math::vector3b;
using ::framework::math::vector3d;
using ::framework::math::vector3f;
using ::framework::math::vector4b;
using ::framework::math::vector4d;
using ::framework::math::vector4i;

using ::framework::math::almost_equal;

class vector_operators_test : public framework::unit_test::suite
{
public:
    vector_operators_test() : suite("vector_operators_test")
    {
        add_test([this]() { assign_operator(); }, "assign_operator");
        add_test([this]() { access_operator(); }, "access_operator");
        add_test([this]() { data_function(); }, "data_function");
        add_test([this]() { unary_minus_operator(); }, "unary_minus_operator");
        add_test([this]() { unary_plus_operator(); }, "unary_plus_operator");
        add_test([this]() { add_assign_operator(); }, "add_assign_operator");
        add_test([this]() { subtract_assign_operator(); }, "subtract_assign_operator");
        add_test([this]() { multiplies_assign_operator(); }, "multiplies_assign_operator");
        add_test([this]() { divides_assign_operator(); }, "divides_assign_operator");
        add_test([this]() { add_operator(); }, "add_operator");
        add_test([this]() { subtract_operator(); }, "subtract_operator");
        add_test([this]() { multiply_operator(); }, "multiply_operator");
        add_test([this]() { divide_operator(); }, "divide_operator");
        add_test([this]() { equality_operator(); }, "equality_operator");
        add_test([this]() { inequality_operator(); }, "inequality_operator");
    }

private:
    void assign_operator()
    {
        const vector4d v4d(1.1, 2.2, 3.3, 4);
        const vector3f v3f(5.5f, 6.6f, 7.7f);
        const vector2i v2i(1, 2);

        vector4d v4d_result;
        vector3f v3f_result;
        vector2i v2i_result;

        vector4i v4i_result;
        vector3d v3d_result;
        vector2f v2f_result;

        v4d_result = v4d;
        v3f_result = v3f;
        v2i_result = v2i;

        v4i_result = static_cast<vector4i>(v4d);
        v3d_result = static_cast<vector3d>(v3f);
        v2f_result = static_cast<vector2f>(v2i);

        TEST_ASSERT(v4i_result == vector4i(1, 2, 3, 4), "Assign to vector4i failed.");
        TEST_ASSERT(v4d_result == vector4d(1.1, 2.2, 3.3, 4), "Assign to vector4d failed.");

        TEST_ASSERT(v3d_result == vector3d(float64(5.5f), float64(6.6f), float64(7.7f)), "Assign to vector3d failed.");
        TEST_ASSERT(v3f_result == vector3f(5.5f, 6.6f, 7.7f), "Assign to vector3f failed.");

        TEST_ASSERT(v2f_result == vector2f(1, 2), "Assign to vector2f failed.");
        TEST_ASSERT(v2i_result == vector2i(1, 2), "Assign to vector2i failed.");
    }

    void access_operator()
    {
        const vector4d v4d(1.1, 2.2, 3.3, 4.4);
        const vector3f v3f(5.5f, 6.6f, 7.7f);
        const vector2i v2i(1, 2);

        // clang-format off
        TEST_ASSERT(almost_equal(v4d[0], 1.1) &&
                    almost_equal(v4d[1], 2.2) &&
                    almost_equal(v4d[2], 3.3) &&
                    almost_equal(v4d[3], 4.4),
                    "Access to vector4d filed.");

        TEST_ASSERT(almost_equal(v3f[0], 5.5f) &&
                    almost_equal(v3f[1], 6.6f) &&
                    almost_equal(v3f[2], 7.7f),
                    "Access to vector3f failed.");

        TEST_ASSERT(v2i[0] == 1 && v2i[1] == 2, "Access to vector2i failed.");
        // clang-format on
    }

    void data_function()
    {
        const vector4d v4d(1.1, 2.2, 3.3, 4.4);
        const vector3f v3f(5.5f, 6.6f, 7.7f);
        const vector2i v2i(1, 2);

        const float64* float64_pointer = v4d.data();
        const float32* float32_pointer = v3f.data();
        const int32* int_pointer       = v2i.data();

        // clang-format off
        TEST_ASSERT(almost_equal(float64_pointer[0], 1.1) &&
                    almost_equal(float64_pointer[1], 2.2) &&
                    almost_equal(float64_pointer[2], 3.3) &&
                    almost_equal(float64_pointer[3], 4.4),
                    "Access to data of vector4d filed.");

        TEST_ASSERT(almost_equal(float32_pointer[0], 5.5f) &&
                    almost_equal(float32_pointer[1], 6.6f) &&
                    almost_equal(float32_pointer[2], 7.7f),
                    "Access to data of vector3f failed.");

        TEST_ASSERT(int_pointer[0] == 1 && int_pointer[1] == 2, "Access to data of vector2i failed.");
        // clang-format on
    }

    void unary_minus_operator()
    {
        const vector4d v4d(1.4);
        const vector3f v3f(2.4f);
        const vector2i v2i(3);

        TEST_ASSERT(-v4d == vector4d(-1.4, -1.4, -1.4, -1.4), "Inverse of vector4d failed.");
        TEST_ASSERT(-v3f == vector3f(-2.4f, -2.4f, -2.4f), "Inverse of vector3f failed.");
        TEST_ASSERT(-v2i == vector2i(-3, -3), "Inverse of vector2i failed.");
    }

    void unary_plus_operator()
    {
        const vector4d v4d(1.4);
        const vector3f v3f(2.4f);
        const vector2i v2i(3);

        TEST_ASSERT(+v4d == vector4d(1.4, 1.4, 1.4, 1.4), "Unary add of vector4d failed.");
        TEST_ASSERT(+v3f == vector3f(2.4f, 2.4f, 2.4f), "Unary add of vector3f failed.");
        TEST_ASSERT(+v2i == vector2i(3, 3), "Unary add of vector2i failed.");
    }

    void add_assign_operator()
    {
        vector4d v4d(1.0);
        vector3f v3f(1.0f);
        vector2i v2i(1);

        v4d += vector4d(1.0);
        TEST_ASSERT(v4d == vector4d(2.0), "Add_assign operator failed.");

        v4d += 1.0;
        TEST_ASSERT(v4d == vector4d(3.0), "Add_assign operator failed.");

        v3f += vector3f(1.0f);
        TEST_ASSERT(v3f == vector3f(2.0f), "Add_assign operator failed.");

        v3f += 1.0f;
        TEST_ASSERT(v3f == vector3f(3.0f), "Add_assign operator failed.");

        v2i += vector2i(1);
        TEST_ASSERT(v2i == vector2i(2), "Add_assign operator failed.");

        v2i += 1;
        TEST_ASSERT(v2i == vector2i(3), "Add_assign operator failed.");
    }

    void subtract_assign_operator()
    {
        vector4d v4d(3.0);
        vector3f v3f(3.0f);
        vector2i v2i(3);

        v4d -= vector4d(1.0);
        TEST_ASSERT(v4d == vector4d(2.0), "Subtract_assign operator failed.");

        v4d -= 1.0;
        TEST_ASSERT(v4d == vector4d(1.0), "Subtract_assign operator failed.");

        v3f -= vector3f(1.0f);
        TEST_ASSERT(v3f == vector3f(2.0f), "Subtract_assign operator failed.");

        v3f -= 1.0f;
        TEST_ASSERT(v3f == vector3f(1.0f), "Subtract_assign operator failed.");

        v2i -= vector2i(1);
        TEST_ASSERT(v2i == vector2i(2), "Subtract_assign operator failed.");

        v2i -= 1;
        TEST_ASSERT(v2i == vector2i(1), "Subtract_assign operator failed.");
    }

    void multiplies_assign_operator()
    {
        vector4d v4d(1.0);
        vector3f v3f(1.0f);
        vector2i v2i(1);

        v4d *= vector4d(2.0);
        TEST_ASSERT(v4d == vector4d(2.0), "Multiplies_assign operator failed.");

        v4d *= 2.0;
        TEST_ASSERT(v4d == vector4d(4.0), "Multiplies_assign operator failed.");

        v3f *= vector3f(2.0f);
        TEST_ASSERT(v3f == vector3f(2.0f), "Multiplies_assign operator failed.");

        v3f *= 2.0f;
        TEST_ASSERT(v3f == vector3f(4.0f), "Multiplies_assign operator failed.");

        v2i *= vector2i(2);
        TEST_ASSERT(v2i == vector2i(2), "Multiplies_assign operator failed.");

        v2i *= 2;
        TEST_ASSERT(v2i == vector2i(4), "Multiplies_assign operator failed.");
    }

    void divides_assign_operator()
    {
        vector4d v4d(4.0);
        vector3f v3f(4.0f);
        vector2i v2i(4);

        v4d /= vector4d(2.0);
        TEST_ASSERT(v4d == vector4d(2.0), "Divides_assign operator failed.");

        v4d /= 2.0;
        TEST_ASSERT(v4d == vector4d(1.0), "Divides_assign operator failed.");

        v3f /= vector3f(2.0f);
        TEST_ASSERT(v3f == vector3f(2.0f), "Divides_assign operator failed.");

        v3f /= 2.0f;
        TEST_ASSERT(v3f == vector3f(1.0f), "Divides_assign operator failed.");

        v2i /= vector2i(2);
        TEST_ASSERT(v2i == vector2i(2), "Divides_assign operator failed.");

        v2i /= 2;
        TEST_ASSERT(v2i == vector2i(1), "Divides_assign operator failed.");
    }

    void add_operator()
    {
        const vector4d v4d(1.0);
        const vector3f v3f(1.0f);
        const vector2i v2i(1);

        TEST_ASSERT(v4d + v4d == vector4d(2.0), "Add operator failed.");
        TEST_ASSERT(v4d + 1.0 == vector4d(2.0), "Add operator failed.");
        TEST_ASSERT(1.0 + v4d == vector4d(2.0), "Add operator failed.");

        TEST_ASSERT(v3f + v3f == vector3f(2.0f), "Add operator failed.");
        TEST_ASSERT(v3f + 1.0f == vector3f(2.0f), "Add operator failed.");
        TEST_ASSERT(1.0f + v3f == vector3f(2.0f), "Add operator failed.");

        TEST_ASSERT(v2i + v2i == vector2i(2), "Add operator failed.");
        TEST_ASSERT(v2i + 1 == vector2i(2), "Add operator failed.");
        TEST_ASSERT(1 + v2i == vector2i(2), "Add operator failed.");
    }

    void subtract_operator()
    {
        const vector4d v4d(1.0);
        const vector3f v3f(1.0f);
        const vector2i v2i(1);

        TEST_ASSERT(v4d - v4d == vector4d(0.0), "Subtract operator failed.");
        TEST_ASSERT(v4d - 1.0 == vector4d(0.0), "Subtract operator failed.");
        TEST_ASSERT(1.0 - v4d == vector4d(0.0), "Subtract operator failed.");

        TEST_ASSERT(v3f - v3f == vector3f(0.0f), "Subtract operator failed.");
        TEST_ASSERT(v3f - 1.0f == vector3f(0.0f), "Subtract operator failed.");
        TEST_ASSERT(1.0f - v3f == vector3f(0.0f), "Subtract operator failed.");

        TEST_ASSERT(v2i - v2i == vector2i(0), "Subtract operator failed.");
        TEST_ASSERT(v2i - 1 == vector2i(0), "Subtract operator failed.");
        TEST_ASSERT(1 - v2i == vector2i(0), "Subtract operator failed.");
    }

    void multiply_operator()
    {
        const vector4d v4d(2.0);
        const vector3f v3f(2.0f);
        const vector2i v2i(2);

        TEST_ASSERT(v4d * v4d == vector4d(4.0), "Multiply operator failed.");
        TEST_ASSERT(v4d * 2.0 == vector4d(4.0), "Multiply operator failed.");
        TEST_ASSERT(2.0 * v4d == vector4d(4.0), "Multiply operator failed.");

        TEST_ASSERT(v3f * v3f == vector3f(4.0f), "Multiply operator failed.");
        TEST_ASSERT(v3f * 2.0f == vector3f(4.0f), "Multiply operator failed.");
        TEST_ASSERT(2.0f * v3f == vector3f(4.0f), "Multiply operator failed.");

        TEST_ASSERT(v2i * v2i == vector2i(4), "Multiply operator failed.");
        TEST_ASSERT(v2i * 2 == vector2i(4), "Multiply operator failed.");
        TEST_ASSERT(2 * v2i == vector2i(4), "Multiply operator failed.");
    }

    void divide_operator()
    {
        const vector4d v4d(2.0);
        const vector3f v3f(2.0f);
        const vector2i v2i(2);

        TEST_ASSERT(v4d / v4d == vector4d(1.0), "Divide operator failed.");
        TEST_ASSERT(v4d / 2.0 == vector4d(1.0), "Divide operator failed.");
        TEST_ASSERT(2.0 / v4d == vector4d(1.0), "Divide operator failed.");

        TEST_ASSERT(v3f / v3f == vector3f(1.0f), "Divide operator failed.");
        TEST_ASSERT(v3f / 2.0f == vector3f(1.0f), "Divide operator failed.");
        TEST_ASSERT(2.0f / v3f == vector3f(1.0f), "Divide operator failed.");

        TEST_ASSERT(v2i / v2i == vector2i(1), "Divide operator failed.");
        TEST_ASSERT(v2i / 2 == vector2i(1), "Divide operator failed.");
        TEST_ASSERT(2 / v2i == vector2i(1), "Divide operator failed.");
    }

    void equality_operator()
    {
        const vector4d v4d(1.1, 2.2, 3.3, 4);
        const vector3f v3f(5.5f, 6.6f, 7.7f);
        const vector2i v2i(1, -2);
        const vector2u v2u(1, 2);

        TEST_ASSERT(v4d == v4d, "Equality operator for vector4d failed.");
        TEST_ASSERT(v3f == v3f, "Equality operator for vector3f failed.");
        TEST_ASSERT(v2i == v2i, "Equality operator for vector2i failed.");
        TEST_ASSERT(v2u == v2u, "Equality operator for vector2u failed.");
    }

    void inequality_operator()
    {
        const vector4d v4d(1.1, 2.2, 3.3, 4);
        const vector3f v3f(5.5f, 6.6f, 7.7f);
        const vector2i v2i(1, -2);
        const vector2u v2u(1, 2);

        TEST_ASSERT(vector4d(1.1, 2.2, 3.3, 4.4) != v4d, "Inequality operator for vector4d failed.");
        TEST_ASSERT(!(vector3f(5.5f, 6.6f, 7.7f) != v3f), "Inequality operator for vector3f failed.");
        TEST_ASSERT(vector2i(-2, 1) != v2i, "Inequality operator for vector2i failed.");
        TEST_ASSERT(!(vector2u(1, 2) != v2u), "Inequality operator for vector2u failed.");
    }
};

class bool_vector_operators_test : public framework::unit_test::suite
{
public:
    bool_vector_operators_test() : suite("bool_vector_operators_test")
    {
        add_test([this]() { assign_operator(); }, "assign_operator");
        add_test([this]() { access_operator(); }, "access_operator");
        add_test([this]() { data_access(); }, "data_access");
    }

private:
    void assign_operator()
    {
        const vector4b v4b(true, false, true, false);
        const vector3b v3b(true, false, true);
        const vector2b v2b(true, false);

        const vector4d v4d(-1.1, 0.0, 3.3, 0.0);
        const vector3f v3f(5.5f, 0.0, -7.7f);
        const vector2i v2i(1, 0);

        vector4b v4b_result;
        vector3b v3b_result;
        vector2b v2b_result;

        v4b_result = v4b;
        v3b_result = v3b;
        v2b_result = v2b;

        TEST_ASSERT(v4b_result == v4b, "Assign to vector4b failed.");
        TEST_ASSERT(v3b_result == v3b, "Assign to vector3b failed.");
        TEST_ASSERT(v2b_result == v2b, "Assign to vector2b failed.");

        v4b_result = static_cast<vector4b>(v4d);
        v3b_result = static_cast<vector3b>(v3f);
        v2b_result = static_cast<vector2b>(v2i);

        TEST_ASSERT(v4b_result == v4b, "Assign to vector4b failed.");
        TEST_ASSERT(v3b_result == v3b, "Assign to vector3b failed.");
        TEST_ASSERT(v2b_result == v2b, "Assign to vector2b failed.");
    }

    void access_operator()
    {
        const vector4b v4b(true, false, true, false);
        const vector3b v3b(true, false, true);
        const vector2b v2b(true, false);

        TEST_ASSERT(v4b[0] && !v4b[1] && v4b[2] && !v4b[3], "Access to vector4b failed.");
        TEST_ASSERT(v3b[0] && !v3b[1] && v3b[2], "Access to vector3b failed.");
        TEST_ASSERT(v2b[0] && !v2b[1], "Access to vector2b failed.");
    }

    void data_access()
    {
        const vector4b v4b(true, false, true, false);
        const vector3b v3b(true, false, true);
        const vector2b v2b(true, false);

        const bool* bool4 = v4b.data();
        const bool* bool3 = v3b.data();
        const bool* bool2 = v2b.data();

        TEST_ASSERT(bool4[0] && !bool4[1] && bool4[2] && !bool4[3], "Access to data of vector4b failed.");
        TEST_ASSERT(bool3[0] && !bool3[1] && bool3[2], "Access to data of vector3b failed.");
        TEST_ASSERT(bool2[0] && !bool2[1], "Access to data of vector2b failed.");
    }
};

int main()
{
    return run_tests(vector_operators_test(), bool_vector_operators_test());
}
