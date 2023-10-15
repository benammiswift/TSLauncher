#pragma once
#pragma comment(lib, "Advapi32.lib")
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include "stdio.h"
#include "Windows.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <string>
#include <iostream>

//Stringybois
#define RW_REG_KEY_PATH "SOFTWARE\\WOW6432Node\\railsimulator.com\\railworks"
#define RW_32BIT_EXE "Railworks.exe"
#define RW_64BIT_EXE "RailWorks64.exe"
#define RW_DX12_EXE "RailWorksDX12_64.exe"

//functions to serialise and deserialise numerical variables to strings
#define REG_STORE_SERIALISE_OUT(str) sprintf(str, "%d,%d", (int) this->panelDevState, this->argFlags );
#define REG_STORE_SERIALISE_IN(str)  sscanf(str, "%d,%d", &this->panelDevState, &this->argFlags );

// Checkbox indexes
#define CH_BOX_BIT_LOGMATE 0
#define CH_BOX_BIT_LUA_DEBUG 1
#define CH_BOX_BIT_CTRL_DIALOG 2
#define CH_BOX_BIT_SOUND_DIALOG 3
#define CH_BOX_BIT_NO_BP_CACHE 4
#define CH_BOX_BIT_ASYNC 5
#define CH_BOX_BIT_MULTICORE 6
#define CH_BOX_BIT_FOLLOWAI 7



namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



#ifdef _DEBUG

#define CH_BOX_SET_BIT(argFlags, bit, sender) \
		CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender); \
		if (checkBox->Checked) { \
			(argFlags) |= (1 << (bit)); \
		} else { \
			(argFlags) &= ~(1 << (bit)); \
		} \
		char* ser = (char*)malloc(2048); \
		REG_STORE_SERIALISE_OUT(ser); \
		this->SetStringToRegistry(RW_REG_KEY_PATH, "launcher_store", ser); \
		printf("Value of the store is now %d\n", argFlags); 

#define TEXT_BOX_STORE_FROM_EVENT(location, sender, regKey) \
		TextBox^ textBox = dynamic_cast<TextBox^>(sender); \
		String^ text = textBox->Text; \
		msclr::interop::marshal_context context; \
		const char* charPtr = context.marshal_as<const char*>(text); \
		location = _strdup(charPtr); \
		this->SetStringToRegistry(RW_REG_KEY_PATH, regKey, location); \
		printf("Text box changed to : %s\n", location);
#else

#define CH_BOX_SET_BIT(argFlags, bit, sender) \
		CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender); \
		if (checkBox->Checked) { \
			(argFlags) |= (1 << (bit)); \
		} else { \
			(argFlags) &= ~(1 << (bit)); \
		} \
		char* ser = (char*)malloc(2048); \
		REG_STORE_SERIALISE_OUT(ser); \
		this->SetStringToRegistry(RW_REG_KEY_PATH, "launcher_store", ser); 

#define TEXT_BOX_STORE_FROM_EVENT(location, sender, regKey) \
		TextBox^ textBox = dynamic_cast<TextBox^>(sender); \
		String^ text = textBox->Text; \
		msclr::interop::marshal_context context; \
		const char* charPtr = context.marshal_as<const char*>(text); \
		location = _strdup(charPtr); \
		this->SetStringToRegistry(RW_REG_KEY_PATH, regKey, location); 
	
#endif

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
#ifdef _DEBUG
			bool chk = AllocConsole();
			if (chk)
			{
				freopen("CONOUT$", "w", stdout);
				//printf(" printing to console");
			}
			
