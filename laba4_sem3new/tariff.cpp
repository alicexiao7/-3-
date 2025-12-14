#include "Tariff.h"


TariffException::TariffException(const std::string& msg) : message(msg) {}
const char* TariffException::what() const noexcept { return message.c_str(); }


Tariff::Tariff(const std::string& name, double price)
    : tariffName(name), basePrice(price) {
}

double Tariff::calculateCost() const {
    return basePrice;
}

void Tariff::show() const {
    std::cout << "Тариф: " << tariffName << ", цена: " << calculateCost() << "\n";
}

std::string Tariff::getName() const { return tariffName; }
double Tariff::getBasePrice() const { return basePrice; }


Tariff* Tariff::operator+(const Tariff& other) const {
    double newBase = this->basePrice + other.basePrice;
    std::string newName = this->tariffName + " + " + other.tariffName;

    bool d1 = this->isDiscountTariff();
    bool d2 = other.isDiscountTariff();

    if (d1 && d2) {
        double avg = (this->getDiscountValue() + other.getDiscountValue()) / 2.0;
        return new DiscountTariff(newName, newBase, avg);
    }
    if (d1) {
        return new DiscountTariff(newName, newBase, this->getDiscountValue());
    }
    if (d2) {
        return new DiscountTariff(newName, newBase, other.getDiscountValue());
    }
    return new Tariff(newName, newBase);
}


DiscountTariff::DiscountTariff(const std::string& name, double price, double disc)
    : Tariff(name, price), discount(disc) {
}

double DiscountTariff::calculateCost() const {
    return basePrice * (1.0 - discount / 100.0);
}

void DiscountTariff::show() const {
    std::cout << "Тариф: " << tariffName
        << ", базовая цена: " << basePrice
        << ", скидка: " << discount << "%, итог: " << calculateCost() << "\n";
}
