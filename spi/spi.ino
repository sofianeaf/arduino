#include <SPI.h>

// -- SPI ----------------
const int SSPin = 8;
byte spi_wr_buf[8];
byte spi_rd_buf[8];
// -- UART ---------------
byte serial_buf;
int j = 0;
int k;

void setup() {
  // -- UART ---------------------------
  Serial.begin(9600);
  // -- SPI ----------------------------
  SPI.begin();
  SPI.setClockDivider(85); // Arduino DUE only
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  // -- IOs ----------------------------
  pinMode(SSPin, OUTPUT);
  digitalWrite(SSPin, HIGH);
  // -- init ---------------------------
  k = 0;
  initSpiBuffers();
}

void loop(){
  // READ UART UNTIL "ENTER"
  if(Serial.available() > 0){
    serial_buf = Serial.read();
    j++;
  }
  if(Serial.available() == 0 && j > 0){
    for(int i = 0; i < j; i++) {
      Serial.print("(");
      Serial.print(serial_buf, HEX);
      Serial.print(") ");
      
      // next line after ENTER
      if(serial_buf == 10){
        Serial.println();
        spiTransaction();
        k = 0;
        initSpiBuffers();
      }
      else{
        spi_wr_buf[k] = translate(serial_buf);
        k++;
      }
     }
    j = 0;
  }
}
// ----------------------------------------------------
// TRANSLATE SPECIFIC BYTES FROM (ASCII) TO (HEX) -----
byte translate(byte input) {
  byte output;
  switch(input)
  {
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
        output = input - 48;
        break;
    case 97:
        output = 0xAA;
        break;
    case 98:
        output = 0xBB;
        break;
    default:
        output = input;
        break;
  }
  return output;
}
// ----------------------------------------------------
// INIT SPI CMD & DATA BUFFERS ------------------------
void initSpiBuffers() {
  spi_wr_buf[0] = 0x00; spi_rd_buf[0] = 0x00;
  spi_wr_buf[1] = 0x00; spi_rd_buf[1] = 0x00;
  spi_wr_buf[2] = 0x00; spi_rd_buf[2] = 0x00;
  spi_wr_buf[3] = 0x00; spi_rd_buf[3] = 0x00;
  spi_wr_buf[4] = 0x00; spi_rd_buf[4] = 0x00;
  spi_wr_buf[5] = 0x00; spi_rd_buf[5] = 0x00;
  spi_wr_buf[6] = 0x00; spi_rd_buf[6] = 0x00;
  spi_wr_buf[7] = 0x00; spi_rd_buf[7] = 0x00;
}
// ----------------------------------------------------
// SPI transaction ------------------------------------
void spiTransaction() {
  
  digitalWrite(SSPin, LOW);
  for(int i = 0; i < 8; i++) spi_rd_buf[i] = SPI.transfer(cmd_wr_buf[i]);
  digitalWrite(SSPin, HIGH);
  
  for(int i = 0; i < 8; i++) {Serial.print(spi_wr_buf[i],HEX);Serial.print(" ");} Serial.print("\n");
  for(int i = 0; i < 8; i++) {Serial.print(spi_rd_buf[i],HEX);Serial.print(" ");} Serial.print("\n");
  
}

