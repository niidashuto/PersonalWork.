#pragma once
#include "vector3.h"

struct Matrix4
{
	float m[4][4];
};

//単位行列を求める
Matrix4 identity();

//拡大縮小行列の設定
Matrix4 scale(const Vector3& s);

//回転行列の設定
Matrix4 rotateX(float angle);
Matrix4 rotateY(float angle);
Matrix4 rotateZ(float angle);

//平行移動行列の設定
Matrix4 translate(const Vector3& t);

//座標変換(ベクトルと行列の掛け算)
Vector3 transform(const Vector3& v, const Matrix4& m);

//代入演算子オーバーロード
Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);

//2項演算子オーバーロード
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
Vector3 operator*(const Vector3& v, const Matrix4& m);

