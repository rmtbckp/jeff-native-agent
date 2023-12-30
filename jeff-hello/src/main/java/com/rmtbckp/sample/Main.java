package com.rmtbckp.sample;

public class Main {

    public static void main(String[] args) throws Exception {
        /****/
        //Main main = new Main();
        //Main.ddoMalloc();
        /****/
    
        String test1 = "test string1";
        //String test6 = "test string6";
        String test6 = null;
        int test2 = 123;
        long test3 = 234; // long and double need a bit of rework in the agent
        //float test3=2.34f;
        byte test4 = 127;
        boolean test5 = true;
        Main.testIntermediateMethodWithOtherVariable(test1, test2, test3, test4, test5, test6);
    }

    public static void testIntermediateMethodWithOtherVariable(String test1, int test2, long /*float*/ test3, byte test4, boolean test5, String test6) {
        int foo=4;
        boolean bar=false;
        Main.testMethod(test1, test2, test3, test4, test5, test6);
    }

    public static void /*String*/ testMethod(String methodParam1_String, int methodParam2_int, long /*float*/ methodParam3_long, byte methodParam4_byte, boolean methodParam5_boolean, String methodParam6_String) {
        System.out.printf("testMethod parameters: %s %s %s %s %s %s%n", methodParam1_String, methodParam2_int, methodParam3_long, methodParam4_byte, methodParam5_boolean, methodParam6_String);
        // System.out.printf("TEST METHOD %s %s %s %s%n", test2, test3, test4, test5);
        //int zxc = 0;
        methodParam2_int = 4444;
        Pet myPet = new Pet(4,10);
        int hjk=10;
        
        System.out.println("Trying methodParam1_String.length() with methodParam1_String=" + methodParam1_String);
        int length = methodParam1_String.length();
        System.out.println("Length = " + length);
        
        System.out.println("Trying methodParam6_String.length() with methodParam6_String=" + methodParam6_String);
        length = methodParam6_String.length();
        System.out.println("Length = " + length);
        
        /*try {
            methodParam1_String.substring(0,50);
            //String msg = "Test exception";
            //throw new IllegalArgumentException(msg);
        } catch(Exception e) {
            System.out.println("Exception" + e);
        }*/
        Main.testMethod2(new boolean[] { true, false, false, true });
        // return "";
    }

    public static void testMethod2(boolean[] array1) {
        String msg = "Test exception";
        Main.throwingMethod(msg);
    }

    public static void throwingMethod(String msg) {
        throw new IllegalArgumentException(msg);
    }
    
    public static class Pet {
        int age;
        int weight;
        
        public Pet(int age, int weight) {
            this.age=age;
            this.weight=weight;
        }
    
    }
    
    //private static native void doMalloc();
    
}
