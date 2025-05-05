int STEP = 5;                  // Светодиод подсоединен к цифровому выводу 13
int DIR = 4;

void setup()
{
  pinMode(STEP, OUTPUT);       // устанавливаем режим работы вывода, как "выход"
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, HIGH);
}

void loop()
{
  digitalWrite(STEP, HIGH);    // включаем светодиод
  delay(1);                   // ждем 1 секунду
  digitalWrite(STEP, LOW);     // выключаем светодиод
  delay(1);                   // ждем 1 секунду
}