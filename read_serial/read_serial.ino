byte buf[8];
// -- UART -----------------------------
byte serial_buf;
int j = 0;
int k;

void setup() {
  // -- UART ---------------------------
  Serial.begin(9600);
  // -- init ---------------------------
  k = 0;
  initBuffers();
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
        action();
        k = 0;
        initBuffer();
      }
      else{
        buf[k] = translate(serial_buf);
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
// -- INIT BUFFERS ------------------------------------
void initBuffer() {
  buf[0] = 0x00;
  buf[1] = 0x00;
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = 0x00;
  buf[6] = 0x00;
  buf[7] = 0x00;
}
// ----------------------------------------------------
// -- ACTION ------------------------------------------
void action() {
  // print buffer
  for(int i = 0; i < 8; i++) {Serial.print(buf[i],HEX);Serial.print(" ");} Serial.print("\n");
}

