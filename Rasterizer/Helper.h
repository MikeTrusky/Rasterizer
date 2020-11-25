#pragma once
#include <vector>
#include <iostream>

#define PI 3.1415926

struct float3
{
	float x, y, z;
	float3() = default;
	float3(float x, float y, float z) : x(x), y(y), z(z) {};
	float3(float value) : x(value), y(value), z(value) {};
};

#pragma region float3 - funkcje
inline float3 &normalize(float3 &vec) {
	float length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length > 0)
	{
		float invertedLength = 1 / length;
		vec.x *= invertedLength;
		vec.y *= invertedLength;
		vec.z *= invertedLength;
	}
	return vec;
}
inline float3 cross(float3 &vecA, float3 &vecB) { return float3(vecA.y * vecB.z - vecA.z * vecB.y, vecA.z * vecB.x - vecA.x * vecB.z, vecA.x * vecB.y - vecA.y * vecB.x); }
inline float dot(float3 &vecA, float3 &vecB) { return vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z; }
inline float3 operator + (float3 &vecA, float3 &vecB) { return float3(vecA.x + vecB.x, vecA.y + vecB.y, vecA.z + vecB.z); }
inline float3 operator - (float3 &vecA, float3 &vecB) { return float3(vecA.x - vecB.x, vecA.y - vecB.y, vecA.z - vecB.z); }
inline float3 operator * (float3 &vec, float value) { return float3(vec.x * value, vec.y * value, vec.z * value); }
inline std::ostream& operator << (std::ostream& os, const float3& vec) { os << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << "\n"; return os; }
#pragma endregion

struct float4
{
	float x, y, z, w;
	float4() = default;
	float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
	float operator[] (int i) 
	{
		switch (i)
		{
		case 0:
			return x;
			break;
		case 1:
			return y;
			break;
		case 2:
			return z;
			break;
		case 3:
			return w;
			break;
		}
	}
};

#pragma region float4 - Funkcje
inline float4 operator + (float4 &vecA, float4 &vecB) { return float4(vecA.x + vecB.x, vecA.y + vecB.y, vecA.z + vecB.z, vecA.w + vecB.w); }
inline float4 operator - (float4 &vecA, float4 &vecB) { return float4(vecA.x - vecB.x, vecA.y - vecB.y, vecA.z - vecB.z, vecA.w - vecB.w); }
inline float4 operator * (float4 &vec, float value) { return float4(vec.x * value, vec.y * value, vec.z * value, vec.w * value); }
#pragma endregion

struct float4x4
{
	float4 matrix[4] = { {float4(0,0,0,0)}, {float4(0,0,0,0)}, {float4(0,0,0,0)}, {float4(0,0,0,0)} };
	float4x4() = default;
	float4x4(float4 x, float4 y, float4 z, float4 w)
	{
		matrix[0] = x;
		matrix[1] = y;
		matrix[2] = z;
		matrix[3] = w;
	}
	float4 operator[] (int i) { return matrix[i]; }
};

#pragma region float4x4 - Funkcje
inline float4x4 mul(float4x4 matrixA, float4x4 matrixB)
{
	float4x4 matrixNew;
	for (int i = 0; i < 4; ++i)
	{
		matrixNew.matrix[i] = float4(matrixA[i][0] * matrixB[0][0] + matrixA[i][1] * matrixB[1][0] + matrixA[i][2] * matrixB[2][0] + matrixA[i][3] * matrixB[3][0],
							  matrixA[i][0] * matrixB[0][1] + matrixA[i][1] * matrixB[1][1] + matrixA[i][2] * matrixB[2][1] + matrixA[i][3] * matrixB[3][1],
							  matrixA[i][0] * matrixB[0][2] + matrixA[i][1] * matrixB[1][2] + matrixA[i][2] * matrixB[2][2] + matrixA[i][3] * matrixB[3][2],
							  matrixA[i][0] * matrixB[0][3] + matrixA[i][1] * matrixB[1][3] + matrixA[i][2] * matrixB[2][3] + matrixA[i][3] * matrixB[3][3]);
	}
	return matrixNew;
}

inline float4 mul(float4x4 matrix, float4 value)
{
	float values[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			values[i] += value[j] * matrix[i][j];
		}
	}
	float4 valueNew(values[0], values[1], values[2], values[3]);
	return valueNew;
}
#pragma endregion