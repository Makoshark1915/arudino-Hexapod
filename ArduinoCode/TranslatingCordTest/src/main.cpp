
double xglob = 0.0;//given corinates
double yglob = 0.0;

double xrel;// coordinates relative to the arm
double yrel;

double angle = 0.0;// angle of the arm relativle to the front of the robot


void setup() {

}

void loop() {
  
  xrel = xglob*cos(angle) - yglob*sin(angle);
  yrel = xglob*sin(angle) + yglob*cos(angle);

  serial.print("xrel: ");
  serial.print(xrel); 

  serial.print("  yrel: ");
  serial.println(yrel);
  
}

