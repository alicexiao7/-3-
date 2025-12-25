#include "MainForm.h"
#include "AddEditForm.h"

namespace ATCWinForm
{
    MainForm::MainForm()
    {
        Text = "ATC";
        Width = 600;
        Height = 400;

        atc = gcnew ATC();
        atc->LoadCSV("data.csv");
        grid = gcnew DataGridView();
        grid->Dock = DockStyle::Top;
        grid->Height = 200; 

        btnAdd = gcnew Button();
        btnAdd->Text = "Add";
        btnAdd->Click += gcnew System::EventHandler(this, &MainForm::AddClick);

        btnRemove = gcnew Button();
        btnRemove->Text = "Remove";
        btnRemove->Click += gcnew System::EventHandler(this, &MainForm::RemoveClick);

        btnSave = gcnew Button();
        btnSave->Text = "Save CSV";
        btnSave->Click += gcnew System::EventHandler(this, &MainForm::SaveClick);

        btnLoad = gcnew Button();
        btnLoad->Text = "Load CSV";
        btnLoad->Click += gcnew System::EventHandler(this, &MainForm::LoadClick);

        btnSortName = gcnew Button();
        btnSortName->Text = "Sort Name";
        btnSortName->Click += gcnew System::EventHandler(this, &MainForm::SortNameClick);

        btnSortPrice = gcnew Button();
        btnSortPrice->Text = "Sort Price";
        btnSortPrice->Click += gcnew System::EventHandler(this, &MainForm::SortPriceClick);

        Controls->Add(grid);
        Controls->Add(btnAdd);
        Controls->Add(btnRemove);
        Controls->Add(btnSave);
        Controls->Add(btnLoad);
        Controls->Add(btnSortName);
        Controls->Add(btnSortPrice);

        btnAdd->Location = System::Drawing::Point(10, 220);
        btnRemove->Location = System::Drawing::Point(100, 220);
        btnSave->Location = System::Drawing::Point(190, 220);
        btnLoad->Location = System::Drawing::Point(280, 220);

        btnSortName->Location = System::Drawing::Point(10, 260);
        btnSortPrice->Location = System::Drawing::Point(100, 260);

        Refresh();
    }

    void MainForm::RefreshGrid()
    {
        grid->DataSource = nullptr;
        grid->DataSource = atc->GetAll();
        grid->AutoGenerateColumns = true;
        grid->ReadOnly = true;
        grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        grid->MultiSelect = false;

    }

   void MainForm::AddClick(System::Object^, System::EventArgs^)
{
    AddEditForm^ f = gcnew AddEditForm();
    if (f->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        atc->Add(f->Result);
        atc->SaveCSV("data.csv");
        RefreshGrid();
    }
}


    void MainForm::RemoveClick(System::Object^, System::EventArgs^)
    {
        if (grid->CurrentRow)
        {
            atc->Remove(grid->CurrentRow->Index);
            atc->SaveCSV("data.csv");
            Refresh();
        }
    }
    void MainForm::SortNameClick(System::Object^, System::EventArgs^)
    {
        atc->SortByName();
        RefreshGrid();
    }

    void MainForm::SortPriceClick(System::Object^, System::EventArgs^)
    {
        atc->SortByPrice();
        RefreshGrid();
    }

    void MainForm::SaveClick(System::Object^, System::EventArgs^)
    {
        atc->SaveCSV("data.csv"); // сохраняем автоматически
        MessageBox::Show("Saved to data.csv");
    }


    void MainForm::LoadClick(System::Object^, System::EventArgs^)
    {
        atc->LoadCSV("data.csv"); // загружаем автоматически
        RefreshGrid();
        MessageBox::Show("Loaded from data.csv");
        
    }

}
