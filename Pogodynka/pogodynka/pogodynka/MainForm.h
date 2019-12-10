#pragma once
#include <curl/curl.h>
#include <string>
#include <Windows.h>
#include "json/json.h"
#include "rapidjson/document.h"
#include <algorithm>
#include <sstream> 
#include <ctime>
#include <msclr\marshal_cppstd.h>
#include <chrono>


static std::string readBuffer;
namespace pogodynka {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace rapidjson;
	Json::Reader reader;
	Json::Value root;
	Json::FastWriter fastWriter;

	Document document;
	/// <summary>
	/// Podsumowanie informacji o MainForm
	/// </summary>
	size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
		data->append((char*)ptr, size * nmemb);
		return size * nmemb;
	}

	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	public ref class MainForm : public System::Windows::Forms::Form
	{
		static int timezoneForTimer = 1;
	
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
			CURL* hnd = curl_easy_init();

			curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
			char linkChar[1100];
			std::string linkString = "https://community-open-weather-map.p.rapidapi.com/forecast/daily?";
			linkString.append(params_string({ {"q",toStandardString(this->textBox1->Text) }
				}));
			strcpy(linkChar, linkString.c_str());
			curl_easy_setopt(hnd, CURLOPT_URL, linkChar);

			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "x-rapidapi-host: community-open-weather-map.p.rapidapi.com");
			headers = curl_slist_append(headers, "x-rapidapi-key: f90acf6696msh3be9bb78dc5c56ep1a4015jsnb4b983675d4c");
			curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

			//System::String^ response_string;
			//System::String^ header_string;
			std::string readBuffer;
			//curl_easy_setopt(hnd, CURLOPT_WRITEDATA, response_string);
			//curl_easy_setopt(hnd, CURLOPT_HEADERDATA, header_string);
			curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

			CURLcode ret = curl_easy_perform(hnd);
			curl_easy_cleanup(hnd);
			String^ something = gcnew String(readBuffer.c_str());
			reader.parse(readBuffer, root);

			std::string code = fastWriter.write(root["cod"]);
			code.erase(std::remove(code.begin(), code.end(), '\"'));
			int codeInt = std::stoi(code);
			if (codeInt == 200) {
				//timezone
				std::string timezone = fastWriter.write(root["city"]["timezone"]).c_str();
				timezone.erase(std::remove(timezone.begin(), timezone.end(), '\"'));
				int timezoneInt = std::stoi(timezone);
				int result = timezoneInt / 3600;
				timezoneForTimer = result;
				std::string resultTimezone = (std::to_string(result) + " GMT");

				std::string main = fastWriter.write(root["list"][0]["weather"][0]["main"]);
				main.erase(std::remove(main.begin(), main.end(), '\"'));
				char snow[] = "S";
				char rain[] = "R";
				char sun[] = "e";
				char cloud[] = "l";
				char storm[] = "t";
				if (main[2] == sun[0]) {
					pictureBox2->Image = Image::FromFile("assets/sun.png");
				}
				else if (main[1] == cloud[0]) {
					pictureBox2->Image = Image::FromFile("assets/cloud.png");

				}
				else if (main[0] == snow[0]) {
					pictureBox2->Image = Image::FromFile("assets/snow.png");
				}
				else if (main[0] == rain[0]) {
					pictureBox2->Image = Image::FromFile("assets/rain.png");

				}
				else if (main[1] == storm[0]) {
					pictureBox2->Image = Image::FromFile("assets/storm.png");

				}

				//wschod
				std::string sunrise = fastWriter.write(root["list"][0]["sunrise"]).c_str();
				sunrise.erase(std::remove(sunrise.begin(), sunrise.end(), '\"'));
				time_t sunriseString = atoi(sunrise.c_str());
				tm sunriseTime = *localtime(&sunriseString);
				char bufor[64];
				strftime(bufor, sizeof(bufor), "%H:%M:%S", &sunriseTime);
				std::string sunriseResult = ("[container]: \"%s\"\n", bufor);
				this->labelSunriseData->Text = gcnew String(sunriseResult.c_str());

				//zachod
				std::string sunset = fastWriter.write(root["list"][0]["sunset"]).c_str();
				sunset.erase(std::remove(sunset.begin(), sunset.end(), '\"'));
				time_t sunsetString = atoi(sunset.c_str());
				tm sunsetTime = *localtime(&sunsetString);
				char bufor2[64];
				strftime(bufor, sizeof(bufor), "%H:%M:%S", &sunsetTime);
				std::string sunsetResult = ("[container]: \"%s\"\n", bufor);
				this->labelSunsetData->Text = gcnew String(sunsetResult.c_str());

				//chmury
				std::string clouds = fastWriter.write(root["list"][0]["clouds"]).c_str();
				clouds.erase(std::remove(clouds.begin(), clouds.end(), '\"'));
				int cloudsUtil = std::stoi(clouds);
				std::string resultChmury = (std::to_string(cloudsUtil) + "%");
				this->labelVisibilityData->Text = gcnew String(resultChmury.c_str());

				//cisnienie
				std::string pressure = fastWriter.write(root["list"][0]["pressure"]).c_str();
				pressure.erase(std::remove(pressure.begin(), pressure.end(), '\"'));
				int pressureUtil = std::stoi(pressure);
				std::string resultPressure = (std::to_string(pressureUtil) + "Pa");
				this->labelPressureData->Text = gcnew String(resultPressure.c_str());

				//temperatura
				std::string temp = fastWriter.write(root["list"][0]["temp"]["day"]).c_str();
				temp.erase(std::remove(temp.begin(), temp.end(), '\"'));
				int tempInt = std::stoi(temp) - 272;
				std::string resultTemp = (std::to_string(tempInt) + "°C");

				this->labelTempData->Text = gcnew String(resultTemp.c_str());

				//wilgotnosc
				std::string humidity = fastWriter.write(root["list"][0]["humidity"]).c_str();
				humidity.erase(std::remove(humidity.begin(), humidity.end(), '\"'));
				int humidityUtil = std::stoi(humidity);
				std::string resultHumidity = (std::to_string(humidityUtil) + "%");
				this->labelHumidityData->Text = gcnew String(resultHumidity.c_str());

				//wiatr
				std::string wind = fastWriter.write(root["list"][0]["speed"]).c_str();
				wind.erase(std::remove(wind.begin(), wind.end(), '\"'));
				int windInt = std::stoi(wind);
				std::string resultWind = (std::to_string(windInt) + "km/h");
				this->labelWindData->Text = gcnew String(resultWind.c_str());

				//min temp
				std::string minTemp = fastWriter.write(root["list"][0]["temp"]["min"]).c_str();
				minTemp.erase(std::remove(minTemp.begin(), minTemp.end(), '\"'));
				int minTempInt = std::stoi(minTemp) - 272;
				std::string resultMinTemp = (std::to_string(minTempInt) + "°C");
				this->labelMinTempData->Text = gcnew String(resultMinTemp.c_str());

				//maxtemp
				std::string maxTemp = fastWriter.write(root["list"][0]["temp"]["max"]).c_str();
				maxTemp.erase(std::remove(maxTemp.begin(), maxTemp.end(), '\"'));
				int maxTempInt = std::stoi(maxTemp) - 272;
				std::string resultMaxTemp = (std::to_string(maxTempInt) + "°C");
				this->labelMaxTempData->Text = gcnew String(resultMaxTemp.c_str());

				int tempList[7];
				int humidityList[7];
				std::string dayList[7];

				this->chart2->Series["Wilgotność [%]"]->Points->Clear();
				this->chart1->Series["Temperatura [°C]"]->Points->Clear();

				for (int i = 0; i <= 6; i++) {

					std::string dt = fastWriter.write(root["list"][i]["dt"]).c_str();
					dt.erase(std::remove(dt.begin(), dt.end(), '\"'));
					time_t dtString = atoi(dt.c_str());
					tm dtTime = *localtime(&dtString);
					char bufor[64];
					strftime(bufor, sizeof(bufor), "%d.%m", &dtTime);
					std::string dtResult = ("[container]: \"%s\"\n", bufor);
					dayList[i] = dtResult;

					std::string x = fastWriter.write(root["list"][i]["temp"]["day"]).c_str();
					x.erase(std::remove(x.begin(), x.end(), '\"'));
					tempList[i] = std::stoi(x) - 272;
					this->chart1->Series["Temperatura [°C]"]->Points->AddXY(gcnew String(dayList[i].c_str()), tempList[i]);

					std::string y = fastWriter.write(root["list"][i]["humidity"]).c_str();
					y.erase(std::remove(y.begin(), y.end(), '\"'));
					humidityList[i] = std::stoi(y);
					this->chart2->Series["Wilgotność [%]"]->Points->AddXY(gcnew String(dayList[i].c_str()), humidityList[i]);

				}
				// Ustawienie miasta
				this->label2->Text = this->textBox1->Text;
				this->label4->Text = this->textBox1->Text;
				this->label6->Text = this->textBox1->Text;


				std::string main1 = fastWriter.write(root["list"][0]["weather"][0]["main"]);
				main1.erase(std::remove(main1.begin(), main1.end(), '\"'));
				char s[] = "S";
				char r[] = "R";
				if (main1[0] == s[0]) {
					pictureBox37->Image = Image::FromFile("assets/winter2.png");

				}
				else if (main1[0] == r[0]) {
					pictureBox37->Image = Image::FromFile("assets/parasol.png");

				}

				if (tempInt < 2) {
					pictureBoxGirl->Image = Image::FromFile("assets/winter.png");
				}
				else if (tempInt >= 2 && tempInt < 15) {
					pictureBoxGirl->Image = Image::FromFile("assets/autumn.png");
				}
				else if (tempInt >= 15 && tempInt < 25) {
					pictureBoxGirl->Image = Image::FromFile("assets/spring.png");

				}
				else {
					pictureBoxGirl->Image = Image::FromFile("assets/summer.png");
					if (main1 != "Rain") {
						pictureBox37->Image = Image::FromFile("assets/summer2.png");
					}

				}
			}
			else {
				MessageBox::Show("Źle wpisane miasto", "Błąd");
			}
		}



	protected:
		/// <summary>
		/// Wyczyść wszystkie używane zasoby.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;




	private: System::Windows::Forms::Label^ labelTemp;
	private: System::Windows::Forms::Label^ labelVisibilityData;
	private: System::Windows::Forms::Label^ labelVisibility;



	private: System::Windows::Forms::Label^ labelMaxTemp;
	private: System::Windows::Forms::Label^ labelMinTempData;



	private: System::Windows::Forms::Label^ labelMinTemp;

	private: System::Windows::Forms::Label^ labelPressureData;






	private: System::Windows::Forms::Label^ labelSunsetData;
	private: System::Windows::Forms::Label^ labelWindData;
	private: System::Windows::Forms::Label^ labelWind;
	private: System::Windows::Forms::Label^ labelSunset;
	private: System::Windows::Forms::Label^ labelSunriseData;
	private: System::Windows::Forms::Label^ labelSunrise;
	private: System::Windows::Forms::Label^ labelHumidityData;
	private: System::Windows::Forms::Label^ labelHumidity;
	private: System::Windows::Forms::Label^ labelTempData;


	private: System::Windows::Forms::Label^ labelMaxTempData;

	private: System::Windows::Forms::Label^ labelPressure;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TabPage^ tabPage3;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox12;
	private: System::Windows::Forms::PictureBox^ pictureBox11;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::PictureBox^ pictureBox7;
	private: System::Windows::Forms::PictureBox^ pictureBox6;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox3;

	private: System::Windows::Forms::PictureBox^ pictureBox14;


	private: System::Windows::Forms::PictureBox^ pictureBox18;
	private: System::Windows::Forms::PictureBox^ pictureBox17;
	private: System::Windows::Forms::PictureBox^ pictureBox16;
	private: System::Windows::Forms::PictureBox^ pictureBox15;
	private: System::Windows::Forms::PictureBox^ pictureBox23;
	private: System::Windows::Forms::PictureBox^ pictureBox22;
	private: System::Windows::Forms::PictureBox^ pictureBox21;
	private: System::Windows::Forms::PictureBox^ pictureBox20;
	private: System::Windows::Forms::PictureBox^ pictureBoxGirl;




	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::PictureBox^ pictureBox25;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::PictureBox^ pictureBox24;
	private: System::Windows::Forms::PictureBox^ pictureBox27;
	private: System::Windows::Forms::PictureBox^ pictureBox26;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::PictureBox^ pictureBox28;
	private: System::Windows::Forms::PictureBox^ pictureBox29;
	private: System::Windows::Forms::PictureBox^ pictureBox30;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::PictureBox^ pictureBox31;
	private: System::Windows::Forms::PictureBox^ pictureBox32;
	private: System::Windows::Forms::PictureBox^ pictureBox33;
	private: System::Windows::Forms::PictureBox^ pictureBox34;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::PictureBox^ pictureBox35;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
	private: System::Windows::Forms::Label^ dataLabel;
	private: System::Windows::Forms::PictureBox^ pictureBox36;
