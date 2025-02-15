#pragma once

#define USE_GLM

#ifdef USE_GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif // USE_GLM

#include "ImportExportDLL.h"

template <typename T>
struct rot
{
	T yaw, pitch, roll;
};

using DRot = rot<double>;


constexpr double PI = 3.14159265358979323846;

template <typename T>
struct alignas(16) vec3
{
	T x, y, z;
};

template <typename T>
class mat4
{
public:
	mat4()
	{
		_data.fill(0.f);
	}
	explicit mat4(const T val)
	{
		_data.fill(val);
	}

	T& operator()(int _x, int _y)
	{
		return _data[_x + 4 * _y];
	}

	std::array<T, 16> _data;
};

#ifdef USE_GLM
using FVec2 = glm::vec2;
using FVec3 = glm::vec3;
using FMat4 = glm::mat4;
#else // USE_GLM
using FVec3 = vec3<float>;
using FMat4 = mat4<float>;
#endif // USE_GLM

struct Transform
{
	FVec3 position;
	FVec3 size;
};

template <typename T>
struct VecType
{};

template <typename T>
struct VecType<vec3<T>>
{
	using value = T;
};

template <typename T>
struct VecType<mat4<T>>
{
	using value = T;
};

template <typename T>
using Vec3Type = typename VecType<T>::value;

template <typename T>
using Mat4Type = typename VecType<T>::value;


template <typename T>
struct Cross
{
	T operator()(const T& A, const T& B)
	{
		return { A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x };
	}
};

template <typename T>
struct Normalize
{
	T operator()(const T& A)
	{
		Vec3Type<T> length = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
		return T{ A.x / length, A.y / length, A.z / length };
	}
};

template <typename T>
struct Dot
{
	Vec3Type<T> operator()(const T& A, const T& B)
	{
		return A.x * B.x + A.y * B.x + A.z * B.z;
	}
};

template <typename T>
struct Radian
{
	T operator()(const T degree)
	{
		return degree * (PI /180.0);
	}
};

template <typename T>
struct Perspective
{
	using type = typename Mat4Type<T>;
	T operator()(type fov, type aspect, type near, type far)
	{
		type const tanHalfFovy = tan(fov / static_cast<type>(2));

		T Result{0.f};

		Result(0, 0) = static_cast<type>(1) / (aspect * tanHalfFovy);
		Result(1, 1) = static_cast<type>(1) / (tanHalfFovy);
		Result(2, 2) = -(far + near) / (far - near);
		Result(2, 3) = -static_cast<type>(1);
		Result(3, 2) = -(static_cast<type>(2) * far * near) / (far - near);
		return Result;
	}
};

template <typename T>
struct LookAt
{
	template <typename SubT>
	T operator()(const SubT& position, const SubT& forward, const SubT& upVector)
	{
		Cross<SubT> cross;
		Normalize<SubT> normalize;
		Dot<SubT> dot;
		SubT right = normalize(cross(upVector, forward));
		SubT new_up = cross(forward, right);

		T viewMatrix;
		viewMatrix(0, 0) = right.x;
		viewMatrix(1, 0) = right.y;
		viewMatrix(2, 0) = right.z;
		viewMatrix(0, 1) = new_up.x;
		viewMatrix(1, 1) = new_up.y;
		viewMatrix(2, 1) = new_up.z;
		viewMatrix(0, 2) = -forward.x;
		viewMatrix(1, 2) = -forward.y;
		viewMatrix(2, 2) = -forward.z;
		viewMatrix(3, 0) = -dot(right, position);
		viewMatrix(3, 1) = -dot(new_up, position);
		viewMatrix(3, 2) = dot(forward, position);
		return viewMatrix;
	}
};

namespace LeafMath
{
	template <typename T>
	inline decltype(auto) GetData(const T& val)
	{
		return &*val._data.begin();
	}

#ifdef USE_GLM
	template <>
	inline decltype(auto) GetData<FMat4>(const FMat4& val)
	{
		return glm::value_ptr(val);
	}

	template <>
	inline decltype(auto) GetData<FVec3>(const FVec3& val)
	{
		return glm::value_ptr(val);
	}
#else
	template <>
	inline decltype(auto) GetData<FVec3>(const FVec3& val)
	{
		return &val.x;
	}
#endif // USE_GLM

}

#ifdef USE_GLM

template <>
struct Cross<FVec3>
{
	FVec3 operator()(const FVec3& A, const FVec3& B)
	{
		return glm::cross(A, B);
	}
};

template <>
struct Normalize<FVec3>
{
	FVec3 operator()(const FVec3& A)
	{
		if (glm::length(A) > 1)
		{
			return glm::normalize(A);
		}
		return A;
	}
};

template <>
struct Dot<FVec3>
{
	float operator()(const FVec3& A, const FVec3& B)
	{
		return glm::dot(A, B);
	}
};

template <>
struct Radian<float>
{
	float operator()(const float degree)
	{
		return glm::radians(degree);
	}
};

template <>
struct Perspective<FMat4>
{
	template <typename type>
	FMat4 operator()(type fov, type aspect, type near, type far)
	{
		return glm::perspective(fov, aspect, near, far);
	}
};

template <>
struct LookAt<FMat4>
{
	template <typename SubT>
	FMat4 operator()(const SubT& position, const SubT& forward, const SubT& upVector)
	{
		return glm::lookAt(position, position + forward, upVector);
	}
};

#endif // USE_GLM