#endif

			//Create some strings to store stuff in 
			char* regStore = (char*)malloc(4096);
			char* regLogmate = (char*)malloc(4096);
			char* regFPS = (char*)malloc(4096);

			//Read from registry
			regStore = this->ReadStringFromRegistry(RW_REG_KEY_PATH, "launcher_store");
			regLogmate = this->ReadStringFromRegistry(RW_REG_KEY_PATH, "launcher_store_logmate");
			regFPS = this->ReadStringFromRegistry(RW_REG_KEY_PATH, "launcher_store_FPS");

			//Deserialise if there's an entry for the boolean flags
			if (regStore != nullptr)
				REG_STORE_SERIALISE_IN(regStore);

			//Get the RW Path
			this->rwPath = this->ReadStringFromRegistry(RW_REG_KEY_PATH, "install_path");
			if (this->rwPath != nullptr)
			{
				char* tempVal = (char*)malloc(4096);
				sprintf(tempVal, "Found railworks path : %s", this->rwPath);
				std::string str(tempVal);
				System::String^ text = msclr::interop::marshal_as<System::String^>(str);
				rwLoc->Text = text;
			}
			else
			{
				char* tempVal = (char*)malloc(4096);
				std::string str("Error : DID NOT FIND RAILWORKS PATH");
				System::String^ text = msclr::interop::marshal_as<System::String^>(str);
				rwLoc->Text = text;
			}

			//Handle the string fields being loaded from the Registry
			if (regLogmate)
			{
				puts("setting logmate");
				std::string str(regLogmate);
				System::String^ text = msclr::interop::marshal_as<System::String^>(str);
				textLogmateFilters->Text = text;
			}

			if (regFPS != nullptr)
			{
				puts("setting fps");
				std::string str(regFPS);
				System::String^ text = msclr::interop::marshal_as<System::String^>(str);
				textFPSLimit->Text = text;
			}
			
			//If there's no bit options loaded from the registry we're done
			if (regStore == nullptr)
			{
				return;
			}

			//Hide or show the Developer launch options
			if (this->panelDevState)
				this->panelDev->Show();

			
			//Set all the checkboxes from the registry
			for (int i = 0; i < 32; i++) {
				bool state = (this->argFlags & (1 << i)) != 0;

				switch (i) {
				case CH_BOX_BIT_LOGMATE:
					if (state)
						this->chBoxLogmate->Checked = true;
					break;
				case CH_BOX_BIT_LUA_DEBUG:
					if (state)
						this->chBoxLuaDebug->Checked = true;
					break;
				case CH_BOX_BIT_CTRL_DIALOG:
					if (state)
						this->chBoxControlDialog->Checked = true;
					break;
				case CH_BOX_BIT_SOUND_DIALOG:
					if (state)
						this->chBoxSoundDialog->Checked = true;
					break;
				case CH_BOX_BIT_NO_BP_CACHE:
					if (state)
						this->chBoxNoBpCache->Checked = true;
					break;
				case CH_BOX_BIT_ASYNC:
					if (state)
						this->chBoxAsync->Checked = true;
					break;
				case CH_BOX_BIT_MULTICORE:
					if (state)
						this->chBoxMulticore->Checked = true;
					break;
				case CH_BOX_BIT_FOLLOWAI:
					if (state)
						this->chBoxFollowAI->Checked = true;
					break;
				default:
					// Handle the default case (for values not listed in the cases)
					break;
				}
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	//Reads a REG_SZ from the registry
	private: char* ReadStringFromRegistry(const char* keyPath, const char* valueName) {
		HKEY hKey;
		if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
			std::cout << "Failed to open registry key." << std::endl;
			return nullptr;
		}

		DWORD dataSize = 0;
		if (RegQueryValueExA(hKey, valueName, nullptr, nullptr, nullptr, &dataSize) != ERROR_SUCCESS) {
			std::cout << "Failed to get the size of registry value." << std::endl;
			RegCloseKey(hKey);
			return nullptr;
		}

		char* data = new char[dataSize];

		if (RegQueryValueExA(hKey, valueName, nullptr, nullptr, reinterpret_cast<BYTE*>(data), &dataSize) != ERROR_SUCCESS) {
			std::cout << "Failed to read registry value." << std::endl;
			delete[] data;
			RegCloseKey(hKey);
			return nullptr;
		}

		RegCloseKey(hKey);

		return data;
	}
	
	//Stores a string in a REG_SZ registry key
	private: bool SetStringToRegistry(const char* keyPath, const char* valueName, const char* data) {
			HKEY hKey;
			if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, keyPath, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
				std::cout << "Failed to open registry key." << std::endl;
				return false;
			}
			if (RegSetValueExA(hKey, valueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(data), static_cast<DWORD>(strlen(data) + 1)) != ERROR_SUCCESS) {
				std::cout << "Failed to write registry value." << std::endl;
				RegCloseKey(hKey);
				return false;
			}
			RegCloseKey(hKey);
			return true;
		}
	private: char* rwPath;
	private: bool panelDevState;
	private: uint32_t argFlags;
	private: char* logmateFilters;
	private: char* fpsLimit;
	private: System::Windows::Forms::Button^ launchBit32;


	protected:
	protected:
	private: System::Windows::Forms::Button^ launchBit64;
	private: System::Windows::Forms::Button^ launchDX12;
	private: System::Windows::Forms::Button^ toggleDev;
	private: System::Windows::Forms::TextBox^ textFPSLimit;

	private: System::Windows::Forms::Label^ labelLogmateFilter;
	private: System::Windows::Forms::Panel^ panelDev;
	private: System::Windows::Forms::CheckBox^ chBoxLogmate;
	private: System::Windows::Forms::CheckBox^ chBoxLuaDebug;
	private: System::Windows::Forms::TextBox^ textLogmateFilters;
	private: System::Windows::Forms::CheckBox^ chBoxNoBpCache;
	private: System::Windows::Forms::CheckBox^ chBoxSoundDialog;
	private: System::Windows::Forms::CheckBox^ chBoxControlDialog;
	private: System::Windows::Forms::Label^ rwLoc;
	private: System::Windows::Forms::CheckBox^ chBoxAsync;
	private: System::Windows::Forms::CheckBox^ chBoxMulticore;
	private: System::Windows::Forms::CheckBox^ chBoxFollowAI;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::Label^ title;
			System::Windows::Forms::Label^ labelFPSLimit;
			this->labelLogmateFilter = (gcnew System::Windows::Forms::Label());
			this->launchBit32 = (gcnew System::Windows::Forms::Button());
			this->launchBit64 = (gcnew System::Windows::Forms::Button());
			this->launchDX12 = (gcnew System::Windows::Forms::Button());
			this->toggleDev = (gcnew System::Windows::Forms::Button());
			this->textFPSLimit = (gcnew System::Windows::Forms::TextBox());
			this->panelDev = (gcnew System::Windows::Forms::Panel());
			this->chBoxNoBpCache = (gcnew System::Windows::Forms::CheckBox());
			this->chBoxSoundDialog = (gcnew System::Windows::Forms::CheckBox());
			this->chBoxControlDialog = (gcnew System::Windows::Forms::CheckBox());
			this->chBoxLuaDebug = (gcnew System::Windows::Forms::CheckBox());
			this->textLogmateFilters = (gcnew System::Windows::Forms::TextBox());
			this->chBoxLogmate = (gcnew System::Windows::Forms::CheckBox());
			this->rwLoc = (gcnew System::Windows::Forms::Label());
			this->chBoxAsync = (gcnew System::Windows::Forms::CheckBox());
			this->chBoxMulticore = (gcnew System::Windows::Forms::CheckBox());
			this->chBoxFollowAI = (gcnew System::Windows::Forms::CheckBox());
			title = (gcnew System::Windows::Forms::Label());
			labelFPSLimit = (gcnew System::Windows::Forms::Label());
			this->panelDev->SuspendLayout();
			this->SuspendLayout();
			// 
			// title
			// 
			title->AutoSize = true;
			title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			title->Location = System::Drawing::Point(16, 8);
			title->Name = L"title";
			title->Size = System::Drawing::Size(411, 73);
			title->TabIndex = 8;
			title->Text = L"TS Launcher";
			title->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// labelFPSLimit
			// 
			labelFPSLimit->AutoSize = true;
			labelFPSLimit->Location = System::Drawing::Point(40, 392);
			labelFPSLimit->Name = L"labelFPSLimit";
			labelFPSLimit->Size = System::Drawing::Size(51, 13);
			labelFPSLimit->TabIndex = 10;
			labelFPSLimit->Text = L"FPS Limit";
			// 
			// labelLogmateFilter
			// 
			this->labelLogmateFilter->AutoSize = true;
			this->labelLogmateFilter->Location = System::Drawing::Point(0, 8);
			this->labelLogmateFilter->Name = L"labelLogmateFilter";
			this->labelLogmateFilter->Size = System::Drawing::Size(78, 13);
			this->labelLogmateFilter->TabIndex = 7;
			this->labelLogmateFilter->Text = L"Logmate Filters";
			this->labelLogmateFilter->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// launchBit32
			// 
			this->launchBit32->Location = System::Drawing::Point(32, 120);
			this->launchBit32->Name = L"launchBit32";
			this->launchBit32->Size = System::Drawing::Size(121, 35);
			this->launchBit32->TabIndex = 0;
			this->launchBit32->Text = L"32 Bit";
			this->launchBit32->UseVisualStyleBackColor = true;
			this->launchBit32->Click += gcnew System::EventHandler(this, &Form1::launchBit32_Click);
			// 
			// launchBit64
			// 
			this->launchBit64->Location = System::Drawing::Point(160, 120);
			this->launchBit64->Name = L"launchBit64";
			this->launchBit64->Size = System::Drawing::Size(121, 35);
			this->launchBit64->TabIndex = 2;
			this->launchBit64->Text = L"64 Bit";
			this->launchBit64->UseVisualStyleBackColor = true;
			this->launchBit64->Click += gcnew System::EventHandler(this, &Form1::launchBit64_Click_1);
			// 
			// launchDX12
			// 
			this->launchDX12->Location = System::Drawing::Point(288, 120);
			this->launchDX12->Name = L"launchDX12";
			this->launchDX12->Size = System::Drawing::Size(121, 35);
			this->launchDX12->TabIndex = 3;
			this->launchDX12->Text = L"DX12 ";
			this->launchDX12->UseVisualStyleBackColor = true;
			this->launchDX12->Click += gcnew System::EventHandler(this, &Form1::launchDX12_Click_1);
			// 
			// toggleDev
			// 
			this->toggleDev->Location = System::Drawing::Point(248, 176);
			this->toggleDev->Name = L"toggleDev";
			this->toggleDev->Size = System::Drawing::Size(128, 35);
			this->toggleDev->TabIndex = 4;
			this->toggleDev->Text = L"Developer Options";
			this->toggleDev->UseVisualStyleBackColor = true;
			this->toggleDev->Click += gcnew System::EventHandler(this, &Form1::toggleDev_Click);
			// 
			// textFPSLimit
			// 
			this->textFPSLimit->Location = System::Drawing::Point(32, 416);
			this->textFPSLimit->Name = L"textFPSLimit";
			this->textFPSLimit->Size = System::Drawing::Size(184, 20);
			this->textFPSLimit->TabIndex = 9;
			this->textFPSLimit->TextChanged += gcnew System::EventHandler(this, &Form1::textFPSLimit_TextChanged);
			// 
			// panelDev
			// 
			this->panelDev->Controls->Add(this->chBoxNoBpCache);
			this->panelDev->Controls->Add(this->chBoxSoundDialog);
			this->panelDev->Controls->Add(this->chBoxControlDialog);
			this->panelDev->Controls->Add(this->chBoxLuaDebug);
			this->panelDev->Controls->Add(this->textLogmateFilters);
			this->panelDev->Controls->Add(this->chBoxLogmate);
			this->panelDev->Controls->Add(this->labelLogmateFilter);
			this->panelDev->Location = System::Drawing::Point(232, 240);
			this->panelDev->Name = L"panelDev";
			this->panelDev->Size = System::Drawing::Size(192, 208);
			this->panelDev->TabIndex = 11;
			this->panelDev->Visible = false;
			// 
			// chBoxNoBpCache
			// 
			this->chBoxNoBpCache->AutoSize = true;
			this->chBoxNoBpCache->Location = System::Drawing::Point(0, 160);
			this->chBoxNoBpCache->Name = L"chBoxNoBpCache";
			this->chBoxNoBpCache->Size = System::Drawing::Size(149, 17);
			this->chBoxNoBpCache->TabIndex = 16;
			this->chBoxNoBpCache->Text = L"Dont Use Blueprint Cache";
			this->chBoxNoBpCache->UseVisualStyleBackColor = true;
			this->chBoxNoBpCache->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxNoBpCache_CheckedChanged);
			// 
			// chBoxSoundDialog
			// 
			this->chBoxSoundDialog->AutoSize = true;
			this->chBoxSoundDialog->Location = System::Drawing::Point(0, 136);
			this->chBoxSoundDialog->Name = L"chBoxSoundDialog";
			this->chBoxSoundDialog->Size = System::Drawing::Size(125, 17);
			this->chBoxSoundDialog->TabIndex = 15;
			this->chBoxSoundDialog->Text = L"Sound Debug Dialog";
			this->chBoxSoundDialog->UseVisualStyleBackColor = true;
			this->chBoxSoundDialog->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxSoundDialog_CheckedChanged);
			// 
			// chBoxControlDialog
			// 
			this->chBoxControlDialog->AutoSize = true;
			this->chBoxControlDialog->Location = System::Drawing::Point(0, 112);
			this->chBoxControlDialog->Name = L"chBoxControlDialog";
			this->chBoxControlDialog->Size = System::Drawing::Size(120, 17);
			this->chBoxControlDialog->TabIndex = 14;
			this->chBoxControlDialog->Text = L"Control State Dialog";
			this->chBoxControlDialog->UseVisualStyleBackColor = true;
			this->chBoxControlDialog->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxControlDialog_CheckedChanged);
			// 
			// chBoxLuaDebug
			// 
			this->chBoxLuaDebug->AutoSize = true;
			this->chBoxLuaDebug->Location = System::Drawing::Point(0, 88);
			this->chBoxLuaDebug->Name = L"chBoxLuaDebug";
			this->chBoxLuaDebug->Size = System::Drawing::Size(130, 17);
			this->chBoxLuaDebug->TabIndex = 13;
			this->chBoxLuaDebug->Text = L"Lua Debug Messages";
			this->chBoxLuaDebug->UseVisualStyleBackColor = true;
			this->chBoxLuaDebug->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxLuaDebug_CheckedChanged);
			// 
			// textLogmateFilters
			// 
			this->textLogmateFilters->Location = System::Drawing::Point(0, 32);
			this->textLogmateFilters->Name = L"textLogmateFilters";
			this->textLogmateFilters->Size = System::Drawing::Size(184, 20);
			this->textLogmateFilters->TabIndex = 6;
			this->textLogmateFilters->TextChanged += gcnew System::EventHandler(this, &Form1::textLogmateFilters_TextChanged);
			// 
			// chBoxLogmate
			// 
			this->chBoxLogmate->AutoSize = true;
			this->chBoxLogmate->Location = System::Drawing::Point(0, 64);
			this->chBoxLogmate->Name = L"chBoxLogmate";
			this->chBoxLogmate->Size = System::Drawing::Size(67, 17);
			this->chBoxLogmate->TabIndex = 12;
			this->chBoxLogmate->Text = L"Logmate";
			this->chBoxLogmate->UseVisualStyleBackColor = true;
			this->chBoxLogmate->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxLogmate_CheckedChanged);
			// 
			// rwLoc
			// 
			this->rwLoc->AutoSize = true;
			this->rwLoc->Location = System::Drawing::Point(40, 96);
			this->rwLoc->Name = L"rwLoc";
			this->rwLoc->Size = System::Drawing::Size(35, 13);
			this->rwLoc->TabIndex = 12;
			this->rwLoc->Text = L"label1";
			// 
			// chBoxAsync
			// 
			this->chBoxAsync->AutoSize = true;
			this->chBoxAsync->ForeColor = System::Drawing::SystemColors::ControlText;
			this->chBoxAsync->Location = System::Drawing::Point(32, 168);
			this->chBoxAsync->Name = L"chBoxAsync";
			this->chBoxAsync->Size = System::Drawing::Size(81, 17);
			this->chBoxAsync->TabIndex = 17;
			this->chBoxAsync->Text = L"Async Keys";
			this->chBoxAsync->UseVisualStyleBackColor = true;
			this->chBoxAsync->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxAsync_CheckedChanged);
			// 
			// chBoxMulticore
			// 
			this->chBoxMulticore->AutoSize = true;
			this->chBoxMulticore->ForeColor = System::Drawing::SystemColors::ControlText;
			this->chBoxMulticore->Location = System::Drawing::Point(32, 192);
			this->chBoxMulticore->Name = L"chBoxMulticore";
			this->chBoxMulticore->Size = System::Drawing::Size(69, 17);
			this->chBoxMulticore->TabIndex = 18;
			this->chBoxMulticore->Text = L"Multicore";
			this->chBoxMulticore->UseVisualStyleBackColor = true;
			this->chBoxMulticore->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxMulticore_CheckedChanged);
			// 
			// chBoxFollowAI
			// 
			this->chBoxFollowAI->AutoSize = true;
			this->chBoxFollowAI->ForeColor = System::Drawing::SystemColors::ControlText;
			this->chBoxFollowAI->Location = System::Drawing::Point(32, 216);
			this->chBoxFollowAI->Name = L"chBoxFollowAI";
			this->chBoxFollowAI->Size = System::Drawing::Size(96, 17);
			this->chBoxFollowAI->TabIndex = 19;
			this->chBoxFollowAI->Text = L"Follow AI Train";
			this->chBoxFollowAI->UseVisualStyleBackColor = true;
			this->chBoxFollowAI->CheckedChanged += gcnew System::EventHandler(this, &Form1::chBoxFollowAI_CheckedChanged);
			// 
			// Form1
			// 
			this->AccessibleDescription = L"Launcher for Train Sim";
			this->AccessibleName = L"TSLauncher";
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->ClientSize = System::Drawing::Size(442, 449);
			this->Controls->Add(this->chBoxFollowAI);
			this->Controls->Add(this->chBoxMulticore);
			this->Controls->Add(this->chBoxAsync);
			this->Controls->Add(this->rwLoc);
			this->Controls->Add(this->panelDev);
			this->Controls->Add(labelFPSLimit);
			this->Controls->Add(this->textFPSLimit);
			this->Controls->Add(title);
			this->Controls->Add(this->toggleDev);
			this->Controls->Add(this->launchDX12);
			this->Controls->Add(this->launchBit64);
			this->Controls->Add(this->launchBit32);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TSLauncher";
			this->panelDev->ResumeLayout(false);
			this->panelDev->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	// function to set a bit field in the argFlags
	private: void setChBoxBitField(int bit, bool state)
	{
		// Set the bit to 1
		if (state) {
			this->argFlags |= (1 << bit);
			return;
		}
		// Set the bit to 0
		this->argFlags &= ~(1 << bit);
	}
