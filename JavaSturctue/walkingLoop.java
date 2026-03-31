import java.util.Scanner;




public class walkingLoop {
  static Scanner input;

  
    final static float[][] legsDefault = {{132.95f, 80.0f, 90.0f}, {132.95f, 80.0f, 90.0f}, {132.95f, 80.0f, 90.0f} }; // default position for all 6 legs, will be used to set legs to a default "standing" position


    static float[][] legsGroup1 // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = legsDefault;
    static float[][] legsGroup2 // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = legsDefault;

    static final float mult = 1; // multiplier for how much the joystick input affects movement

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

      System.out.println("Enter the xy joystick values (x y): ");
      String joystickInput = input.nextLine();
      


      
      joystickX = Float.parseFloat(joystickInput.split(" ")[0]);
      joystickY = Float.parseFloat(joystickInput.split(" ")[1]);








      if(!joystickAtRest()){ // if the joystick is not in the neutral position, run the walking cycle

          moving(joystickX, joystickY);
        
      }


      reCenter(); // if the joystick is in the neutral position, run the code to re-center the legs to the default position



    

    }
  }
  




static void moving(float joystickX, float joystickY) { // run the first step of walking cycle


   



  

    if(groupUp() == 0 || groupUp() == 1){

    while(inRange() && legsGroup1[0][2] >= legsDefault[0][2] && !joystickAtRest()){ // while the legs are in range and the first leg group is up, move the legs according to the joystick input

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


    }
  }
  else if(groupUp() == 2){


    while(inRange() && legsGroup2[0][2] >= legsDefault[0][2] && !joystickAtRest()){ // while the legs are in range and the first leg group down, move the legs according to the joystick input

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


    }
  }
  else{
    while (true){
    System.out.println("ERROR bad read on Scenario");
    }
  }








  }

static void reCenter() { // run re-center the legs to the default position
 legsGroup1=legsDefault;
 legsGroup2=legsDefault;
}

static void applyChanges() { // apply the changes to the legs

    
}

static boolean inRange() { // check's if the giver xyz values for all legs are in a reachable position



    boolean inRange = true; 



    return inRange;
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
  
  if(legsGroup1==legsDefault && legsGroup2==legsDefault){//at default group 1 moves up, scenario 0
  
      legsGroup2[0][2] = legsDefault[0][2];
      legsGroup2[1][2] = legsDefault[1][2];
      legsGroup2[2][2] = legsDefault[2][2];
      applyChanges();


      legsGroup1[0][2] = legsDefault[0][2]-10;
      legsGroup1[1][2] = legsDefault[1][2]-10;
      legsGroup1[2][2] = legsDefault[2][2]-10;
      applyChanges();

      scenario = 0;
      
    }
    else if(legsGroup1[0][2] == legsDefault[0][2] && legsGroup2[0][2] == legsDefault[0][2]-10){ //group 1 moves up group 2 moves down, scenario 1

      legsGroup2[0][2] = legsDefault[0][2];
      legsGroup2[1][2] = legsDefault[1][2];
      legsGroup2[2][2] = legsDefault[2][2];
      applyChanges();

      legsGroup1[0][2] = legsDefault[0][2]-10;
      legsGroup1[1][2] = legsDefault[1][2]-10;
      legsGroup1[2][2] = legsDefault[2][2]-10;
      applyChanges();

      scenario = 1;

    } 
    else if(legsGroup2[0][2] == legsDefault[0][2] && legsGroup1[0][2] == legsDefault[0][2]-10){ //group 1 moves down group 2 moves up, scenario 2

      legsGroup1[0][2] = legsDefault[0][2];
      legsGroup1[1][2] = legsDefault[1][2];
      legsGroup1[2][2] = legsDefault[2][2];
      applyChanges();

      legsGroup2[0][2] = legsDefault[0][2]-10;
      legsGroup2[1][2] = legsDefault[1][2]-10;
      legsGroup2[2][2] = legsDefault[2][2]-10;
      applyChanges();

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





}