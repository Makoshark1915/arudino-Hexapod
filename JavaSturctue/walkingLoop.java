import java.util.Scanner;




public class walkingLoop {
  static Scanner input;

    
    static int step = 0; // variable to keep track of which step in the walking cycle we are on, will be updated every loop

  
    final static float[][] legsDefault = {{132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f}, 
    {132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f} }; // default position for all 6 legs, will be used to set legs to a default "standing" position


    static float[][] legs // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = legsDefault;


    final float mult = 1; // multiplier for how much the joystick input affects movement

    static float joystickX; // variable to store the x value of the joystick input, will be updated every loop
    static float joystickY; // variable to store the y value of the joystick input, will be updated every loop






  public static void main(String[] args) {
    input = new Scanner(System.in);
    
    while (true) {

      System.out.println("Enter the xy joystick values (x y): ");
      String joystickInput = input.nextLine();
      


      
      joystickX = Float.parseFloat(joystickInput.split(" ")[0]);
      joystickY = Float.parseFloat(joystickInput.split(" ")[1]);








      while(joystickX != 0 || joystickY != 0){ // if the joystick is not in the neutral position, run the walking cycle
       
        
      
        if(step == 0){ 
          step0(joystickX, joystickY);    
        }




        else if(step == 1){ // if we are in the first step of the walking cycle, run the code for the first step
          step1(joystickX, joystickY);
        }
        else if(step == 2){ // if we are in the second step of the walking cycle, run the code for the second step
          step2(joystickX, joystickY);
        }
        else if(step == 3){ // if we are in the third step of the walking cycle, run the code for the third step
          step3(joystickX, joystickY);
        }



        else {// if we are in any other step, break the loop (this should never happen, but is here as a safety measure) 
          
          System.out.println("Error: Invalid step in walking cycle. Step: " + step);        
          break;  
        }

      }


      reCenter(); // if the joystick is in the neutral position, run the code to re-center the legs to the default position



    

    }
  }
  


  static void step0(float joystickX, float joystickY) { //run the init step of walking cycle: group1 lift/move, group2 move

  }




  static void step1(float joystickX, float joystickY) { // run the first step of walking cycle: group1 drop, group2 lift/move
 
  }



  static void step2(float joystickX, float joystickY) { // run the second step of walking cycle:  group1 move, group2 drop
 
  }



  static void step3(float joystickX, float joystickY) { //run the third step of walking cycle: group1 lift/move, group2 drop/move

  }





  static void reCenter() { // run re-center the legs to the default position
 
  }

}