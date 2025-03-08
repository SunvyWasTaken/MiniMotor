#include "MiniMotor.h"
#include "Collision.h"
#include "Quadtree.h"

#define ALOG(x, ...) std::cerr << std::format(x, ##__VA_ARGS__) << std::endl;

class Cursor : public Sunset::Entity
{
public:
	void Init() override
	{
		AddComponent<Sunset::MeshComponent>(Sunset::NamesList{"../../Ressources/SunsetBaseColor.jpg", ""});
		AddComponent<Sunset::TransformComponent>(Sunset::Transform{});
	}

	void Update(float deltatime) override
	{
		Sunset::TransformComponent& trans = GetComponent<Sunset::TransformComponent>();
		//trans.AddRotAxis<Sunset::Roll>(24);

		glm::vec3 NewPos = ProjectMouseToWorld();
		trans.SetLocation(NewPos);
	}

private:

	glm::vec3 ProjectMouseToWorld()
	{
		Sunset::BasicApp& app = Sunset::BasicApp::Get();
		Sunset::Camera* cam = app.GetCam();

		glm::vec2 mousPos = Sunset::Inputs::GetMousePosition();

		mousPos.x = (2.f * mousPos.x / app.GetWindow().GetWidth()) - 1.f;
		mousPos.y = 1.f - (2.f * mousPos.y / app.GetWindow().GetHeight());

		glm::vec4 ray_clip(mousPos.x, mousPos.y, -1.0f, 1.0f);

		glm::vec4 ray_eye = glm::inverse(cam->GetProjection()) * ray_clip;
		ray_eye.z = -1.0f;
		ray_eye.w = 0.0f;

		glm::vec3 ray_world = glm::vec3(glm::inverse(cam->GetViewMatrice()) * ray_eye);

		return ray_world;
	}
};

class CubeStatic : public Sunset::Entity
{
public:
	explicit CubeStatic(const Sunset::Transform& tran)
		: trans(tran)
	{ }

	void Init() override
	{
		AddComponent<Sunset::MeshComponent>(Sunset::NamesList{ "../../Ressources/Pinkie.png", "" });
		AddComponent<Sunset::TransformComponent>(trans);
	}

	void SetColor(const glm::vec3& color)
	{
		Sunset::MeshComponent& mesh = GetComponent<Sunset::MeshComponent>();
		mesh.color = color;
	}

	Sunset::Transform trans;
};

class DefaultApp : public Sunset::BasicApp
{
public:
	void Init()
	{
		cur = GetWorld().SpawnEntity<Cursor>();
		float y = 0;
		float x = 0;
		for (uint8_t i = 0; i < 100; ++i)
		{
			constexpr float Size = 0.4f;
			auto val = i%10;
			if (val == 0)
			{
				x = 0;
				++y;
			}
			++x;
			
			walls[i] = GetWorld().SpawnEntity<CubeStatic>(Sunset::Transform{x * Size - 2.f, y * Size - 2.f, 0.f});
		}
	};

	void Update()
	{
		Rect Cusor;
		Cusor.Location = cur->GetComponent<Sunset::TransformComponent>().GetLocation();
		Cusor.Height = 0.1;
		Cusor.Width = 0.1;

		Rect Wall;
		for (auto wa : walls)
		{
			Wall.Location = wa->trans.pos;
			Wall.Height = 0.1f;
			Wall.Width = 0.1f;

			if (TestCollision(Cusor, Wall))
				wa->SetColor({0.1, 0.8, 0.9});

			else
				wa->SetColor(glm::vec3(1.f));
		}
	};

	Cursor* cur = nullptr;
	std::array<CubeStatic*, 100> walls;
};


int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
}
