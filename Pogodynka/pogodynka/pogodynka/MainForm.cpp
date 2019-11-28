#include "MainForm.h"
#include <Windows.h>

using namespace System;
using namespace Windows;
using namespace Forms;

int main()
{
	Application::EnableVisualStyles();
	Application::Run(gcnew pogodynka::MainForm());
	return 0;
}