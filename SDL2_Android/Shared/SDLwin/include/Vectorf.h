#pragma once

#include <cmath>

class vec2f {
public:
	vec2f() { x = 0.f; y = 0.f; }
	vec2f(float _x, float _y) { x = _x; y = _y; }

	void Normalise()
	{
		float v = sqrtf(x*x + y*y);
		x = x / v;
		y = y / v;
	}

	vec2f operator - () const
	{
		return vec2f(-x, -y);
	}

	vec2f operator - (vec2f rhs)
	{
		return vec2f(x - rhs.x, y - rhs.y);
	}

	vec2f operator + (vec2f rhs)
	{
		return vec2f(x + rhs.x, y + rhs.y);
	}

	bool operator == (vec2f rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}

	bool operator!=(vec2f rhs)
	{
		return (x != rhs.x || y != rhs.y);
	}

	vec2f operator*(float scale)
	{
		return vec2f(x * scale, y * scale);
	}

	vec2f operator/(float div)
	{
		return vec2f(x / div, y / div);
	}

	vec2f & operator += (vec2f const & v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	vec2f & operator -= (vec2f const & v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	vec2f & operator *= (float v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	float GetLength() const
	{
		return sqrtf(x*x + y*y);
	}


	static vec2f g_Zero;

	float x;
	float y;
};

class vec3f {
public:
	vec3f() : x(0.f), y(0.f), z(0.f) {
	}

	vec3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

	vec3f operator - ()
	{
		return vec3f(-x, -y, -z);
	}

	vec3f operator - (vec3f rhs)
	{
		return vec3f(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	vec3f operator + (vec3f rhs)
	{
		return vec3f(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	vec3f & operator += (vec3f const & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	bool operator==(vec3f rhs)
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	vec3f operator*(float scale)
	{
		return vec3f(x * scale, y * scale, z * scale);
	}

	vec3f operator/(float div)
	{
		return vec3f(x / div, y / div, z / div);
	}

	bool IsZero() const
	{
		return ((x == 0.f) && (y == 0.f) && (z == 0.f));
	}

	static vec3f g_Zero;

	float x;
	float y;
	float z;
};

class matrix3f {
public:

// VARS

	static matrix3f g_Identity;
	float m[3][3];
	vec3f t;

// FUNCTIONS

	matrix3f() {
		m[0][0] = 1;
		m[1][0] = 0;
		m[2][0] = 0;
		m[0][1] = 0;
		m[1][1] = 1;
		m[2][1] = 0;
		m[0][2] = 0;
		m[1][2] = 0;
		m[2][2] = 1;
		t.x = 0;
		t.y = 0;
		t.z = 0;
	};

	vec3f TransformVec(vec3f const &v) const { 
		return vec3f(
			((m[0][0] * v.x) + (m[1][0] * v.y) + (m[2][0] * v.z)) + t.x,
			((m[0][1] * v.x) + (m[1][1] * v.y) + (m[2][1] * v.z)) + t.y,
			((m[0][2] * v.x) + (m[1][2] * v.y) + (m[2][2] * v.z)) + t.z
		);
	}
	
	vec3f TransposeRotateVec(vec3f const &v) const {
		return vec3f(
			((m[0][0] * v.x) + (m[0][1] * v.y) + (m[0][2] * v.z)),
			((m[1][0] * v.x) + (m[1][1] * v.y) + (m[1][2] * v.z)),
			((m[2][0] * v.x) + (m[2][1] * v.y) + (m[2][2] * v.z))
		);
	}

	matrix3f operator * (matrix3f const & m2) const
	{
		matrix3f nm;
		nm.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0];
		nm.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1];
		nm.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2];
		nm.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0];
		nm.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1];
		nm.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2];
		nm.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0];
		nm.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1];
		nm.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2];

