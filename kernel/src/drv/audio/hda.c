//
// Created by ndraey on 21.01.24.
//

#include "drv/pci.h"
#include "drv/audio/hda.h"
#include "io/ports.h"
#include "io/tty.h"

uint8_t hda_bus = 0,
        hda_slot = 0,
        hda_func = 0;

uint16_t hda_vendor = 0,
         hda_device = 0;

uint32_t hda_addr = 0;

void hda_init() {
    pci_find_device_by_class_and_subclass(4, 3, &hda_vendor, &hda_device, &hda_bus, &hda_slot, &hda_func);

    if(hda_vendor && hda_device) {
        qemu_ok("Found Intel HDA! (%x:%x)", hda_vendor, hda_device);
    } else {
        return;
    }

    hda_addr = pci_read32(hda_bus, hda_slot, hda_func, 0x10) & ~0x10;

    qemu_ok("HDA address: %x", hda_addr);
    tty_printf("HDA address: %x", hda_addr);
}