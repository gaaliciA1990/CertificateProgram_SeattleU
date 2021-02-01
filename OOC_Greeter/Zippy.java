/*
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 1/13/21
 * Class: CPSC 5011-02
 */

package hw1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Zippy {
    private final ArrayList<String> zippy = new ArrayList<>();
    private final Random rand = new Random();

    /**
     * Constructor to populate an ArrayList with the phrases from the zippy file
     *
     * @param filename The zippy file holding random phrases
     * @throws FileNotFoundException when invalid file path is found
     */
    public Zippy(String filename) throws FileNotFoundException {
        File file = new File(filename);
        Scanner inFile = new Scanner(file);
        String zipLine;

        // Read each line of the zippy file and populate the zippy ArrayList
        while (inFile.hasNext()) {
            zipLine = inFile.nextLine();
            zippy.add(zipLine);
        }
    }

    /**
     * This method will generate a random number with the max size set to the size
     * of the ArrayList. The randomly generated number is then used as the index
     * to pull the phrase from the zippy file.
     *
     * @return random phrase from the Zippy ArrayList
     */
    public String randomZippyGen() {
        int max = zippy.size();
        int index = rand.nextInt(max);
        return zippy.get(index);
    }
}