private: System::Windows::Forms::PictureBox^ pictureBox37;
private: System::Windows::Forms::Timer^ timer1;
private: System::Windows::Forms::PictureBox^ pictureBox2;
private: System::Windows::Forms::PictureBox^ pictureBox19;
private: System::ComponentModel::IContainer^ components;












	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox37 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBoxGirl = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox22 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox21 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->labelMinTempData = (gcnew System::Windows::Forms::Label());
			this->labelMaxTempData = (gcnew System::Windows::Forms::Label());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->labelMaxTemp = (gcnew System::Windows::Forms::Label());
			this->labelWind = (gcnew System::Windows::Forms::Label());
			this->labelMinTemp = (gcnew System::Windows::Forms::Label());
			this->labelHumidity = (gcnew System::Windows::Forms::Label());
			this->labelVisibilityData = (gcnew System::Windows::Forms::Label());
			this->labelWindData = (gcnew System::Windows::Forms::Label());
			this->labelPressureData = (gcnew System::Windows::Forms::Label());
			this->labelSunsetData = (gcnew System::Windows::Forms::Label());
			this->labelHumidityData = (gcnew System::Windows::Forms::Label());
			this->labelVisibility = (gcnew System::Windows::Forms::Label());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->labelTempData = (gcnew System::Windows::Forms::Label());
			this->labelSunriseData = (gcnew System::Windows::Forms::Label());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->labelPressure = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->labelSunset = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelSunrise = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->labelTemp = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pictureBox26 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox27 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox25 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox24 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pictureBox28 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox29 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox30 = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pictureBox31 = (gcnew System::Windows::Forms::PictureBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->dataLabel = (gcnew System::Windows::Forms::Label());
			this->pictureBox36 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox32 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox33 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox34 = (gcnew System::Windows::Forms::PictureBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->pictureBox35 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox37))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxGirl))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->BeginInit();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::RoyalBlue;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->button1->ForeColor = System::Drawing::Color::White;
			this->button1->Location = System::Drawing::Point(653, 123);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(413, 31);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Sprawdź";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Margin = System::Windows::Forms::Padding(4);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1136, 738);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->pictureBox2);
			this->tabPage1->Controls->Add(this->pictureBox37);
			this->tabPage1->Controls->Add(this->pictureBoxGirl);
			this->tabPage1->Controls->Add(this->pictureBox23);
			this->tabPage1->Controls->Add(this->pictureBox22);
			this->tabPage1->Controls->Add(this->pictureBox21);
			this->tabPage1->Controls->Add(this->pictureBox20);
			this->tabPage1->Controls->Add(this->pictureBox19);
			this->tabPage1->Controls->Add(this->pictureBox18);
			this->tabPage1->Controls->Add(this->pictureBox17);
			this->tabPage1->Controls->Add(this->pictureBox16);
			this->tabPage1->Controls->Add(this->pictureBox15);
			this->tabPage1->Controls->Add(this->pictureBox14);
			this->tabPage1->Controls->Add(this->pictureBox11);
			this->tabPage1->Controls->Add(this->pictureBox12);
			this->tabPage1->Controls->Add(this->labelMinTempData);
			this->tabPage1->Controls->Add(this->labelMaxTempData);
			this->tabPage1->Controls->Add(this->pictureBox6);
			this->tabPage1->Controls->Add(this->pictureBox5);
			this->tabPage1->Controls->Add(this->labelMaxTemp);
			this->tabPage1->Controls->Add(this->labelWind);
			this->tabPage1->Controls->Add(this->labelMinTemp);
			this->tabPage1->Controls->Add(this->labelHumidity);
			this->tabPage1->Controls->Add(this->labelVisibilityData);
			this->tabPage1->Controls->Add(this->labelWindData);
			this->tabPage1->Controls->Add(this->labelPressureData);
			this->tabPage1->Controls->Add(this->labelSunsetData);
			this->tabPage1->Controls->Add(this->labelHumidityData);
			this->tabPage1->Controls->Add(this->labelVisibility);
			this->tabPage1->Controls->Add(this->pictureBox10);
			this->tabPage1->Controls->Add(this->labelTempData);
			this->tabPage1->Controls->Add(this->labelSunriseData);
			this->tabPage1->Controls->Add(this->pictureBox9);
			this->tabPage1->Controls->Add(this->pictureBox8);
			this->tabPage1->Controls->Add(this->pictureBox7);
			this->tabPage1->Controls->Add(this->labelPressure);
			this->tabPage1->Controls->Add(this->pictureBox4);
			this->tabPage1->Controls->Add(this->pictureBox3);
			this->tabPage1->Controls->Add(this->labelSunset);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->labelSunrise);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->labelTemp);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Margin = System::Windows::Forms::Padding(4);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(4);
			this->tabPage1->Size = System::Drawing::Size(1128, 709);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Start";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &MainForm::tabPage1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(51, 169);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(219, 106);
			this->pictureBox2->TabIndex = 41;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MainForm::pictureBox2_Click);
			// 
			// pictureBox37
			// 
			this->pictureBox37->Location = System::Drawing::Point(945, 198);
			this->pictureBox37->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox37->Name = L"pictureBox37";
			this->pictureBox37->Size = System::Drawing::Size(176, 438);
			this->pictureBox37->TabIndex = 40;
			this->pictureBox37->TabStop = false;
			// 
			// pictureBoxGirl
			// 
			this->pictureBoxGirl->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBoxGirl.Image")));
			this->pictureBoxGirl->Location = System::Drawing::Point(571, 206);
			this->pictureBoxGirl->Margin = System::Windows::Forms::Padding(4);
			this->pictureBoxGirl->Name = L"pictureBoxGirl";
			this->pictureBoxGirl->Size = System::Drawing::Size(400, 431);
			this->pictureBoxGirl->TabIndex = 39;
			this->pictureBoxGirl->TabStop = false;
			// 
			// pictureBox23
			// 
			this->pictureBox23->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox23.Image")));
			this->pictureBox23->Location = System::Drawing::Point(31, 567);
			this->pictureBox23->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->Size = System::Drawing::Size(13, 69);
			this->pictureBox23->TabIndex = 37;
			this->pictureBox23->TabStop = false;
			// 
			// pictureBox22
			// 
			this->pictureBox22->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox22.Image")));
			this->pictureBox22->Location = System::Drawing::Point(31, 478);
			this->pictureBox22->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox22->Name = L"pictureBox22";
			this->pictureBox22->Size = System::Drawing::Size(13, 69);
			this->pictureBox22->TabIndex = 36;
			this->pictureBox22->TabStop = false;
			// 
			// pictureBox21
			// 
			this->pictureBox21->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox21.Image")));
			this->pictureBox21->Location = System::Drawing::Point(31, 388);
			this->pictureBox21->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox21->Name = L"pictureBox21";
			this->pictureBox21->Size = System::Drawing::Size(13, 69);
			this->pictureBox21->TabIndex = 35;
			this->pictureBox21->TabStop = false;
			// 
			// pictureBox20
			// 
			this->pictureBox20->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox20.Image")));
			this->pictureBox20->Location = System::Drawing::Point(31, 297);
			this->pictureBox20->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->Size = System::Drawing::Size(13, 69);
			this->pictureBox20->TabIndex = 34;
			this->pictureBox20->TabStop = false;
			// 
			// pictureBox19
			// 
			this->pictureBox19->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox19.Image")));
			this->pictureBox19->Location = System::Drawing::Point(31, 185);
			this->pictureBox19->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->Size = System::Drawing::Size(13, 69);
			this->pictureBox19->TabIndex = 33;
			this->pictureBox19->TabStop = false;
			// 
			// pictureBox18
			// 
			this->pictureBox18->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox18.Image")));
			this->pictureBox18->Location = System::Drawing::Point(291, 567);
			this->pictureBox18->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->Size = System::Drawing::Size(13, 69);
			this->pictureBox18->TabIndex = 32;
			this->pictureBox18->TabStop = false;
			// 
			// pictureBox17
			// 
			this->pictureBox17->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox17.Image")));
			this->pictureBox17->Location = System::Drawing::Point(292, 478);
			this->pictureBox17->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->Size = System::Drawing::Size(13, 69);
			this->pictureBox17->TabIndex = 31;
			this->pictureBox17->TabStop = false;
			// 
			// pictureBox16
			// 
			this->pictureBox16->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox16.Image")));
			this->pictureBox16->Location = System::Drawing::Point(291, 386);
			this->pictureBox16->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->Size = System::Drawing::Size(13, 69);
			this->pictureBox16->TabIndex = 30;
			this->pictureBox16->TabStop = false;
			// 
			// pictureBox15
			// 
			this->pictureBox15->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox15.Image")));
			this->pictureBox15->Location = System::Drawing::Point(292, 297);
			this->pictureBox15->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->Size = System::Drawing::Size(13, 69);
			this->pictureBox15->TabIndex = 29;
			this->pictureBox15->TabStop = false;
			// 
			// pictureBox14
			// 
			this->pictureBox14->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox14.Image")));
			this->pictureBox14->Location = System::Drawing::Point(292, 206);
			this->pictureBox14->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->Size = System::Drawing::Size(13, 69);
			this->pictureBox14->TabIndex = 28;
			this->pictureBox14->TabStop = false;
			// 
			// pictureBox11
			// 
			this->pictureBox11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.Image")));
			this->pictureBox11->Location = System::Drawing::Point(308, 597);
			this->pictureBox11->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(43, 39);
			this->pictureBox11->TabIndex = 15;
			this->pictureBox11->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.Image")));
			this->pictureBox12->Location = System::Drawing::Point(309, 507);
			this->pictureBox12->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(43, 39);
			this->pictureBox12->TabIndex = 16;
			this->pictureBox12->TabStop = false;
			// 
			// labelMinTempData
			// 
			this->labelMinTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMinTempData->AutoSize = true;
			this->labelMinTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelMinTempData->Location = System::Drawing::Point(360, 512);
			this->labelMinTempData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelMinTempData->Name = L"labelMinTempData";
			this->labelMinTempData->Size = System::Drawing::Size(166, 25);
			this->labelMinTempData->TabIndex = 23;
			this->labelMinTempData->Text = L"Min. Temperature";
			this->labelMinTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelMaxTempData
			// 
			this->labelMaxTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMaxTempData->AutoSize = true;
			this->labelMaxTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelMaxTempData->Location = System::Drawing::Point(359, 602);
			this->labelMaxTempData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelMaxTempData->Name = L"labelMaxTempData";
			this->labelMaxTempData->Size = System::Drawing::Size(111, 25);
			this->labelMaxTempData->TabIndex = 26;
			this->labelMaxTempData->Text = L"Max. Temp";
			this->labelMaxTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(308, 416);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(43, 39);
			this->pictureBox6->TabIndex = 10;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(309, 326);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(43, 39);
			this->pictureBox5->TabIndex = 9;
			this->pictureBox5->TabStop = false;
			// 
			// labelMaxTemp
			// 
			this->labelMaxTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMaxTemp->AutoSize = true;
			this->labelMaxTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelMaxTemp->Location = System::Drawing::Point(303, 561);
			this->labelMaxTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelMaxTemp->Name = L"labelMaxTemp";
			this->labelMaxTemp->Size = System::Drawing::Size(218, 29);
			this->labelMaxTemp->TabIndex = 24;
			this->labelMaxTemp->Text = L"Max temperatura";
			this->labelMaxTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelWind
			// 
			this->labelWind->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelWind->AutoSize = true;
			this->labelWind->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelWind->Location = System::Drawing::Point(303, 382);
			this->labelWind->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelWind->Name = L"labelWind";
			this->labelWind->Size = System::Drawing::Size(77, 29);
			this->labelWind->TabIndex = 11;
			this->labelWind->Text = L"Wiatr";
			this->labelWind->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelMinTemp
			// 
			this->labelMinTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMinTemp->AutoSize = true;
			this->labelMinTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelMinTemp->Location = System::Drawing::Point(304, 473);
			this->labelMinTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelMinTemp->Name = L"labelMinTemp";
			this->labelMinTemp->Size = System::Drawing::Size(220, 29);
			this->labelMinTemp->TabIndex = 22;
			this->labelMinTemp->Text = L"Min. temperatura";
			this->labelMinTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelHumidity
			// 
			this->labelHumidity->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelHumidity->AutoSize = true;
			this->labelHumidity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelHumidity->Location = System::Drawing::Point(304, 292);
			this->labelHumidity->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelHumidity->Name = L"labelHumidity";
			this->labelHumidity->Size = System::Drawing::Size(148, 29);
			this->labelHumidity->TabIndex = 7;
			this->labelHumidity->Text = L"Wilgotność";
			this->labelHumidity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelHumidity->Click += gcnew System::EventHandler(this, &MainForm::labelHumidity_Click);
			// 
			// labelVisibilityData
			// 
			this->labelVisibilityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelVisibilityData->AutoSize = true;
			this->labelVisibilityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelVisibilityData->Location = System::Drawing::Point(99, 512);
			this->labelVisibilityData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelVisibilityData->Name = L"labelVisibilityData";
			this->labelVisibilityData->Size = System::Drawing::Size(82, 25);
			this->labelVisibilityData->TabIndex = 25;
			this->labelVisibilityData->Text = L"Visibility";
			this->labelVisibilityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelWindData
			// 
			this->labelWindData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelWindData->AutoSize = true;
			this->labelWindData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelWindData->Location = System::Drawing::Point(359, 416);
			this->labelWindData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelWindData->Name = L"labelWindData";
			this->labelWindData->Size = System::Drawing::Size(58, 25);
			this->labelWindData->TabIndex = 12;
			this->labelWindData->Text = L"Wind";
			this->labelWindData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelPressureData
			// 
			this->labelPressureData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelPressureData->AutoSize = true;
			this->labelPressureData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelPressureData->Location = System::Drawing::Point(99, 602);
			this->labelPressureData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelPressureData->Name = L"labelPressureData";
			this->labelPressureData->Size = System::Drawing::Size(90, 25);
			this->labelPressureData->TabIndex = 18;
			this->labelPressureData->Text = L"Pressure";
			this->labelPressureData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunsetData
			// 
			this->labelSunsetData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunsetData->AutoSize = true;
			this->labelSunsetData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelSunsetData->Location = System::Drawing::Point(99, 421);
			this->labelSunsetData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSunsetData->Name = L"labelSunsetData";
			this->labelSunsetData->Size = System::Drawing::Size(74, 25);
			this->labelSunsetData->TabIndex = 16;
			this->labelSunsetData->Text = L"Sunset";
			this->labelSunsetData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelHumidityData
			// 
			this->labelHumidityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelHumidityData->AutoSize = true;
			this->labelHumidityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelHumidityData->Location = System::Drawing::Point(360, 332);
			this->labelHumidityData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelHumidityData->Name = L"labelHumidityData";
			this->labelHumidityData->Size = System::Drawing::Size(87, 25);
			this->labelHumidityData->TabIndex = 8;
			this->labelHumidityData->Text = L"Humidity";
			this->labelHumidityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelVisibility
			// 
			this->labelVisibility->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelVisibility->AutoSize = true;
			this->labelVisibility->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelVisibility->Location = System::Drawing::Point(43, 471);
			this->labelVisibility->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelVisibility->Name = L"labelVisibility";
			this->labelVisibility->Size = System::Drawing::Size(161, 29);
			this->labelVisibility->TabIndex = 18;
			this->labelVisibility->Text = L"Widoczność";
			this->labelVisibility->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelVisibility->Click += gcnew System::EventHandler(this, &MainForm::label7_Click);
			// 
			// pictureBox10
			// 
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(48, 507);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(43, 39);
			this->pictureBox10->TabIndex = 14;
			this->pictureBox10->TabStop = false;
			// 
			// labelTempData
			// 
			this->labelTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTempData->AutoSize = true;
			this->labelTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelTempData->Location = System::Drawing::Point(360, 242);
			this->labelTempData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTempData->Name = L"labelTempData";
			this->labelTempData->Size = System::Drawing::Size(124, 25);
			this->labelTempData->TabIndex = 6;
			this->labelTempData->Text = L"Temperature";
			this->labelTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunriseData
			// 
			this->labelSunriseData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunriseData->AutoSize = true;
			this->labelSunriseData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelSunriseData->Location = System::Drawing::Point(99, 331);
			this->labelSunriseData->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSunriseData->Name = L"labelSunriseData";
			this->labelSunriseData->Size = System::Drawing::Size(79, 25);
			this->labelSunriseData->TabIndex = 14;
			this->labelSunriseData->Text = L"Sunrise";
			this->labelSunriseData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox9
			// 
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(48, 597);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(43, 39);
			this->pictureBox9->TabIndex = 13;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(48, 417);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(43, 39);
			this->pictureBox8->TabIndex = 12;
			this->pictureBox8->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(48, 326);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(43, 39);
			this->pictureBox7->TabIndex = 11;
			this->pictureBox7->TabStop = false;
			// 
			// labelPressure
			// 
			this->labelPressure->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelPressure->AutoSize = true;
			this->labelPressure->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelPressure->Location = System::Drawing::Point(43, 561);
			this->labelPressure->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelPressure->Name = L"labelPressure";
			this->labelPressure->Size = System::Drawing::Size(127, 29);
			this->labelPressure->TabIndex = 17;
			this->labelPressure->Text = L"Ciśnienie";
			this->labelPressure->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelPressure->Click += gcnew System::EventHandler(this, &MainForm::label10_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(309, 235);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(43, 39);
			this->pictureBox4->TabIndex = 8;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(653, 78);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(43, 39);
			this->pictureBox3->TabIndex = 7;
			this->pictureBox3->TabStop = false;
			// 
			// labelSunset
			// 
			this->labelSunset->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunset->AutoSize = true;
			this->labelSunset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelSunset->Location = System::Drawing::Point(43, 382);
			this->labelSunset->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSunset->Name = L"labelSunset";
			this->labelSunset->Size = System::Drawing::Size(103, 29);
			this->labelSunset->TabIndex = 15;
			this->labelSunset->Text = L"Zachód";
			this->labelSunset->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label1->Location = System::Drawing::Point(671, 27);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(371, 52);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Twoja lokalizacja";
			// 
			// labelSunrise
			// 
			this->labelSunrise->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunrise->AutoSize = true;
			this->labelSunrise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelSunrise->Location = System::Drawing::Point(43, 292);
			this->labelSunrise->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelSunrise->Name = L"labelSunrise";
			this->labelSunrise->Size = System::Drawing::Size(111, 29);
			this->labelSunrise->TabIndex = 13;
			this->labelSunrise->Text = L"Wschód";
			this->labelSunrise->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(19, 27);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(424, 133);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox1->Location = System::Drawing::Point(704, 86);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(361, 26);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"Rzeszow";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
			// 
			// labelTemp
			// 
			this->labelTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTemp->AutoSize = true;
			this->labelTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelTemp->Location = System::Drawing::Point(303, 198);
			this->labelTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelTemp->Name = L"labelTemp";
			this->labelTemp->Size = System::Drawing::Size(168, 29);
			this->labelTemp->TabIndex = 5;
			this->labelTemp->Text = L"Temperatura";
			this->labelTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelTemp->Click += gcnew System::EventHandler(this, &MainForm::label1_Click_3);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->chart1);
			this->tabPage2->Controls->Add(this->pictureBox26);
			this->tabPage2->Controls->Add(this->pictureBox27);
			this->tabPage2->Controls->Add(this->pictureBox25);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->pictureBox24);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Margin = System::Windows::Forms::Padding(4);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(4);
			this->tabPage2->Size = System::Drawing::Size(1128, 709);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Temperatura 7 dni";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// chart1
			// 
			chartArea3->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->chart1->Legends->Add(legend3);
			this->chart1->Location = System::Drawing::Point(19, 182);
			this->chart1->Margin = System::Windows::Forms::Padding(4);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::EarthTones;
			series3->ChartArea = L"ChartArea1";
			series3->Legend = L"Legend1";
			series3->Name = L"Temperatura [°C]";
			this->chart1->Series->Add(series3);
			this->chart1->Size = System::Drawing::Size(1005, 466);
			this->chart1->TabIndex = 35;
			this->chart1->Text = L"chart1";
			// 
			// pictureBox26
			// 
			this->pictureBox26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox26.Image")));
			this->pictureBox26->Location = System::Drawing::Point(509, 26);
			this->pictureBox26->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox26->Name = L"pictureBox26";
			this->pictureBox26->Size = System::Drawing::Size(144, 134);
			this->pictureBox26->TabIndex = 34;
			this->pictureBox26->TabStop = false;
			// 
			// pictureBox27
			// 
			this->pictureBox27->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox27.Image")));
			this->pictureBox27->Location = System::Drawing::Point(687, 89);
			this->pictureBox27->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox27->Name = L"pictureBox27";
			this->pictureBox27->Size = System::Drawing::Size(43, 39);
			this->pictureBox27->TabIndex = 33;
			this->pictureBox27->TabStop = false;
			// 
			// pictureBox25
			// 
			this->pictureBox25->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox25.Image")));
			this->pictureBox25->Location = System::Drawing::Point(669, 59);
			this->pictureBox25->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox25->Name = L"pictureBox25";
			this->pictureBox25->Size = System::Drawing::Size(13, 69);
			this->pictureBox25->TabIndex = 32;
			this->pictureBox25->TabStop = false;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->label2->Location = System::Drawing::Point(737, 96);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(91, 25);
			this->label2->TabIndex = 30;
			this->label2->Text = L"Rzeszow";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->label3->Location = System::Drawing::Point(680, 52);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(94, 29);
			this->label3->TabIndex = 29;
			this->label3->Text = L"Miasto";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox24
			// 
			this->pictureBox24->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox24.Image")));
			this->pictureBox24->Location = System::Drawing::Point(19, 27);
			this->pictureBox24->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox24->Name = L"pictureBox24";
			this->pictureBox24->Size = System::Drawing::Size(424, 133);
			this->pictureBox24->TabIndex = 5;
			this->pictureBox24->TabStop = false;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->chart2);
			this->tabPage3->Controls->Add(this->pictureBox28);
			this->tabPage3->Controls->Add(this->pictureBox29);
			this->tabPage3->Controls->Add(this->pictureBox30);
			this->tabPage3->Controls->Add(this->label4);
			this->tabPage3->Controls->Add(this->label5);
			this->tabPage3->Controls->Add(this->pictureBox31);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Margin = System::Windows::Forms::Padding(4);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(4);
			this->tabPage3->Size = System::Drawing::Size(1128, 709);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Wilgotność 7 dni";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// chart2
			// 
			chartArea4->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea4);
			legend4->Name = L"Legend1";
			this->chart2->Legends->Add(legend4);
			this->chart2->Location = System::Drawing::Point(19, 182);
			this->chart2->Margin = System::Windows::Forms::Padding(4);
			this->chart2->Name = L"chart2";
			series4->ChartArea = L"ChartArea1";
			series4->Legend = L"Legend1";
			series4->Name = L"Wilgotność [%]";
			this->chart2->Series->Add(series4);
			this->chart2->Size = System::Drawing::Size(1005, 466);
			this->chart2->TabIndex = 41;
			this->chart2->Text = L"chart2";
			// 
			// pictureBox28
			// 
			this->pictureBox28->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox28.Image")));
			this->pictureBox28->Location = System::Drawing::Point(509, 26);
			this->pictureBox28->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox28->Name = L"pictureBox28";
			this->pictureBox28->Size = System::Drawing::Size(144, 134);
			this->pictureBox28->TabIndex = 40;
			this->pictureBox28->TabStop = false;
			// 
			// pictureBox29
			// 
			this->pictureBox29->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox29.Image")));
			this->pictureBox29->Location = System::Drawing::Point(687, 89);
			this->pictureBox29->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox29->Name = L"pictureBox29";
			this->pictureBox29->Size = System::Drawing::Size(43, 39);
			this->pictureBox29->TabIndex = 39;
			this->pictureBox29->TabStop = false;
			// 
			// pictureBox30
			// 
			this->pictureBox30->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox30.Image")));
			this->pictureBox30->Location = System::Drawing::Point(669, 59);
			this->pictureBox30->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox30->Name = L"pictureBox30";
			this->pictureBox30->Size = System::Drawing::Size(13, 69);
			this->pictureBox30->TabIndex = 38;
			this->pictureBox30->TabStop = false;
			// 
			// label4
			// 
			this->label4->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->label4->Location = System::Drawing::Point(737, 96);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(91, 25);
			this->label4->TabIndex = 37;
			this->label4->Text = L"Rzeszow";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label5
			// 
			this->label5->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->label5->Location = System::Drawing::Point(680, 52);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(94, 29);
			this->label5->TabIndex = 36;
			this->label5->Text = L"Miasto";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox31
			// 
			this->pictureBox31->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox31.Image")));
			this->pictureBox31->Location = System::Drawing::Point(19, 27);
			this->pictureBox31->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox31->Name = L"pictureBox31";
			this->pictureBox31->Size = System::Drawing::Size(424, 133);
			this->pictureBox31->TabIndex = 35;
			this->pictureBox31->TabStop = false;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->dataLabel);
			this->tabPage4->Controls->Add(this->pictureBox36);
			this->tabPage4->Controls->Add(this->pictureBox32);
			this->tabPage4->Controls->Add(this->pictureBox33);
			this->tabPage4->Controls->Add(this->pictureBox34);
			this->tabPage4->Controls->Add(this->label6);
			this->tabPage4->Controls->Add(this->label7);
			this->tabPage4->Controls->Add(this->pictureBox35);
			this->tabPage4->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 55, System::Drawing::FontStyle::Bold));
			this->tabPage4->ForeColor = System::Drawing::SystemColors::ControlText;
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Margin = System::Windows::Forms::Padding(4);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(4);
			this->tabPage4->Size = System::Drawing::Size(1128, 709);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Zegar";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// dataLabel
			// 
			this->dataLabel->AutoSize = true;
			this->dataLabel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(74)),
				static_cast<System::Int32>(static_cast<System::Byte>(94)));
			this->dataLabel->Font = (gcnew System::Drawing::Font(L"Arial Black", 49, System::Drawing::FontStyle::Bold));
			this->dataLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->dataLabel->Location = System::Drawing::Point(232, 341);
			this->dataLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->dataLabel->Name = L"dataLabel";
			this->dataLabel->Size = System::Drawing::Size(541, 115);
			this->dataLabel->TabIndex = 48;
			this->dataLabel->Text = L"14 : 28 : 33";
			this->dataLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox36
			// 
			this->pictureBox36->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox36.Image")));
			this->pictureBox36->Location = System::Drawing::Point(183, 231);
			this->pictureBox36->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox36->Name = L"pictureBox36";
			this->pictureBox36->Size = System::Drawing::Size(689, 362);
			this->pictureBox36->TabIndex = 47;
			this->pictureBox36->TabStop = false;
			// 
			// pictureBox32
			// 
			this->pictureBox32->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox32.Image")));
			this->pictureBox32->Location = System::Drawing::Point(509, 26);
			this->pictureBox32->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox32->Name = L"pictureBox32";
			this->pictureBox32->Size = System::Drawing::Size(144, 134);
			this->pictureBox32->TabIndex = 46;
			this->pictureBox32->TabStop = false;
			// 
			// pictureBox33
			// 
			this->pictureBox33->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox33.Image")));
			this->pictureBox33->Location = System::Drawing::Point(687, 89);
			this->pictureBox33->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox33->Name = L"pictureBox33";
			this->pictureBox33->Size = System::Drawing::Size(43, 39);
			this->pictureBox33->TabIndex = 45;
			this->pictureBox33->TabStop = false;
			// 
			// pictureBox34
			// 
			this->pictureBox34->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox34.Image")));
			this->pictureBox34->Location = System::Drawing::Point(669, 59);
			this->pictureBox34->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox34->Name = L"pictureBox34";
			this->pictureBox34->Size = System::Drawing::Size(13, 69);
			this->pictureBox34->TabIndex = 44;
			this->pictureBox34->TabStop = false;
			// 
			// label6
			// 
			this->label6->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->label6->Location = System::Drawing::Point(737, 96);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(91, 25);
			this->label6->TabIndex = 43;
			this->label6->Text = L"Rzeszow";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label7
			// 
			this->label7->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->label7->Location = System::Drawing::Point(680, 52);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(94, 29);
			this->label7->TabIndex = 42;
			this->label7->Text = L"Miasto";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox35
			// 
			this->pictureBox35->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox35.Image")));
			this->pictureBox35->Location = System::Drawing::Point(19, 27);
			this->pictureBox35->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox35->Name = L"pictureBox35";
			this->pictureBox35->Size = System::Drawing::Size(424, 133);
			this->pictureBox35->TabIndex = 41;
			this->pictureBox35->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1133, 686);
			this->Controls->Add(this->tabControl1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MainForm";
			this->Text = L"Pogodynka";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox37))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxGirl))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox24))->EndInit();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox31))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox35))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tabPage1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void splitContainer1_Panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
	private: System::Void splitContainer1_Panel2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void splitContainer1_Panel1_Paint_1(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}

	private: System::Void labelCityData_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click_3(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label10_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void labelHumidity_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		CURL* hnd = curl_easy_init();

		curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET"); 
		char linkChar[1100];
		std::string linkString = "https://community-open-weather-map.p.rapidapi.com/forecast/daily?";
		linkString.append(params_string({ {"q",toStandardString(this->textBox1->Text) }}));
		strcpy(linkChar, linkString.c_str());
		curl_easy_setopt(hnd, CURLOPT_URL, linkChar);

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "x-rapidapi-host: community-open-weather-map.p.rapidapi.com");
		headers = curl_slist_append(headers, "x-rapidapi-key: f90acf6696msh3be9bb78dc5c56ep1a4015jsnb4b983675d4c");
		curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

		//System::String^ response_string;
		//System::String^ header_string;
		std::string readBuffer;
		//curl_easy_setopt(hnd, CURLOPT_WRITEDATA, response_string);
		//curl_easy_setopt(hnd, CURLOPT_HEADERDATA, header_string);
		curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);

		CURLcode ret = curl_easy_perform(hnd);
		curl_easy_cleanup(hnd);
		String^ something = gcnew String(readBuffer.c_str());
		reader.parse(readBuffer, root);

		std::string code = fastWriter.write(root["cod"]);
		code.erase(std::remove(code.begin(), code.end(), '\"'));
		int codeInt = std::stoi(code);
		if (codeInt == 200) {
			//timezone
			std::string timezone = fastWriter.write(root["city"]["timezone"]).c_str();
			timezone.erase(std::remove(timezone.begin(), timezone.end(), '\"'));
			int timezoneInt = std::stoi(timezone);
			int result = timezoneInt / 3600;
			timezoneForTimer = result;
			std::string resultTimezone = (std::to_string(result) + " GMT");

			std::string main = fastWriter.write(root["list"][0]["weather"][0]["main"]);
			main.erase(std::remove(main.begin(), main.end(), '\"'));			
			char s[] = "S";
			char r[] = "R";
			char sun[] = "e";
			char cloud[] = "l";
			char storm[] = "t";
			if (main[2] == sun[0]) {
				pictureBox2->Image = Image::FromFile("assets/sun.png");
			}
			else if (main[1] == cloud[0]) {
				pictureBox2->Image = Image::FromFile("assets/cloud.png");

			}
			else if (main[0] == s[0]) {
				pictureBox2->Image = Image::FromFile("assets/snow.png");
			}
			else if (main[0] == r[0]) {
				pictureBox2->Image = Image::FromFile("assets/rain.png");

			}
			else if (main[1] == storm[0]) {
				pictureBox2->Image = Image::FromFile("assets/storm.png");

			}
			//wschod
			std::string sunrise = fastWriter.write(root["list"][0]["sunrise"]).c_str();
			sunrise.erase(std::remove(sunrise.begin(), sunrise.end(), '\"'));
			time_t sunriseString = atoi(sunrise.c_str());
			tm sunriseTime = *localtime(&sunriseString);
			char bufor[64];
			strftime(bufor, sizeof(bufor), "%H:%M:%S", &sunriseTime);
			std::string sunriseResult = ("[container]: \"%s\"\n", bufor);
			this->labelSunriseData->Text = gcnew String(sunriseResult.c_str());

			//zachod
			std::string sunset = fastWriter.write(root["list"][0]["sunset"]).c_str();
			sunset.erase(std::remove(sunset.begin(), sunset.end(), '\"'));
			time_t sunsetString = atoi(sunset.c_str());
			tm sunsetTime = *localtime(&sunsetString);
			char bufor2[64];
			strftime(bufor, sizeof(bufor), "%H:%M:%S", &sunsetTime);
			std::string sunsetResult = ("[container]: \"%s\"\n", bufor);
			this->labelSunsetData->Text = gcnew String(sunsetResult.c_str());

			//chmury
			std::string clouds = fastWriter.write(root["list"][0]["clouds"]).c_str();
			clouds.erase(std::remove(clouds.begin(), clouds.end(), '\"'));
			int cloudsUtil = std::stoi(clouds);
			std::string resultChmury = (std::to_string(cloudsUtil) + "%");
			this->labelVisibilityData->Text = gcnew String(resultChmury.c_str());

			//cisnienie
			std::string pressure = fastWriter.write(root["list"][0]["pressure"]).c_str();
			pressure.erase(std::remove(pressure.begin(), pressure.end(), '\"'));
			int pressureUtil = std::stoi(pressure);
			std::string resultPressure = (std::to_string(pressureUtil) + "Pa");
			this->labelPressureData->Text = gcnew String(resultPressure.c_str());

			//temperatura
			std::string temp = fastWriter.write(root["list"][0]["temp"]["day"]).c_str();
			temp.erase(std::remove(temp.begin(), temp.end(), '\"'));
			int tempInt = std::stoi(temp) - 272;
			std::string resultTemp = (std::to_string(tempInt) + "°C");

			this->labelTempData->Text = gcnew String(resultTemp.c_str());

			//wilgotnosc
			std::string humidity = fastWriter.write(root["list"][0]["humidity"]).c_str();
			humidity.erase(std::remove(humidity.begin(), humidity.end(), '\"'));
			int humidityUtil = std::stoi(humidity);
			std::string resultHumidity = (std::to_string(humidityUtil) + "%");
			this->labelHumidityData->Text = gcnew String(resultHumidity.c_str());

			//wiatr
			std::string wind = fastWriter.write(root["list"][0]["speed"]).c_str();
			wind.erase(std::remove(wind.begin(), wind.end(), '\"'));
			int windInt = std::stoi(wind);
			std::string resultWind = (std::to_string(windInt) + "km/h");
			this->labelWindData->Text = gcnew String(resultWind.c_str());

			//min temp
			std::string minTemp = fastWriter.write(root["list"][0]["temp"]["min"]).c_str();
			minTemp.erase(std::remove(minTemp.begin(), minTemp.end(), '\"'));
			int minTempInt = std::stoi(minTemp) - 272;
			std::string resultMinTemp = (std::to_string(minTempInt) + "°C");
			this->labelMinTempData->Text = gcnew String(resultMinTemp.c_str());

			//maxtemp
			std::string maxTemp = fastWriter.write(root["list"][0]["temp"]["max"]).c_str();
			maxTemp.erase(std::remove(maxTemp.begin(), maxTemp.end(), '\"'));
			int maxTempInt = std::stoi(maxTemp) - 272;
			std::string resultMaxTemp = (std::to_string(maxTempInt) + "°C");
			this->labelMaxTempData->Text = gcnew String(resultMaxTemp.c_str());

			int tempList[7];
			int humidityList[7];
			std::string dayList[7];

			this->chart2->Series["Wilgotność [%]"]->Points->Clear();
			this->chart1->Series["Temperatura [°C]"]->Points->Clear();

			for (int i = 0; i <= 6; i++) {

				std::string dt = fastWriter.write(root["list"][i]["dt"]).c_str();
				dt.erase(std::remove(dt.begin(), dt.end(), '\"'));
				time_t dtString = atoi(dt.c_str());
				tm dtTime = *localtime(&dtString);
				char bufor[64];
				strftime(bufor, sizeof(bufor), "%d.%m", &dtTime);
				std::string dtResult = ("[container]: \"%s\"\n", bufor);
				dayList[i] = dtResult;

				std::string x = fastWriter.write(root["list"][i]["temp"]["day"]).c_str();
				x.erase(std::remove(x.begin(), x.end(), '\"'));
				tempList[i] = std::stoi(x) - 272;
				this->chart1->Series["Temperatura [°C]"]->Points->AddXY(gcnew String(dayList[i].c_str()), tempList[i]);

				std::string y = fastWriter.write(root["list"][i]["humidity"]).c_str();
				y.erase(std::remove(y.begin(), y.end(), '\"'));
				humidityList[i] = std::stoi(y);
				this->chart2->Series["Wilgotność [%]"]->Points->AddXY(gcnew String(dayList[i].c_str()), humidityList[i]);

			}
			// Ustawienie miasta
			this->label2->Text = this->textBox1->Text;
			this->label4->Text = this->textBox1->Text;
			this->label6->Text = this->textBox1->Text;


			std::string main1 = fastWriter.write(root["list"][0]["weather"][0]["main"]);
			main1.erase(std::remove(main1.begin(), main1.end(), '\"'));
			const char* snow1 = "Snow";
			std::string snow = "Snow";

				if (main1[0] == s[0]) {
					pictureBox37->Image = Image::FromFile("assets/winter2.png");

				}
				else if (main1[0] == r[0]) {
					pictureBox37->Image = Image::FromFile("assets/parasol.png");

				}

			if (tempInt < 2) {
				pictureBoxGirl->Image = Image::FromFile("assets/winter.png");
			}
			else if (tempInt >= 2 && tempInt < 15) {
				pictureBoxGirl->Image = Image::FromFile("assets/autumn.png");
			}
			else if (tempInt >= 15 && tempInt < 25) {
				pictureBoxGirl->Image = Image::FromFile("assets/spring.png");
			
			}
			else {
				pictureBoxGirl->Image = Image::FromFile("assets/summer.png");
				if (main1[0] != r[0]) {
					pictureBox37->Image = Image::FromFile("assets/summer2.png");
				}
				
			}
		}
 else {
 MessageBox::Show("Źle wpisane miasto", "Błąd");
}
	}



	public: System::Drawing::Image^ getImageFromRes(long resource_ID) {
		// Function getImageFromRes
		// A function for loading PNG images from resources in C++ CLR/CLI
		// Copyright (C) Giuseppe Pischedda 2007 for most code
		// and a little part of this code by Bordon and adapted by me for PNG images in C++ CLR/CLI.

		//Load the resource module:
		HMODULE hInst = NULL;

		// Find the resource using the resource ID from file "resource.h"
		HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(resource_ID), L"PNG");
		if (!hResource) return nullptr;

		// Load the resource and save the total size.
		DWORD Size = SizeofResource(hInst, hResource);
		HGLOBAL MemoryHandle = LoadResource(hInst, hResource);
		if (MemoryHandle == NULL) return nullptr;

		//Create a cli::array of byte with size = total size + 2
		cli::array<BYTE>^ MemPtr = gcnew array<BYTE>(Size + 2);

		//Cast from LPVOID to char *
		char* lkr = (char*)(LockResource(MemoryHandle));

		//Copy from unmanaged memory to managed array
		System::Runtime::InteropServices::Marshal::Copy((IntPtr)lkr, MemPtr, 0, Size);

		// Create a new MemoryStream with size = MemPtr
		System::IO::MemoryStream^ stream = gcnew System::IO::MemoryStream(MemPtr);

		//Write in the MemoryStream
		stream->Write(MemPtr, 0, Size);

		//Set the position for read the stream
		stream->Position = 0;

		//Free allocated resources
		FreeLibrary(hInst);

		//Create an Image abstract class pointer
		System::Drawing::Image^ ptrPNG;

		//Assign the stream to abstract class pointer
		ptrPNG = System::Drawing::Image::FromStream(stream);
		return ptrPNG;
	}
		  typedef std::map<std::string, std::string> Params;

		  static std::string params_string(Params const& params)
		  {
			  if (params.empty()) return "";
			  Params::const_iterator pb = params.cbegin(), pe = params.cend();
			  std::string data = pb->first + "=" + pb->second;
			  ++pb; if (pb == pe) return data;
			  for (; pb != pe; ++pb)
				  data += "&" + pb->first + "=" + pb->second;
			  return data;
		  }
		  static std::string toStandardString(System::String^ string)
		  {
			  using System::Runtime::InteropServices::Marshal;

			  if (string->Length == 0 || string->Length < 0)
			  {
				  MessageBox::Show("No field can be empty");

			  }

			  System::IntPtr pointer = Marshal::StringToHGlobalAnsi(string);
			  char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
			  std::string returnString(charPointer, string->Length);
			  Marshal::FreeHGlobal(pointer);


			  return returnString;
		  }

	private: System::Void winter_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBoxGirl->Image = Image::FromFile("assets/winter.png");
	}
	private: System::Void autumn_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBoxGirl->Image = Image::FromFile("assets/autumn.png");
	}
	private: System::Void rain_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBoxGirl->Image = Image::FromFile("assets/rain.png");
	}
	private: System::Void summer_Click(System::Object^ sender, System::EventArgs^ e) {
		pictureBoxGirl->Image = Image::FromFile("assets/summer.png");
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		// Czas
		time_t time = std::time(0);
		std::tm* now = std::localtime(&time);
		int hourInt = now->tm_hour + timezoneForTimer - 1;
		if (hourInt >= 24) {
			hourInt -=24;
		}
		std::string hour = std::string(2 - std::to_string(hourInt).length(), '0') + std::to_string(hourInt);
		std::string min = std::string(2 - std::to_string(now->tm_min).length(), '0') + std::to_string(now->tm_min);
		std::string sec = std::string(2 - std::to_string(now->tm_sec).length(), '0') + std::to_string(now->tm_sec);

		
		

		this->dataLabel->Text = gcnew String(hour.c_str()) + " : " + gcnew String(min.c_str()) + " : " + gcnew String(sec.c_str());
	}
private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
