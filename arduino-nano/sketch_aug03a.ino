
// PIN # 3,5,6,9,11  PULSE WIDTH MODULATION ( PWM ) PINS.
int fan_1 = 3;
int fan_2 = 5;
int fan_3 = 6;
int fan_4 = 9;
int fan_speed_1, fan_speed_2, fan_speed_3, fan_speed_4;
String str_data = "";
boolean recieved_flag, print_flag;
int min_val = 80;
int max_val = 255;
int interval = 10000;
unsigned long previous_millis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(fan_1, OUTPUT);
  pinMode(fan_2, OUTPUT);
  pinMode(fan_3, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {

  unsigned long current_millis = millis();

  if (Serial.available() > 0) 
  {
    str_data = ""; // очистить строку
                             
    while (Serial.available() > 0) {    // пока идут данные
      str_data += (char)Serial.read();  // забиваем строку принятыми данными
      delay(2);                         // обязательно задержка, иначе вылетим из цикла раньше времени
    }
    recieved_flag = true;               // поднять флаг что получили данные
  }

  if (recieved_flag){
    int int_val = str_data.substring(2).toInt();  // перевести в int всю строку кроме первых двух символов!
    String header = str_data.substring(0, 2);    // создать мини строку, содержащую первые два символа

    if (str_data.startsWith("f1")) {
        fan_speed_1 = int_val;
        print_flag = true;
    }

    if (str_data.startsWith("f2")) {
        fan_speed_2 = int_val;
        print_flag = true;
    }

    if (str_data.startsWith("f3")) {
        fan_speed_3 = int_val;
        print_flag = true;
    }

    recieved_flag = false;
  }

  if (print_flag){
       Serial.print("fan 1 (cpu): ");
       Serial.print(fan_speed_1);
       Serial.println();
       Serial.print("fan 2: ");
       Serial.print(fan_speed_2);
       Serial.println();
       Serial.print("fan 3: ");
       Serial.print(fan_speed_3);
       Serial.println();
       print_flag = false;
    }

  if((fan_speed_1 >= min_val) && (fan_speed_1 <= max_val)){
    analogWrite(fan_1, fan_speed_1);
  }else{
    fan_speed_1 = 155;
  }

  if((fan_speed_2 >= min_val) && (fan_speed_2 <= max_val)){
    analogWrite(fan_2, fan_speed_2);
  }else{
    fan_speed_2 = 155;
  }

  if((fan_speed_3 >= min_val) && (fan_speed_3 <= max_val)){
    analogWrite(fan_3, fan_speed_3);
  }else{
    fan_speed_3 = 155;
  }

  if (current_millis - previous_millis >= interval){ 
    previous_millis = current_millis;
    print_flag = true;
  }
}
