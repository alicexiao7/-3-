#include "tariff.h"
#include <iostream>

Tariff::Tariff(const std::string& tariffName, double price)
    : tariffName(tariffName), basePrice(price) {
    if (price < 0 || price > 1000000)
        throw TariffException("Стоимость тарифа должна быть от 0 до 1,000,000");
}

RegularTariff::RegularTariff(const std::string& name, double price)
    : Tariff(name, price) {
}

double RegularTariff::calculateCost() const {
    return basePrice;
}

DiscountTariff::DiscountTariff(const std::string& name, double price, double discount)
    : Tariff(name, price), discountPercent(discount) {
    if (discount < 0 || discount > 100)
        throw TariffException("Скидка должна быть от 0 до 100%");
}

double DiscountTariff::calculateCost() const {
    return basePrice * (1 - discountPercent / 100.0);
}