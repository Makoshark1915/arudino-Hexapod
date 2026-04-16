import java.util.Scanner;




public class walkingLoop {
  static Scanner input;

    static final float defaultX = 132.95f; // default x value for the legs
    static final float defaultY = 80.0f; // default y value for the legs
    static final float defaultZ = 90.0f; // default z value for the legs

    static float[][] legsGroup1 // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = {
      {defaultX, defaultY, defaultZ},
      {defaultX, defaultY, defaultZ},
      {defaultX, defaultY, defaultZ}
    };
    static float[][] legsGroup2 // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = {
      {defaultX, defaultY, defaultZ},
      {defaultX, defaultY, defaultZ},
      {defaultX, defaultY, defaultZ}
    };

    static final float mult = 5; // multiplier for how much the joystick input affects movement

    static float joystickX; // variable to store the x value of the joystick input, will be updated every loop
    static float joystickY; // variable to store the y value of the joystick input, will be updated every loop


/* leg setup

      front
    1-1   2-1   

  2-2       1-2

    1-3   2-3
       back

*/
  public static void main(String[] args) {
    input = new Scanner(System.in);
    
    while (true) {

      joystickInput(); // get the joystick input and store it in the joystickX and joystickY variables

      if(joystickAtRest()){ // if the joystick is at rest go to default or else, start moving

        reCenter(); // if the joystick is in the neutral position, run the code to re-center the legs to the default position

      }

      else{
        moving(joystickX, joystickY);// the code to move the legs according to the joystick input and the current scenario of which leg group is up (only runs if the joystick is not in the neutral position )
      }
      


      
    }
  }
  




static void moving(float joystickX, float joystickY) { // run the first step of walking cycle


   



  

    if(groupUp() == 0 || groupUp() == 1){

      legsGroup1[0][2] = defaultZ-10;
      legsGroup1[1][2] = defaultZ-10;
      legsGroup1[2][2] = defaultZ-10;
      applyChanges();


    do{ // while the legs are in range and the first leg group is up, move the legs according to the joystick input

      legsGroup1[0][0] += joystickX * mult;
      legsGroup1[0][1] += joystickY * mult; // joystickY for all of these might need to be flipped/have changed signs
 
      legsGroup1[1][0] += joystickX * mult;
      legsGroup1[1][1] += joystickY * mult; 

      legsGroup1[2][0] += joystickX * mult;
      legsGroup1[2][1] += joystickY * mult;


      legsGroup2[0][0] -= joystickX * mult;
      legsGroup2[0][1] -= joystickY * mult;

      legsGroup2[1][0] -= joystickX * mult;
      legsGroup2[1][1] -= joystickY * mult;

      legsGroup2[2][0] -= joystickX * mult;
      legsGroup2[2][1] -= joystickY * mult;

      joystickInput();
      applyChanges();
      
    }while(inRange() && joystickAtRest() == false);

      legsGroup2[0][2] = defaultZ-10;
      legsGroup2[1][2] = defaultZ-10;
      legsGroup2[2][2] = defaultZ-10;

      legsGroup1[0][2] = defaultZ;
      legsGroup1[1][2] = defaultZ;
      legsGroup1[2][2] = defaultZ;


      applyChanges();




  }
  else if(groupUp() == 2){

    do{ // while the legs are in range and the first leg group down, move the legs according to the joystick input

      legsGroup1[0][0] -= joystickX * mult;
      legsGroup1[0][1] -= joystickY * mult; // joystickY for all of these might need to be flipped/have changed signs
 
      legsGroup1[1][0] -= joystickX * mult;
      legsGroup1[1][1] -= joystickY * mult;

      legsGroup1[2][0] -= joystickX * mult; 
      legsGroup1[2][1] -= joystickY * mult;


      legsGroup2[0][0] += joystickX * mult;
      legsGroup2[0][1] += joystickY * mult;

      legsGroup2[1][0] += joystickX * mult;
      legsGroup2[1][1] += joystickY * mult;

      legsGroup2[2][0] += joystickX * mult;
      legsGroup2[2][1] += joystickY * mult;

      joystickInput();

    }while(inRange() && joystickAtRest() == false);

      legsGroup1[0][2] = defaultZ-10;
      legsGroup1[1][2] = defaultZ-10;
      legsGroup1[2][2] = defaultZ-10;

      legsGroup2[0][2] = defaultZ;
      legsGroup2[1][2] = defaultZ;
      legsGroup2[2][2] = defaultZ;



  }
  else{
    while (true){
    System.out.println("ERROR bad read on Scenario");
    }
  }








  }

