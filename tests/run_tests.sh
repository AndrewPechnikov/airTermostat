#!/bin/bash

# Кольори для виводу
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Перевірка залежностей
check_requirements() {
    command -v arduino-cli >/dev/null 2>&1 || { echo "arduino-cli not found"; exit 1; }
}

# Очищення
cleanup() {
    echo "Cleaning up..."
    rm -f *.hex
}

# Функція для запуску тесту
run_test() {
    echo "Running $1..."
    arduino-cli compile --fqbn arduino:avr:nano "$1"
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Compilation successful${NC}"
        arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano "$1"
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Upload successful${NC}"
            echo "Starting serial monitor..."
            arduino-cli monitor -p /dev/ttyUSB0
        else
            echo -e "${RED}Upload failed${NC}"
            return 1
        fi
    else
        echo -e "${RED}Compilation failed${NC}"
        return 1
    fi
}

# Встановлення trap для cleanup
trap cleanup EXIT

# Перевірка залежностей
check_requirements

# Запуск всіх тестів
echo "=== Starting Test Suite ==="

echo -e "\n=== Hardware Tests ==="
run_test "tests/hardware/RadioTest/RadioTest.ino"
run_test "tests/hardware/SensorTest/SensorTest.ino"

echo -e "\n=== Functional Tests ==="
run_test "tests/functional/PowerTest/PowerTest.ino"

echo -e "\n=== Integration Tests ==="
run_test "tests/integration/SystemTest/SystemTest.ino"

echo -e "\n=== Test Suite Completed ===" 