
//Plane is controled manualy, Arduino is counting speed, getting signals from ground and conrols Aeronautical lights
void flightData() {
  //doLight(0);  // Aeronautical lights and landing lights are written here
  tmrSpd = millis();
}

//Plane is flying automatic, trying to fly staight (x = 0, y = 0, z = startZ)
void flyStraight() {
  //doLight(0);                                                                                                                                                                                               // Aeronautical lights and landing lights are written here
  getInfo(&rGx, &rGy, &rGz);
  Serial.println(constrain(computePid((rGy - (90 / kPX)), 0, kPX), 10, 170));                                                                                                                              // Get our angles
  angleWrite(constrain(computePid((rGy - (90 / kPX)), 0, kPX), 10, 170), constrain(180 - computePid((rGx - (90 / kPY)), 0, kPY), 10, 170), constrain(computePid((rGz - (90 / kPZ)), rTz, kPZ), 10, 170));  // Calculate servo output
  Gh = cos(radians(rGx)) * cos(radians(rGy)) * getDist();
  //debugPrint("OUT: ", constrain(computePid((rGy - (90 / kPX)), 0, kPX), 10, 170), "Error: ", (float)(rGy - (90 / kPX)), "rGy ", (float)rGy);  // Get our height from sonic(from 1cm to 5m)
  // Get signal from ground
  tmrSpd = millis();
}


//Plane is flying automatic, trying to mantain angles, given from ground
void flyWithTask() {
  doLight();                                                                                                                                                                                                   // Aeronautical lights and landing lights are written here
  getInfo(&rGx, &rGy, &rGz);                                                                                                                                                                                   // Get our angles
  angleWrite(constrain(computePid((rGy - (90 / kPX)), rTx, kPX), 10, 170), constrain(180 - computePid((rGx - (90 / kPY)), rTy, kPY), 10, 170), constrain(computePid((rGz - (90 / kPZ)), rTz, kPZ), 10, 170));  // Calculate servo output
  Serial.println(constrain(computePid((rGy - (90 / kPX)), 0, kPX), 10, 170));

  tmrSpd = millis();
}
