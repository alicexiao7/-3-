#include "Tariff.h"

namespace ATCWinForm
{
    Tariff::Tariff(String^ n, double p, double d)
    {
        name = n;
        price = p;
        discount = d;
    }

    String^ Tariff::Name::get() { return name; }
    void Tariff::Name::set(String^ v) { name = v; }

    double Tariff::Price::get() { return price; }
    void Tariff::Price::set(double v) { price = v; }

    double Tariff::Discount::get() { return discount; }
    void Tariff::Discount::set(double v) { discount = v; }

    double Tariff::CalculateCost()
    {
        return price - price * discount / 100.0;
    }
}
