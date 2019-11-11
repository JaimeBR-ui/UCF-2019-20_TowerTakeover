// Jaime Bohorquez
// le me trying to understand static vs dynamic binding.

import java.util.Arrays;

public class DynamAndStatic
{
     public static void main(String[] args)
     {
          Stonk s1 = new Stonk();
          Stonk s2 = new JavaStonk();
          JavaStonk s3 = new JavaStonk();

          Stonk.stonkSort(new int[]{1, 20, 2, 9, 3, 5, 4, 6, 7, 8});

          s1.buyStonk(s1); // prints: stonk object with Stonk reference
          s2.buyStonk(s2); // prints: stonk object with Stonk reference
          s3.buyStonk(s3); // prints: JavaStonk object with JavaStonk reference

          s1.buyStonk(s3); // prints: stonk object with JavaStonk reference
          s2.buyStonk(s1); // prints: stonk object with Stonk reference
          s3.buyStonk(s2); // prints: JavaStonk object with Stonk reference
     }
}

class Stonk
{

     public static void buyStonk(Stonk s)
     {
          System.out.println("stonk object with Stonk reference");
     }

     public void buyStonk(JavaStonk s)
     {
          System.out.println("Stonk object with JavaStonk reference");
     }
}

class JavaStonk extends Stonk
{
     public static void buyStonk(Stonk s)
     {
          System.out.println("JavaStonk object with Stonk reference");
     }

     @Override
     public void buyStonk(JavaStonk s)
     {
          System.out.println("JavaStonk object with JavaStonk reference");
     }
}
