#include "PowerManager.h"
#include <avr/wdt.h>

void PowerManager::setup() {
    watchdogSetup();
}

void PowerManager::enterSleepMode() {
    // Глибокий сон
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    power_all_disable();
    sleep_mode();
}

void PowerManager::enterLightSleep() {
    // Легкий сон, дозволяє працювати перериванням
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_mode();
    sleep_disable();
}

void PowerManager::wakeUp() {
    sleep_disable();
    power_all_enable();
}

void PowerManager::watchdogSetup() {
    cli();
    wdt_reset();
    MCUSR &= ~(1<<WDRF);
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    WDTCSR = 1<<WDP1 | 1<<WDP2; // 1 секунда
    WDTCSR |= _BV(WDIE);
    sei();
} 