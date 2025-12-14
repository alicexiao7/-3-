#pragma once
#include <string>
#include "Tariff.h"

class ATC {
private:
    Tariff* tariffs[100];
    int count;
public:
    ATC();
    ~ATC();

    void addRegularTariff(const std::string& name, double price);
    void addDiscountTariff(const std::string& name, double price, double discount);

    void displayAllTariffs() const;
    double calculateAverageCost() const;

    void printTariffInfo(const Tariff& tariff) const;

  
    Tariff* getTariff(int index) const;
    int getTariffCount() const { return count; }
    Tariff* getFirstTariff() const { return (count > 0) ? tariffs[0] : nullptr; }
};
