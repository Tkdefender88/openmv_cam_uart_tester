const int BUFFER_SIZE = 100;
const int COMMAND_SIZE = 5;
char buffer[BUFFER_SIZE];
char reset_cmd[]            = {0x56, 0x00, 0x26, 0x00};
char capture_img_cmd[]      = {0x56, 0x00, 0x36, 0x01, 0x00};
char read_img_data_length[] = {0x56, 0x00, 0x34, 0x01, 0x00};
char read_img_data[]        = {0x56, 0x00, 0x0C, 0x00, 0x0A};
char stop_capture[]         = {0x56, 0x00, 0x36, 0x01, 0x03};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    int len = Serial.readBytesUntil(0x0A, buffer, BUFFER_SIZE);
    if (len > 0) {
      if(compareBuf(buffer, "start up", len)) {
        Serial.write(capture_img_cmd, COMMAND_SIZE);
      }
    }
  }
}

int compareBuf(char* a, char* b, int len) {
  for (int i = 0; i < len; i++) {
    if (a[i] != b[i]) return 0; 
  }
  return 1;
}
