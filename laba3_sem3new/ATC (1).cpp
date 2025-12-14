#include "ATC.h"
#include <iostream>
#include <iomanip>

bool ATC::isValidPrice(double price) const {
    return price >= 0 && price <= 1000000;
}

bool ATC::isValidDiscount(double discount) const {
    return discount >= 0 && discount <= 100;
}

ATC::ATC() {
    // Начальные тарифы из скриншота
    tariffs.push_back(std::make_unique<RegularTariff>("Местный", 500));
    tariffs.push_back(std::make_unique<RegularTariff>("Междугородный", 1500));
    tariffs.push_back(std::make_unique<DiscountTariff>("Льготный местный", 500, 10));
    tariffs.push_back(std::make_unique<DiscountTariff>("Льготный междугородный", 1500, 15));
}

void ATC::addRegularTariff(const std::string& name, double price) {
    if (!isValidPrice(price))
        throw TariffException("Некорректная стоимость тарифа");
    tariffs.push_back(std::make_unique<RegularTariff>(name, price));
    std::cout << "Добавлен обычный тариф \"" << name << "\" — " << price << " руб.\n";
}

void ATC::addDiscountTariff(const std::string& name, double price, double discount) {
    if (!isValidPrice(price))
        throw TariffException("Некорректная стоимость тарифа");
    if (!isValidDiscount(discount))
        throw TariffException("Некорректный размер скидки");
    tariffs.push_back(std::make_unique<DiscountTariff>(name, price, discount));
    std::cout << "Добавлен льготный тариф \"" << name << "\" — " << price
        << " руб. со скидкой " << discount << "%\n";
}

double ATC::calculateAverageCost() const {
    if (tariffs.empty()) return 0.0;
    double sum = 0;
    for (const auto& t : tariffs)
        sum += t->calculateCost();
    return sum / tariffs.size();
}

size_t ATC::getTariffCount() const {
    return tariffs.size();
}

void ATC::displayAllTariffs() const {
    std::cout << "\n=== ВСЕ ТАРИФЫ АТС ===\n";
    for (size_t i = 0; i < tariffs.size(); ++i) {
        const auto& t = tariffs[i];
        std::cout << i + 1 << ". " << t->getName()
            << " — Базовая стоимость: " << t->getBasePrice() << " руб.";
        if (auto* dt = dynamic_cast<DiscountTariff*>(t.get())) {
            std::cout << ", Итоговая стоимость: "
                << std::fixed << std::setprecision(0) << dt->calculateCost() << " руб.";
        }
        else {
            std::cout << ", Итоговая стоимость: " << t->calculateCost() << " руб.";
        }
        std::cout << "\n";
    }
}