#ifndef ATC_H
#define ATC_H

#include "tariff.h"
#include <vector>
#include <memory>
#include <string>

class ATC {
private:
    std::vector<std::unique_ptr<Tariff>> tariffs;

    bool isValidPrice(double price) const;
    bool isValidDiscount(double discount) const;

public:
    ATC();
    void addRegularTariff(const std::string& name, double price);
    void addDiscountTariff(const std::string& name, double price, double discount);
    double calculateAverageCost() const;
    size_t getTariffCount() const;
    void displayAllTariffs() const;
};

#endif
