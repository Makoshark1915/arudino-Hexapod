import java.util.LinkedList;
import java.util.Scanner;




public class singleArmCodeStructure {
  static Scanner input;

  static double[] cords = new double[3]; // x, y, z coordinates of the target position for the leg


  public static void main(String[] args) {
    input = new Scanner(System.in);

    LinkedList<Double> methodInput = new LinkedList<Double>();

    double servo1Angle;
    double servo2Angle;
    double servo3Angle;
    
    double isInRange;
   
    while (true) {

      System.out.println("Enter x, y, z coordinates for the leg (separated by spaces):");
      String[] inputCords = input.nextLine().split(" ");
      cords[0] = Double.parseDouble(inputCords[0]);
      cords[1] = Double.parseDouble(inputCords[1]);
      cords[2] = Double.parseDouble(inputCords[2]);



    System.out.println("Ready for top down Check / solve for A?");
    input.nextLine();


    methodInput = topDownCheck(cords);

    
    servo1Angle = methodInput.getLast();
 
    methodInput.removeLast();




    System.out.println("Ready for front back Check / solve for B?");
    input.nextLine();

    methodInput = frontBackCheck(methodInput, cords[2]);
    isInRange = methodInput.getLast();
    methodInput.removeLast();
    



    System.out.println("Ready for in between Check / solve last angles?");
    input.nextLine();

      methodInput = lastAngleCheck(methodInput);

      servo2Angle = methodInput.getFirst();
      servo3Angle = methodInput.getLast();

  
    input.nextLine();


    for (int i = 0; i < 50; i++) {
      System.out.println();
    }


    System.out.println("Servo 1 angle = " + servo1Angle);
    System.out.println("Servo 2 angle = " + servo2Angle);
    System.out.println("Servo 3 angle = " + servo3Angle);


    
      System.out.println("Is in range = " + isInRange);
    
      

      

    for (int i = 0; i < 2; i++) {
      System.out.println();
    }

      System.out.println("Try again? (y/n)");
      if (input.nextLine().equalsIgnoreCase("n")) {
        break;
      }
    }


  }

  static LinkedList<Double> topDownCheck(double[] cords) {

    LinkedList<Double> output = new LinkedList<Double>();


    double x =cords[0]-132.95; // Adjusting x coordinate to be relative to the leg's base position
    double y =cords[1];

    double maxRadius = 132.95;
    double tarRadius;
    double finRadius;

    double angle1;

    boolean isInRange = true;



    tarRadius = Math.sqrt(x*x + y*y);

    angle1 = Math.toDegrees(Math.atan2(y,x));
 
    if (tarRadius > maxRadius) {
      
      isInRange = false;

       x = maxRadius * Math.cos(angle1);
       y = maxRadius * Math.sin(angle1); 

       finRadius = maxRadius;
    } 
    else {
      finRadius = tarRadius;
    }



    output.addFirst(finRadius);
    output.addLast(angle1);
    return output;
  }

  static LinkedList<Double> frontBackCheck(LinkedList<Double> methodInput, double z) {

    LinkedList<Double> output = new LinkedList<Double>();

    double R =methodInput.getFirst();

    double maxRadius = 132.95;
    double tarRadius;
    double finRadius;

    double angle1;

    double isInRange = 1.0;


  

    tarRadius = Math.sqrt(R*R + z*z);

    angle1 = Math.toDegrees(Math.atan2(z,R));
 
    if (tarRadius > maxRadius) {
      
      isInRange = 0.0;

       R = maxRadius * Math.cos(angle1);
       z = maxRadius * Math.sin(angle1); 

       finRadius = maxRadius;

      
    } 
    else {
      finRadius = tarRadius;
     
    }
    



    output.addFirst(finRadius);
    output.add(angle1);
    output.addLast(isInRange);
    return output;
  }

  static LinkedList<Double> lastAngleCheck(LinkedList<Double> methodInput) {
  
   LinkedList<Double> output = new LinkedList<Double>();

  double a = 47.6;
  double b = 85.35;
  double c = methodInput.getFirst();

  double angleA;
  double angleB;
  
  angleA = Math.toDegrees(Math.acos((a*a + c*c - b*b) / (2*c*a)));
  angleB = Math.toDegrees(Math.acos((b*b + a*a - c*c) / (2*a*b)));

  angleA -= methodInput.getLast();
  angleA = 90 - angleA;

  output.addFirst(angleA);
  output.addLast(angleB);






  return output;
}



public static boolean rangeCheck(double[] cords) {
  

   


    LinkedList<Double> methodInput2 = new LinkedList<Double>();


    
    double isInRange;
    boolean inRangeOut = true;
  


    methodInput2 = topDownCheck(cords);

 
    methodInput2.removeLast();





    methodInput2 = frontBackCheck(methodInput2, cords[2]);
    isInRange = methodInput2.getLast();
    methodInput2.removeLast();
    





  
  





    
     if (isInRange == 1.0) {
       inRangeOut = true;
     }
     else {
       inRangeOut = false;
     }
    
      

    
    

     return inRangeOut;
  }




  }

