#define Radius 10



//-Main math func are written here-----------------------------------------------------------
float computePid(float error, float target, float kp) {  // Compute pid with error, target val and p coef.
  float p = (target - error) * kp;
  return p;
}
// /*

// /*
//   Funcs for gps
// */


// float RadialX = 0, RadialY = 0, hyp = 0;

// float computePointDist(float x1, float y1, float x2, float y2) {  // Compute distance between two points
//   float dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
//   return dist;
// }



// void getLine(point pointA, point pointB) {  // Get line coef (when represented by y=kx+b)
//   line.k = (pointB.y - pointA.y) / (pointB.x - pointA.x);
//   line.b = pointA.y - (k * pointA.x);

//   line.PointA = pointA;
//   line.PointB = pointB;

// }


// float dists[360] = {};
// int count = 0;

// int getErrorAngle(line Line) {  // Calculate angle to the point on line (there a point in R radius from plane)
//   for (float i = -90; i < 90, = ; i += 0.5) {
//     dist = getDistToLine(Radius, Line, i);
//     dists[count] = dist;
//     count++;
//   }
//   count = 0;
// }

// float getDistToLine(int R, line Line,  int A) {
//   i = Coords.heading + a;
//   RadialX = Plane.XY.X + (cos(degrees(i)) * R);
//   RadialY = Plane.XY.y + (sin(degrees(i)) * R);
//   X_on_Line = (RadialY / Line.k) - Line.b;
//   Y_on_Line = Line.k * RadialX + Line.b;
//   hyp = hypot(X_on_Line, Y_on_Line);
//   return((radialX-X_on_Line)*(radialY-Y_on_Line))/hyp;
// }
