# Скрипт запуску тестів AirTermostat

## Опис

Скрипт `run_tests.sh` використовується для автоматизації процесу тестування системи AirTermostat. Він виконує послідовний запуск всіх тестів, компіляцію та завантаження прошивок на Arduino.

## Функції

### 1. Логування
- `log_message()` - логування інформаційних повідомлень
- `log_error()` - логування помилок

### 2. Перевірка вимог
- Перевірка наявності arduino-cli
- Перевірка версії arduino-cli
- Перевірка наявності Python 3

### 3. Очищення
- Видалення тимчасових файлів
- Очищення при виході

### 4. Налаштування
- Створення директорій для тестів
- Підготовка середовища

### 5. Компіляція та завантаження
- Компіляція тестових файлів
- Завантаження на Arduino
- Обробка помилок

### 6. Тести
- Апаратні тести
- Функціональні тести
- Інтеграційні тести

## Використання

### Запуск
```bash
./run_tests.sh
```

### Вимоги
- arduino-cli
- Python 3
- Доступ до Arduino через USB
- Встановлені бібліотеки

### Лог-файли
- test_results.log - результати тестів
- test_errors.log - помилки

## Структура

```
tests/
├── run_tests.sh      # Скрипт запуску
├── run_tests.md      # Документація
├── test_results.log  # Результати
└── test_errors.log   # Помилки
```

## Код

### Логування
```bash
log_message() {
    echo -e "${GREEN}[INFO]${NC} $1"
    echo "[INFO] $1" >> test_results.log
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
    echo "[ERROR] $1" >> test_errors.log
}
```

### Перевірка вимог
```bash
check_requirements() {
    log_message "Перевірка вимог..."
    
    if ! command -v arduino-cli &> /dev/null; then
        log_error "arduino-cli не встановлено"
        return 1
    fi
    
    version=$(arduino-cli version)
    log_message "arduino-cli версія: $version"
    
    if ! command -v python3 &> /dev/null; then
        log_error "Python 3 не встановлено"
        return 1
    fi
    
    return 0
}
```

### Компіляція та завантаження
```bash
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
```

## Виправлення помилок

### 1. Помилка компіляції
- Перевірте наявність всіх бібліотек
- Перевірте синтаксис коду
- Перевірте версію arduino-cli

### 2. Помилка завантаження
- Перевірте підключення Arduino
- Перевірте права доступу
- Перевірте порт USB

### 3. Помилка вимог
- Встановіть arduino-cli
- Встановіть Python 3
- Оновіть бібліотеки

## Безпека

1. Перевірте права доступу
2. Використовуйте безпечні порти
3. Захищайте від перевантаження 