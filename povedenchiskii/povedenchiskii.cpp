#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class VendingMachine;

// Абстрактное состояние
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine* vm) = 0;
    virtual void ejectCoin(VendingMachine* vm) = 0;
    virtual void dispense(VendingMachine* vm) = 0;
};

// Состояние: Напитки закончились
class SoldOutState : public State {
public:
    void insertCoin(VendingMachine* vm) override { cout << "Автомат пуст. Монета возвращена." << endl; }
    void ejectCoin(VendingMachine* vm) override { cout << "Вы не вставляли монету." << endl; }
    void dispense(VendingMachine* vm) override { cout << "Напитки кончились!" <<endl; }
};

// Состояние: Нет монеты
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override;
    void ejectCoin(VendingMachine* vm) override { cout << "Монета не вставлена." << endl; }
    void dispense(VendingMachine* vm) override { cout << "Вставьте монету сначала!" << endl; }
};

// Состояние: Монета вставлена
class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override { cout << "Монета уже есть." << endl; }
    void ejectCoin(VendingMachine* vm) override;
    void dispense(VendingMachine* vm) override;
};

// Состояние: Победитель (бонус)
class WinnerState : public State {
public:
    void insertCoin(VendingMachine* vm) override { cout << "Подождите, выдаем бонус!" << endl; }
    void ejectCoin(VendingMachine* vm) override { cout << "Нельзя вернуть монету во время выдачи." << endl; }
    void dispense(VendingMachine* vm) override;
};

class VendingMachine {
private:
    State* currentState;
    int inventory;
public:
    VendingMachine(int count) : inventory(count) {
        if (inventory > 0) currentState = new NoCoinState();
        else currentState = new SoldOutState();
        srand(time(0));
    }
    ~VendingMachine() { delete currentState; }

    void setState(State* s) { delete currentState; currentState = s; }
    int getInventory() const { return inventory; }
    void releaseDrink() { if (inventory > 0) inventory--; }

    void insertCoin() { currentState->insertCoin(this); }
    void ejectCoin() { currentState->ejectCoin(this); }
    void dispense() { currentState->dispense(this); }
};

// Реализация методов состояний
void NoCoinState::insertCoin(VendingMachine* vm) {
    cout << "Монета вставлена." << endl;
    vm->setState(new HasCoinState());
}

void HasCoinState::ejectCoin(VendingMachine* vm) {
    cout << "Монета возвращена." << endl;
    vm->setState(new NoCoinState());
}

void HasCoinState::dispense(VendingMachine* vm) {
    cout << "Проверка на выигрыш..." << endl;
    int winner = rand() % 10; // 10% шанс
    if ((winner == 0) && (vm->getInventory() > 1)) {
        vm->setState(new WinnerState());
        vm->dispense();
    }
    else {
        cout << "Напиток выдан!" << endl;
        vm->releaseDrink();
        if (vm->getInventory() > 0) vm->setState(new NoCoinState());
        else vm->setState(new SoldOutState());
    }
}

void WinnerState::dispense(VendingMachine* vm) {
    cout << "ПОЗДРАВЛЯЕМ! Вы получили второй напиток бесплатно!" << endl;
    vm->releaseDrink();
    vm->releaseDrink();
    if (vm->getInventory() > 0) vm->setState(new NoCoinState());
    else vm->setState(new SoldOutState());
}

int main() {
    setlocale(LC_ALL, "ru");
    VendingMachine vm(5);
    vm.insertCoin();
    vm.ejectCoin();
    vm.insertCoin();
    vm.dispense();
    return 0;
}