#pragma endregion
	private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		CheckedListBox^ checkedListBox = dynamic_cast<CheckedListBox^>(sender);

		if (checkedListBox != nullptr) {
			uint32_t newUserOptions = 0;
			for (int i = 0; i < checkedListBox->Items->Count; i++) {
				if (checkedListBox->GetItemChecked(i)) {
					printf("%d index checkbox was checked\n", i);
					uint32_t bitFlag = 1U << i;
					newUserOptions |= bitFlag;
				}
				else
				{
					printf("%d index checkbox was not checked\n", i);
				}
			}
			//this->flagsUserField = newUserOptions;
			printf("resultant value was %d\n", newUserOptions);
		}
	}
	// Stubs
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	//Enable Developer options
	private: System::Void toggleDev_Click(System::Object^ sender, System::EventArgs^ e) {
		this->panelDevState = !this->panelDevState;
		puts("toggling dev panel");
		char* ser = (char*) malloc(2048);
		REG_STORE_SERIALISE_OUT(ser);
		this->SetStringToRegistry(RW_REG_KEY_PATH, "launcher_store", ser);
		if (this->panelDevState)
		{
			this->panelDev->Show();
			return;
		}
		this->panelDev->Hide();
	}
	
	//Checkboxes
	private: System::Void chBoxLogmate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_LOGMATE, sender);
	}

	private: System::Void chBoxLuaDebug_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_LUA_DEBUG, sender);
	}
	private: System::Void chBoxControlDialog_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_CTRL_DIALOG, sender);
	}	
	private: System::Void chBoxSoundDialog_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_SOUND_DIALOG, sender);
	}
	private: System::Void chBoxNoBpCache_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_NO_BP_CACHE, sender);
	}
	private: System::Void chBoxAsync_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_ASYNC, sender);
	}
	private: System::Void chBoxMulticore_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_MULTICORE, sender);
	}
	private: System::Void chBoxFollowAI_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		CH_BOX_SET_BIT(this->argFlags, CH_BOX_BIT_FOLLOWAI, sender);
	}

	//Text Fields
	private: System::Void textFPSLimit_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		TEXT_BOX_STORE_FROM_EVENT(this->fpsLimit, sender, "launcher_store_fps");
	}
	private: System::Void textLogmateFilters_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		TEXT_BOX_STORE_FROM_EVENT(this->logmateFilters, sender, "launcher_store_logmate");
	}
	//Launch buttons
	private: System::Void launchBit32_Click(System::Object^ sender, System::EventArgs^ e) {
		this->launchTS(0);
	}
	private: System::Void launchBit64_Click_1(System::Object^ sender, System::EventArgs^ e) {
		this->launchTS(1);
	}
	private: System::Void launchDX12_Click_1(System::Object^ sender, System::EventArgs^ e) {
		this->launchTS(2);
	}

	//Common functions that are launched by the launch buttons
	private: void launchTS(int version)
	{
		//Make a buffer and put the start of our command in
		char buffer[8096];
		strcpy(buffer, "START /D ");
		strcat(buffer, this->rwPath);
		strcat(buffer, " ");

		//Add the RW EXE name
		switch (version)
		{
			case 0:
				strcat(buffer, RW_32BIT_EXE);
				break;
			case 1:
				strcat(buffer, RW_64BIT_EXE);
				break;
			case 2:
				strcat(buffer, RW_DX12_EXE);
				break;
		}

		//Handle all the boolean launch functions

		for (int i = 0; i < 32; i++) {
			bool state = (this->argFlags & (1 << i)) != 0;

			switch (i) {
			case CH_BOX_BIT_LOGMATE:
				if (state)
					strcat(buffer, " -LogMate");
				break;
			case CH_BOX_BIT_LUA_DEBUG:
				if (state)
					strcat(buffer, " -lua-debug-messages");
				break;
			case CH_BOX_BIT_CTRL_DIALOG:
				if (state)
					strcat(buffer, " -ShowControlStateDialog");
				break;
			case CH_BOX_BIT_SOUND_DIALOG:
				if (state)
					strcat(buffer, " -EnableSoundDebugDialogs");
				break;
			case CH_BOX_BIT_NO_BP_CACHE:
				if (state)
					strcat(buffer, " -DontUseBlueprintCache");
				break;
			case CH_BOX_BIT_ASYNC:
				if (state)
					strcat(buffer, " -EnableAsyncKeys");
				break;
			case CH_BOX_BIT_MULTICORE:
				if (state)
					strcat(buffer, " -Multicore");
				break;
			case CH_BOX_BIT_FOLLOWAI:
				if (state)
					strcat(buffer, " -followaitrain");
				break;
			default:
				break;
			}
		}

		//Check if the text fields exist, if they do build their argument and add it.

		if (this->logmateFilters!= NULL && strlen(this->logmateFilters) > 0)
		{
			char catTemp[256];
			sprintf(catTemp, " -SetLogFilters=\"%s\"", this->logmateFilters);
			strcat(buffer, catTemp);
		}

		if (this->fpsLimit != NULL && strlen(this->fpsLimit) > 0)
		{
			char catTemp[256];
			sprintf(catTemp, " -FPSLimit=%s", this->fpsLimit);
			strcat(buffer, catTemp);
		}

		//printf("%s\n", buffer);
		//return;
		system(buffer);
	}
};
}


