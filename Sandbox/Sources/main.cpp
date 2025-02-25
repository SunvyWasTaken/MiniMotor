#include "MiniMotor.h"

// Astronomical unit
constexpr double AU = 1e2;
// EarthSize scale down
constexpr double S = 1;

namespace Solar
{
	double SimulationSpeed = 1e7;

	struct Time
	{
		double years, days = 0;

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
		Aster(const double _distance, const double& _size, const Time& _time, const Sunset::NamesList& textures)
			: distance(_distance)
			, Size(_size, _size, _size)
			, RevoSpeed(_time.ToSec())
			, angle(0)
			, texturesList(textures)
		{}

		virtual void Init() override
		{
			// todo : add a way to custom the mesh directly from here.
			AddComponent<Sunset::MeshComponent>(texturesList);
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

		Sunset::NamesList texturesList;
	};

	#define CREATE_ASTER(x, ...) class x : public Aster { public: x() : Aster(__VA_ARGS__) {} };

	// All data come from wikipedia

	//			Name		Distance	Size		years,	Days
	CREATE_ASTER(Sun,		0,			10.9,		{},					{"../../Ressources/Sun.jpg", ""})
	CREATE_ASTER(Mercury,	0.37 * AU,	0.382 * S,	{0,		87.969},	{"../../Ressources/mercure.jpg", ""})
	CREATE_ASTER(Venus,		0.723 * AU,	0.949 * S,	{0,		224.7},		{"../../Ressources/venus.jpg", ""})
	CREATE_ASTER(Earth,		AU,			S,			{0,		365.256},	{"../../Ressources/Earth.jpg", ""})
	CREATE_ASTER(Mars,		1.534 * AU, 0.532 * S,	{1,		321},		{"../../Ressources/Mars.jpg", ""})
	CREATE_ASTER(Jupiter,	5.2 * AU,	10.973 * S,	{11,	315},		{"../../Ressources/jupiter.jpg", ""})
	CREATE_ASTER(Saturne,	9 * AU,		9.135 * S,	{29,	167},		{"../../Ressources/SunsetBaseColor.jpg", ""})
	CREATE_ASTER(Uranus,	19 * AU,	3.981 * S,	{84,	0},			{"../../Ressources/SunsetBaseColor.jpg", ""})
	CREATE_ASTER(Neptune,	30 * AU,	3.865 * S,	{164,	280},		{"../../Ressources/SunsetBaseColor.jpg", ""})

	// Typelist of all the planet you want to display
	using SolarSys = Typelist<Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturne, Uranus, Neptune>;

	class DefaultApp : public Sunset::BasicApp
	{
	public:

		virtual void Init() override
		{
			InitEntities(std::make_index_sequence<TypelistSize<SolarSys>::value>{});

			// todo : change the light way cuz for now it will be a diff obj from the aster sun.
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
