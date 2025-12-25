#pragma once
#include "ATC.h"

using namespace System::Windows::Forms;

namespace ATCWinForm
{
    public ref class MainForm : public Form
    {
    private:
        ATC^ atc;
        DataGridView^ grid;

        Button^ btnAdd;
        Button^ btnRemove;
        Button^ btnSave;
        Button^ btnLoad;
        Button^ btnSortName;
        Button^ btnSortPrice;

        void RefreshGrid();

        void AddClick(System::Object^, System::EventArgs^);
        void RemoveClick(System::Object^, System::EventArgs^);
        void SaveClick(System::Object^, System::EventArgs^);
        void LoadClick(System::Object^, System::EventArgs^);
        void SortNameClick(System::Object^, System::EventArgs^);
        void SortPriceClick(System::Object^, System::EventArgs^);

    public:
        MainForm();
    };
}
