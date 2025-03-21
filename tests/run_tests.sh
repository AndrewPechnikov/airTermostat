#!/bin/bash

# Кольори для виводу
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Функції логування
log_message() {
    echo -e "${GREEN}[INFO]${NC} $1"
    echo "[INFO] $1" >> test_results.log
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
    echo "[ERROR] $1" >> test_errors.log
}

# Перевірка вимог
check_requirements() {
    log_message "Перевірка вимог..."
    
    # Перевірка arduino-cli
    if ! command -v arduino-cli &> /dev/null; then
        log_error "arduino-cli не встановлено"
        return 1
    fi
    
    # Перевірка версії arduino-cli
    version=$(arduino-cli version)
    log_message "arduino-cli версія: $version"
    
    # Перевірка Python
    if ! command -v python3 &> /dev/null; then
        log_error "Python 3 не встановлено"
        return 1
    fi
    
    return 0
}

# Очищення тимчасових файлів
cleanup() {
    log_message "Очищення тимчасових файлів..."
    rm -f *.hex *.elf *.bin
}

# Створення директорій
setup() {
    log_message "Створення директорій..."
    mkdir -p hardware functional integration
}

# Компіляція та завантаження тесту
compile_and_upload() {
    local test_file=$1
    local test_name=$2
    
    log_message "Компіляція $test_name..."
    if ! arduino-cli compile --fqbn arduino:avr:nano "$test_file"; then
        log_error "Помилка компіляції $test_name"
        return 1
    fi
    
    log_message "Завантаження $test_name..."
    if ! arduino-cli upload -p /dev/ttyUSB0 "$test_file"; then
        log_error "Помилка завантаження $test_name"
        return 1
    fi
    
    return 0
}

# Апаратні тести
run_hardware_tests() {
    log_message "Запуск апаратних тестів..."
    
    # Тест радіомодуля
    compile_and_upload "hardware/RadioTest/RadioTest.ino" "RadioTest"
    
    # Тест датчика
    compile_and_upload "hardware/SensorTest/SensorTest.ino" "SensorTest"
    
    # Тест живлення
    compile_and_upload "hardware/PowerTest/PowerTest.ino" "PowerTest"
}

# Функціональні тести
run_functional_tests() {
    log_message "Запуск функціональних тестів..."
    
    # Тест дисплея
    compile_and_upload "functional/DisplayTest/DisplayTest.ino" "DisplayTest"
    
    # Тест часу
    compile_and_upload "functional/TimeTest/TimeTest.ino" "TimeTest"
}

# Інтеграційні тести
run_integration_tests() {
    log_message "Запуск інтеграційних тестів..."
    
    # Тест системи
    compile_and_upload "integration/SystemTest/SystemTest.ino" "SystemTest"
}

# Головна функція
main() {
    # Створення лог-файлів
    > test_results.log
    > test_errors.log
    
    # Перевірка вимог
    if ! check_requirements; then
        log_error "Не виконано вимоги"
        exit 1
    fi
    
    # Очищення
    cleanup
    
    # Налаштування
    setup
    
    # Запуск тестів
    run_hardware_tests
    run_functional_tests
    run_integration_tests
    
    # Аналіз результатів
    if [ -s test_errors.log ]; then
        log_error "Тести завершились з помилками"
        exit 1
    else
        log_message "Всі тести успішно завершено"
        exit 0
    fi
}

# Запуск головної функції
main

# Очищення при виході
trap cleanup EXIT 