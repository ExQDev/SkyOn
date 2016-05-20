#include "About.h"

using namespace SkyOnConfigurer; 

[STAThreadAttribute]
int mainAbout(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew About());
	return 0;
}