# Інструкція з використання тестів Air Thermostat

## Структура тестів

## Опис тестів

### Тести апаратної частини (hardware)
1. **RadioTest**:
   - Перевіряє ініціалізацію nRF24L01
   - Тестує налаштування каналу та потужності
   - Перевіряє якість зв'язку

2. **SensorTest**:
   - Перевіряє роботу DHT22
   - Тестує стабільність показань
   - Перевіряє діапазон температур

### Функціональні тести (functional)
1. **PowerTest**:
   - Тестує режими енергозбереження
   - Перевіряє цикли сну/пробудження
   - Вимірює споживання енергії

### Інтеграційні тести (integration)
1. **SystemTest**:
   - Перевіряє взаємодію всіх компонентів
   - Тестує повний цикл роботи
   - Перевіряє обробку помилок

## Типові проблеми та їх вирішення

### 1. Помилка компіляції

## Підготовка до тестування

1. **Встановлення необхідного ПЗ**:
   ```bash
   # Встановлення Arduino CLI
   curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

   # Встановлення бібліотек
   arduino-cli lib install "RF24"
   arduino-cli lib install "DHT sensor library"
   arduino-cli lib install "LiquidCrystal I2C"
   ```

2. **Підготовка обладнання**:
   - Підключіть Arduino Nano до комп'ютера
   - Переконайтесь, що всі компоненти підключені згідно WIRING.md
   - Перевірте напругу живлення

## Запуск тестів

### Запуск всіх тестів
```bash
# Зробіть скрипт виконуваним
chmod +x tests/run_tests.sh

# Запустіть всі тести
./tests/run_tests.sh
```

### Запуск окремих тестів
```bash
# Тест радіомодуля
arduino-cli compile --fqbn arduino:avr:nano tests/hardware/RadioTest
arduino-cli upload -p /dev/ttyUSB0 tests/hardware/RadioTest

# Тест датчика
arduino-cli compile --fqbn arduino:avr:nano tests/hardware/SensorTest
arduino-cli upload -p /dev/ttyUSB0 tests/hardware/SensorTest

# і т.д.
```

## Інтерпретація результатів

### Кольорові позначення
- 🟢 Зелений: тест пройдено успішно
- 🔴 Червоний: тест провалено
- 🟡 Жовтий: попередження

### Приклади повідомлень
```
Test 1 - Radio Init: PASS
Test 2 - Radio Settings: FAIL - Cannot set channel
```

## Додавання нових тестів

1. Створіть нову папку в відповідній категорії:
   ```bash
   mkdir -p tests/hardware/NewTest
   ```

2. Створіть файл тесту:
   ```cpp
   void setup() {
       Serial.begin(9600);
       Serial.println("Starting New Test...");
       // Код тесту
   }
   ```

3. Додайте тест до run_tests.sh:
   ```bash
   run_test "tests/hardware/NewTest/NewTest.ino"
   ```

## Автоматизація тестування

### Періодичне тестування
```bash
# Додайте в crontab
0 0 * * * /path/to/tests/run_tests.sh > /path/to/logs/test_$(date +\%Y\%m\%d).log
```

### Збереження результатів
```bash
# Запуск з логуванням
./tests/run_tests.sh | tee test_results.log
```

## Безпека

1. Завжди відключайте живлення перед зміною підключень
2. Перевіряйте напругу живлення перед тестами
3. Не перевищуйте максимальні значення струму

## Контакти підтримки

При виникненні проблем:
1. Перевірте розділ "Типові проблеми"
2. Перегляньте лог-файли
3. Зверніться до розробника: [контакти]

## Оновлення тестів

1. Регулярно перевіряйте наявність оновлень
2. Синхронізуйте з репозиторієм
3. Оновлюйте бібліотеки
