void debugPrint(String a, int x, String b, int y, String c, int z) {
  Serial.print("X: ");
  Serial.print(x);
  Serial.print('\t');
  Serial.print("y: ");
  Serial.print(y);
  Serial.print('\t');
  Serial.print("Z: ");
  Serial.print(z);
  Serial.println('\t');

}
void debugPrint(String a, float x, String b, float y, String c, float z) {
  Serial.print(a);
  Serial.print(x, 3);
  Serial.print('\t');
  Serial.print(b);
  Serial.print(y, 3);
  Serial.print('\t');
  Serial.print(c);
  Serial.print(z, 3);
  Serial.println('\t');

}