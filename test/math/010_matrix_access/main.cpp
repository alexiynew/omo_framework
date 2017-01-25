#include <math/math.hpp>
#include <unit_test/test.hpp>

using namespace framework::math;

class matrix_access_test : public test::suite
{
public:
    matrix_access_test()
        : suite("matrix_access_test")
    {
        add_test([this]() { access_operator(); }, "access_operator");
        add_test([this]() { column_function(); }, "column_function");
        add_test([this]() { row_function(); }, "row_function");
        add_test([this]() { data_function(); }, "data_function");

        // clang-format off
        matrix44 = {
            0, 1, 2, 3,
            0, 1, 2, 3,
            0, 1, 2, 3,
            0, 1, 2, 3
        };

        matrix43 = {
            0, 1, 2,
            0, 1, 2,
            0, 1, 2,
            0, 1, 2
        };

        matrix42 = {
            0, 1,
            0, 1,
            0, 1,
            0, 1
        };

        matrix34 = {
            0, 1, 2, 3,
            0, 1, 2, 3,
            0, 1, 2, 3
        };

        matrix33 = {
            0, 1, 2,
            0, 1, 2,
            0, 1, 2
        };

        matrix32 = {
            0, 1,
            0, 1,
            0, 1
        };

        matrix24 = {
            0, 1, 2, 3,
            0, 1, 2, 3
        };

        matrix23 = {
            0, 1, 2,
            0, 1, 2
        };

        matrix22 = {
            0, 1,
            0, 1
        };
        // clang-format on
    }

private:
    void access_operator()
    {
        // clang-format off
        TEST_ASSERT(matrix44[0] == Vector4F(0, 1, 2, 3) &&
                    matrix44[1] == Vector4F(0, 1, 2, 3) &&
                    matrix44[2] == Vector4F(0, 1, 2, 3) &&
                    matrix44[3] == Vector4F(0, 1, 2, 3),
                    "Matrix 4x4 access operator failed.");

        TEST_ASSERT(matrix43[0] == Vector3F(0, 1, 2) &&
                    matrix43[1] == Vector3F(0, 1, 2) &&
                    matrix43[2] == Vector3F(0, 1, 2) &&
                    matrix43[3] == Vector3F(0, 1, 2),
                    "Matrix 4x3 access operator failed.");

        TEST_ASSERT(matrix42[0] == Vector2F(0, 1) &&
                    matrix42[1] == Vector2F(0, 1) &&
                    matrix42[2] == Vector2F(0, 1) &&
                    matrix42[3] == Vector2F(0, 1),
                    "Matrix 4x2 access operator failed.");

        TEST_ASSERT(matrix34[0] == Vector4F(0, 1, 2, 3) &&
                    matrix34[1] == Vector4F(0, 1, 2, 3) &&
                    matrix34[2] == Vector4F(0, 1, 2, 3),
                    "Matrix 3x4 access operator failed.");

        TEST_ASSERT(matrix33[0] == Vector3F(0, 1, 2) &&
                    matrix33[1] == Vector3F(0, 1, 2) &&
                    matrix33[2] == Vector3F(0, 1, 2),
                    "Matrix 3x3 access operator failed.");

        TEST_ASSERT(matrix32[0] == Vector2F(0, 1) &&
                    matrix32[1] == Vector2F(0, 1) &&
                    matrix32[2] == Vector2F(0, 1),
                    "Matrix 3x2 access operator failed.");

        TEST_ASSERT(matrix24[0] == Vector4F(0, 1, 2, 3) &&
                    matrix24[1] == Vector4F(0, 1, 2, 3),
                    "Matrix 2x4 access operator failed.");

        TEST_ASSERT(matrix23[0] == Vector3F(0, 1, 2) &&
                    matrix23[1] == Vector3F(0, 1, 2),
                    "Matrix 2x3 access operator failed.");

        TEST_ASSERT(matrix22[0] == Vector2F(0, 1) &&
                    matrix22[1] == Vector2F(0, 1),
                    "Matrix 2x2 access operator failed.");
        // clang-format on
    }

