#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/AssignmentScene1.h"
#include "scenes/AssignmentScene2.h"
#include "scenes/AssignmentScene3.h"
#include "scenes/AssignmentScene4.h"
#include "scenes/PlanetScene.h"
#include <random>

int main(int argc, char** argv)
{
	// Add newly created scenes here so that they show up in the menu.
	std::vector<Scene*> scenes = 
	{
		new TestScene(),
		new AssignmentScene1(),
		new AssignmentScene2(),
		new AssignmentScene3(),
		new AssignmentScene4(),
		new PlanetScene()
	};

	//init time
	srand(time({}));

	Application app(scenes);
	return app.Run();
}
