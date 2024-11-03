#include "doctest/doctest.h"
#include "../include/vec3d.h"

using namespace spacely;

TEST_CASE("Vec3d Default Constructor") {
    Vec3d v;
    CHECK(v.x() == 0);
    CHECK(v.y() == 0);
    CHECK(v.z() == 0);
}

TEST_CASE("Vec3d Constructor") {
    Vec3d v(1, 2, 3);
    CHECK(v.x() == 1);
    CHECK(v.y() == 2);
    CHECK(v.z() == 3);
}

TEST_CASE("Vec3d Accessors") {
    Vec3d v(1, 2, 3);
    CHECK(v.x() == 1);
    CHECK(v.y() == 2);
    CHECK(v.z() == 3);
}

TEST_CASE("Vec3d Negation") {
    Vec3d v(1, 2, 3);
    Vec3d neg = -v;
    CHECK(neg.x() == -1);
    CHECK(neg.y() == -2);
    CHECK(neg.z() == -3);
}   

TEST_CASE("Vec3d Addition") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    Vec3d sum = v1 + v2;
    CHECK(sum.x() == 5);
    CHECK(sum.y() == 7);
    CHECK(sum.z() == 9);
}

TEST_CASE("Vec3d Subtraction") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    Vec3d diff = v1 - v2;
    CHECK(diff.x() == -3);
    CHECK(diff.y() == -3);
    CHECK(diff.z() == -3);
}

TEST_CASE("Vec3d Scalar Multiplication") {
    Vec3d v(1, 2, 3);
    Vec3d scaled = v * 2;
    CHECK(scaled.x() == 2);
    CHECK(scaled.y() == 4);
    CHECK(scaled.z() == 6);
}

TEST_CASE("Vec3d Scalar Division") {
    Vec3d v(1, 2, 3);
    Vec3d scaled = v / 2;
    CHECK(scaled.x() == 0.5);
    CHECK(scaled.y() == 1);
    CHECK(scaled.z() == 1.5);
}

TEST_CASE("Vec3d Dot Product") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    double dot = Vec3d::dot(v1, v2);
    CHECK(dot == 32);
}

TEST_CASE("Vec3d Cross Product") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    Vec3d cross = Vec3d::cross(v1, v2);
    CHECK(cross.x() == -3);
    CHECK(cross.y() == 6);
    CHECK(cross.z() == -3);
}

TEST_CASE("Vec3d Min") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    Vec3d min = Vec3d::min(v1, v2);
    CHECK(min.x() == 1);
    CHECK(min.y() == 2);
    CHECK(min.z() == 3);
}

TEST_CASE("Vec3d Max") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    Vec3d max = Vec3d::max(v1, v2);
    CHECK(max.x() == 4);
    CHECK(max.y() == 5);
    CHECK(max.z() == 6);
}

TEST_CASE("Vec3d Distance") {
    Vec3d v1(1, 2, 3);
    Vec3d v2(4, 5, 6);
    double dist = Vec3d::distance(v1, v2);
    CHECK(dist == std::sqrt(3*3 + 3*3 + 3*3));
}

TEST_CASE("Vec3d Length") {
    Vec3d v(3, 4, 5);
    CHECK(v.length() == std::sqrt(3*3 + 4*4 + 5*5));
}   

TEST_CASE("Vec3d Length Squared") {
    Vec3d v(3, 4, 5);
    CHECK(v.length_squared() == 3*3 + 4*4 + 5*5);
}

TEST_CASE("Vec3d Near Zero") {
    Vec3d v(1e-8, 2e-8, 3e-8);
    CHECK(v.near_zero());
}

TEST_CASE("Vec3d Unit Vector") {
    Vec3d v(1, 2, 3);
    Vec3d unit = Vec3d::unit_vector(v);
    CHECK(unit.length() == 1);
}

TEST_CASE("Mat3x3 Identity") {
    mat3x3 id = Vec3d::mat3x3_identity();
    CHECK(id[0][0] == 1);
    CHECK(id[1][1] == 1);
    CHECK(id[2][2] == 1);
}

TEST_CASE("Mat3x3 Transpose") {
    mat3x3 m{{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}}};
    mat3x3 trans = Vec3d::mat3x3_transpose(m);
    CHECK(trans[0][0] == 1);
}

TEST_CASE("Mat3x3 Determinant") {
    mat3x3 m{{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}}};
    CHECK(Vec3d::mat3x3_det(m) == 0);
}   

TEST_CASE("Vec3d Mat3x3 Inverse") {
    mat3x3 m{{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}}};
    mat3x3 inv = Vec3d::mat3x3_inverse(m);
    CHECK(Vec3d::mat3x3_det(inv) == 1);
}

TEST_CASE("Vec3d Mat3x3 Multiplication") {
    mat3x3 m1 {{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}}};
    mat3x3 m2 {{
        {9, 8, 7},
        {6, 5, 4},  
        {3, 2, 1}}};
    mat3x3 mult = Vec3d::mat3x3_mult(m1, m2);
    CHECK(Vec3d::mat3x3_det(mult) == 1);
}
