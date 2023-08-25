# Autopilot

## Введение


## Структура прошивки
  В папке Plane_Code:
  - В файле Plane_Code написан основной цикл программы
  - В файле Math написаны основные математические функции
  - В файле 433 написана функция для получения сигнала с приемника 
  - В файле Debug написаны функции для вывода отладочных данных
  - В файле Dist написаны функции для получения относительной высоты (до 5 метров)
  - В файле GPS будут написаны функции обработки координат и направления самолета в необходимую точку
  - В файле Gyro написаны функции получения текущего угла самолета
  - В файле Led написаны функции работы с адресной светодиодной лентой
  - В файле Servo_contr  написаны функции управления сервомоторами
  - В файле TX-Rx написаны Функции получения текущего режима полета (Автопилот или ручной)
  
  В папке Transmitter_code:
  - Файл Transmitter_code содержит код передатчика, нахадящегося на земле.

## Принцип управления самолетом  
  ![Working_scheme](/Readme_photos/Project_scheme.jpg)
  Для ручного управления и переключения режима полета используется аппаратура FlySky I6 с приемником FlySky I6A.
  Для изменения коэффициентов и параметров автопилота используется контроллер Arduino Nano и передатчик RF 315, работающий на частоте 433 МГц
  
  
  
## Принцип работы кода
	
  Для наглядности я сделал блок схему, которая поможет вам лучше понять логику работы кода
	
 ![Code scheme](/Readme_photos/Code%20scheme.jpg)
 
 *в [папке](/Readme_photos) есть файл с большим разрешением.
 
 Режим полета изменяется при помощи тумблера на аппаратуре управления.
 

## Сборка проекта
  - Купите указанные компоненты:
  - Откройте схему самолетной части и спаяйте компоненты в соответствии со схемой.
  - (Опционально) Откройте схему передатчика и спаяйте компоненты в соответствии со схемой.
  > Если вы не собираете передатчик, то на схеме самолетной части не припаивайте приемник 433 Mгц. Самолет, в режиме автопилота, **будет удерживать те параметры, которые указаны в прошивке**!!!


## Установка необходимых программ и прошивка платы

  - Для программирования робота вам понаxдобится [Arduino IDE](https://www.arduino.cc/en/software). Это программное обеспечение с открытым исходным кодом позволяет легко писать код и загружать его в плату. Откройте exe-файл и следуйте инструкциям программы установки.

  - Скачайте [папку с  библиотеками](/libraries)  и добавьте их в папку C:\Users\Админ\Documents\Arduino\libraries.
	
  - Скачайте и откройте файлы прошивки : [прошивка самолетной части](/Plane_Code), [прошивка передающей части](/Transmitter_code).
  
  
  - Подключите плату к компьютеру. 
  - Нажав на прямоугольник сверху, надите плату Arduino Nano  и порт, в который она подключена(для меня это порт 11).
  ![Open code files](/Readme_photos/Файл%20прошивки.jpg)
  ![Choice of board and port](/Readme_photos/Выбор%20платы.jpg)
  - Нажмите кнопку "Компилировать".
  ![Upload](/Readme_photos/Загрузить.jpg)
  
  В случае возникновеня каких либо проблем советую прочитать [вот эту статью](https://alexgyver.ru/arduino-first/).
