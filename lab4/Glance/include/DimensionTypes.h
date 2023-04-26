#pragma once

// TODO: change postfix to f

struct Size
{
	float width;
	float height;
};

struct Vector2d
{
	float x;
	float y;
};

struct Vector3d
{
	float x;
	float y;
	float z;

	Vector3d const operator+(Vector3d const& v) const
	{
		return { x + v.x, y + v.y, z + v.z };
	}


	Vector3d& operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	float GetLength() const
	{
		return static_cast<float>(sqrt(x * x + y * y + z * z));
	}

	// Нормализуем
	void Normalize()
	{
		float invLength = 1 / GetLength();
		x *= invLength;
		y *= invLength;
		z *= invLength;
	}
};

struct Vector4d
{
	float x;
	float y;
	float z;
	float w;
};