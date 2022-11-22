#pragma once

#include <DirectXMath.h>
#include <initializer_list>
#include <array>
#include <cmath>
#include <cassert>
#include <limits>
static inline void operator+= (DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    auto itr{ v2.begin() };
    v1.x += *itr;
    itr++;
    v1.y += *itr;
    itr++;
    v1.z += *itr;
}

static inline void operator-= (DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    auto itr{ v2.begin() };
    v1.x -= *itr;
    itr++;
    v1.y -= *itr;
    itr++;
    v1.z -= *itr;
}

static inline void operator/= (DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    auto itr{ v2.begin() };
    v1.x /= *itr;
    itr++;
    v1.y /= *itr;
    itr++;
    v1.z /= *itr;
}

static inline void operator*= (DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    auto itr{ v2.begin() };
    v1.x *= *itr;
    itr++;
    v1.y *= *itr;
    itr++;
    v1.z *= *itr;
}

static inline void operator%= (DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    auto itr{ v2.begin() };
    v1.x = ::fmodf(v1.x, *itr);
    itr++;
    v1.y = ::fmodf(v1.y, *itr);
    itr++;
    v1.z = ::fmodf(v1.z, *itr);
}

_NODISCARD static inline auto operator+ (const DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    DirectX::XMFLOAT3 temp{ v1 };
    auto itr{ v2.begin() };

    temp.x += *itr;
    itr++;
    temp.y += *itr;
    itr++;
    temp.z += *itr;

    return temp;
}

_NODISCARD static inline auto operator- (const DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    DirectX::XMFLOAT3 temp{ v1 };
    auto itr{ v2.begin() };

    temp.x -= *itr;
    itr++;
    temp.y -= *itr;
    itr++;
    temp.z -= *itr;

    return temp;
}

_NODISCARD static inline auto operator* (const DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    DirectX::XMFLOAT3 temp{ v1 };
    auto itr{ v2.begin() };

    temp.x *= *itr;
    itr++;
    temp.y *= *itr;
    itr++;
    temp.z *= *itr;

    return temp;
}

_NODISCARD static inline auto operator/ (const DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    DirectX::XMFLOAT3 temp{ v1 };
    auto itr{ v2.begin() };

    temp.x /= *itr;
    itr++;
    temp.y /= *itr;
    itr++;
    temp.z /= *itr;

    return temp;
}

_NODISCARD static inline auto operator% (const DirectX::XMFLOAT3& v1, const std::initializer_list<float>& v2)
{
    assert(v2.size() == 3u && "不正なイニシャライザーリスト");

    DirectX::XMFLOAT3 temp{ v1 };
    auto itr{ v2.begin() };

    temp.x = ::fmodf(v1.x, *itr);
    itr++;
    temp.y = ::fmodf(v1.y, *itr);
    itr++;
    temp.z = ::fmodf(v1.z, *itr);

    return temp;
}

static inline void operator+= (DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
}

static inline void operator-= (DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
}

static inline void operator*= (DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    v1.x *= v2.x;
    v1.y *= v2.y;
    v1.z *= v2.z;
}

static inline void operator/= (DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    v1.x /= v2.x;
    v1.y /= v2.y;
    v1.z /= v2.z;
}

static inline void operator%= (DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    v1.x = ::fmodf(v1.x, v2.x);
    v1.y = ::fmodf(v1.y, v2.y);
    v1.z = ::fmodf(v1.z, v2.z);
}

_NODISCARD static inline constexpr auto operator+ (const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    return DirectX::XMFLOAT3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

_NODISCARD static inline constexpr auto operator- (const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    return DirectX::XMFLOAT3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

_NODISCARD static inline constexpr auto operator* (const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    return DirectX::XMFLOAT3{ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

_NODISCARD static inline constexpr auto operator/ (const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    return DirectX::XMFLOAT3{ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
}

_NODISCARD static inline constexpr auto operator% (const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2)
{
    return DirectX::XMFLOAT3{ ::fmodf(v1.x, v2.x), ::fmodf(v1.y, v2.y), ::fmodf(v1.z, v2.z) };
}

static inline void operator+= (DirectX::XMFLOAT3& v1, const float num)
{
    v1.x += num;
    v1.y += num;
    v1.z += num;
}

static inline void operator-= (DirectX::XMFLOAT3& v1, const float num)
{
    v1.x -= num;
    v1.y -= num;
    v1.z -= num;
}

static inline void operator/= (DirectX::XMFLOAT3& v1, const float num)
{
    v1.x /= num;
    v1.y /= num;
    v1.z /= num;
}

static inline void operator*= (DirectX::XMFLOAT3& v1, const float num)
{
    v1.x *= num;
    v1.y *= num;
    v1.z *= num;
}

static inline void operator%= (DirectX::XMFLOAT3& v1, const float num)
{
    v1.x = ::fmodf(v1.x, num);
    v1.y = ::fmodf(v1.y, num);
    v1.z = ::fmodf(v1.z, num);
}

_NODISCARD static inline constexpr auto operator+ (const DirectX::XMFLOAT3& v1, const float num)
{
    return DirectX::XMFLOAT3{ v1.x + num, v1.y + num, v1.z + num };
}

_NODISCARD static inline constexpr auto operator- (const DirectX::XMFLOAT3& v1, const float num)
{
    return DirectX::XMFLOAT3{ v1.x - num, v1.y - num, v1.z - num };
}

_NODISCARD static inline constexpr auto operator* (const DirectX::XMFLOAT3& v1, const float num)
{
    return DirectX::XMFLOAT3{ v1.x * num, v1.y * num, v1.z * num };
}

_NODISCARD static inline constexpr auto operator% (const DirectX::XMFLOAT3& v1, const float num)
{
    return DirectX::XMFLOAT3{ ::fmodf(v1.x, num), ::fmodf(v1.y, num), ::fmodf(v1.z, num) };
}

_NODISCARD static inline constexpr auto operator/ (const DirectX::XMFLOAT3& v1, const float num)
{
    return DirectX::XMFLOAT3{ v1.x / num, v1.y / num, v1.z / num };
}

_NODISCARD static inline constexpr auto operator+ (const float num, DirectX::XMFLOAT3& v1)
{
    return DirectX::XMFLOAT3{ num + v1.x, num - v1.y, num - v1.z };
}

_NODISCARD static inline constexpr auto operator- (const float num, DirectX::XMFLOAT3& v1)
{
    return DirectX::XMFLOAT3{ num - v1.x, num - v1.y, num - v1.z };
}

_NODISCARD static inline constexpr auto operator* (const float num, DirectX::XMFLOAT3& v1)
{
    return DirectX::XMFLOAT3{ num * v1.x, num - v1.y, num - v1.z };
}

_NODISCARD static inline constexpr auto operator/ (const float num, DirectX::XMFLOAT3& v1)
{
    return DirectX::XMFLOAT3{ num / v1.x, num / v1.y, num / v1.z };
}

_NODISCARD static inline constexpr auto operator% (const float num, DirectX::XMFLOAT3& v1)
{
    return DirectX::XMFLOAT3{ fmodf(num, v1.x), fmodf(num, v1.y), fmodf(num, v1.z) };
}
