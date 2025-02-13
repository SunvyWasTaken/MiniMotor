#include "MiniMotor.h"

struct DefaultApp : BasicApp<OpenGLRender>
{
	virtual void Init() override
	{
		Entity* cube = GetWorld()->SpawnEntity<Entity>();
		cube->AddComponent<MeshComponent>();
	}

	virtual void Update() override
	{

	}
};

int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
	return 0;
}
