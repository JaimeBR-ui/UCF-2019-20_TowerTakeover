class Monster
{
   static void frightenWithFriend(Monster m)
   {
      System.out.println("(a) Monster instigator with Monster friend.");
   }

   void frightenWithFriend(Vampire v)
   {
      System.out.println("(b) Monster instigator with Vampire friend.");
   }
}

class Vampire extends Monster
{
   static void frightenWithFriend(Monster m)
   {
      System.out.println("(c) Vampire instigator with Monster friend.");
   }

   void frightenWithFriend(Vampire v)
   {
      System.out.println("(d) Vampire instigator with Vampire friend.");
   }
}

class ModifiedReVampRedux
{
   static void whichFWF(Monster m1, Monster m2)
   {
      m1.frightenWithFriend(m2);
   }

   public static void main(String [] args)
   {
      Vampire v1 = new Vampire();
      Vampire v2 = new Vampire();

      Monster m1 = new Monster();
      Monster m2 = new Monster();

      Monster mv1 = new Vampire();
      Monster mv2 = new Vampire();

      System.out.println();
      System.out.println("===========================================");
      System.out.println("Part 1: Vampire References, Vampire Objects");
      System.out.println("===========================================");

      whichFWF(v1, v2);          // prints: (a) Monster instigator with Monster friend.
      v1.frightenWithFriend(v2); //prints: (d) Vampire instigator with Vampire friend.

      System.out.println();
      System.out.println("===========================================");
      System.out.println("Part 2: Monster References, Monster Objects");
      System.out.println("===========================================");

      whichFWF(m1, m2);          // prints: (a) Monster instigator with Monster friend.
      m1.frightenWithFriend(m2); // prints: (a) Monster instigator with Monster friend.

      System.out.println();
      System.out.println("=====================");
      System.out.println("Part 3: Mixed Company");
      System.out.println("=====================");

      m1.frightenWithFriend(v1); //prints: (b) Monster instigator with Vampire friend.
      v1.frightenWithFriend(m1); //prints: (c) Vampire instigator with Monster friend.

      System.out.println();
      System.out.println("===========================================");
      System.out.println("Part 4: Monster References, Vampire Objects");
      System.out.println("===========================================");

      whichFWF(mv1, mv2);          // prints: (a) Monster instigator with Monster friend.
      mv1.frightenWithFriend(mv2); // prints: (a) Monster instigator with Monster friend.

      System.out.println();
      System.out.println("====================");
      System.out.println("Part 5: Total Mayhem");
      System.out.println("====================");

      mv1.frightenWithFriend(m1); // prints: (a) Monster instigator with Monster friend.
      mv1.frightenWithFriend(v1); // prints: (d) Vampire instigator with Vampire friend.
      whichFWF(mv1, v1);          // prints: (a) Monster instigator with Monster friend.
      m1.frightenWithFriend(mv1); // prints: (a) Monster instigator with Monster friend.
      v1.frightenWithFriend(mv1); // prints: (c) Vampire instigator with Monster friend.

      System.out.println();
   }
}