    void column_function()
    {
        // clang-format off
        TEST_ASSERT(matrix44.column(0) == Vector4F(0, 1, 2, 3) &&
                    matrix44.column(1) == Vector4F(0, 1, 2, 3) &&
                    matrix44.column(2) == Vector4F(0, 1, 2, 3) &&
                    matrix44.column(3) == Vector4F(0, 1, 2, 3),
                    "Matrix 4x4 column function failed.");

        TEST_ASSERT(matrix43.column(0) == Vector3F(0, 1, 2) &&
                    matrix43.column(1) == Vector3F(0, 1, 2) &&
                    matrix43.column(2) == Vector3F(0, 1, 2) &&
                    matrix43.column(3) == Vector3F(0, 1, 2),
                    "Matrix 4x3 column function failed.");

        TEST_ASSERT(matrix42.column(0) == Vector2F(0, 1) &&
                    matrix42.column(1) == Vector2F(0, 1) &&
                    matrix42.column(2) == Vector2F(0, 1) &&
                    matrix42.column(3) == Vector2F(0, 1),
                    "Matrix 4x2 column function failed.");

        TEST_ASSERT(matrix34.column(0) == Vector4F(0, 1, 2, 3) &&
                    matrix34.column(1) == Vector4F(0, 1, 2, 3) &&
                    matrix34.column(2) == Vector4F(0, 1, 2, 3),
                    "Matrix 3x4 column function failed.");

        TEST_ASSERT(matrix33.column(0) == Vector3F(0, 1, 2) &&
                    matrix33.column(1) == Vector3F(0, 1, 2) &&
                    matrix33.column(2) == Vector3F(0, 1, 2),
                    "Matrix 3x3 column function failed.");

        TEST_ASSERT(matrix32.column(0) == Vector2F(0, 1) &&
                    matrix32.column(1) == Vector2F(0, 1) &&
                    matrix32.column(2) == Vector2F(0, 1),
                    "Matrix 3x2 column function failed.");

        TEST_ASSERT(matrix24.column(0) == Vector4F(0, 1, 2, 3) &&
                    matrix24.column(1) == Vector4F(0, 1, 2, 3),
                    "Matrix 2x4 column function failed.");

        TEST_ASSERT(matrix23.column(0) == Vector3F(0, 1, 2) &&
                    matrix23.column(1) == Vector3F(0, 1, 2),
                    "Matrix 2x3 column function failed.");

        TEST_ASSERT(matrix22.column(0) == Vector2F(0, 1) &&
                    matrix22.column(1) == Vector2F(0, 1),
                    "Matrix 2x2 column function failed.");
        // clang-format on
    }

    void row_function()
    {
        // clang-format off
        TEST_ASSERT(matrix44.row(0) == Vector4F(0, 0, 0, 0) &&
                    matrix44.row(1) == Vector4F(1, 1, 1, 1) &&
                    matrix44.row(2) == Vector4F(2, 2, 2, 2) &&
                    matrix44.row(3) == Vector4F(3, 3, 3, 3),
                    "Matrix 4x4 row function failed.");

        TEST_ASSERT(matrix43.row(0) == Vector4F(0, 0, 0, 0) &&
                    matrix43.row(1) == Vector4F(1, 1, 1, 1) &&
                    matrix43.row(2) == Vector4F(2, 2, 2, 2),
                    "Matrix 4x3 row function failed.");

        TEST_ASSERT(matrix42.row(0) == Vector4F(0, 0, 0, 0) &&
                    matrix42.row(1) == Vector4F(1, 1, 1, 1),
                    "Matrix 4x2 row function failed.");

        TEST_ASSERT(matrix34.row(0) == Vector3F(0, 0, 0) &&
                    matrix34.row(1) == Vector3F(1, 1, 1) &&
                    matrix34.row(2) == Vector3F(2, 2, 2) &&
                    matrix34.row(3) == Vector3F(3, 3, 3),
                    "Matrix 3x4 row function failed.");

        TEST_ASSERT(matrix33.row(0) == Vector3F(0, 0, 0) &&
                    matrix33.row(1) == Vector3F(1, 1, 1) &&
                    matrix33.row(2) == Vector3F(2, 2, 2),
                    "Matrix 3x3 row function failed.");

        TEST_ASSERT(matrix32.row(0) == Vector3F(0, 0, 0) &&
                    matrix32.row(1) == Vector3F(1, 1, 1),
                    "Matrix 3x2 row function failed.");

        TEST_ASSERT(matrix24.row(0) == Vector2F(0, 0) &&
                    matrix24.row(1) == Vector2F(1, 1) &&
                    matrix24.row(2) == Vector2F(2, 2) &&
                    matrix24.row(3) == Vector2F(3, 3),
                    "Matrix 2x4 row function failed.");

        TEST_ASSERT(matrix23.row(0) == Vector2F(0, 0) &&
                    matrix23.row(1) == Vector2F(1, 1) &&
                    matrix23.row(2) == Vector2F(2, 2),
                    "Matrix 2x3 row function failed.");


        TEST_ASSERT(matrix22.row(0) == Vector2F(0, 0) &&
                    matrix22.row(1) == Vector2F(1, 1),
                    "Matrix 2x2 row function failed.");
        // clang-format on
    }

