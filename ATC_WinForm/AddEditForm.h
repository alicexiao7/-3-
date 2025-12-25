#pragma once
#include "Tariff.h"

using namespace System::Windows::Forms;

namespace ATCWinForm
{
    public ref class AddEditForm : public Form
    {
    public:
        Tariff^ Result;

        AddEditForm();
        AddEditForm(Tariff^ t);

    private:
        TextBox^ tbName;
        TextBox^ tbPrice;
        TextBox^ tbDiscount;
        Button^ btnOK;

        void OnOK(System::Object^, System::EventArgs^);
    };
}
