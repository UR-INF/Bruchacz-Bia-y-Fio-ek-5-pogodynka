#include "MainForm.h"
#include <Windows.h>
#include <curl/curl.h>
#include <string>

using namespace System;
using namespace System::Windows::Forms;



int main()
{
	
	/*
	auto r = cpr::Get(cpr::Url{ "https://community-open-weather-map.p.rapidapi.com/weather" },
		cpr::Parameters{ {"q", "London"} },
		cpr::Header{
			{"RapidAPI Project","default_application_4048218"},
			{"X-RapidAPI-Host", "community-open-weather-map.p.rapidapi.com" },
			{ "X-RapidAPI-Key", "f90acf6696msh3be9bb78dc5c56ep1a4015jsnb4b983675d4c"}
		} );
	r.status_code;
	
	r.text;                         // JSON text string
	*/
	Application::EnableVisualStyles();
	Application::Run(gcnew pogodynka::MainForm());
	return 0;
}