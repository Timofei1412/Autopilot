//-Vals for line def
double delta = 0.00001;
int R = 2;

//--- PID VALS----------------------------
#define iMin -0.4
#define iMax 0.4


float lastErrorZ = 0;
float iSum_Z = 0;
float lastErrorX = 0;
float iSum_X = 0;
float lastErrorY = 0;
float iSum_Y = 0;

//-Main math func are written here-----------------------------------------------------------
float computePid(float error, float target, float kp) {  // Compute pid with error, target val and p coef.
  float p = (target - error) * kp;
  return p;
}

int XPid(int error) {
  float up = error * kPX;
  iSum_X += error;
  if (iSum_X < iMin) iSum_X = iMin;
  if (iSum_X > iMax) iSum_X = iMax;
  float ui = iSum_X * kIX;
  float ud = (error - lastErrorX) * kDX;
  lastErrorX = error;
  return constrain(int(up + ui + ud), 0, 180);
}

int YPid(int error) {
  float up = error * kPY;
  iSum_Y += error;
  if (iSum_Y < iMin) iSum_Y = iMin;
  if (iSum_Y > iMax) iSum_Y = iMax;
  float ui = iSum_Y * kIY;
  float ud = (error - lastErrorY) * kDY;
  lastErrorY = error;
  return constrain(int(up + ui + ud), 0, 180);
}

int ZPid(int error) {
  float up = error * kPZ;
  iSum_Z += error;
  if (iSum_Z < iMin) iSum_Z = iMin;
  if (iSum_Z > iMax) iSum_Z = iMax;
  float ui = iSum_Z * kIZ;
  float ud = (error - lastErrorZ) * kDZ;
  lastErrorZ = error;
  return constrain(int(up + ui + ud), 0, 180);
}
/*

    Funcs for gps 

    
float computePointDist(float x1, float y1, float x2, float y2) {  // Compute distance between two points
  float dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  return dist;
}

void straightLine getLine(pointA, pointB) {  // Get line coef (when represented by y=kx+b)
  straightLine.k = (pointB.y - pointA.y) / (pointB.x - pointA.x);
  straightLine.b = pointA.y - (k * pointA.x);
}

int getErrorAngle(PointPlane, planeCource, straightLine) {  // Calculate angle to the point on line (there a point in R radius from plane)
  planeCource -= 90;
  for (float A = 0.0; A <= 180.0; A += 0.5) {
    float y = b + sin(A + planeCource) * R;
    float x = a + cos(A + planeCource   Z) * R;
    double y_1 = straightLine.k * x + straightLine.b;
    if (y_1 - delta <= y <= y_1 + delta) {
      return A - 90;
      break;
    }
  }
}
*/
