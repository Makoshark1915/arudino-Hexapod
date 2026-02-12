import java.util.LinkedList;
import java.util.Scanner;




public class singleArmCodeStructure {
  static Scanner input;

  public static void main(String[] args) {
    input = new Scanner(System.in);

    LinkedList<Double> methodInput = new LinkedList<Double>();

    double servo1Angle;
    double servo2Angle;
    double servo3Angle;
    
    double isInRange;
   

    System.out.println("Ready for top down Check / solve for A?");
    input.nextLine();

    methodInput = topDownCheck();

    
    servo1Angle = methodInput.getLast();
 
    methodInput.removeLast();




    System.out.println("Ready for front back Check / solve for B?");
    input.nextLine();

    methodInput = frontBackCheck(methodInput);
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


    if (isInRange == 1.0) {
      System.out.println("Is in range = Yes");
    } else {
      System.out.println("Is in range = No");
    }


    for (int i = 0; i < 2; i++) {
      System.out.println();
    }





  }

  static LinkedList<Double> topDownCheck() {

    LinkedList<Double> output = new LinkedList<Double>();


    double x =0;
    double y =0;

    double maxRadius = 132.95;
    double tarRadius;
    double finRadius;

    double angle1;

    boolean isInRange = true;

    System.out.println("Enter the target x:");
    x = 132.95 - input.nextDouble();
    System.out.println("Enter the target y:");
    y = input.nextDouble();

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
    
    System.out.println();
    System.out.println("x = " + x);
    System.out.println("y = " + y);
    System.out.println();
    System.out.println("servo1 angle = " + angle1);
    System.out.println("tarRadius = " + tarRadius);
    System.out.println("isInRange = " + isInRange);



    output.addFirst(finRadius);
    output.addLast(angle1);
    return output;
  }

  static LinkedList<Double> frontBackCheck(LinkedList<Double> methodInput) {

    LinkedList<Double> output = new LinkedList<Double>();

    double R =methodInput.getFirst();
    double z =0;

    double maxRadius = 132.95;
    double tarRadius;
    double finRadius;

    double angle1;

    double isInRange = 1.0;


    System.out.println("Enter the target z:");
    z = input.nextDouble();

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
    
    System.out.println();
    System.out.println("R = " + R);
    System.out.println("z = " + z);
    System.out.println();
    System.out.println("angle1 = " + angle1);
    System.out.println("tarRadius = " + tarRadius);
    System.out.println("isInRange = " + isInRange);



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

  
  System.out.println("servo2 angle = " + angleA);
  System.out.println("servo3 angle = " + angleB);




  return output;
}

}