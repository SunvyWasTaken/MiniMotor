// Boids system to delevlop :/

#include "MiniMotorApp.h"
#include "CoreMinimal.h"
#include "ECS/Entitys.h"
#include "ECS/Components/CollisionComponent.h"
#include "World.h"

#include <random>

std::default_random_engine rGen;
using intRand = std::uniform_int_distribution<int>;

namespace
{
	MAKE_STATE(Idle)
	MAKE_STATE(Collide)

	MAKE_STATE_MACHINE(BoidsStateMachine, Idle, Collide)
}

class Boids : public Entity
{
public:

	void BeginPlay() override
	{
		Entity::BeginPlay();

		AddComponent<RendableComponent>(Texture{"Ressources/kawaii-pinkie-pie-pack.png", m_IdleCoord});
		CollisionComponent& comp = AddComponent<CollisionComponent>();
		comp.BindOnCollision(std::bind(&Boids::OnCollision, this));
		comp.BindOnStopCollision(std::bind(&Boids::OnStopCollision, this));

		rGen.seed(std::random_device()());

		intRand randX(0, 2000);
		intRand randY(0, 2000);

		SetWorldPosition(FVec2{ randX(rGen), randY(rGen) });
	}

	void Update(float deltaTime) override
	{
		Entity::Update(deltaTime);

		Dir = FVec2{ intRand(-1, 1)(rGen), intRand(-1, 1)(rGen) };

		if (GetWorldPosition().x > 2000)
		{
			Dir.x = -1;
		}
		else if (GetWorldPosition().x < 0)
		{
			Dir.x = 1;
		}
		if (GetWorldPosition().y > 2000)
		{
			Dir.y = -1;
		}
		else if (GetWorldPosition().y < 0)
		{
			Dir.y = 1;
		}
		
		AddWorldOffset(Dir);
	}

	void OnCollision()
	{
		m_CurrentState = Collide();
		GetComponent<RendableComponent>().texture.coord = m_CollidCoord;
	}

	void OnStopCollision()
	{
		m_CurrentState = Idle();
		GetComponent<RendableComponent>().texture.coord = m_IdleCoord;
	}

private:
	BoidsStateMachine m_CurrentState;

	const TextureCoord m_IdleCoord{ IVec2{321, 0}, {651, 0}, {651, 326}, {321, 326} };
	const TextureCoord m_CollidCoord{ IVec2{0, 0}, {321, 0}, {321, 326}, {0, 326} };

	FVec2 Dir;
};

int main()
{
	MiniMotorApp* app = MiniMotorApp::GetInstance();
	app->Init();
	std::unique_ptr<World> world = std::make_unique<World>();

	app->SetWorld(world.get());

	for (size_t i = 0; i < 10000; ++i)
	{
		Boids* boid = world->SpawnEntity<Boids>(TEXT("Boids{}", i));
	}

	app->Run();
	app->Shutdown();
	return 0;
}