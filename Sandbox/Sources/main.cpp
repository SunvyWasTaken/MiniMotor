#include "MiniMotor.h"
#include "Collision.h"
#include "Quadtree.h"

constexpr int NbrRow = 55;

// nbr de cube dans la scene
constexpr int Nbr = NbrRow * NbrRow;

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
		quad = Quadtree<Rect>(glm::vec3(0), glm::vec3{3000, 3000, 1});
		cur = GetWorld().SpawnEntity<Cursor>();
		float y = 0;
		float x = 0;
		for (uint32_t i = 0; i < Nbr; ++i)
		{
			constexpr float Size = 0.21f;
			auto val = i%NbrRow;
			if (val == 0)
			{
				x = 0;
				++y;
			}
			++x;
			
			walls[i] = GetWorld().SpawnEntity<CubeStatic>(Sunset::Transform{x * Size - 2.f, y * Size - 2.f, 0.f});

			Rect tmp;
			tmp.Location = { x * Size - 2.f, y * Size - 2.f, 0.f };
			tmp.Height = 0.1f;
			tmp.Width = 0.1f;
			quad.Push(tmp);
		}
	};

	void Update()
	{
		Rect Cusor;
		Cusor.Location = cur->GetComponent<Sunset::TransformComponent>().GetLocation();
		Cusor.Height = 0.1;
		Cusor.Width = 0.1;

		Rect Wall1;
		Wall1.Height = 0.1f;
		Wall1.Width = 0.1f;

		for (auto wa : walls)
		{
			wa->SetColor(glm::vec3(1.f));
			Wall1.Location = wa->GetComponent<Sunset::TransformComponent>().GetLocation();

			if (TestCollision(Cusor, Wall1))
				wa->SetColor({ 0.1, 0.8, 0.9 });
		}

		std::vector<Rect> res;

		quad.Get(Cusor, res);

		for (auto& tmp : res)
		{
			std::cerr << "Collision with : " << tmp.Location.x << " " << tmp.Location.y << std::endl;
		}
	};

	Cursor* cur = nullptr;
	std::array<CubeStatic*, Nbr> walls;
	Quadtree<Rect> quad;
};


int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
}
