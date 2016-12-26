typedef unsigned char Color;
typedef unsigned char byte;

class Matrix;

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator-(const Vector3& other);

	static Vector3 zero();
	static Vector3 up();
	static Vector3 transformCoordinate(Vector3 vector, Matrix transformation);
	static Vector3 cross(Vector3 left, Vector3 right);
	static float dot(Vector3 left, Vector3 right);

	float length();
	void normalize();
};

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();

	static Quaternion rotationYawPitchRoll(float yaw, float pitch, float roll);

	Matrix toRotationMatrix();
};

class Matrix
{
public:
	float m[16];

	Matrix();
	Matrix(float m[16]);
	Matrix(float initialM11, float initialM12, float initialM13, float initialM14,
	       float initialM21, float initialM22, float initialM23, float initialM24,
	       float initialM31, float initialM32, float initialM33, float initialM34,
	       float initialM41, float initialM42, float initialM43, float initialM44);

	Matrix operator*(const Matrix& other);

	static Matrix zero();
	static Matrix identity();
	static Matrix translation(Vector3 vector);
	static Matrix translation(float x, float y, float z);
	static Matrix lookAtLH(Vector3 eye, Vector3 target, Vector3 up);
	static Matrix perspectiveFovLH(float fov, float aspect, float znear, float zfar);
	static Matrix rotationYawPitchRoll(float yaw, float pitch, float roll);
};

struct Face
{
public:
	byte a;
	byte b;
	byte c;
	Vector3 normal;
	
	Face();
	Face(byte a, byte b, byte c);
};

class Mesh
{
public:
	int numberOfVertices;
	Vector3 *vertices;
	int numberOfFaces;
	Face *faces;
	Vector3 position;
	Vector3 rotation;

	Mesh(int numberOfVertices, int numberOfFaces);
};

class Camera
{
public:
	Vector3 position;
	Vector3 target;

	Camera();
};

class Device
{
private:
	float width;
	float height;
public:
	Device();

	void clear();
	void present();
	Vector3 project(Vector3 coord, Matrix transMat);
	void drawPoint(Vector3 point);
	void drawLine(Vector3 point0, Vector3 point1);
	void render(Camera *camera, Mesh **meshes, int numberOfMeshes);
};
