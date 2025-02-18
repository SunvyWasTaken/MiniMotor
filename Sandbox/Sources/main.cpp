#include "MiniMotor.h"

// Astronomical unit
constexpr double AU = 1e1;

namespace Solar
{
	double SimulationSpeed = 100000000.f;

	struct Time
	{
		double years, days;

		double ToSec() const
		{
			double secInYear = years * 365 * 24 * 60 * 60;
			double secInDays = days * 24 * 60 * 60;
			return secInYear + secInDays;
		}
	};

	class Aster : public Sunset::Entity
	{
	public:
		Aster(const double _distance, const double& _size, const Solar::Time& _time)
			: distance(_distance)
			, Size(_size, _size, _size)
			, RevoSpeed(_time.ToSec())
			, angle(0)
		{}

		virtual void Init() override
		{
			// todo : add a way to custom the mesh directly from here.
			AddComponent<Sunset::MeshComponent>(Sunset::NamesList{"../../Ressources/SunsetBaseColor.jpg", "../../Ressources/SunsetSpec.jpg"});
			AddComponent<Sunset::TransformComponent>(Transform{FVec3{distance, 0, 0}, Size});
		}

		// Fake the rotation
		void Process(const float deltatime)
		{
			angle += (2 * PI / RevoSpeed) * deltatime;
			SetPosition(FVec3{ distance * cos(angle), 0, distance * sin(angle) });
		}

		void SetPosition(const FVec3& position)
		{
			Sunset::TransformComponent& comp = GetComponent<Sunset::TransformComponent>();
			comp().position = position;
		}

		const double distance;
	
		// Size of the aster
		FVec3 Size;
		// How much it take for the aster to make a hole rotation around the sun. (in days)
		double RevoSpeed;

		// Angle around the sun
		double angle;
	};

	#define CREATE_ASTER(x, ...) class x : public Aster { public: x() : Aster(__VA_ARGS__) {} };

	// All data come from wikipedia
	CREATE_ASTER(Sun, 0, 1, Time())

	CREATE_ASTER(Mercury,	0.37 * AU,	1,		Time{0, 87.969})
	CREATE_ASTER(Venus,		0.723 * AU,	0.5,	Time{0, 224.7})
	CREATE_ASTER(Earth,		AU,			1,		Time{0, 365.256})
	CREATE_ASTER(Mars,		1.534 * AU, 3,		Time{1, 321})
	CREATE_ASTER(Jupiter,	5.2 * AU,	1,		Time{11, 315})
	CREATE_ASTER(Saturne,	9 * AU,		1,		Time{29, 167})
	CREATE_ASTER(Uranus,	19 * AU,	1,		Time{84, 0})
	CREATE_ASTER(Neptune,	30 * AU,	10,		Time{164, 280})

	// Typelist of all the planet you want to display
	using SolarSys = Typelist<Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturne, Uranus, Neptune>;

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
				solarSys[i]->Process(Deltatime * SimulationSpeed);
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
	};
}

int main()
{
	std::unique_ptr<Solar::DefaultApp> curr = std::make_unique<Solar::DefaultApp>();
	curr->Run();
}
