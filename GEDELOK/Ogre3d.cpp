#include "MySceneManager.h"
#include "MyFrameListener.h"
int main()
{
	MySceneManager app;
	app.startup();
	while( app.keepRunning() )
	{
		app.renderOneFrame();
	}
	return 0;
}