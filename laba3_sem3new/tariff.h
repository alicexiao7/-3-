#ifndef TARIFF_H
#define TARIFF_H

#include <string>
#include <stdexcept>

class TariffException : public std::runtime_error {
public:
    explicit TariffException(const std::string& msg)
        : std::runtime_error(msg.c_str()) {}
};

class Tariff {
protected:
    std::string tariffName;
    double basePrice;

public:
    Tariff(const std::string& name, double price);
    virtual ~Tariff() = default;
    virtual double calculateCost() const = 0;

    std::string getName() const { return tariffName; }
    double getBasePrice() const { return basePrice; }
};

class RegularTariff : public Tariff {
public:
    RegularTariff(const std::string& name, double price);
    double calculateCost() const override;
};

class DiscountTariff : public Tariff {
    double discountPercent;
public:
    DiscountTariff(const std::string& name, double price, double discount);
    double calculateCost() const override;
    double getDiscount() const { return discountPercent; }
};

#endif