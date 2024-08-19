# CAPUF-USB-PD-HUSB238-Lib
Library to interface CAPUF Embedded USB-PD Board (HUSB238), which connects to MCU via I2C interface


# Note
- HUSB238 IC I2C Device address is 0x08(7-Bit address).
- Connect External 4.7K Resistance on your MCU board. They are not present on the USB-PD board.
- Remember to connect the ground of the USB-PD board to your MCU board's ground.
- Don't use long wires for an I2C connection (more than a few inches). 
