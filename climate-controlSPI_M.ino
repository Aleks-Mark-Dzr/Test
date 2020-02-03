#include <HID.h>


// библиотека для работы с датчиком DHT11
#include <TroykaDHT.h>
int minute = 1;

// номер цифрового пина реле 1
#define RELAY_1_PIN  A4

// создаём объект класса DHT11 и передаём номер пина к которому подключён датчик
DHT dht(4, DHT11);

// переменная для хранения состояние системы
// а именно какую информацию выводить на дисплей
// температуру или влажность
// bool state = true;

// переменная для хранения показателя температуры окружающей среды
float temperature = 0;
// переменная для хранения показателя влажности окружающей среды
float humidity = 0;

long currentMillis = 0;
void setup()
{
  // мы хотим передавать информацию на компьютер через USB, а
  // точнее через последовательный (англ. serial) порт.
  // Для этого необходимо начать (англ. begin) передачу, указав
  // скорость. 9600 бит в секунду — традиционная скорость.
  // Функция «begin» не является глобальной, она принадлежит
  // объекту с именем «Serial». Объекты — это «продвинутые»
  // переменные, которые обладают собственными функциями,
  // к которым обращаются через символ точки.
  Serial.begin(9600);
  // передаём заголовок нашей таблицы в текстовом виде, иначе
  // говоря печатаем строку (англ. print line). Символы «\t» —
  // это специальная последовательность, которая заменяется на
  // знак табуляции (англ. tab): 8-кратный выровненный пробел
  Serial.println("Minute\tTemperature\tHumidity");
  // начало работы с датчиком DHT11
  dht.begin();
  // назначаем пин в режиме выхода
  pinMode(RELAY_1_PIN, OUTPUT);
  currentMillis = millis();
}

void loop()
{

  // если прошёл заданный интервал времени
  // считывам показания датчика
  if (millis() - currentMillis > 10000) {
    // state = !state;
    currentMillis = millis();
    dht.read();
  }

  switch (dht.getState()) {
    // всё OK
    case DHT_OK:
      // считываем показания температуры и влажности с датчика
      temperature = dht.getTemperatureC();
      humidity = dht.getHumidity();
      // печатаем текущую минуту и температуру, разделяя их табом.
      // println переводит курсор на новую строку, а print — нет
      Serial.print(minute);
      Serial.print("\t");
      Serial.print(temperature);
      Serial.print("\t");
      Serial.println(humidity);
  }
  // если температура превысила 28 градусов
  //if (temperature > 28) {
  // включаем реле 1
  //digitalWrite(RELAY_1_PIN, HIGH);
  //} else {
  // иначе выключаем реле
  //digitalWrite(RELAY_1_PIN, LOW);
  //}
  // если влажность стала больше 80 %
  if (humidity > 80) {
    // включаем реле 1
    digitalWrite(RELAY_1_PIN, HIGH);
  } else {
    // иначе выключаем реле 1
    digitalWrite(RELAY_1_PIN, LOW);
  }
  // ждём 10 секунд
  delay(10000);
}
