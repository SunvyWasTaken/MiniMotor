#include "MiniMotor.h"

constexpr double G = 6.67430e-11;

class Aster : public Entity
{
public:
	Aster(FVec3 position, double mass)
		: Position(position)
		, M(mass)
	{
	}

	virtual void Init() override
	{
		AddComponent<MeshComponent>();
		AddComponent<TransformComponent>(Position);
	}

	
	FVec3 Position;

	// Masse de l'astre
	double M;
};

struct ProcessF
{
	FVec3 operator()(const Aster& A1, const Aster& A2)
	{
		FVec3 pos1 = A1.GetComponent<TransformComponent>()();
		FVec3 pos2 = A2.GetComponent<TransformComponent>()();

		FVec3 distance = { pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z };
		double r = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
		double forceMagnitude = G * A1.M * A2.M / (r * r);
		FVec3 force = { forceMagnitude * distance.x / r, forceMagnitude * distance.y / r, forceMagnitude * distance.z / r };
		return force;
	}
};

struct DefaultApp : BasicApp<OpenGLRender>
{
	virtual void Init() override
	{
		Sun = GetWorld()->SpawnEntity<Aster>(FVec3{0, 0, 0}, 1.989e3);
		Earth = GetWorld()->SpawnEntity<Aster>(FVec3{ 149, 0.0, 0.0 }, 0.005972);
	}

	virtual void Update() override
	{
		FVec3 force = gravitationForce(*Earth, *Sun);
		FVec3 acceleration = { force.x / Earth->M, force.y / Earth->M, force.z / Earth->M };
		updatePositionAndVelocity(Earth->GetComponent<TransformComponent>()(), velocityTerre, acceleration, Deltatime);
		auto pos = Earth->GetComponent<TransformComponent>()();
		std::cerr << "Coord : " << pos.x << ", y :" << pos.y << ", z :" << pos.z << std::endl;
		std::cerr << "distance : " << glm::length(pos) << std::endl;
	}

	void updatePositionAndVelocity(FVec3& position, FVec3& velocity, FVec3 acceleration, double dt) {
		position.x += velocity.x * dt;
		position.y += velocity.y * dt;
		position.z += velocity.z * dt;
		velocity.x += acceleration.x * dt;
		velocity.y += acceleration.y * dt;
		velocity.z += acceleration.z * dt;
	}

	ProcessF gravitationForce;

	Aster* Sun = nullptr;
	Aster* Earth = nullptr;
	FVec3 velocityTerre = { 0, 0.0278, 0 };
};

int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
	return 0;
}
