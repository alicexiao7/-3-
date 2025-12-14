#include "ATC.h"
#include <iostream>
#include <iomanip>

ATC::ATC() : count(0) {
    for (int i = 0; i < 100; ++i) tariffs[i] = nullptr;
}

ATC::~ATC() {
    for (int i = 0; i < count; ++i) {
        delete tariffs[i];
        tariffs[i] = nullptr;
    }
}

void ATC::addRegularTariff(const std::string& name, double price) {
    if (count >= 100) throw TariffException("Превышено максимальное количество тарифов");
    tariffs[count++] = new Tariff(name, price);
}

void ATC::addDiscountTariff(const std::string& name, double price, double discount) {
    if (count >= 100) throw TariffException("Превышено максимальное количество тарифов");
    tariffs[count++] = new DiscountTariff(name, price, discount);
}

void ATC::displayAllTariffs() const {
    for (int i = 0; i < count; ++i) {
        std::cout << (i + 1) << ". ";
        tariffs[i]->show();
    }
}

double ATC::calculateAverageCost() const {
    if (count == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < count; ++i) {
        sum += tariffs[i]->calculateCost();
    }
    return sum / count;
}

void ATC::printTariffInfo(const Tariff& tariff) const {
    std::cout << "Информация о тарифе:\n";
    std::cout << "Название: " << tariff.getName() << "\n";
    std::cout << "Базовая цена: " << tariff.getBasePrice() << "\n";
    std::cout << "Итоговая цена: " << tariff.calculateCost() << "\n";
}

Tariff* ATC::getTariff(int index) const {
    if (index >= 0 && index < count) return tariffs[index];
    return nullptr;
}
