# Профилировщик состояний процесса  
Данное приложение позволяет отслеживать изменение состояний потоков профилируемого процесса во времени, а также их переключения между процессорами. Программа предназначена для использования разработчиками и тестировщиками ПО в операционных системах на базе Linux.  
Дополнительно предусмотрена поддержка работы в режиме реального времени в ОС "Эльбрус".  

## Инструкция по эксплуатации  
Запуск приложения производится из командной строки со следующими параметрами:  

| Описание | Синтаксис (полная запись) | Синтаксис (краткая запись) |
| ---------------------------------------------------- | ---------------------------- | ------------------------- |
| Номер процесса: | --pid X | -p X |
| Период снятия показаний в мкс: | --delta X | -d X |
| Имя выходного файла: | --file X | -f X |
| Количество потоков приложения: | --threads X | -t X |
| Период проверки количества потоков процесса в мкс: | --count X | -c X |
| Версия: | --version | -v |
| Помощь: | --help | -h |

Первые два параметра **являются обязательными** для запуска.

Для завершения работы приложения необходимо ввести комбинацию клавиш ^C.

В результате работы приложения будет получен бинарный файл, содержащий собранные данные.
