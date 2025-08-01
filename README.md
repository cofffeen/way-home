# way-home
## Задача

Спроектировать и реализовать консольное приложение для нахождения маршрутов из Санкт-Петербурга до Вашего родного города, используя Yandex Api и внешние библиотеки.


## Требования

Консольное приложение должно искать список возможных маршрутов из Санкт-Петербурга до вашего родного города (в случае если вы из Санкт-Петербурга, то до Пскова) и обратно с не более чем 1 пересадкой любыми видами транспорта (например самолет + поезд) на определенную дату (передается аргументом командной строки). Кэшировать найденые промежуточные результаты в памяти и на файловой системе для уменьшения количества запросов на внешний сервис.

## Источник данных

В качестве источника информации должно быть использовано [API Яндекса Расписаний](https://yandex.ru/dev/rasp/doc/ru/). 
Для разработчиков оно ограничено 500 запросами в день. Стоит внимательно изучить API, подумать какая информация является неизменной, что можно сохранить локально и переиспользовать.

## Реализация 

Работа с API предполагает выполнение [HTTP-запросов](https://en.wikipedia.org/wiki/HTTP). Для этого необходимо воспользоваться библиотекой [С++ Requests](https://github.com/libcpr/cpr). В качестве библиотеки для работы с json-ответом - [nlohmann/json](https://github.com/nlohmann/json).


В данной работе, при взаимодействии с внешним сервисами, может возникать достаточно большое количество коллизий и краевых случаев. Внимательно, подумайте об этом! Ваша программа должна корректно работать и "не падать".


## NB

Работа с внешними библиотеками является основной частью данной работы. Рекомендуется внимательно ознакомиться с документацией, тестами и исходным кодом вышеуказанных библиотек.