		nm.t = m2.TransformVec(t);
		return nm;
	}

	void SetRotX(float ang = 0)
	{
		m[0][0] = 1.0f;
		m[1][1] = m[2][2] = (float)cos(ang);
		m[1][2] = -(m[2][1] = (float)sin(ang));
	}

	void SetRotY(float ang = 0)
	{
		m[1][1] = 1.0f;
		m[0][0] = m[2][2] = (float)cos(ang);
		m[2][0] = -(m[0][2] = (float)sin(ang));
	}

	void SetRotZ(float ang = 0)
	{
		m[2][2] = 1.0f;
		m[0][0] = m[1][1] = (float)cos(ang);
		m[0][1] = -(m[1][0] = (float)sin(ang));
	}

	vec3f TransposeTransformVec(vec3f const &V)
	{
		return vec3f(
			((m[0][0] * (V.x - t.x)) + (m[0][1] * (V.y - t.y)) + (m[0][2] * (V.z - t.z))),
			((m[1][0] * (V.x - t.x)) + (m[1][1] * (V.y - t.y)) + (m[1][2] * (V.z - t.z))),
			((m[2][0] * (V.x - t.x)) + (m[2][1] * (V.y - t.y)) + (m[2][2] * (V.z - t.z)))
		);
	}

	matrix3f & SetTrans(vec3f const & v)
	{
		t = v;
		return *this;
	}

	float TransformVecX(vec3f const &V) const { return (((m[0][0] * V.x) + (m[1][0] * V.y) + (m[2][0] * V.z))) + t.x; }
	float TransformVecY(vec3f const &V) const { return (((m[0][1] * V.x) + (m[1][1] * V.y) + (m[2][1] * V.z))) + t.y; }
	float TransformVecZ(vec3f const &V) const { return (((m[0][2] * V.x) + (m[1][2] * V.y) + (m[2][2] * V.z))) + t.z; }
	float TransformVecX(float x, float y, float z) const { return (((m[0][0] * x) + (m[1][0] * y) + (m[2][0] * z))) + t.x; }
	float TransformVecY(float x, float y, float z) const { return (((m[0][1] * x) + (m[1][1] * y) + (m[2][1] * z))) + t.y; }
	float TransformVecZ(float x, float y, float z) const { return (((m[0][2] * x) + (m[1][2] * y) + (m[2][2] * z))) + t.z; }

	vec3f RotateVec(vec3f const &V) const
	{
		return vec3f(
			((m[0][0] * V.x) + (m[1][0] * V.y) + (m[2][0] * V.z)),
			((m[0][1] * V.x) + (m[1][1] * V.y) + (m[2][1] * V.z)),
			((m[0][2] * V.x) + (m[1][2] * V.y) + (m[2][2] * V.z))
		);
	}

	float RotateVecX(const vec3f& V) const
	{
		return m[0][0] * V.x + m[1][0] * V.y + m[2][0] * V.z;
	}

	float RotateVecY(const vec3f& V) const
	{
		return m[0][1] * V.x + m[1][1] * V.y + m[2][1] * V.z;
	}

	float RotateVecZ(const vec3f& V) const
	{
		return m[0][2] * V.x + m[1][2] * V.y + m[2][2] * V.z;
	}

	bool IsRotZero() const
	{
		return m[0][0] == 0 &&
			m[0][1] == 0 &&
			m[0][2] == 0 &&
			m[1][0] == 0 &&
			m[1][1] == 0 &&
			m[1][2] == 0 &&
			m[2][0] == 0 &&
			m[2][1] == 0 &&
			m[2][2] == 0;
	}

	bool IsTransZero() const
	{
		return t.x == 0 && t.y == 0 && t.z == 0;
	}

	bool IsZero() const
	{
		return IsRotZero() && IsTransZero();
	}

	void LookAt(const vec3f &from, const vec3f &to, const vec3f &up)
	{
		//// This is set up for a right-handed coordinate system
		//vec3f vx, vy, vz;

		//vz = (to - from).GetNormalised();  // Forward vector
		//vx = (up ^ vz);                    // Right vector
		//if (vx.IsZero())
		//	vx.x = 1.0f;
		//else
		//	vx.Normalise();
		//vy = (vz ^ vx);
		//m[0][0] = vx.x; m[0][1] = vx.y; m[0][2] = vx.z;
		//m[1][0] = vy.x; m[1][1] = vy.y; m[1][2] = vy.z;
		//m[2][0] = vz.x; m[2][1] = vz.y; m[2][2] = vz.z;
	}

	void SetIdentity() {
		*this = g_Identity;
	}



private:
	




};

class matrix2f
{
public:

	float m[2][2];
	vec2f t;

	static matrix2f g_Identity;

	matrix2f() {
		m[0][0] = m[1][1] = 1.f;
		m[0][1] = m[1][0] = 0;
		t.x = t.y = 0;
	};

	explicit matrix2f(float f)
	{
		m[0][0] = m[1][1] = f;
		m[0][1] = m[1][0] = 0;
		t.x = t.y = 0;
	}

	matrix2f(matrix2f const & R, vec2f const & T)
	{
		m[0][0] = R.m[0][0];
		m[1][0] = R.m[1][0];
		m[0][1] = R.m[0][1];
		m[1][1] = R.m[1][1];
		t = T;
	}

	void Normalise()
	{
		vec2f * pVecX = (vec2f*)&m[0][0];
		vec2f * pVecY = (vec2f*)&m[1][0];

		pVecX->Normalise();
		pVecY->Normalise();

		*pVecY = vec2f(-pVecX->y, pVecX->x);
	}

