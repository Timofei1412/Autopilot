












float RadialX = 0, RadialY = 0, hyp = 0;

float getDistToLine(int R, line Line, plane Coords, int i) {
  RadialX = Coords.x + (cos(i) * R);
  RadialY = Coords.Y + (sin(i) * R);

  X_on_Line = (RadialY / Line.k) - Line.b;
  Y_on_Line = Line.k * RadialX + Line.b;

  hyp = hypot(X_on_Line, Y_on_Line);
  C = (X_on_Line + Y_on_Line) / min(X_on_Line, Y_on_Line);
  return hypot(hyt / C, min(X_on_Line, Y_on_Line));
}
