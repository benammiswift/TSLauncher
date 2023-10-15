#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include "stdio.h"
#include "Windows.h"
#include "stdint.h"


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			bool chk = AllocConsole();
			if (chk)
			{
				freopen("CONOUT$", "w", stdout);
				//printf(" printing to console");
			}
			this->checkboxesDev->CheckOnClick = false;
			this->checkboxesUser->CheckOnClick = false;
			this->panelDevState = false;
			puts("deez");
			//TODO: Add the constructor code here
			//
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
	private: bool panelDevState;
	private: uint32_t flagsDevField;
	private: uint32_t flagsUserField;
	private: System::Windows::Forms::Button^ LaunchBit32;
	private: System::Windows::Forms::CheckedListBox^ checkboxesUser;
	protected:

	protected:


	private: System::Windows::Forms::Button^ launchBit64;
	private: System::Windows::Forms::Button^ launchDX12;
	private: System::Windows::Forms::Button^ toggleDev;
	private: System::Windows::Forms::CheckedListBox^ checkboxesDev;
	private: System::Windows::Forms::TextBox^ textLogmateFilters;













	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ labelLogmateFilter;
	private: System::Windows::Forms::Panel^ panelDev;
	private: System::Windows::Forms::CheckBox^ checkBox1;
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
			this->LaunchBit32 = (gcnew System::Windows::Forms::Button());
			this->checkboxesUser = (gcnew System::Windows::Forms::CheckedListBox());
			this->launchBit64 = (gcnew System::Windows::Forms::Button());
			this->launchDX12 = (gcnew System::Windows::Forms::Button());
			this->toggleDev = (gcnew System::Windows::Forms::Button());
			this->checkboxesDev = (gcnew System::Windows::Forms::CheckedListBox());
			this->textLogmateFilters = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panelDev = (gcnew System::Windows::Forms::Panel());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
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
			title->Location = System::Drawing::Point(16, 0);
			title->Name = L"title";
			title->Size = System::Drawing::Size(411, 73);
			title->TabIndex = 8;
			title->Text = L"TS Launcher";
			title->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// labelFPSLimit
			// 
			labelFPSLimit->AutoSize = true;
			labelFPSLimit->Location = System::Drawing::Point(40, 360);
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
			// LaunchBit32
			// 
			this->LaunchBit32->Location = System::Drawing::Point(32, 88);
			this->LaunchBit32->Name = L"LaunchBit32";
			this->LaunchBit32->Size = System::Drawing::Size(121, 35);
			this->LaunchBit32->TabIndex = 0;
			this->LaunchBit32->Text = L"32 Bit";
			this->LaunchBit32->UseVisualStyleBackColor = true;
			this->LaunchBit32->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// checkboxesUser
			// 
			this->checkboxesUser->FormattingEnabled = true;
			this->checkboxesUser->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Async Keys", L"Multicore", L"Follow AI Train" });
			this->checkboxesUser->Location = System::Drawing::Point(32, 136);
			this->checkboxesUser->Name = L"checkboxesUser";
			this->checkboxesUser->Size = System::Drawing::Size(184, 214);
			this->checkboxesUser->TabIndex = 1;
			this->checkboxesUser->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::checkedListBox1_SelectedIndexChanged);
			// 
			// launchBit64
			// 
			this->launchBit64->Location = System::Drawing::Point(160, 88);
			this->launchBit64->Name = L"launchBit64";
			this->launchBit64->Size = System::Drawing::Size(121, 35);
			this->launchBit64->TabIndex = 2;
			this->launchBit64->Text = L"64 Bit";
			this->launchBit64->UseVisualStyleBackColor = true;
			// 
			// launchDX12
			// 
			this->launchDX12->Location = System::Drawing::Point(288, 88);
			this->launchDX12->Name = L"launchDX12";
			this->launchDX12->Size = System::Drawing::Size(121, 35);
			this->launchDX12->TabIndex = 3;
			this->launchDX12->Text = L"DX12 ";
			this->launchDX12->UseVisualStyleBackColor = true;
			// 
			// toggleDev
			// 
			this->toggleDev->Location = System::Drawing::Point(248, 144);
			this->toggleDev->Name = L"toggleDev";
			this->toggleDev->Size = System::Drawing::Size(128, 35);
			this->toggleDev->TabIndex = 4;
			this->toggleDev->Text = L"Developer Options";
			this->toggleDev->UseVisualStyleBackColor = true;
			this->toggleDev->Click += gcnew System::EventHandler(this, &Form1::toggleDev_Click);
			// 
			// checkboxesDev
			// 
			this->checkboxesDev->FormattingEnabled = true;
			this->checkboxesDev->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Logmate", L"Lua Debug Messages", L"Control State Dialog",
					L"Sound Debug Dialog", L"Dont Use Blueprint Cache"
			});
			this->checkboxesDev->Location = System::Drawing::Point(0, 72);
			this->checkboxesDev->Name = L"checkboxesDev";
			this->checkboxesDev->Size = System::Drawing::Size(184, 139);
			this->checkboxesDev->TabIndex = 5;
			this->checkboxesDev->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::checkedListBox2_SelectedIndexChanged);
			// 
			// textLogmateFilters
			// 
			this->textLogmateFilters->Location = System::Drawing::Point(0, 32);
			this->textLogmateFilters->Name = L"textLogmateFilters";
			this->textLogmateFilters->Size = System::Drawing::Size(184, 20);
			this->textLogmateFilters->TabIndex = 6;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(32, 384);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(184, 20);
			this->textBox2->TabIndex = 9;
			// 
			// panelDev
			// 
			this->panelDev->Controls->Add(this->checkboxesDev);
			this->panelDev->Controls->Add(this->textLogmateFilters);
			this->panelDev->Controls->Add(this->labelLogmateFilter);
			this->panelDev->Location = System::Drawing::Point(232, 208);
			this->panelDev->Name = L"panelDev";
			this->panelDev->Size = System::Drawing::Size(192, 208);
			this->panelDev->TabIndex = 11;
			this->panelDev->Visible = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(232, 184);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(80, 17);
			this->checkBox1->TabIndex = 12;
			this->checkBox1->Text = L"checkBox1";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// Form1
			// 
			this->AccessibleDescription = L"Launcher for Train Sim";
			this->AccessibleName = L"TSLauncher";
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->ClientSize = System::Drawing::Size(442, 669);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->panelDev);
			this->Controls->Add(labelFPSLimit);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(title);
			this->Controls->Add(this->toggleDev);
			this->Controls->Add(this->launchDX12);
			this->Controls->Add(this->launchBit64);
			this->Controls->Add(this->checkboxesUser);
			this->Controls->Add(this->LaunchBit32);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Name = L"Form1";
			this->Text = L"TSLauncher";
			this->panelDev->ResumeLayout(false);
			this->panelDev->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

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
			this->flagsUserField = newUserOptions;
			printf("resultant value was %d\n", newUserOptions);
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
		   /*
	private: System::Void checkedListBox2_OnMouseDoubleClick(System::Object^ sender, System::EventArgs^ e) {
		puts("double click");
	}
	private: System::Void checkedListBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		CheckedListBox^ checkedListBox = dynamic_cast<CheckedListBox^>(sender);

		if (checkedListBox != nullptr) {
			uint32_t newDevOptions = 0;
			for (int i = 0; i < checkedListBox->Items->Count; i++) {
				if (checkedListBox->GetItemChecked(i)) {
					printf("%d index checkbox was checked\n", i);
					uint32_t bitFlag = 1U << i;
					newDevOptions |= bitFlag;
				}
				else
				{
					printf("%d index checkbox was not checked\n", i);
				}
			}
			this->flagsDevField = newDevOptions;
			printf("resultant value was %d\n", newDevOptions);
		}
	}
	private: System::Void checkedListBox2_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
		if (e->CurrentValue == CheckState::Unchecked && e->NewValue == CheckState::Unchecked) {
			// This check ensures it's a single-click (both the current and new values are unchecked)
			e->NewValue = CheckState::Checked; // Manually check the item
		}
		else if (e->CurrentValue == CheckState::Checked && e->NewValue == CheckState::Checked) {
			// This check ensures it's a single-click (both the current and new values are checked)
			e->NewValue = CheckState::Unchecked; // Manually uncheck the item
		}
	}
	*/
	private: bool isDoubleClick = false; // Flag to track double-click

