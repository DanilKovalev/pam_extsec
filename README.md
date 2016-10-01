#pam_stepic

Идея состоит в написании PAM модуля для linux.
Модуль буcдет устанавливать ограничения на сессию в зависимости через какую консоль будет происходить вход.
Для установки ограничений будут использоваться следующие 'технологии':

1. seccomp (http://man7.org/linux/man-pages/man2/seccomp.2.html)
  * Для запрета некоторых системных вызовов.
2. libcap (capabilities) http://man7.org/linux/man-pages/man3/libcap.3.html
  * Для запрета возможностей
3. setrlimit(http://linux.die.net/man/2/setrlimit)
  * Для установки лимитов на использование памяти, кол-ва ядер ...
  
## Build
```
cmake
make
```
Будет созданна папка output.
  * output/lib - содержит сам модуль
  * output/lib - содержит тесты
  
Чтобы запустить тесты выполните `ctest --verbose`

Для сборки требуется cmake, libcppunit, libpam, libcap, libjsoncpp, libboost_program_options

Для установки на debian/Ubuntu выполните:
```
apt-get install cmake libcppunit-dev libpam0g-dev libcap-dev libjsoncpp-dev libboost-program-options-dev
```

## Config
```
{
  "<consol>": {
    "capabilities": [
        "список запрещеных capabilities"
    ],
    "syscalls": [
        "список запрещеных системных вызовов"
    ]
  },
}
```
example:
```
{
  "tty1": {
    "capabilities": [
      "cap_chown",
      "cap_kill"
    ],
    "syscalls": [
      "nanosleep",
      "mmap"
    ]
  },
  "tty2": {
    "capabilities": [
      "cap_chown",
      "cap_kill"
    ],
    "syscalls": [
      "nanosleep"
    ]
  }
}
```