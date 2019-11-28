#include "MainForm.h"
#include <Windows.h>

using namespace System;


int main()
{
	System::Windows::Forms::Application::Run(gcnew pogodynka::MainForm());
	return 0;
}