    void data_function()
    {
        float* p44 = matrix44.data();
        float* p34 = matrix34.data();
        float* p24 = matrix24.data();
        float* p43 = matrix43.data();
        float* p33 = matrix33.data();
        float* p23 = matrix23.data();
        float* p42 = matrix42.data();
        float* p32 = matrix32.data();
        float* p22 = matrix22.data();

        // clang-format off
        TEST_ASSERT(p44[0]  == 0.0f &&  p44[1] == 1.0f && p44[2]  == 2.0f && p44[3]  == 3.0f &&
                    p44[4]  == 0.0f &&  p44[5] == 1.0f && p44[6]  == 2.0f && p44[7]  == 3.0f &&
                    p44[8]  == 0.0f &&  p44[9] == 1.0f && p44[10] == 2.0f && p44[11] == 3.0f &&
                    p44[12] == 0.0f && p44[13] == 1.0f && p44[14] == 2.0f && p44[15] == 3.0f,
                    "Matrix4x4 pointer data access failed.");

        TEST_ASSERT(p43[0] == 0.0f && p43[1]  == 1.0f && p43[2]  == 2.0f &&
                    p43[3] == 0.0f && p43[4]  == 1.0f && p43[5]  == 2.0f &&
                    p43[6] == 0.0f && p43[7]  == 1.0f && p43[8]  == 2.0f &&
                    p43[9] == 0.0f && p43[10] == 1.0f && p43[11] == 2.0f,
                    "Matrix4x3 pointer data access failed.");

        TEST_ASSERT(p42[0] == 0.0f && p42[1] == 1.0f &&
                    p42[2] == 0.0f && p42[3] == 1.0f &&
                    p42[4] == 0.0f && p42[5] == 1.0f &&
                    p42[6] == 0.0f && p42[7] == 1.0f,
                    "Matrix4x2 pointer data access failed.");

        TEST_ASSERT(p34[0] == 0.0f && p34[1] == 1.0f && p34[2]  == 2.0f && p34[3]  == 3.0f &&
                    p34[4] == 0.0f && p34[5] == 1.0f && p34[6]  == 2.0f && p34[7]  == 3.0f &&
                    p34[8] == 0.0f && p34[9] == 1.0f && p34[10] == 2.0f && p34[11] == 3.0f,
                    "Matrix3x4 pointer data access failed.");

        TEST_ASSERT(p33[0] == 0.0f && p33[1] == 1.0f && p33[2] == 2.0f &&
                    p33[3] == 0.0f && p33[4] == 1.0f && p33[5] == 2.0f &&
                    p33[6] == 0.0f && p33[7] == 1.0f && p33[8] == 2.0f,
                    "Matrix3x3 pointer data access failed.");

        TEST_ASSERT(p32[0] == 0.0f && p32[1] == 1.0f &&
                    p32[2] == 0.0f && p32[3] == 1.0f &&
                    p32[4] == 0.0f && p32[5] == 1.0f,
                    "Matrix3x2 pointer data access failed.");

        TEST_ASSERT(p24[0] == 0.0f && p24[1] == 1.0f && p24[2] == 2.0f && p24[3] == 3.0f &&
                    p24[4] == 0.0f && p24[5] == 1.0f && p24[6] == 2.0f && p24[7] == 3.0f,
                    "Matrix2x4 pointer data access failed.");

        TEST_ASSERT(p23[0] == 0.0f && p23[1] == 1.0f && p23[2] == 2.0f &&
                    p23[3] == 0.0f && p23[4] == 1.0f && p23[5] == 2.0f,
                    "Matrix2x3 pointer data access failed.");

        TEST_ASSERT(p22[0] == 0.0f && p22[1] == 1.0f &&
                    p22[2] == 0.0f && p22[3] == 1.0f,
                    "Matrix2x2 pointer data access failed.");
        // clang-format on
    }

    Matrix4x4F matrix44;
    Matrix4x3F matrix43;
    Matrix4x2F matrix42;

    Matrix3x4F matrix34;
    Matrix3x3F matrix33;
    Matrix3x2F matrix32;

    Matrix2x4F matrix24;
    Matrix2x3F matrix23;
    Matrix2x2F matrix22;
};

int main()
{
    return run_tests(matrix_access_test());
}
