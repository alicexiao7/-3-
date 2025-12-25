#include "AddEditForm.h"

namespace ATCWinForm
{
    AddEditForm::AddEditForm()
    {
        Text = "Add tariff";
        Width = 300;
        Height = 250;
        StartPosition = FormStartPosition::CenterParent;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;

        Label^ l1 = gcnew Label();
        l1->Text = "Name:";
       
        l1->Location = System::Drawing::Point(10, 10);

        tbName = gcnew TextBox();
        tbName->Location = System::Drawing::Point(10, 30);
        tbName->Width = 250;

        Label^ l2 = gcnew Label();
        l2->Text = "Price:";
        l2->Location = System::Drawing::Point(10, 60);

        tbPrice = gcnew TextBox();
        tbPrice->Location = System::Drawing::Point(10, 80);
        tbPrice->Width = 250;

        Label^ l3 = gcnew Label();
        l3->Text = "Discount:";
        l3->Location = System::Drawing::Point(10, 110);

        tbDiscount = gcnew TextBox();
        tbDiscount->Location = System::Drawing::Point(10, 130);
        tbDiscount->Width = 250;

        btnOK = gcnew Button();
        btnOK->Text = "OK";
        btnOK->Location = System::Drawing::Point(90, 160);
        btnOK->Click += gcnew EventHandler(this, &AddEditForm::OnOK);

        Controls->Add(l1);
        Controls->Add(tbName);
        Controls->Add(l2);
        Controls->Add(tbPrice);
        Controls->Add(l3);
        Controls->Add(tbDiscount);
        Controls->Add(btnOK);
    }


    AddEditForm::AddEditForm(Tariff^ t) : AddEditForm()
    {
        Text = "Edit tariff";
        tbName->Text = t->Name;
        tbPrice->Text = t->Price.ToString();
        tbDiscount->Text = t->Discount.ToString();
        Result = t;
    }


    void AddEditForm::OnOK(System::Object^, System::EventArgs^)
    {
        if (String::IsNullOrWhiteSpace(tbName->Text))
        {
            MessageBox::Show("Введите название тарифа");
            return;
        }

        double price;
        double discount = 0;

        if (!Double::TryParse(tbPrice->Text, price))
        {
            MessageBox::Show("Цена должна быть числом");
            return;
        }

        if (price <= 0)
        {
            MessageBox::Show("Цена должна быть больше 0");
            return;
        }
        if (!String::IsNullOrWhiteSpace(tbDiscount->Text))
        {
            if (!Double::TryParse(tbDiscount->Text, discount))
            {
                MessageBox::Show("Скидка должна быть числом");
                return;
            }

            if (discount < 0 || discount > 100)
            {
                MessageBox::Show("Скидка должна быть от 0 до 100%");
                return;
            }
        }

        Result = gcnew Tariff(tbName->Text, price, discount);

        DialogResult = System::Windows::Forms::DialogResult::OK;
        Close();
    }


}
