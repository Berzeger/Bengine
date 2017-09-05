#pragma once

#include "maths.h"

namespace bengine
{
	namespace maths
	{
		struct Matrix4
		{
			union
			{
				float elements[4 * 4];
				Vector4 columns[4];
			};
			
			Matrix4();
			Matrix4(float diagonal);

			static Matrix4 identity();
			Matrix4& multiply(const Matrix4& other);
			friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
			Matrix4& operator*=(const Matrix4& other);

			Vector3 multiply(const Vector3& other) const;
			friend Vector3 operator*(const Matrix4& left, const Vector3& right);

			Vector4 multiply(const Vector4& other) const;
			friend Vector4 operator*(const Matrix4& left, const Vector4& right);

			static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix4 perspective(float fov, float aspectRatio, float near, float far);

			static Matrix4 translation(const Vector3& translation);
			static Matrix4 rotation(float angle, const Vector3& axis);
			static Matrix4 scale(const Vector3& scale);
		};
	}
}