	void Transpose()
	{
		float temp = m[0][1];
		m[0][1] = m[1][0];
		m[1][0] = temp;
	}

	vec2f const & GetTrans() const
	{
		return t;
	}

	matrix2f & SetTrans(vec2f const & v)
	{
		t = v;
		return *this;
	}

	matrix2f & operator += (vec2f & V)
	{
		t += V;
		return *this;
	}

	matrix2f operator + (vec2f & V)
	{
		return matrix2f(*this, t + V);
	}

	vec2f ColumnX() const
	{
		return vec2f(m[0][0], m[1][0]);
	}

	vec2f ColumnY() const
	{
		return vec2f(m[0][1], m[1][1]);
	}

#define VecX RowX

	vec2f RowX() const
	{
		return vec2f(m[0][0], m[0][1]);
	}

#define VecY RowY

	vec2f RowY() const
	{
		return vec2f(m[1][0], m[1][1]);
	}

	vec2f RotateVec(vec2f const &V) const
	{
		return vec2f(
			((m[0][0] * V.x) + (m[1][0] * V.y)),
			((m[0][1] * V.x) + (m[1][1] * V.y))
		);
	}

	vec2f TransformVec(vec2f const &V) const
	{
		return vec2f(
			((m[0][0] * V.x) + (m[1][0] * V.y)) + t.x,
			((m[0][1] * V.x) + (m[1][1] * V.y)) + t.y
		);
	}

	vec2f TransposeRotateVec(vec2f const &V) const
	{
		return vec2f(
			((m[0][0] * V.x) + (m[0][1] * V.y)),
			((m[1][0] * V.x) + (m[1][1] * V.y))
		);
	}

	vec2f TransposeTransformVec(vec2f const &V) const
	{
		return vec2f(
			((m[0][0] * (V.x - t.x)) + (m[0][1] * (V.y - t.y))),
			((m[1][0] * (V.x - t.x)) + (m[1][1] * (V.y - t.y)))
		);
	}


	float TransformVecX(vec2f const &V) const { return (((m[0][0] * V.x) + (m[1][0] * V.y))) + t.x; }
	float TransformVecY(vec2f const &V) const { return (((m[0][1] * V.x) + (m[1][1] * V.y))) + t.y; }
	float TransformVecX(float x, float y) const { return (((m[0][0] * x) + (m[1][0] * y))) + t.x; }
	float TransformVecY(float x, float y) const { return (((m[0][1] * x) + (m[1][1] * y))) + t.y; }

	float RotateVecX(const vec2f& V)
	{
		return m[0][0] * V.x + m[1][0] * V.y;
	}
	
	float RotateVecY(const vec2f& V)
	{
		return m[0][1] * V.x + m[1][1] * V.y;
	}

	matrix2f GetTranspose() const
	{
		matrix2f N;
		N.m[0][0] = m[0][0];
		N.m[1][0] = m[0][1];
		N.m[0][1] = m[1][0];
		N.m[1][1] = m[1][1];

		N.t = vec2f(0, 0);
		return N;
	}

	void SetRot(float r = 0, bool resetTrans = true)
	{
		if (resetTrans)     t.x = t.y = 0;
		m[0][0] = m[1][1] = (float)cos(-r);
		m[0][1] = -(m[1][0] = (float)sin(-r));
	}

	void SetRot(float r, vec2f& centre)
	{
		m[0][0] = m[1][1] = (float)cos(-r);
		m[0][1] = -(m[1][0] = (float)sin(-r));
		t = centre - RotateVec(centre);
	}

	void PreRotate(float r)
	{
		matrix2f rz;
		rz.SetRot(r, true);
		PreRotate(rz);
	}
	
	void PostRotate(float r)
	{
		matrix2f rz;
		rz.SetRot(r, true);
		PostRotate(rz);
	}

	matrix2f operator * (matrix2f const & M) const
	{
		matrix2f N;
		N.m[0][0] = FindComponentFromBA(M, *this, 0, 0);
		N.m[0][1] = FindComponentFromBA(M, *this, 0, 1);

		N.m[1][0] = FindComponentFromBA(M, *this, 1, 0);
		N.m[1][1] = FindComponentFromBA(M, *this, 1, 1);

		N.t = M.TransformVec(t);

		return N;
	}

	matrix2f & PreMult(matrix2f const & M)
	{
		return (*this = M * (*this));
	}

	matrix2f & PreMultiply(matrix2f const & M)
	{
		return PreMult(M);
	}

	matrix2f & PostMult(matrix2f const & M)
	{
		return (*this = (*this) * M);
	}

	matrix2f & PostMultiply(matrix2f const & M)
	{
		return PostMult(M);
	}

