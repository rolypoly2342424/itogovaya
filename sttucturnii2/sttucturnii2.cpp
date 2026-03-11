#include <iostream>
#include <string>
using namespace std;
class USBPrinter {
public:
    virtual string printUSB(const string& data, int quality) = 0;
    virtual ~USBPrinter() {}
};

class USBScanner {
public:
    virtual string scanUSB(int quality) = 0;
    virtual ~USBScanner() {}
};

class OldLPTPrinter {
public:
    string printLPT(const string& data) {
        return "LPT Печать: " + data;
    }
};

class OldLPTScanner {
public:
    string scanLPT() {
        return "Данные со старого сканера";
    }
};

class LPTToUSBScannerAdapter : public USBScanner {
private:
    OldLPTScanner* oldScanner;
public:
    LPTToUSBScannerAdapter(OldLPTScanner* s) : oldScanner(s) {}
    string scanUSB(int quality) override {
        return oldScanner->scanLPT() + " [Качество: " + to_string(quality) + " DPI]";
    }
};

class PrinterClassAdapter : public USBPrinter, private OldLPTPrinter {
public:
    string printUSB(const string& data, int quality) override {
        string modifiedData = data + " (Q:" + to_string(quality) + ")";
        return printLPT(modifiedData);
    }
};
int main() {
    setlocale(LC_ALL, "ru");
    USBPrinter* printer = new PrinterClassAdapter();
    cout << printer->printUSB("Отчет", 300) << endl;

    OldLPTScanner oldScanner;
    USBScanner* scanner = new LPTToUSBScannerAdapter(&oldScanner);
    cout << scanner->scanUSB(600) << endl;

    delete printer;
    delete scanner;
    return 0;
}