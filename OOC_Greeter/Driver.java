/*
 * Author: Scott McMaster, Alicia Garcia
 * Version: 2.0
 * Date: 1/13/21
 * Class: CPSC 5011-02
 */

package hw1;

import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;

/**
 * The class to implements the commands from other methods
 */
public class Driver {

    /**
     * The main method will print a greeting for the user, using either the hashmap
     * data inputted by the program, or a randomly generated zippy line.
     *
     * @param args  A string array containing the command line arguments.
     * @throws FileNotFoundException when invalid file path is found
     */
    public static void main(String[] args) throws FileNotFoundException {
        String template = "Good $daypart $name - that's a nice $color shirt.";

        Map<String, String> templateVars = new HashMap<String, String>();
        templateVars.put("$name", "Daenerys");
        templateVars.put("$color", "green");
        
        Greeter g = new Greeter(template);
        String greeting = g.getGreeting(templateVars);
        System.out.print(greeting);

        template = "$newline";
        g = new Greeter(template);
        greeting = g.getGreeting(templateVars);
        System.out.print(greeting);

        template = "Zippy quote: $zippy";
        g = new Greeter(template);
        greeting = g.getGreeting(templateVars);
        System.out.println(greeting);
    }
}
