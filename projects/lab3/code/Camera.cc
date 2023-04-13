#include "Camera.h"

Matrix4D& Camera::getPerspRef()
{
	return perspective;
}

Matrix4D Camera::getPersp()
{
	return perspective;
}

void Camera::setPersp(Matrix4D persp)
{
	perspective = persp;
}

Matrix4D& Camera::getViewRef()
{
	return view;
}

Matrix4D Camera::getView()
{
	return view;
}

void Camera::setView(Matrix4D newView)
{
	view = newView;
}
void Camera::setView()
{
	view = view.lookat(camPos, camTarget, Vector4D(0.0f, 1.0f, 0.0f));
}

Vector4D Camera::getPosition()
{
	return camPos;
}

void Camera::setPosition(Vector4D position)
{
	camPos = position;
}

