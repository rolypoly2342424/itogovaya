#include <iostream>
#include <string>
using namespace std;
// Абстрактные продукты (семейство UI-элементов)
class Button {
public:
    virtual string render() = 0;
    virtual void interact() = 0;
    virtual ~Button() {}
};

class ScrollBar {
public:
    virtual string render() = 0;
    virtual void interact() = 0;
    virtual ~ScrollBar() {}
};
class CheckBox
{
public:
    virtual string render() = 0;
    virtual void interact() = 0;
    virtual ~CheckBox() {}
};

class LinuxButton : public Button
{
public:
    string render() override { return "Линукс кнопка"; }
    void interact() override { cout << "Клик по кнопке Линукс" << endl; }
};

class LinuxScrollBar : public ScrollBar
{
public:
    string render() override { return "Линукс Скроллбар"; }
    void interact() override { cout << "Прокрутка Линукс" << endl; }
};
class LinuxCheckBox : public CheckBox
{
    string render() override { return "Линукс Чекбокс"; }
    void interact() override { cout << "Галочка Линукс" << endl; }
};

// Конкретные продукты для Windows
class WinButton : public Button {
public:
    string render() override { return "Windows Кнопка"; }
    void interact() override { cout << "Клик по кнопке Win" << endl; }
};

class WinScrollBar : public ScrollBar {
public:
    string render() override { return "Windows Скроллбар"; }
    void interact() override { cout << "Прокрутка Win" << endl; }
};

class WinCheckBox : public CheckBox
{
public:
    string render() override { return "Windows Чекбокс"; }
    void interact() override { cout << "Галочка Win" << endl; }
};

class UIFactory
{
public:
    virtual Button* createButton() = 0;
    virtual ScrollBar* createScrollBar() = 0;
    virtual CheckBox* createCheckBox() = 0;
    virtual ~UIFactory() {}
};

// Конкретные фабрики
class WinFactory : public UIFactory {
public:
    Button* createButton() override { return new WinButton(); }
    ScrollBar* createScrollBar() override { return new WinScrollBar(); }
    CheckBox* createCheckBox() override { return new WinCheckBox(); }
};

class LinuxFactory : public UIFactory {
public:
    Button* createButton() override { return new LinuxButton(); }
    ScrollBar* createScrollBar() override { return new LinuxScrollBar(); }
    CheckBox* createCheckBox() override { return new LinuxCheckBox(); }
};


int main() {
    setlocale(LC_ALL, "ru");
    string config = "linux"; // Логика выбора фабрики по строке
    UIFactory* factory = nullptr;

    if (config == "win") {
        factory = new WinFactory();
    }
    else if (config == "linux") {
        factory = new LinuxFactory();
    }

    if (factory) {
        Button* btn = factory->createButton();
        ScrollBar* sb = factory->createScrollBar();
        CheckBox* cb = factory->createCheckBox();

        cout << btn->render() << ", " << sb->render() << " и " << cb->render() << endl;

        btn->interact();
        cb->interact();

        delete btn; delete sb; delete cb; delete factory;
    }
    else {
        cout << "Неизвестная платформа!" << endl;
    }
    return 0;
}