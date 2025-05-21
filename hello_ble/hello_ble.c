#include <furi.h>
#include <furi_hal.h>
#include <ble/ble.h>
#include <ble/gatt.h>
#include <stdio.h>

int32_t hello_ble_main(void* p) {
    UNUSED(p);

    ble_init();

    GattService* service = gatt_service_create(0x180A); // UUID service arbitraire
    GattCharacteristic* charac = gatt_char_create(0x2A58, GattCharacteristicProperties::Notify);
    gatt_service_add_characteristic(service, charac);
    gatt_server_add_service(service);

    gatt_server_start();

    int counter = 1;
    char buffer[64];

    while(1) {
        snprintf(buffer, sizeof(buffer), "Hello from Flipper #%d", counter++);
        gatt_server_notify(charac, (uint8_t*)buffer, strlen(buffer));
        furi_delay_ms(3000); // toutes les 3 secondes
    }

    return 0;
}
