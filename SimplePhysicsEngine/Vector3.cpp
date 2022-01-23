#include "Vector3.h"

namespace utils {
    Vector3::Vector3(float xc, float yc, float zc) : x{ xc }, y{ yc }, z{ zc } {}
    Vector3 Vector3::operator+(Vector3 v) const {
        float nx = x + v.x;
        float ny = y + v.y;
        float nz = z + v.z;

        return Vector3(nx, ny, nz);
    }

    Vector3 Vector3::operator-() const
    {
        return *this * -1;
    }

    Vector3 Vector3::operator-(Vector3 v) const {
        float nx = x - v.x;
        float ny = y - v.y;
        float nz = z - v.z;

        return Vector3(nx, ny, nz);
    }

    Vector3 Vector3::operator*(float i) const {
        float nx = x * i;
        float ny = y * i;
        float nz = z * i;

        return Vector3(nx, ny, nz);
    }

    Vector3 Vector3::operator/(float i) const {
        if (i == 0)
            throw 0;

        float nx = x / i;
        float ny = y / i;
        float nz = z / i;

        return Vector3(nx, ny, nz);
    }

    Vector3 Vector3::Lerp(Vector3 depart, Vector3 dest, float rate)
    {
        return depart * rate + dest * (1.0f - rate);
    }

    float Vector3::GetVectorSize() const {
        float powDist = x * x + y * y + z * z;
        return sqrt(powDist);
    }

    float Vector3::GetMagnitude() const
    {
        return sqrtf(x*x+y*y+z*z);
    }

    float Vector3::GetDistance(Vector3 v1, Vector3 v2) {
        return sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
    }

    Vector3 Vector3::Normalize(Vector3& v) {
        float vSize = v.GetVectorSize();
        return Vector3(v.x / vSize, v.y / vSize, v.z / vSize);
    }

    float Vector3::DotProduct(const Vector3& v1, const Vector3& v2)
    {
        float nx = v1.x * v2.x;
        float ny = v1.y * v2.y;
        float nz = v1.z * v2.z;

        return nx + ny + nz;
    }

    Vector3 Vector3::CrossProduct(const Vector3& v1, const Vector3& v2)
    {
        float nx = (v1.y * v2.z) - (v1.z * v2.y);
        float ny = (v1.z * v2.x) - (v1.x * v2.z);
        float nz = (v1.x * v2.y) - (v1.y * v2.x);

        return Vector3(nx, ny, nz);
    }

    Vector3& Vector3::operator+=(const Vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& Vector3::operator/=(float i)
    {
        x /= i;
        y /= i;
        z /= i;

        return *this;
    }

    Vector3& Vector3::operator*=(float i)
    {
        x *= i;
        y *= i;
        z *= i;

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Vector3& v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
}