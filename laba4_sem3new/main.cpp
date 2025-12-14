#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "ATC.h"

double getValidatedInput(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            // clear trailing newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Ошибка! Введите число от " << min << " до " << max << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

void displayMenu() {
    std::cout << "\n=== МЕНЮ АТС ===\n";
    std::cout << "1. Добавить обычный тариф\n";
    std::cout << "2. Добавить льготный тариф\n";
    std::cout << "3. Показать все тарифы\n";
    std::cout << "4. Рассчитать среднюю стоимость\n";
    std::cout << "5. Выход\n";
    std::cout << "6. Показать первый тариф (объект как аргумент)\n";
    std::cout << "7. Объединить два тарифа (перегрузка operator+)\n";
    std::cout << "Выберите действие: ";
}

int main() {
    
    setlocale(LC_ALL, "");

    ATC atc;


    atc.addRegularTariff("Базовый", 100);
    atc.addRegularTariff("Стандарт", 200);
    atc.addDiscountTariff("Льготный", 150, 10);
    atc.addDiscountTariff("Премиум", 300, 15);

    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ ТАРИФАМИ АТС ===\n";
    std::cout << "Загружены начальные тарифы (4 шт.)\n";

    while (true) {
        displayMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
        }
        // очистить строку после чтения числа
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1: {
                std::string name = getStringInput("Введите название тарифа: ");
                double price = getValidatedInput("Введите стоимость тарифа (0-1,000,000): ", 0, 1000000);
                atc.addRegularTariff(name, price);
                std::cout << "Обычный тариф добавлен!\n";
                break;
            }
            case 2: {
                std::string name = getStringInput("Введите название тарифа: ");
                double price = getValidatedInput("Введите стоимость тарифа (0-1,000,000): ", 0, 1000000);
                double disc = getValidatedInput("Введите размер скидки (0-100%): ", 0, 100);
                atc.addDiscountTariff(name, price, disc);
                std::cout << "Льготный тариф добавлен!\n";
                break;
            }
            case 3:
                if (atc.getTariffCount() > 0) {
                    atc.displayAllTariffs();
                }
                else {
                    std::cout << "Тарифов пока нет.\n";
                }
                break;
            case 4: {
                if (atc.getTariffCount() > 0) {
                    double avg = atc.calculateAverageCost();
                    std::cout << "\nСредняя стоимость всех тарифов: "
                        << std::fixed << std::setprecision(2) << avg << " руб.\n";
                }
                else {
                    std::cout << "Нет тарифов для расчета.\n";
                }
                break;
            }
            case 5:
                std::cout << "Выход из программы.\n";
                return 0;
            case 6:
                if (atc.getTariffCount() > 0) {
                    Tariff* first = atc.getFirstTariff();
                    if (first) atc.printTariffInfo(*first);
                }
                else {
                    std::cout << "Тарифов пока нет.\n";
                }
                break;
            case 7: {
                std::cout << "\n=== ОБЪЕДИНЕНИЕ ТАРИФОВ ===\n";

                if (atc.getTariffCount() < 2) {
                    std::cout << "Для объединения нужно минимум 2 тарифа!\n";
                    break;
                }

                
                std::cout << "Доступные тарифы:\n";
                atc.displayAllTariffs();

                int choice1 = 0, choice2 = 0;
                while (true) {
                    std::cout << "\nВыберите первый тариф для объединения (1-" << atc.getTariffCount() << "): ";
                    if (std::cin >> choice1 && choice1 >= 1 && choice1 <= atc.getTariffCount()) break;
                    std::cout << "Неверный выбор! Попробуйте снова.\n";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                while (true) {
                    std::cout << "Выберите второй тариф для объединения (1-" << atc.getTariffCount() << "): ";
                    if (std::cin >> choice2 && choice2 >= 1 && choice2 <= atc.getTariffCount()) {
                        if (choice2 != choice1) break;
                        std::cout << "Нельзя выбрать тот же тариф! Выберите другой.\n";
                    }
                    else {
                        std::cout << "Неверный выбор! Попробуйте снова.\n";
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                    }
                }
                // очистка остатка
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Tariff* t1 = atc.getTariff(choice1 - 1);
                Tariff* t2 = atc.getTariff(choice2 - 1);

                std::cout << "\nВы выбрали:\n1. "; t1->show();
                std::cout << "2. "; t2->show();

                std::cout << "\n=== РЕЗУЛЬТАТ ОБЪЕДИНЕНИЯ ===\n";

                Tariff* result = *t1 + *t2;
                std::cout << "Новый тариф (результат operator+):\n";
                result->show();

                
                std::cout << "\nДетали:\n";
                std::cout << "Название: \"" << t1->getName() << "\" + \"" << t2->getName()
                    << "\" = \"" << result->getName() << "\"\n";
                std::cout << "Базовая цена: " << t1->getBasePrice() << " + " << t2->getBasePrice()
                    << " = " << result->getBasePrice() << "\n";
                std::cout << "Итоговая цена (с учётом скидок): " << result->calculateCost() << "\n";

                
                std::cout << "\nХотите добавить этот объединённый тариф в систему? (1 - да, 0 - нет): ";
                int addChoice;
                if (std::cin >> addChoice && addChoice == 1) {
                    if (result->isDiscountTariff()) {
                        atc.addDiscountTariff(result->getName(), result->getBasePrice(), result->getDiscountValue());
                        delete result; 
                    }
                    else {
                        atc.addRegularTariff(result->getName(), result->getBasePrice());
                        delete result;
                    }
                    std::cout << "Тариф добавлен в систему.\n";
                }
                else {
                    delete result;
                    std::cout << "Тариф не добавлен.\n";
                }

                std::cout << "\n=== ЦЕПОЧКА (пример): тариф1 + тариф2 + тариф1 ===\n";
                Tariff* tmp = *t1 + *t2;      // tmp - новый объект
                Tariff* chain = *tmp + *t1;  // chain - новый объект
                chain->show();
                delete tmp;
                delete chain;

                break;
            }
            default:
                std::cout << "Выберите пункт от 1 до 7!\n";
            }
        }
        catch (const TariffException& e) {
            std::cout << "Ошибка тарифа: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
        catch (...) {
            std::cout << "Неожиданная ошибка!\n";
        }
    } // while

    return 0;
}