private: System::Void checkedListBox2_DoubleClick(System::Object^ sender, System::EventArgs^ e) {
    isDoubleClick = true; // Set the flag to indicate a double-click
    printf("Double-click detected.\n");
}
	private: System::Void checkedListBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void checkedListBox2_OnItemCheck(System::Object^ sender, System::EventArgs^ e) {
    CheckedListBox^ checkedListBox = dynamic_cast<CheckedListBox^>(sender);

    if (checkedListBox != nullptr) {
        if (isDoubleClick) {
            // Handle double-click to toggle the checkbox state
            int selectedIndex = checkedListBox->SelectedIndex;
            if (selectedIndex != -1) {
                checkedListBox->SetItemChecked(selectedIndex, !checkedListBox->GetItemChecked(selectedIndex));
                printf("Toggled checkbox at index %d.\n", selectedIndex);
            }
            isDoubleClick = false; // Reset the flag
        } else {
            // Handle regular selection changes and update flagsDevField
            uint32_t newDevOptions = 0;
            for (int i = 0; i < checkedListBox->Items->Count; i++) {
                if (checkedListBox->GetItemChecked(i)) {
                    uint32_t bitFlag = 1U << i;
                    newDevOptions |= bitFlag;
                    printf("%d index checkbox was checked.\n", i);
                } else {
                    printf("%d index checkbox was not checked.\n", i);
                }
            }
            this->flagsDevField = newDevOptions;
            printf("flagsDevField updated to %d.\n", newDevOptions);
        }
    }
}



	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void toggleDev_Click(System::Object^ sender, System::EventArgs^ e) {
		this->panelDevState = !this->panelDevState;
		puts("toggling dev panel");
		if (this->panelDevState)
		{
			this->panelDev->Show();
			return;
		}
		this->panelDev->Hide();
	}
		   
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		puts("Check changed");
	}
};
}
