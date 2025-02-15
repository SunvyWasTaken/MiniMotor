#include "MiniMotor.h"

// Gravitational constant. m^3 kg^-1 s^-2
constexpr double G = 6.67430e-11;

class Aster : public Sunset::Entity
{
public:
	Aster(const FVec3& _position, const FVec3& _size, const FVec3& _velocity, double _m)
		: Position(_position)
		, Size(_size)
		, Velocity(_velocity)
		, M(_m)
	{}

	virtual void Init() override
	{
		AddComponent<Sunset::MeshComponent>();
		AddComponent<Sunset::TransformComponent>(Transform{Position, Size});
	}
	
	// Position relative to the 0 . 0 . 0 which is gonna be the sun.
	FVec3 Position;
	// Size of the aster
	FVec3 Size;

	FVec3 Velocity;
	// Masse de l'astre
	double M;
};

#define CREATE_ASTER(x, ...) class x : public Aster { public: x() : Aster(__VA_ARGS__) {} };

CREATE_ASTER(Sun, {0, 0, 0}, { 7, 7, 7 }, {0, 0, 0}, 1.989e3)
//CREATE_ASTER(Mercure)
//CREATE_ASTER(Venus)
CREATE_ASTER(Earth, { 149, 0.0, 0.0 }, { 1, 1, 1 }, { 0, 0.0278, 0 }, 0.005972)
//CREATE_ASTER(Mars)
//CREATE_ASTER(Jupiter)
//CREATE_ASTER(Saturne)
//CREATE_ASTER(Uranus)
//CREATE_ASTER(Neptune)

using SolarSys = Typelist<Sun, Earth>;

class DefaultApp : public Sunset::BasicApp<Sunset::OpenGLRender>
{
public:

	virtual void Init() override
	{
		InitEntities(std::make_index_sequence<TypelistSize<SolarSys>::value>{});
	}

	virtual void Update() override
	{
		// Let i start at 1 cuz the sun is at the index 0. (supposedly)
		for (int i = 1; i < solarSys.size(); ++i)
		{
			Aster& currentAster = *(solarSys[i]);
			FVec3 F = gravitationForce(currentAster, At<Sun>());
			FVec3 acc = { F.x / currentAster.M, F.y / currentAster.M, F.z / currentAster.M };
			updatePositionAndVelocity(currentAster, acc, Deltatime);
		}
	}

private:

	void updatePositionAndVelocity(Aster& aster, FVec3 acceleration, double dt)
	{
		FVec3& position = aster.GetComponent<Sunset::TransformComponent>()().position;
		FVec3& velocity = aster.Velocity;

		position.x += velocity.x * dt;
		position.y += velocity.y * dt;
		position.z += velocity.z * dt;
		velocity.x += acceleration.x * dt;
		velocity.y += acceleration.y * dt;
		velocity.z += acceleration.z * dt;
	}

	FVec3 gravitationForce(const Aster& A1, const Aster& A2)
	{
		FVec3 pos1 = A1.GetComponent<Sunset::TransformComponent>()().position;
		FVec3 pos2 = A2.GetComponent<Sunset::TransformComponent>()().position;

		FVec3 distance = { pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z };
		double r = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
		double forceMagnitude = G * A1.M * A2.M / (r * r);
		FVec3 force = { forceMagnitude * distance.x / r, forceMagnitude * distance.y / r, forceMagnitude * distance.z / r };
		return force;
	}

	template <typename T>
	Aster& At()
	{
		return *solarSys[TypeIndex<T, SolarSys>::value];
	}

private:

	// Generated at compile time the for loop to create each aster list in the typelist.
	template <size_t... Is>
	void InitEntities(std::index_sequence<Is...>)
	{
		((solarSys[Is] = GetWorld()->SpawnEntity<typename GetTypeAtIndex<Is, SolarSys>::value>()), ...);
	}

public:

	std::array<Aster*, TypelistSize<SolarSys>::value> solarSys = {};
};

int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
	return 0;
}
