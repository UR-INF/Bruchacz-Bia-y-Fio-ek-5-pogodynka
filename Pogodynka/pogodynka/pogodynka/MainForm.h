#pragma once

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
	private: System::Windows::Forms::Label^ labelTitle;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->labelMaxTempData = (gcnew System::Windows::Forms::Label());
			this->labelVisibilityData = (gcnew System::Windows::Forms::Label());
			this->labelVisibility = (gcnew System::Windows::Forms::Label());
			this->labelMaxTemp = (gcnew System::Windows::Forms::Label());
			this->labelMinTempData = (gcnew System::Windows::Forms::Label());
			this->labelMinTemp = (gcnew System::Windows::Forms::Label());
			this->labelPressureData = (gcnew System::Windows::Forms::Label());
			this->labelPressure = (gcnew System::Windows::Forms::Label());
			this->labelSunsetData = (gcnew System::Windows::Forms::Label());
			this->labelWindData = (gcnew System::Windows::Forms::Label());
			this->labelWind = (gcnew System::Windows::Forms::Label());
			this->labelSunset = (gcnew System::Windows::Forms::Label());
			this->labelSunriseData = (gcnew System::Windows::Forms::Label());
			this->labelSunrise = (gcnew System::Windows::Forms::Label());
			this->labelHumidityData = (gcnew System::Windows::Forms::Label());
			this->labelHumidity = (gcnew System::Windows::Forms::Label());
			this->labelTempData = (gcnew System::Windows::Forms::Label());
			this->labelCity = (gcnew System::Windows::Forms::Label());
			this->labelCityData = (gcnew System::Windows::Forms::Label());
			this->labelTemp = (gcnew System::Windows::Forms::Label());
			this->labelTimezoneData = (gcnew System::Windows::Forms::Label());
			this->labelTimezone = (gcnew System::Windows::Forms::Label());
			this->labelTitle = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(557, 449);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Wyślij";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(3, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(688, 530);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->tableLayoutPanel1);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->labelTitle);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(680, 504);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"tabPage1";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Click += gcnew System::EventHandler(this, &MainForm::tabPage1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(557, 418);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"Rzeszów";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				31.26294F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				68.73706F)));
			this->tableLayoutPanel1->Controls->Add(this->labelMaxTempData, 1, 10);
			this->tableLayoutPanel1->Controls->Add(this->labelVisibilityData, 1, 8);
			this->tableLayoutPanel1->Controls->Add(this->labelVisibility, 0, 8);
			this->tableLayoutPanel1->Controls->Add(this->labelMaxTemp, 0, 10);
			this->tableLayoutPanel1->Controls->Add(this->labelMinTempData, 0, 9);
			this->tableLayoutPanel1->Controls->Add(this->labelMinTemp, 0, 9);
			this->tableLayoutPanel1->Controls->Add(this->labelPressureData, 1, 7);
			this->tableLayoutPanel1->Controls->Add(this->labelPressure, 0, 7);
			this->tableLayoutPanel1->Controls->Add(this->labelSunsetData, 1, 6);
			this->tableLayoutPanel1->Controls->Add(this->labelWindData, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->labelWind, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->labelSunset, 0, 6);
			this->tableLayoutPanel1->Controls->Add(this->labelSunriseData, 1, 5);
			this->tableLayoutPanel1->Controls->Add(this->labelSunrise, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->labelHumidityData, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->labelHumidity, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->labelTempData, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelCity, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelCityData, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->labelTemp, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->labelTimezoneData, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->labelTimezone, 0, 4);
			this->tableLayoutPanel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(17, 156);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 11;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel1->Size = System::Drawing::Size(483, 223);
			this->tableLayoutPanel1->TabIndex = 2;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// labelMaxTempData
			// 
			this->labelMaxTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMaxTempData->AutoSize = true;
			this->labelMaxTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelMaxTempData->Location = System::Drawing::Point(153, 201);
			this->labelMaxTempData->Name = L"labelMaxTempData";
			this->labelMaxTempData->Size = System::Drawing::Size(162, 20);
			this->labelMaxTempData->TabIndex = 26;
			this->labelMaxTempData->Text = L"labelMaxTempData";
			this->labelMaxTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelVisibilityData
			// 
			this->labelVisibilityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelVisibilityData->AutoSize = true;
			this->labelVisibilityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelVisibilityData->Location = System::Drawing::Point(153, 160);
			this->labelVisibilityData->Name = L"labelVisibilityData";
			this->labelVisibilityData->Size = System::Drawing::Size(151, 20);
			this->labelVisibilityData->TabIndex = 25;
			this->labelVisibilityData->Text = L"labelVisibilityData";
			this->labelVisibilityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelVisibility
			// 
			this->labelVisibility->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelVisibility->AutoSize = true;
			this->labelVisibility->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelVisibility->Location = System::Drawing::Point(3, 160);
			this->labelVisibility->Name = L"labelVisibility";
			this->labelVisibility->Size = System::Drawing::Size(99, 20);
			this->labelVisibility->TabIndex = 18;
			this->labelVisibility->Text = L"Widoczność:";
			this->labelVisibility->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelVisibility->Click += gcnew System::EventHandler(this, &MainForm::label7_Click);
			// 
			// labelMaxTemp
			// 
			this->labelMaxTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMaxTemp->AutoSize = true;
			this->labelMaxTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelMaxTemp->Location = System::Drawing::Point(3, 201);
			this->labelMaxTemp->Name = L"labelMaxTemp";
			this->labelMaxTemp->Size = System::Drawing::Size(133, 20);
			this->labelMaxTemp->TabIndex = 24;
			this->labelMaxTemp->Text = L"Max temperatura:";
			this->labelMaxTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelMinTempData
			// 
			this->labelMinTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMinTempData->AutoSize = true;
			this->labelMinTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelMinTempData->Location = System::Drawing::Point(153, 180);
			this->labelMinTempData->Name = L"labelMinTempData";
			this->labelMinTempData->Size = System::Drawing::Size(158, 20);
			this->labelMinTempData->TabIndex = 23;
			this->labelMinTempData->Text = L"labelMinTempData";
			this->labelMinTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelMinTemp
			// 
			this->labelMinTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelMinTemp->AutoSize = true;
			this->labelMinTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelMinTemp->Location = System::Drawing::Point(3, 180);
			this->labelMinTemp->Name = L"labelMinTemp";
			this->labelMinTemp->Size = System::Drawing::Size(133, 20);
			this->labelMinTemp->TabIndex = 22;
			this->labelMinTemp->Text = L"Min. temperatura:";
			this->labelMinTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelPressureData
			// 
			this->labelPressureData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelPressureData->AutoSize = true;
			this->labelPressureData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelPressureData->Location = System::Drawing::Point(153, 140);
			this->labelPressureData->Name = L"labelPressureData";
			this->labelPressureData->Size = System::Drawing::Size(157, 20);
			this->labelPressureData->TabIndex = 18;
			this->labelPressureData->Text = L"labelPressureData";
			this->labelPressureData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelPressure
			// 
			this->labelPressure->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelPressure->AutoSize = true;
			this->labelPressure->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelPressure->Location = System::Drawing::Point(3, 140);
			this->labelPressure->Name = L"labelPressure";
			this->labelPressure->Size = System::Drawing::Size(77, 20);
			this->labelPressure->TabIndex = 17;
			this->labelPressure->Text = L"Ciśnienie:";
			this->labelPressure->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelPressure->Click += gcnew System::EventHandler(this, &MainForm::label10_Click);
			// 
			// labelSunsetData
			// 
			this->labelSunsetData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunsetData->AutoSize = true;
			this->labelSunsetData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelSunsetData->Location = System::Drawing::Point(153, 120);
			this->labelSunsetData->Name = L"labelSunsetData";
			this->labelSunsetData->Size = System::Drawing::Size(143, 20);
			this->labelSunsetData->TabIndex = 16;
			this->labelSunsetData->Text = L"labelSunsetData";
			this->labelSunsetData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelWindData
			// 
			this->labelWindData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelWindData->AutoSize = true;
			this->labelWindData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelWindData->Location = System::Drawing::Point(153, 60);
			this->labelWindData->Name = L"labelWindData";
			this->labelWindData->Size = System::Drawing::Size(126, 20);
			this->labelWindData->TabIndex = 12;
			this->labelWindData->Text = L"labelWindData";
			this->labelWindData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelWind
			// 
			this->labelWind->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelWind->AutoSize = true;
			this->labelWind->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelWind->Location = System::Drawing::Point(3, 60);
			this->labelWind->Name = L"labelWind";
			this->labelWind->Size = System::Drawing::Size(50, 20);
			this->labelWind->TabIndex = 11;
			this->labelWind->Text = L"Wiatr:";
			this->labelWind->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunset
			// 
			this->labelSunset->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunset->AutoSize = true;
			this->labelSunset->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelSunset->Location = System::Drawing::Point(3, 120);
			this->labelSunset->Name = L"labelSunset";
			this->labelSunset->Size = System::Drawing::Size(63, 20);
			this->labelSunset->TabIndex = 15;
			this->labelSunset->Text = L"Zachód";
			this->labelSunset->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunriseData
			// 
			this->labelSunriseData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunriseData->AutoSize = true;
			this->labelSunriseData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelSunriseData->Location = System::Drawing::Point(153, 100);
			this->labelSunriseData->Name = L"labelSunriseData";
			this->labelSunriseData->Size = System::Drawing::Size(147, 20);
			this->labelSunriseData->TabIndex = 14;
			this->labelSunriseData->Text = L"labelSunriseData";
			this->labelSunriseData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelSunrise
			// 
			this->labelSunrise->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelSunrise->AutoSize = true;
			this->labelSunrise->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelSunrise->Location = System::Drawing::Point(3, 100);
			this->labelSunrise->Name = L"labelSunrise";
			this->labelSunrise->Size = System::Drawing::Size(67, 20);
			this->labelSunrise->TabIndex = 13;
			this->labelSunrise->Text = L"Wschód";
			this->labelSunrise->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelHumidityData
			// 
			this->labelHumidityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelHumidityData->AutoSize = true;
			this->labelHumidityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelHumidityData->Location = System::Drawing::Point(153, 40);
			this->labelHumidityData->Name = L"labelHumidityData";
			this->labelHumidityData->Size = System::Drawing::Size(155, 20);
			this->labelHumidityData->TabIndex = 8;
			this->labelHumidityData->Text = L"labelHumidityData";
			this->labelHumidityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelHumidity
			// 
			this->labelHumidity->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelHumidity->AutoSize = true;
			this->labelHumidity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelHumidity->Location = System::Drawing::Point(3, 40);
			this->labelHumidity->Name = L"labelHumidity";
			this->labelHumidity->Size = System::Drawing::Size(91, 20);
			this->labelHumidity->TabIndex = 7;
			this->labelHumidity->Text = L"Wilgotność:";
			this->labelHumidity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelHumidity->Click += gcnew System::EventHandler(this, &MainForm::labelHumidity_Click);
			// 
			// labelTempData
			// 
			this->labelTempData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTempData->AutoSize = true;
			this->labelTempData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelTempData->Location = System::Drawing::Point(153, 20);
			this->labelTempData->Name = L"labelTempData";
			this->labelTempData->Size = System::Drawing::Size(130, 20);
			this->labelTempData->TabIndex = 6;
			this->labelTempData->Text = L"labelTempData";
			this->labelTempData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelCity
			// 
			this->labelCity->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelCity->AutoSize = true;
			this->labelCity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelCity->Location = System::Drawing::Point(3, 0);
			this->labelCity->Name = L"labelCity";
			this->labelCity->Size = System::Drawing::Size(60, 20);
			this->labelCity->TabIndex = 3;
			this->labelCity->Text = L"Miasto:";
			this->labelCity->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelCity->Click += gcnew System::EventHandler(this, &MainForm::label1_Click_2);
			// 
			// labelCityData
			// 
			this->labelCityData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelCityData->AutoSize = true;
			this->labelCityData->Cursor = System::Windows::Forms::Cursors::Default;
			this->labelCityData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelCityData->Location = System::Drawing::Point(153, 0);
			this->labelCityData->Name = L"labelCityData";
			this->labelCityData->Size = System::Drawing::Size(116, 20);
			this->labelCityData->TabIndex = 4;
			this->labelCityData->Text = L"labelCityData";
			this->labelCityData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelCityData->Click += gcnew System::EventHandler(this, &MainForm::labelCityData_Click);
			// 
			// labelTemp
			// 
			this->labelTemp->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTemp->AutoSize = true;
			this->labelTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelTemp->Location = System::Drawing::Point(3, 20);
			this->labelTemp->Name = L"labelTemp";
			this->labelTemp->Size = System::Drawing::Size(104, 20);
			this->labelTemp->TabIndex = 5;
			this->labelTemp->Text = L"Temperatura:";
			this->labelTemp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->labelTemp->Click += gcnew System::EventHandler(this, &MainForm::label1_Click_3);
			// 
			// labelTimezoneData
			// 
			this->labelTimezoneData->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTimezoneData->AutoSize = true;
			this->labelTimezoneData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			this->labelTimezoneData->Location = System::Drawing::Point(153, 80);
			this->labelTimezoneData->Name = L"labelTimezoneData";
			this->labelTimezoneData->Size = System::Drawing::Size(163, 20);
			this->labelTimezoneData->TabIndex = 10;
			this->labelTimezoneData->Text = L"labelTimezoneData";
			this->labelTimezoneData->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelTimezone
			// 
			this->labelTimezone->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->labelTimezone->AutoSize = true;
			this->labelTimezone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->labelTimezone->Location = System::Drawing::Point(3, 80);
			this->labelTimezone->Name = L"labelTimezone";
			this->labelTimezone->Size = System::Drawing::Size(123, 20);
			this->labelTimezone->TabIndex = 9;
			this->labelTimezone->Text = L"Strefa czasowa:";
			this->labelTimezone->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// labelTitle
			// 
			this->labelTitle->AutoSize = true;
			this->labelTitle->Font = (gcnew System::Drawing::Font(L"Arial Black", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelTitle->Location = System::Drawing::Point(184, 3);
			this->labelTitle->Name = L"labelTitle";
			this->labelTitle->Size = System::Drawing::Size(316, 68);
			this->labelTitle->TabIndex = 1;
			this->labelTitle->Text = L"Pogodynka";
			this->labelTitle->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(680, 504);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(688, 527);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MainForm";
			this->Text = L"Pogodynka";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
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
private: System::Void label1_Click_2(System::Object^ sender, System::EventArgs^ e) {
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
};
}
