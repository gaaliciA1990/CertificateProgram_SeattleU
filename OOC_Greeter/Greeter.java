/*
 * Author: Scott McMaster
 * Version: 1.0
 * Date: 1/13/21
 * Class: CPSC 5011-02
 */

package hw1;

import java.io.FileNotFoundException;
import java.util.Map;

public class Greeter {
    
    private Template template;
    
    public Greeter(String s) {
        template = new Template(s);
    }
    
    public String getGreeting(Map<String, String> vars) throws FileNotFoundException {
        return template.instantiate(vars);
    }
    
}