	matrix2f & operator *= (matrix2f const & M)
	{
		return PostMult(M);
	}

	matrix2f &PostRotate(matrix2f const& M)
	{
		matrix2f N;

		N.m[0][0] = FindComponentFromBA(M, *this, 0, 0);
		N.m[0][1] = FindComponentFromBA(M, *this, 0, 1);

		N.m[1][0] = FindComponentFromBA(M, *this, 1, 0);
		N.m[1][1] = FindComponentFromBA(M, *this, 1, 1);

		CopyRot(N);

		return *this;
	}

	matrix2f PreRotate(matrix2f const& M)
	{
		matrix2f tmp = M;
		tmp.t = this->t;
		return (*this = tmp.PostRotate(*this));
	}

	matrix2f &ScaleRot(float v)
	{
		for (int i = 0; i<2; i++)
			for (int j = 0; j<2; j++)
				m[i][j] = (m[i][j] * v);
		return *this;
	}

	matrix2f &ScaleTrans(float v)
	{
		t *= v;
		return *this;
	}

	matrix2f &Scale(float v)
	{
		ScaleRot(v);
		ScaleTrans(v);
		return *this;
	}

	matrix2f & operator *= (const float v)
	{
		Scale(v);
		return *this;
	}


	/**
	* Linear interpolation of rotation elements.
	* @param m0 Start rotation elements.
	* @param m1 End rotation elements.
	* @param fraction Relative amount of start and end elements to use.
	* fraction is constrained to [0, 1.0f].\n
	* fraction = 0 results in rotation being set to that of @a m0.\n
	* fraction = 1.0f results in rotationbeing set to that of @a m1.
	*/
	//void InterpRot(matrix2f const & m0, matrix2f const & m1, float fraction);

	//void InterpolateRot(matrix2f const & m0, matrix2f const & m1, float fraction)
	//{
	//	InterpRot(m0, m1, fraction);
	//}


	/**
	* Linear interpolation of translation elements.
	* @param m0 Start translation elements.
	* @param m1 End translation elements.
	* @param fraction Relative amount of start and end position to use.
	* fraction is constrained to [0, 1.0f]. \n
	* fraction = 0 results in position set to that of @a m0.\n
	* fraction = 1.0f results in position being set to that of @a m1.
	*/
	//void InterpTrans(matrix2f const & m0, matrix2f const & m1, float fraction);

	//void InterpolatePos(matrix2f const & m0, matrix2f const & m1, float fraction)
	//{
	//	InterpTrans(m0, m1, fraction);
	//}

	void CopyRot(const matrix2f& m0)
	{
		m[0][0] = m0.m[0][0];
		m[0][1] = m0.m[0][1];
		m[1][0] = m0.m[1][0];
		m[1][1] = m0.m[1][1];
	}

	void CopyTrans(const matrix2f& m0)
	{
		t = m0.t;
	}

	bool IsRotSame(matrix2f const& m0) const
	{
		return  m[0][0] == m0.m[0][0] &&
			m[0][1] == m0.m[0][1] &&
			m[1][0] == m0.m[1][0] &&
			m[1][1] == m0.m[1][1];
	}

	bool IsTransSame(matrix2f const& m0)
	{
		return (t == m0.t);
	}

	bool operator == (matrix2f const & m0)
	{
		return IsRotSame(m0) && IsTransSame(m0);
	}

	bool operator != (matrix2f const & m0)
	{
		return !IsRotSame(m0) || !IsTransSame(m0);
	}

	bool IsRotIdentity()
	{
		return IsRotSame(g_Identity);
	}

	bool IsTransIdentity()
	{
		return IsTransSame(g_Identity);
	}

	bool IsIdentity()
	{
		return (*this) == g_Identity;
	}

	void SetIdentity()
	{
		*this = g_Identity;
	}

	bool IsRotZero()
	{
		return m[0][0] == 0 &&
			m[0][1] == 0 &&
			m[1][0] == 0 &&
			m[1][1] == 0;
	}

	bool IsTransZero()
	{
		return t.x == 0 &&
			t.y == 0;
	}

	bool IsZero()
	{
		return IsRotZero() && IsTransZero();
	}

	void SetZero()
	{
		m[0][0] = m[0][1] = m[1][0] = m[1][1] = 0.0f;
	}


	void Zero()
	{
		SetZero();
	}

	float GetDeterminant() const
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}


	//matrix2f GetInverse() const;


private:

	static float FindComponentFromBA(const matrix2f& A, const matrix2f& B, const int i, const int j)
	{
		return B.m[i][0] * A.m[0][j] + B.m[i][1] * A.m[1][j];

	}

};
