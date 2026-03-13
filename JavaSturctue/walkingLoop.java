import java.util.Scanner;




public class walkingLoop {
  static Scanner input;

    
    static int step = 0; // variable to keep track of which step in the walking cycle we are on, will be updated every loop

  
    final static float[][] legsDefault = {{132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f}, 
    {132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f}, {132.95f, 60.0f, 70.0f} }; // default position for all 6 legs, will be used to set legs to a default "standing" position


    static float[][] legs // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = legsDefault;


    static final float mult = 1; // multiplier for how much the joystick input affects movement

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
       
       if (step >1) { // if we have completed the walking cycle, reset the step variable to 0 to start the cycle over again
          step = 0;
        } 
      
        if(step == 0){ 
          step0(joystickX, joystickY);    
        }




        else if(step == 1){ // if we are in the first step of the walking cycle, run the code for the first step
          step1(joystickX, joystickY);
        }
    
        



        else {// if we are in any other step, break the loop (this should never happen, but is here as a safety measure) 
          
          System.out.println("Error: Invalid step in walking cycle. Step: " + step);        
          break;  
        }

        step++; // update the step variable to move to the next step in the walking cycle   

      }


      reCenter(); // if the joystick is in the neutral position, run the code to re-center the legs to the default position



    

    }
  }
  


  static void step0(float joystickX, float joystickY) { //run the init step of walking cycle: lift or drop

    legs[0][2] = 0;
    legs[3][2] = 0;
    legs[4][2] = 0;





  }




  static void step1(float joystickX, float joystickY) { // run the first step of walking cycle: move



    legs[1][1] += joystickY * mult;
    legs[2][1] += joystickY * mult;
    legs[5][1] += joystickY * mult;

    legs[1][0] += joystickX * mult;
    legs[2][0] += joystickX * mult;
    legs[5][0] += joystickX * mult;


  }






  static void reCenter() { // run re-center the legs to the default position
 
  }

}