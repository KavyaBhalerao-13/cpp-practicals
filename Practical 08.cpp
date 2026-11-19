#include <iostream>
#include <string>

class AppConfig {
private:
    std::string appName;
    std::string theme;

    // 1. Private constructor prevents direct instantiation from outside
    AppConfig() : appName("StudentPortal"), theme("Light") {
        std::cout << "[AppConfig] Single instance created.\n";
    }

public:
    // 2. Delete copy constructor and copy assignment to prevent cloning
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    // 3. Static method providing global access to the single instance
    static AppConfig& getInstance() {
        static AppConfig instance; // Created once, destroyed automatically at program exit
        return instance;
    }

    void setTheme(const std::string& newTheme) {
        theme = newTheme;
    }

    void displaySettings() const {
        std::cout << "  App Name : " << appName << "\n";
        std::cout << "  Theme    : " << theme << "\n";
    }
};

int main() {
    std::cout << "=== First Call to getInstance() ===\n";
    AppConfig& config1 = AppConfig::getInstance();
    config1.displaySettings();

    std::cout << "\nUpdating theme to 'Dark' via config1...\n";
    config1.setTheme("Dark");

    std::cout << "\n=== Second Call to getInstance() ===\n";
    AppConfig& config2 = AppConfig::getInstance();
    config2.displaySettings();

    std::cout << "\n=== Verifying Single Instance ===\n";
    std::cout << "Address of config1: " << &config1 << "\n";
    std::cout << "Address of config2: " << &config2 << "\n";

    if (&config1 == &config2) {
        std::cout << "Confirmed: Both references point to the EXACT same instance.\n";
    }

    return 0;
}