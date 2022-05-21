void LED_matrix(float temp, int blnk) {
  Wire.begin(I2C_SDA0,I2C_SCL0);
  matrix.begin(LED_ADDR);
  
  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  matrix.clear();
  matrix.setCursor(3,0);
  matrix.print(temp);
  matrix.blinkRate(blnk);
  matrix.writeDisplay();
  delay(100);
}
