# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Целевые файлы
TARGET = mysyslog-daemon
SRC = src/mysyslog-daemon.c
OBJ = $(SRC:.c=.o)

# Сборка целевого файла
all: $(TARGET)

$(TARGET): $(OBJ)
        $(CC) $(CFLAGS) -o $@ $^

# Очистка
clean:
        rm -f $(TARGET) $(OBJ)

# Установка демона
install:
        cp $(TARGET) /usr/sbin/$(TARGET)

# Удаление демона
uninstall:
        rm -f /usr/sbin/$(TARGET)

.PHONY: all clean install uninstall
