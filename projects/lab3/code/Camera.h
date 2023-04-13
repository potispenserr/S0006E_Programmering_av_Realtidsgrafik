#include "Matrix4D.h"
class Camera
{
public:
	Camera(Vector4D cameraPosition, Vector4D cameraTarget)
	{
		camPos = cameraPosition;
		camTarget = cameraTarget;
	}

	~Camera()
	{
	}

	Matrix4D& getPerspRef();
	Matrix4D getPersp();
	void setPersp(Matrix4D persp);

	Matrix4D& getViewRef();
	Matrix4D getView();
	void setView(Matrix4D newView);
	void setView();

	Vector4D getPosition();
	void setPosition(Vector4D position);

	Vector4D camPos;
	Vector4D camTarget;



private:
	Matrix4D perspective;
	Matrix4D view;
};
