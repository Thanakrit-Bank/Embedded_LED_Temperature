float Temperature() {
  byte Temp_data[2];
    Wire.begin(I2C_SDA1,I2C_SCL1);
    Wire.beginTransmission(TEMP_ADDR);  // I2C start and write slave address (ox4D)
    Wire.write(0);                      // write temperature address
    Wire.endTransmission();
    Wire.requestFrom(TEMP_ADDR , 2);    // I2C start and read temperature data two byte
    Temp_data[1] = Wire.read();         // receive MSB temp data
    Temp_data[0] = Wire.read();         // receive LSB temp data
  float temp = 0.0;
  if (Temp_data[1] & 0b10000000) {  // Temp_data[1]
    temp = temp * (-1);
  }
  if (Temp_data[1] & 0b01000000) {
    temp = temp + 128;
  }
  if (Temp_data[1] & 0b00100000) {
    temp = temp + 64;
  }
  if (Temp_data[1] & 0b00010000) {
    temp = temp + 32;
  }
  if (Temp_data[1] & 0b00001000) {
    temp = temp + 16;
  }
  if (Temp_data[1] & 0b00000100) {
    temp = temp + 8;
  }
  if (Temp_data[1] & 0b00000010) {
    temp = temp + 4;
  }
  if (Temp_data[1] & 0b00000001) {
    temp = temp + 2;
  }
  if (Temp_data[0] & 0b10000000) {  // Temp_data[0]
    temp = temp + 1;
  }
  if (Temp_data[0] & 0b01000000) {
    temp = temp + 0.5;
  }
  if (Temp_data[0] & 0b00100000) {
    temp = temp + 0.25;
  }
  if (Temp_data[0] & 0b00010000) {
    temp = temp + 0.125;
  }
  if (Temp_data[0] & 0b00001000) {
    temp = temp + 0.0625;
  }
  if (Temp_data[0] & 0b00000100) {
    temp = temp + 0.03125;
  }
  if (Temp_data[0] & 0b00000010) {
    temp = temp + 0;
  }
  if (Temp_data[0] & 0b00000001) {
    temp = temp + 0;
  }
  return temp;
}
