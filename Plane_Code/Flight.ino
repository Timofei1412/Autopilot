//Plane is controled manualy, Arduino is counting speed, getting signals from ground and conrols Aeronautical lights
void flightData() {
  doLight();                                                                                        // Aeronautical lights and landing lights are written here
  
  getSig();                                                                                         // Get signal from ground
  tmrSpd = millis();
}

//Plane is flying automatic, trying to fly staight (x = 0, y = 0, z = startZ)
void flyStraight() {
  doLight();                                                                                                                                                           // Aeronautical lights and landing lights are written here
  getInfo(&rGx, &rGy, &rGz);                                                                                                                                           // Get our angles
  angleWrite(constrain(computePid(rGy - 45, 0, 2), 10, 170), constrain(180 - computePid(rGx - 45, 0, 2), 10, 170), constrain(computePid(rGz - 45, rTz, 2), 10, 170));  // Calculate servo output
  Gh = cos(radians(rGx)) * cos(radians(rGy)) * getDist();  // Get our height from sonic(from 1cm to 5m)
  getSig();                                                // Get signal from ground
  tmrSpd = millis();
}


//Plane is flying automatic, trying to mantain angles, given from ground
void flyWithTask() {
  doLight();                                                                                                                                                               // Aeronautical lights and landing lights are written here
  getInfo(&rGx, &rGy, &rGz);                                                                                                                                               // Get our angles
  angleWrite(constrain(computePid(rGy - 45, rTy, 2), 10, 170), constrain(180 - computePid(rGx - 45, rTx, 2), 10, 170), constrain(computePid(rGz - 45, rTz, 2), 10, 170));  // Calculate servo output
  Gh = cos(radians(rGx)) * cos(radians(rGy)) * getDist();                                                                                                                  // Get our height from sonic
  
  getSig();  // Get signal from ground
  tmrSpd = millis();
}
