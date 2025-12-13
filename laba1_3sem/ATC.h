#ifndef ATC_H
#define ATC_H

#include <string>
#include <cstdint>
#include <iosfwd>

class ATC {
private:
    std::string address_;
    double subscriptionFee_;    // цена для одного абонента
    int subscribers_;           // количество абонентов (write only)

public:
    ATC();

    //адрес
    void setAddress(const std::string& addr);
    std::string getAddress() const;

    // subscriptionFee
    void setSubscriptionFee(double fee);
    double getSubscriptionFee() const;

    // абоненты кол-во (write-only)
    void setSubscribers(int n);

    // расчет общей
    double calculateTotalFee() const;

    // вывод
    void printSummary(std::ostream& os) const;
};
int getValidInt(const std::string& prompt);
double getValidDouble(const std::string& prompt);
std::string getValidString(const std::string& prompt);

void showMenu();

#endif // ATC_H

