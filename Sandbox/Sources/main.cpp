#include "MiniMotor.h"

class DefaultApp : public Sunset::BasicApp
{
public:
	void Init() {};
	void Update() {};
};


int main()
{
	std::unique_ptr<DefaultApp> curr = std::make_unique<DefaultApp>();
	curr->Run();
}
