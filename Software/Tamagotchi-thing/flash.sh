#!/bin/bash

FIRMWARE="build/Debug/TamagotchiThing.elf"
INTERFACE_CFG="interface/stlink.cfg"
TARGET_CFG="target/stm32l0.cfg"
ADAPTER_SPEED=4000  # in kHz

if [ ! -f "$FIRMWARE" ]; then
  echo "Firmware not found: $FIRMWARE"
  exit 1
fi

openocd -f $INTERFACE_CFG -f $TARGET_CFG -c "adapter speed $ADAPTER_SPEED" -c "program $FIRMWARE verify reset exit"
