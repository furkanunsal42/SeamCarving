#pragma once

#include <iostream>
#include <type_traits>

template <typename T>
class Vec2 {
public:
	T x = NULL;
	T y = NULL;

	Vec2() :
		x(0.0f), y(0.0f) {}

	Vec2(const T& value) :
		x(value), y(value) {}

	Vec2(const T& x, const T& y) :
		x(x), y(y) {}

	template<typename T2>
	Vec2 operator+(const Vec2<T2>& other) const {
		return Vec2(x + other.x, y + other.y);
	}

	template<typename T2>
	Vec2 operator-(const Vec2<T2>& other) const {
		return Vec2(x - other.x, y - other.y);
	}

	template<typename T2>
	bool operator==(const Vec2<T2>& other) const{
		return x == other.x && y == other.y;
	}

	template<typename T2>
	bool operator!=(const Vec2<T2>& other) const {
		return !operator==(other);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec2> operator*(const NUM& coefficient) const {
		return Vec2(x * coefficient, y * coefficient);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec2> operator/(const NUM& coefficient) const {
		return Vec2(x / coefficient, y / coefficient);
	}

	template<typename T2>
	operator Vec2<T2>() {
		return Vec2<T2>(x, y);
	}

	float length() {
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vec2<T>& other) {
	stream << "Vec2(" << other.x << ", " << other.y << ")";
	return stream;
}


template <typename T>
class Vec3 {
public:
	union {
		T x = NULL;
		T r;
	};
	union {
		T y = NULL;
		T g;
	};
	union {
		T z = NULL;
		T b;
	};

	Vec3() :
		x(0.0f), y(0.0f), z(0.0f) {}

	Vec3(const T& value) :
		x(value), y(value), z(value) {}

	Vec3(const T& x, const T& y, const T& z) :
		x(x), y(y), z(z) {}
	
	template<typename T2>
	Vec3 operator+(const Vec3<T2>& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	template<typename T2>
	Vec3 operator-(const Vec3<T2>& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	template<typename T2>
	bool operator==(const Vec3<T2>& other) const{
		if (x == other.x && y == other.y && z == other.z)
			return true;
		return false;
	}

	template<typename T2>
	bool operator!=(const Vec3<T2>& other) const {
		return !operator==(other);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3> operator*(const NUM& coefficient) const {
		return Vec3(x * coefficient, y * coefficient, z * coefficient);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3> operator/(const NUM& coefficient) const {
		return Vec3(x / coefficient, y / coefficient, z / coefficient);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3> operator+(const NUM& number) const {
		return Vec3(x + number, y + number, z + number);
	}
	
	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3> operator-(const NUM& number) const {
		return Vec3(x - number, y - number, z - number);
	}

	template<typename T2>
	operator Vec3<T2>() {
		return Vec3<T2>(x, y, z);
	}

	float length() {
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
	}
};

template<typename NUM, typename T>
std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3<T>> operator*(NUM num, const Vec3<T>& vec){
	return vec * num;
}

template<typename NUM, typename T>
std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3<T>> operator/(NUM num, const Vec3<T>& vec) {
	return Vec3<T>(num/vec.x, num/vec.y, num/vec.z);
}

template<typename NUM, typename T>
std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3<T>> operator+(NUM num, const Vec3<T>& vec) {
	return vec + num;
}

template<typename NUM, typename T>
std::enable_if_t<std::is_arithmetic_v<NUM>, Vec3<T>> operator-(NUM num, const Vec3<T>& vec) {
	return vec - num;
}

template<typename T>
Vec3<T> operator-(const Vec3<T>& vec) {
	return vec * -1;
}


template <typename T>
class Vec4 {
public:
	T x = NULL;
	T y = NULL;
	T z = NULL;
	T w = NULL;

	Vec4() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	Vec4(const T& value) :
		x(value), y(value), z(value), w(value) {}

	Vec4(const T& x, const T& y, const T& z, const T& w) :
		x(x), y(y), z(z), w(w) {}

	template<typename T2>
	Vec4 operator+(const Vec4<T2>& other) const {
		return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	template<typename T2>
	Vec4 operator-(const Vec4<T2>& other) const {
		return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	template<typename T2>
	bool operator==(const Vec4<T2>& other) {
		if (x == other.x && y == other.y && z == other.z && w == other.w)
			return true;
		return false;
	}

	template<typename T2>
	bool operator!=(const Vec4<T2>& other) {
		return !operator==(other);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec4> operator*(const NUM& coefficient) const {
		return Vec4(x * coefficient, y * coefficient, z * coefficient, w * coefficient);
	}

	template<typename NUM>
	std::enable_if_t<std::is_arithmetic_v<NUM>, Vec4> operator/(const NUM& coefficient) const {
		return Vec4(x / coefficient, y / coefficient, z / coefficient, w / coefficient);
	}

	template<typename T2>
	operator Vec4<T2>() {
		return Vec4<T2>(x, y, z, w);
	}

	float length() {
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2));
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vec4<T>& other) {
	stream << "Vec4(" << other.x << ", " << other.y << ", " << other.z << ", " << other.w << ")";
	return stream;
}

// easier to type namings
typedef Vec2<float> vec2;	// default
typedef Vec2<int8_t> vec2c;
typedef Vec2<int16_t> vec2s;
typedef Vec2<int32_t> vec2i;
typedef Vec2<int64_t> vec2l;
typedef Vec2<float> vec2f;
typedef Vec2<double> vec2d;

typedef Vec2<uint8_t> vec2uc;
typedef Vec2<uint16_t> vec2us;
typedef Vec2<uint32_t> vec2ui;
typedef Vec2<uint64_t> vec2ul;

typedef Vec3<float> vec3;	// default
typedef Vec3<int8_t> vec3c;
typedef Vec3<int16_t> vec3s;
typedef Vec3<int32_t> vec3i;
typedef Vec3<int64_t> vec3l;
typedef Vec3<float> vec3f;
typedef Vec3<double> vec3d;

typedef Vec3<uint8_t> vec3uc;
typedef Vec3<uint16_t> vec3us;
typedef Vec3<uint32_t> vec3ui;
typedef Vec3<uint64_t> vec3ul;

typedef Vec4<float> vec4;	// default
typedef Vec4<int8_t> vec4c;
typedef Vec4<int16_t> vec4s;
typedef Vec4<int32_t> vec4i;
typedef Vec4<int64_t> vec4l;
typedef Vec4<float> vec4f;
typedef Vec4<double> vec4d;

typedef Vec4<uint8_t> vec4uc;
typedef Vec4<uint16_t> vec4us;
typedef Vec4<uint32_t> vec4ui;
typedef Vec4<uint64_t> vec4ul;

template<class T>
std::ostream& operator<<(std::ostream& stream, const Vec3<T>& other) {
	stream << "Vec3(" << (double)other.x << ", " << (double)other.y << ", " << (double)other.z << ")";
	return stream;
}

namespace std {
	template<typename T>
	struct hash<Vec2<T>>
	{
		std::size_t operator()(const Vec2<T>& k) const {
			return hash<T>()(k.x) ^ hash<T>()(k.y);
		}
	};

	template<typename T>
	struct hash<Vec3<T>>
	{
		std::size_t operator()(const Vec3<T>& k) const {
			return hash<T>()(k.x) ^ hash<T>()(k.y) ^ hash<T>()(k.z);
		}
	};

	template<typename T>
	struct hash<Vec4<T>>
	{
		std::size_t operator()(const Vec4<T>& k) const {
			return hash<T>()(k.x) ^ hash<T>()(k.y) ^ hash<T>()(k.z) ^ hash<T>()(k.w);
		}
	};
}