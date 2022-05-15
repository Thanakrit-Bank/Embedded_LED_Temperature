void LED_matrix() {
  float Temp = Temperature();
  Wire.begin(I2C_SDA0,I2C_SCL0);
  matrix.begin(LED_ADDR);
  
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(Temp);
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
}
