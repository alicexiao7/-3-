#include <iostream>
#include "ATC.h"


int main() {
    ATC atc;
    int menuNumber=0;
    bool info = false;

    do{
        showMenu();
        menuNumber = getValidInt(" ");
        
        
        try{
            switch( menuNumber){
                case 1:{
                    std::string addr = getValidString("Введите адрес: ");
                    double fee = getValidDouble("Введите абонентскую плату (руб): ");
                    int subs = getValidInt("Введите количество абонентов: ");
                    
                    atc.setAddress(addr);
                    atc.setSubscriptionFee(fee);
                    atc.setSubscribers(subs);
                    info= true;
                    std::cout << "Данные сохранены!\n";
                    break;
                }
                case 2:{
                    if (!info) {
                        std::cout << "Сначала введите данные для АТС (пункт 1)!\n";
                        break;
                            }
                    std::cout << "Общая сумма: "
                    << atc.calculateTotalFee()
                    << " руб.\n";
                    break;
                }
                case 3:{
                    if (!info) {
                        std::cout << "Сначала введите данные для АТС (пункт 1)!\n";
                        break;
                            }
                    double newFee = getValidDouble("Введите новую абонентскую плату: ");
                    atc.setSubscriptionFee(newFee);
                    std::cout << "Абонентская плата обновлена!\n";
                    break;
                }
                case 4:{
                    if (!info) {
                        std::cout << "Сначала введите данные для АТС (пункт 1)!\n";
                        break;
                            }
                    std::cout << "Текущая абонентская плата: "
                    << atc.getSubscriptionFee() << " руб.\n";
                    break;
                }
                case 5:{
                    if (!info) {
                        std::cout << "Сначала введите данные для АТС (пункт 1)!\n";
                        break;
                            }
                    int newSubs = getValidInt("Введите новое число абонентов: ");
                    atc.setSubscribers(newSubs);
                    std::cout << "Число абонентов обновлено!\n";
                    break;
                    
                }
                case 6:{
                    if (!info) {
                        std::cout << "Сначала введите данные для АТС (пункт 1)!\n";
                        break;
                            }
                    std::cout << "Выход...\n";
                    break;
                    
                }
                default: {
                    std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        
    } while (menuNumber != 6);
    
    return 0;
}