static void reCenter() { // run re-center the legs to the default position
  legsGroup1[0][0] = defaultX;
  legsGroup1[0][1] = defaultY;
  legsGroup1[0][2] = defaultZ;

  legsGroup1[1][0] = defaultX;
  legsGroup1[1][1] = defaultY;
  legsGroup1[1][2] = defaultZ;

  legsGroup1[2][0] = defaultX;
  legsGroup1[2][1] = defaultY;
  legsGroup1[2][2] = defaultZ;


  legsGroup2[0][0] = defaultX;
  legsGroup2[0][1] = defaultY;
  legsGroup2[0][2] = defaultZ;

  legsGroup2[1][0] = defaultX;
  legsGroup2[1][1] = defaultY;
  legsGroup2[1][2] = defaultZ;

  legsGroup2[2][0] = defaultX;
  legsGroup2[2][1] = defaultY;
  legsGroup2[2][2] = defaultZ;

}

static void applyChanges() { // apply the changes to the legs

    
}

static boolean inRange() { // check's if the given xyz values for all legs are in a reachable position
boolean inRangeOut = true;

double[] cords = new double[3];


double R1;
double R2;

  for(int i = 0; i < 6; i++){
   
    if(i<=2){

      cords[0] = legsGroup1[i][0]-defaultX;
      cords[1] = legsGroup1[i][1];
      cords[2] = legsGroup1[i][2];

    }
    else{

      cords[0] = legsGroup2[i-3][0]-defaultX;
      cords[1] = legsGroup2[i-3][1];
      cords[2] = legsGroup2[i-3][2];




    }


    R1 = Math.sqrt((cords[0]*cords[0]) + (cords[1]*cords[1]));
    R2 = Math.sqrt((R1*R1) + (cords[2]*cords[2]));



    if(R1 > defaultX || R2 > defaultX){
      inRangeOut = false;
      break;
    }
    

  }



 
  return inRangeOut;
 
}

static boolean joystickAtRest() { // check if the joystick is in the neutral position


  boolean atRest = false;

  if(joystickX == 0 && joystickY == 0){
    atRest = true;
  }

  return atRest;
}

static int groupUp(){// checks which leg group is raised

  
  
  int scenario;
  
  if(legsGroup1[0][2]==defaultZ && legsGroup2[0][2]==defaultZ){//at default both groups are down, scenario 0

      scenario = 0;
      
  }
    else if(legsGroup1[0][2] == defaultZ-10 && legsGroup2[0][2] == defaultZ){ //group 1 is up and group2 is down, scenario 1

      scenario = 1;

    } 
    else if(legsGroup2[0][2] == defaultZ-10 && legsGroup1[0][2] == defaultZ){ //group 1 is down and group2 is up, scenario 2

      scenario = 2;

    }
    else
    {    
       while (true){

        System.out.println("ERROR bad Scenario");

        } // if in none of the previous options something broke run ERROR
    }



    return scenario;
}

static void joystickInput() { // get the joystick input also serves as a pause for the user to see the current leg positions before inputting new joystick values

 
//  try{

  System.out.println("Enter the joystick xy value (x y)");
  String inputString = input.nextLine();

  joystickX = Float.parseFloat(inputString.split(" ")[0]);
  joystickY = Float.parseFloat(inputString.split(" ")[1]);


  System.out.println("joystick at rest: " + joystickAtRest()); // print the joystick input for testing purposes
  System.out.println("Scenario: " + groupUp()); // print the current scenario for testing purposes
  System.out.println("in range: " + inRange()); // print if the legs are in range for testing purposes
  System.out.println("group1 cords: " + legsGroup1[0][0] + " " + legsGroup1[0][1] + " " + legsGroup1[0][2] + " | " + legsGroup1[1][0] + " " + legsGroup1[1][1] + " " + legsGroup1[1][2] + " | " + legsGroup1[2][0] + " " + legsGroup1[2][1] + " " + legsGroup1[2][2]); 
  System.out.println("group2 cords: " + legsGroup2[0][0] + " " + legsGroup2[0][1] + " " + legsGroup2[0][2] + " | " + legsGroup2[1][0] + " " + legsGroup2[1][1] + " " + legsGroup2[1][2] + " | " + legsGroup2[2][0] + " " + legsGroup2[2][1] + " " + legsGroup2[2][2]); 
  System.out.println("default cords: " + defaultX + " " + defaultY + " " + defaultZ + " | " + defaultX + " " + defaultY + " " + defaultZ + " | " + defaultX + " " + defaultY + " " + defaultZ);
/* 
  }
  catch(Exception e){
    System.out.println("ERROR bad input for joystick values, try again");
    joystickInput();
  }

*/
 

}

}