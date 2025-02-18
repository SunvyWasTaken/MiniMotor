#include "MiniMotor.h"

// Gravitational constant. m^3 kg^-1 s^-2
constexpr double G = 6.67430e-11;
constexpr double UA = 1e2;

class Aster : public Sunset::Entity
{
public:
	Aster(const FVec3& _position, const FVec3& _size, const double revolution)
		: Position(_position)
		, Size(_size)
		, RevoSpeed(revolution)
	{}

	virtual void Init() override
	{
		// todo : add a way to custom the mesh directly from here.
		AddComponent<Sunset::MeshComponent>(Sunset::NamesList{"../../Ressources/Sun.jpg", "../../Ressources/SunsetSpec.jpg"});
		AddComponent<Sunset::TransformComponent>(Transform{Position, Size});
	}
	
	// Position relative to the 0 . 0 . 0 which is gonna be the sun.
	FVec3 Position;
	// Size of the aster
	FVec3 Size;
	// How much it take for the aster to make a hole rotation around the sun. (in days)
	double RevoSpeed;
};

#define CREATE_ASTER(x, ...) class x : public Aster { public: x() : Aster(__VA_ARGS__) {} };

CREATE_ASTER(Sun, {0, 0, 0}, { 7, 7, 7 }, 0)
//CREATE_ASTER(Mercure)
//CREATE_ASTER(Venus)
CREATE_ASTER(Earth, { UA, 0, 0.0 }, { 5, 5, 5 }, 365)
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

		// todo : change the light way suz for now it will be a diff obj from the aster sun.
		LightList.emplace_back(Sunset::Directional{FVec3{- 0.2f, -1.0f, -0.3f}, Sunset::Light{FVec3{0.2f, 0.2f, 0.2f}, FVec3{0.5f, 0.5f, 0.5f}, FVec3{1.0f, 1.0f, 1.0f}}});
	}

	virtual void Update() override
	{
		// Let i start at 1 cuz the sun is at the index 0. (supposedly)
		for (int i = 1; i < solarSys.size(); ++i)
		{

		}
	}

private:

	template <typename T>
	Aster& At()
	{
		return *solarSys[TypeIndex<T, SolarSys>::value];
	}

	// Generated at compile time the for loop to create each aster list in the typelist.
	template <size_t... Is>
	void InitEntities(std::index_sequence<Is...>)
	{
		((solarSys[Is] = GetWorld()->SpawnEntity<typename GetTypeAtIndex<Is, SolarSys>::value>()), ...);
	}

public:

	std::array<Aster*, TypelistSize<SolarSys>::value> solarSys = {};

	double SimulationSpeed = 1.f;
};

int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
	return 0;
}
