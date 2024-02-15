import sys
import smbus

# By default the address of LM75A is set to 0x48
# aka A0, A1, and A2 are set to GND (0v).
address = 0x48

# Check if another address has been specified
if len(sys.argv) > 1:
    address = int(sys.argv[1], 16)

# Read I2C data and calculate temperature
bus = smbus.SMBus(1)
raw = bus.read_word_data(address, 0) & 0xFFFF
raw = ((raw << 8) & 0xFF00) + (raw >> 8)

# Convert to signed value
if raw & 0x8000:
    raw -= 1 << 16

temperature = raw / 32.0

# Print temperature
print('Temperature: {0:0.2f} °C'.format(temperature))
