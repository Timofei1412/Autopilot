struct point {
  float x;
  float y;
};

struct plane {
  point XY;
  float heading;
  float altitude;
  float speed;
} Plane;

struct line {
  float k;
  float b;
  point PointA;
  point PointB;
};

struct data {
  int roll;
  int pitch;
  int yaw;

  int Pr;
  int Ir;
  int Dr;

  int Pp;
  int Ip;
  int Dp;

  int Py;
  int Iy;
  int Dy;
} Income;