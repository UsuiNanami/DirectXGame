#include "MyMath.h"
#include <cmath>

using namespace KamataEngine;

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			result.m[y][x] = m1.m[y][0] * m2.m[0][x] + m1.m[y][1] * m2.m[1][x] + m1.m[y][2] * m2.m[2][x] + m1.m[y][3] * m2.m[3][x];
		}
	}

	return result;
}

// アフィン変換行列を作る関数  (アフィン行列はアフィン変換をどんな順序で何度行っても4列目の成分は必ず(0,0,0,1)となる)
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translation) {

	// スケール行列 S
	Matrix4x4 matScale = {scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1};

	// 回転行列（X）Rx
	float cx = cosf(rotation.x);
	float sx = sinf(rotation.x);
	Matrix4x4 matRotX = {1, 0, 0, 0, 0, cx, sx, 0, 0, -sx, cx, 0, 0, 0, 0, 1};

	// 回転行列（Y）Ry
	float cy = cosf(rotation.y);
	float sy = sinf(rotation.y);
	Matrix4x4 matRotY = {cy, 0, -sy, 0, 0, 1, 0, 0, sy, 0, cy, 0, 0, 0, 0, 1};

	// 回転行列（Z）Rz
	float cz = cosf(rotation.z);
	float sz = sinf(rotation.z);
	Matrix4x4 matRotZ = {cz, sz, 0, 0, -sz, cz, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	// 平行移動行列 T
	Matrix4x4 matTrans = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, translation.x, translation.y, translation.z, 1};

	// 合成（S → R → T）W
	Matrix4x4 matWorld = Multiply(matScale, matRotX);
	matWorld = Multiply(matWorld, matRotY);
	matWorld = Multiply(matWorld, matRotZ);
	matWorld = Multiply(matWorld, matTrans);

	return matWorld;
}
