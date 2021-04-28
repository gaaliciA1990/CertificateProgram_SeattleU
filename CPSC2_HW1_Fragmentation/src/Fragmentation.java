import java.util.Random;

/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 4/27/2021 20:25
 */


public class Fragmentation {

    public static void main(String[] args) {
        int blockSize = 2048;
        int iterations = 10000;
        int maxNum = 20000;
        int internalFrag = 0;
        int meanFrag;

        Random rand = new Random();
        for (int i = 0; i < iterations; i++) {
            // generate a random number between 1 & 20K
            int p = rand.nextInt(maxNum) + 1;
            internalFrag += blockSize - (p % blockSize);
        }
        meanFrag = Math.round(internalFrag / iterations);

        System.out.println("Average value of internal fragmentation = " + meanFrag);
    }
}