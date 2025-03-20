# Бездротовий Термостат (Air Thermostat)

Проєкт розумного термостату з бездротовим керуванням на базі Arduino та nRF24L01.

## Функціонал

### Передавач (Transmitter)
- Вимірювання температури за допомогою DHT22
- Відображення поточної та цільової температури на LCD дисплеї
- Налаштування цільової температури через кнопки
- Підтримка денного/нічного режиму з різними температурами
- Енергозберігаючий режим для роботи від батарей
- Збереження налаштувань в EEPROM
- Сповіщення про критичні події (низький заряд, помилки датчика)

### Приймач (Receiver)
- Керування реле для вмикання/вимикання опалення
- Буферизація температурних даних
- Аналіз температурного тренду
- Захист від частих перемикань реле
- Індикація стану роботи
- Система сповіщень про аварійні ситуації

## Структура проєкту

### Передавач 