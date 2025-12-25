#pragma once

using namespace System;

namespace ATCWinForm
{
    public ref class Tariff
    {
    private:
        String^ name;
        double price;
        double discount;

    public:
        Tariff(String^ name, double price, double discount);

        property String^ Name { String^ get(); void set(String^); }
        property double Price { double get(); void set(double); }
        property double Discount { double get(); void set(double); }

        double CalculateCost();
    };
}
