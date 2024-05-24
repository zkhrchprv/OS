# MySyslog Daemon

## Описание
MySyslog Daemon - это простой демон, который записывает сообщения в системный журнал. Этот демон может быть полезен для мониторинга системы и ведения логов различных событий.

## Требования
- GCC (для компиляции)
- systemd (для управления сервисом)

## Установка

1. Клонируйте репозиторий или скопируйте файлы в рабочую директорию.

2. Перейдите в директорию с исходным кодом:

    ```sh
    cd /path/to/mysyslog-daemon
    ```

3. Скомпилируйте демон:

    ```sh
    make
    ```

4. Скопируйте исполняемый файл в системную директорию `/usr/sbin`:

    ```sh
    sudo cp mysyslog-daemon /usr/sbin/
    ```

5. Скопируйте файл службы `mysyslog-daemon.service` в директорию `/etc/systemd/system`:

    ```sh
    sudo cp mysyslog-daemon.service /etc/systemd/system/
    ```

6. Перезапустите systemd для обнаружения нового сервиса:

    ```sh
    sudo systemctl daemon-reload
    ```

7. Включите и запустите сервис:

    ```sh
    sudo systemctl enable mysyslog-daemon
    sudo systemctl start mysyslog-daemon
    ```

## Использование
Демон автоматически будет записывать сообщения в системный журнал. Чтобы проверить его работу, вы можете использовать команду `journalctl`:

```sh
sudo journalctl -u mysyslog-daemon -f
