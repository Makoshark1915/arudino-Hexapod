import java.util.Scanner;




public class walkingLoop {
  static Scanner input;

    
    int step = 0; // variable to keep track of which step in the walking cycle we are on, will be updated every loop

  
    final float[][] legsDefault = {{132.95f, 90, 60}, {132.95f, 90, 60}, {132.95f, 90, 60}, 
    {132.95f, 90, 60}, {132.95f, 90, 60}, {132.05f, 90, 60} }; // default position for all 6 legs, will be used to set legs to a default "standing" position


    float[][] legs // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
    = legsDefault;


    final float mult = 1; // multiplier for how much the joystick input affects movement

  public static void main(String[] args) {
    input = new Scanner(System.in);
    
    while (true) {

      System.out.println("Enter the xy joystick values (x y): ");
      String joystickInput = input.nextLine();
      


      float[] Input = new float[2];
      Input[0] = Float.parseFloat(joystickInput.split(" ")[0]);
      Input[1] = Float.parseFloat(joystickInput.split(" ")[1]);



      System.out.println();
      System.out.println("Joystick Values: " + Input[0] + ", " + Input[1]);



      Step(Input);




    }
  }

  static void Step(float[] Input) 
  {

    float joystickX = Input[0];
    float joystickY = Input[1];






















  }








}