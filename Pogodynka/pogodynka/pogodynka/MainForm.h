#pragma once
#include <curl/curl.h>
#include <string>
#include <Windows.h>
static std::string readBuffer;
namespace pogodynka {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
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


	private: System::Windows::Forms::Label^ labelCity;
	private: System::Windows::Forms::Label^ labelCityData;
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
	private: System::Windows::Forms::Label^ labelTimezoneData;
	private: System::Windows::Forms::Label^ labelTimezone;
	private: System::Windows::Forms::Label^ labelMaxTempData;

	private: System::Windows::Forms::Label^ labelPressure;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
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
	private: System::Windows::Forms::PictureBox^ pictureBox13;










	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->labelMinTempData = (gcnew System::Windows::Forms::Label());
			this->labelMaxTempData = (gcnew System::Windows::Forms::Label());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->labelMaxTemp = (gcnew System::Windows::Forms::Label());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
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
			this->labelTimezoneData = (gcnew System::Windows::Forms::Label());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->labelCityData = (gcnew System::Windows::Forms::Label());
			this->labelPressure = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->labelSunset = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelSunrise = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->labelTimezone = (gcnew System::Windows::Forms::Label());
			this->labelCity = (gcnew System::Windows::Forms::Label());
			this->labelTemp = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
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
			this->button1->Location = System::Drawing::Point(490, 100);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(257, 25);
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
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(800, 600);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->pictureBox11);
			this->tabPage1->Controls->Add(this->pictureBox12);
			this->tabPage1->Controls->Add(this->labelMinTempData);
			this->tabPage1->Controls->Add(this->labelMaxTempData);
			this->tabPage1->Controls->Add(this->pictureBox6);
			this->tabPage1->Controls->Add(this->pictureBox5);
			this->tabPage1->Controls->Add(this->labelMaxTemp);
			this->tabPage1->Controls->Add(this->pictureBox13);
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
			this->tabPage1->Controls->Add(this->labelTimezoneData);
			this->tabPage1->Controls->Add(this->pictureBox7);
			this->tabPage1->Controls->Add(this->labelCityData);
			this->tabPage1->Controls->Add(this->labelPressure);
			this->tabPage1->Controls->Add(this->pictureBox4);
			this->tabPage1->Controls->Add(this->pictureBox3);
			this->tabPage1->Controls->Add(this->labelSunset);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->labelSunrise);
			this->tabPage1->Controls->Add(this->pictureBox2);
			this->tabPage1->Controls->Add(this->pictureBox1);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->labelTimezone);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->labelCity);
			this->tabPage1->Controls->Add(this->labelTemp);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
			this->tabPage1->Size = System::Drawing::Size(792, 574);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Start";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &MainForm::tabPage1_Click);
			// 
			// pictureBox11
			// 
			this->pictureBox11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.Image")));
			this->pictureBox11->Location = System::Drawing::Point(260, 479);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(32, 32);
			this->pictureBox11->TabIndex = 15;
			this->pictureBox11->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.Image")));
			this->pictureBox12->Location = System::Drawing::Point(260, 405);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(32, 32);
			this->pictureBox12->TabIndex = 16;
			this->pictureBox12->TabStop = false;
			// 
			// labelMinTempData
			// 
			this->labelMinTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMinTempData->AutoSize = true;
			this->labelMinTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelMinTempData->Location = System::Drawing::Point(298, 409);
			this->labelMinTempData->Name = L"labelMinTempData";
			this->labelMinTempData->Size = System::Drawing::Size(133, 20);
			this->labelMinTempData->TabIndex = 23;
			this->labelMinTempData->Text = L"Min. Temperature";
			this->labelMinTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelMaxTempData
			// 
			this->labelMaxTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMaxTempData->AutoSize = true;
			this->labelMaxTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelMaxTempData->Location = System::Drawing::Point(298, 483);
			this->labelMaxTempData->Name = L"labelMaxTempData";
			this->labelMaxTempData->Size = System::Drawing::Size(86, 20);
			this->labelMaxTempData->TabIndex = 26;
			this->labelMaxTempData->Text = L"Max. Temp";
			this->labelMaxTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(260, 332);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(32, 32);
			this->pictureBox6->TabIndex = 10;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(260, 259);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(32, 32);
			this->pictureBox5->TabIndex = 9;
			this->pictureBox5->TabStop = false;
			// 
			// labelMaxTemp
			// 
			this->labelMaxTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMaxTemp->AutoSize = true;
			this->labelMaxTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelMaxTemp->Location = System::Drawing::Point(256, 450);
			this->labelMaxTemp->Name = L"labelMaxTemp";
			this->labelMaxTemp->Size = System::Drawing::Size(174, 25);
			this->labelMaxTemp->TabIndex = 24;
			this->labelMaxTemp->Text = L"Max temperatura";
			this->labelMaxTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox13
			// 
			this->pictureBox13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox13.Image")));
			this->pictureBox13->Location = System::Drawing::Point(13, 189);
			this->pictureBox13->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(32, 32);
			this->pictureBox13->TabIndex = 25;
			this->pictureBox13->TabStop = false;
			// 
			// labelWind
			// 
			this->labelWind->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelWind->AutoSize = true;
			this->labelWind->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelWind->Location = System::Drawing::Point(256, 304);
			this->labelWind->Name = L"labelWind";
			this->labelWind->Size = System::Drawing::Size(63, 25);
			this->labelWind->TabIndex = 11;
			this->labelWind->Text = L"Wiatr";
			this->labelWind->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelMinTemp
			// 
			this->labelMinTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMinTemp->AutoSize = true;
			this->labelMinTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelMinTemp->Location = System::Drawing::Point(256, 377);
			this->labelMinTemp->Name = L"labelMinTemp";
			this->labelMinTemp->Size = System::Drawing::Size(174, 25);
			this->labelMinTemp->TabIndex = 22;
			this->labelMinTemp->Text = L"Min. temperatura";
			this->labelMinTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelHumidity
			// 
			this->labelHumidity->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelHumidity->AutoSize = true;
			this->labelHumidity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelHumidity->Location = System::Drawing::Point(256, 231);
			this->labelHumidity->Name = L"labelHumidity";
			this->labelHumidity->Size = System::Drawing::Size(119, 25);
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
			this->labelVisibilityData->Location = System::Drawing::Point(51, 413);
			this->labelVisibilityData->Name = L"labelVisibilityData";
			this->labelVisibilityData->Size = System::Drawing::Size(64, 20);
			this->labelVisibilityData->TabIndex = 25;
			this->labelVisibilityData->Text = L"Visibility";
			this->labelVisibilityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelWindData
			// 
			this->labelWindData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelWindData->AutoSize = true;
			this->labelWindData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelWindData->Location = System::Drawing::Point(298, 332);
			this->labelWindData->Name = L"labelWindData";
			this->labelWindData->Size = System::Drawing::Size(45, 20);
			this->labelWindData->TabIndex = 12;
			this->labelWindData->Text = L"Wind";
			this->labelWindData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelPressureData
			// 
			this->labelPressureData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelPressureData->AutoSize = true;
			this->labelPressureData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelPressureData->Location = System::Drawing::Point(51, 486);
			this->labelPressureData->Name = L"labelPressureData";
			this->labelPressureData->Size = System::Drawing::Size(72, 20);
			this->labelPressureData->TabIndex = 18;
			this->labelPressureData->Text = L"Pressure";
			this->labelPressureData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunsetData
			// 
			this->labelSunsetData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunsetData->AutoSize = true;
			this->labelSunsetData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelSunsetData->Location = System::Drawing::Point(51, 339);
			this->labelSunsetData->Name = L"labelSunsetData";
			this->labelSunsetData->Size = System::Drawing::Size(60, 20);
			this->labelSunsetData->TabIndex = 16;
			this->labelSunsetData->Text = L"Sunset";
			this->labelSunsetData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelHumidityData
			// 
			this->labelHumidityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelHumidityData->AutoSize = true;
			this->labelHumidityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelHumidityData->Location = System::Drawing::Point(298, 264);
			this->labelHumidityData->Name = L"labelHumidityData";
			this->labelHumidityData->Size = System::Drawing::Size(70, 20);
			this->labelHumidityData->TabIndex = 8;
			this->labelHumidityData->Text = L"Humidity";
			this->labelHumidityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelVisibility
			// 
			this->labelVisibility->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelVisibility->AutoSize = true;
			this->labelVisibility->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelVisibility->Location = System::Drawing::Point(9, 380);
			this->labelVisibility->Name = L"labelVisibility";
			this->labelVisibility->Size = System::Drawing::Size(130, 25);
			this->labelVisibility->TabIndex = 18;
			this->labelVisibility->Text = L"Widoczność";
			this->labelVisibility->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelVisibility->Click += gcnew System::EventHandler(this, &MainForm::label7_Click);
			// 
			// pictureBox10
			// 
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(13, 409);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(32, 32);
			this->pictureBox10->TabIndex = 14;
			this->pictureBox10->TabStop = false;
			// 
			// labelTempData
			// 
			this->labelTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTempData->AutoSize = true;
			this->labelTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelTempData->Location = System::Drawing::Point(298, 197);
			this->labelTempData->Name = L"labelTempData";
			this->labelTempData->Size = System::Drawing::Size(100, 20);
			this->labelTempData->TabIndex = 6;
			this->labelTempData->Text = L"Temperature";
			this->labelTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunriseData
			// 
			this->labelSunriseData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunriseData->AutoSize = true;
			this->labelSunriseData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelSunriseData->Location = System::Drawing::Point(51, 266);
			this->labelSunriseData->Name = L"labelSunriseData";
			this->labelSunriseData->Size = System::Drawing::Size(63, 20);
			this->labelSunriseData->TabIndex = 14;
			this->labelSunriseData->Text = L"Sunrise";
			this->labelSunriseData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox9
			// 
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(13, 482);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(32, 32);
			this->pictureBox9->TabIndex = 13;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(13, 336);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(32, 32);
			this->pictureBox8->TabIndex = 12;
			this->pictureBox8->TabStop = false;
			// 
			// labelTimezoneData
			// 
			this->labelTimezoneData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTimezoneData->AutoSize = true;
			this->labelTimezoneData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelTimezoneData->Location = System::Drawing::Point(51, 194);
			this->labelTimezoneData->Name = L"labelTimezoneData";
			this->labelTimezoneData->Size = System::Drawing::Size(78, 20);
			this->labelTimezoneData->TabIndex = 10;
			this->labelTimezoneData->Text = L"Timezone";
			this->labelTimezoneData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(13, 262);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(32, 32);
			this->pictureBox7->TabIndex = 11;
			this->pictureBox7->TabStop = false;
			// 
			// labelCityData
			// 
			this->labelCityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelCityData->AutoSize = true;
			this->labelCityData->Cursor = System::Windows::Forms::Cursors::Default;
			this->labelCityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic));
			this->labelCityData->Location = System::Drawing::Point(527, 197);
			this->labelCityData->Name = L"labelCityData";
			this->labelCityData->Size = System::Drawing::Size(35, 20);
			this->labelCityData->TabIndex = 4;
			this->labelCityData->Text = L"City";
			this->labelCityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelCityData->Click += gcnew System::EventHandler(this, &MainForm::labelCityData_Click);
			// 
			// labelPressure
			// 
			this->labelPressure->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelPressure->AutoSize = true;
			this->labelPressure->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelPressure->Location = System::Drawing::Point(9, 453);
			this->labelPressure->Name = L"labelPressure";
			this->labelPressure->Size = System::Drawing::Size(102, 25);
			this->labelPressure->TabIndex = 17;
			this->labelPressure->Text = L"Ciśnienie";
			this->labelPressure->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelPressure->Click += gcnew System::EventHandler(this, &MainForm::label10_Click);
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(260, 191);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(32, 32);
			this->pictureBox4->TabIndex = 8;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(488, 191);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(32, 32);
			this->pictureBox3->TabIndex = 7;
			this->pictureBox3->TabStop = false;
			// 
			// labelSunset
			// 
			this->labelSunset->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunset->AutoSize = true;
			this->labelSunset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelSunset->Location = System::Drawing::Point(9, 307);
			this->labelSunset->Name = L"labelSunset";
			this->labelSunset->Size = System::Drawing::Size(84, 25);
			this->labelSunset->TabIndex = 15;
			this->labelSunset->Text = L"Zachód";
			this->labelSunset->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label1->Location = System::Drawing::Point(501, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(237, 31);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Twoja lokalizacja";
			// 
			// labelSunrise
			// 
			this->labelSunrise->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunrise->AutoSize = true;
			this->labelSunrise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelSunrise->Location = System::Drawing::Point(9, 234);
			this->labelSunrise->Name = L"labelSunrise";
			this->labelSunrise->Size = System::Drawing::Size(91, 25);
			this->labelSunrise->TabIndex = 13;
			this->labelSunrise->Text = L"Wschód";
			this->labelSunrise->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(396, 22);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(82, 108);
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(14, 22);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(318, 108);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBox1->Location = System::Drawing::Point(490, 70);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(257, 23);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"Rzeszów";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
			// 
			// labelTimezone
			// 
			this->labelTimezone->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTimezone->AutoSize = true;
			this->labelTimezone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelTimezone->Location = System::Drawing::Point(9, 161);
			this->labelTimezone->Name = L"labelTimezone";
			this->labelTimezone->Size = System::Drawing::Size(160, 25);
			this->labelTimezone->TabIndex = 9;
			this->labelTimezone->Text = L"Strefa czasowa";
			this->labelTimezone->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelCity
			// 
			this->labelCity->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelCity->AutoSize = true;
			this->labelCity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelCity->Location = System::Drawing::Point(485, 161);
			this->labelCity->Name = L"labelCity";
			this->labelCity->Size = System::Drawing::Size(76, 25);
			this->labelCity->TabIndex = 3;
			this->labelCity->Text = L"Miasto";
			this->labelCity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelTemp
			// 
			this->labelTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTemp->AutoSize = true;
			this->labelTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold));
			this->labelTemp->Location = System::Drawing::Point(256, 161);
			this->labelTemp->Name = L"labelTemp";
			this->labelTemp->Size = System::Drawing::Size(135, 25);
			this->labelTemp->TabIndex = 5;
			this->labelTemp->Text = L"Temperatura";
			this->labelTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelTemp->Click += gcnew System::EventHandler(this, &MainForm::label1_Click_3);
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
			this->tabPage2->Size = System::Drawing::Size(792, 574);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Wykresy";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3, 3, 3, 3);
			this->tabPage3->Size = System::Drawing::Size(792, 574);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Zegar";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MainForm";
			this->Text = L"Pogodynka";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
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
	curl_easy_setopt(hnd, CURLOPT_URL, "https://community-open-weather-map.p.rapidapi.com/weather?callback=test&id=2172797&units=%2522metric%2522&q=Rzeszow");	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "x-rapidapi-host: community-open-weather-map.p.rapidapi.com");
	headers = curl_slist_append(headers, "x-rapidapi-key: f90acf6696msh3be9bb78dc5c56ep1a4015jsnb4b983675d4c");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	//System::String^ response_string;
	//System::String^ header_string;
	std::string readBuffer;
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);
	//curl_easy_setopt(hnd, CURLOPT_WRITEDATA, response_string);
	//curl_easy_setopt(hnd, CURLOPT_HEADERDATA, header_string);

	CURLcode ret = curl_easy_perform(hnd);
	curl_easy_cleanup(hnd);
	String^ something = gcnew String(readBuffer.c_str());
	this->labelCityData->Text = something;
	//this->labelCity->Text = header_string;
}
};
}
