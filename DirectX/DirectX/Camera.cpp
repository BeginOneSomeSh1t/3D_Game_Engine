#include "Camera.h"
#include "imgui/imgui.h"
#include "MyMath.h"

namespace dx = DirectX;

Camera::Camera() noexcept
{
	Reset();
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	using namespace dx;

	const XMVECTOR forwardBaseVector = XMVectorSet(0.f, 0.f, 1.f, 0.f);
	// apply the camera rotations to a base vector
	const auto lookVector = XMVector3Transform(forwardBaseVector,
		XMMatrixRotationRollPitchYaw(pitch, yaw, 0.f)
	);
	// generate camera transform ( applied to all objects to arrange them
	// relative to camera position/orientation in the world) from cam position and
	// direction camera "top" always faces towards +Y (cannot do a barrell roll)
	const auto camPosition = XMLoadFloat3(&pos);
	const auto camTarget = camPosition + lookVector;
	return XMMatrixLookAtLH(camPosition, camTarget, XMVectorSet(0.f, 1.f, 0.f, 0.f));
}

void Camera::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -80.f, 80.0f, "%.1f");
		ImGui::SliderAngle("Y", &pos.y, -80.0f, 80.0f, "%.1f");
		ImGui::SliderAngle("Z", &pos.z, -80.0f, 80.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Pitch", &pitch, 0.995f * -90.0f, 0.995f * 90.f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Reset() noexcept
{
	pos = { 0.f, 7.5f, -18.f };
	pitch = 0.0f;
	yaw = 0.0f;
	
}

void Camera::Rotate(float dx, float dy) noexcept
{
	yaw = wrap_angle(yaw + dx * rotationSpeed);
	pitch = std::clamp(pitch + dy * rotationSpeed,0.995f * -PI / 2.f, 0.995f * PI / 2.f);
}

void Camera::Translate(DirectX::XMFLOAT3 translation) noexcept
{
	dx::XMStoreFloat3(&translation, dx::XMVector3Transform(
		dx::XMLoadFloat3(&translation),
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.f) *
		dx::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
	));
	pos =
	{
		pos.x + translation.x,
		pos.y + translation.y,
		pos.z + translation.z,
	};
}

void Camera::AddTravelSpeed(float speed) noexcept
{
	travelSpeed += speed;
}

void Camera::SubtractTravelSpeed(float speed) noexcept
{
	if (travelSpeed - speed > 0)
		travelSpeed -= speed;
	else
		travelSpeed = 0;
}
