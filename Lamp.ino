// Опциональные дефайн-настройки (показаны по умолчанию)
//#define EB_FAST 30     // таймаут быстрого поворота, мс
#define EB_DEB 10      // дебаунс кнопки, мс
//#define EB_CLICK 400   // таймаут накликивания, мс
 int ledCold = 9;
 int ledWarm = 10;
 int duty = 0;
#include <EncButton.h>
//EncButton<EB_TICK, 2, 3, 4> enc;  // энкодер с кнопкой <A, B, KEY>
//EncButton<EB_TICK, 2, 3> enc;     // просто энкодер <A, B>
EncButton<EB_TICK, 7> enc;        // просто кнопка <KEY>

void setup() {
TCCR1A = 0b00000001;  // 8bit
TCCR1B = 0b00000001;  // x1 phase correct
  Serial.begin(9600);
  enc.setButtonLevel(HIGH);     // уровень кнопки: LOW - кнопка подключает GND (по умолч.), HIGH - кнопка подключает VCC
  //enc.setHoldTimeout(1000);     // установить время удержания кнопки, мс (до 8 000)
  //enc.setStepTimeout(500);      // установить период импульсов step, мс (до 4 000)

  //enc.holdEncButton(true);      // виртуально зажать кнопку энкодера (для срабатывания нажатых поворотов)
  //enc.setEncReverse(true);      // true - инвертировать направление энкодера (умолч. false)
  //enc.setEncType(EB_HALFSTEP);  // тип энкодера: EB_FULLSTEP (0) по умолч., EB_HALFSTEP (1) если энкодер делает один поворот за два щелчка
}

void loop() {
  enc.tick();                     // опрос происходит здесь
analogWrite (ledCold, duty);
analogWrite (ledWarm, duty);


 
  if (enc.press()) {
    Serial.println("press");
    if (duty > 0) {duty = 0;}  // если выключен, то включаем и наоборот
    else {duty = 2;}
  }
  if (enc.click()) Serial.println("click");
  if (enc.release()) Serial.println("release");

  if (enc.held()) Serial.println("held");     // однократно вернёт true при удержании
  //if (enc.hold()) Serial.println("hold");   // будет постоянно возвращать true после удержания
  if (enc.step()) {
    Serial.println("step");     // импульсное удержание
    duty +=30;
    if (duty > 128) duty = 1;
    Serial.println(duty);
    }


  if (enc.releaseStep()) Serial.println("release step");  // отпущена после импульсного удержания
   
  
  // проверка на количество кликов
  if (enc.hasClicks(1)) Serial.println("action 1 clicks");
  if (enc.hasClicks(2)) {
    Serial.println("action 2 clicks");
    duty = 100;
    }

  // вывести количество кликов
  if (enc.hasClicks()) {
    Serial.print("has clicks ");
    Serial.println(enc.clicks);
  }
}
