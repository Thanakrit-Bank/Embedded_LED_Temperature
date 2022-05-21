void button(){
  if (buttonState11 == LOW && state1 == 0){
    start_time1 = millis();
    state1 = 1 ;
    Serial.println("start1 : " + String(start_time1));
  }
  else if(buttonState11 == HIGH && state1 == 1){
    stop_time1 = millis();
    state1 = 0 ;
    Serial.println("Stop1 : "+ String(stop_time1));
  }

  if (buttonState12 == LOW && state2 == 0){
    start_time2 = millis();
    state2 = 1 ;
    Serial.println("start2 : " + String(start_time2));
  }
  else if(buttonState12 == HIGH && state2 == 1){
    stop_time2 = millis();
    state2 = 0 ;
    Serial.println("Stop2 : "+ String(stop_time2));
  }
  
  if (stop_time1- start_time1 >= 3000){ // กดซ้าย 3 วิ แล้วจะเข้าตั้งค่าสูงสุด 
    Serial.println("กดแล้ว " + String(stop_time1-start_time1));
    blnk = 2;
    set_temp(0);
  }else if (stop_time2- start_time2 >= 3000){// กดขวา 3 วิ แล้วจะเข้าตั้งค่าต่ำสุด 
    Serial.println("กดแล้ว " + String(stop_time2-start_time2));
    blnk = 2;
    set_temp(1);
  }
}

void set_temp(int choose){
  // choose:0 = max, 1 = min, 2 = not use 
  while (choose == 0){
    buttonState11 = digitalRead(SW1);
    buttonState12 = digitalRead(SW2);
    if (buttonState11 == LOW && state1 == 0 && buttonState12 == HIGH){ // กดซ้ายเพิ่ม 
      max_temp += 1;
    }else if (buttonState12 == LOW && state2 == 0 && buttonState11 == HIGH){ // กดขวาลด 
      max_temp -= 1;
    }else if (buttonState12 == LOW && state2 == 0 && buttonState11 == LOW && state1 == 0){// กด สองปุ่มพร้อมกันออก
      start_time1 = millis();
      stop_time1 = millis();
      choose = 2 ;
      Serial.println("Max: " + String(max_temp));
      Serial.println("Min: " + String(min_temp));
      blnk = 0;
    }
    LED_matrix(max_temp);
    delay(100);
  }

  while (choose == 1){
    buttonState11 = digitalRead(SW1);
    buttonState12 = digitalRead(SW2);
    if (buttonState11 == LOW && state1 == 0 && buttonState12 == HIGH){
      min_temp += 1;
    }else if (buttonState12 == LOW && state2 == 0 && buttonState11 == HIGH){
      min_temp -= 1;
    }else if (buttonState12 == LOW && state2 == 0 && buttonState11 == LOW && state1 == 0){ // กด สองปุ่มพร้อมกันออก 
      start_time2 = millis();
      stop_time2 = millis();
      choose = 2 ;
      Serial.println("Max: " + String(max_temp));
      Serial.println("Min: " + String(min_temp));
      blnk = 0;
    }
    LED_matrix(min_temp);
    delay(100);
  }
}
