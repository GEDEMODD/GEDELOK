#include "SceneManager.h"
#include "FrameListener.h"
// Lab2
int main()
{
	SceneManager app;
	app.startup();
	while( app.keepRunning() )
	{
		app.renderOneFrame();
	}
	return 0;
}