import serial

#---------------------------------------------------------

def serial_init(speed):
    dev = serial.Serial(
        # Здесь указывается устройство, с которым будет производится работа
        # /dev/ttyUSBx - для Linux
        # /dev/tty.SLAB_USBtoUART - для MacOS
        port = '/dev/ttyUSB0', 
        # Скорость передачи
        baudrate = speed,
        # Использование бита четности
        parity = serial.PARITY_ODD,
        # Длина стоп-бита
        stopbits = serial.STOPBITS_ONE,
        # Длина пакета
        bytesize = serial.EIGHTBITS,
        # Максимальное время ожидания устройства
        timeout = 3
    )
    return dev

#---------------------------------------------------------

def serial_recv(dev):
    # Для простоты макс. кол-во символов для чтения - 255. Время ожидания - 0.1
    # decode необходим для конвертирования набора полученных байтов в строку
    string = dev.read(255).decode()
    return string

#---------------------------------------------------------

def serial_send(dev, string):
    # encode конвертирует строку в кодировке utf-8 в набор байтов 
    dev.write(string.encode('utf-8'))

#---------------------------------------------------------

dev = serial_init(9600)
serial_send(dev, "DEAD")
ans = serial_recv(dev)
print(ans)