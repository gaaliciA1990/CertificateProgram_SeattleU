/*
 * Author: Scott McMaster
 * Version: 1.0
 * Date: 1/13/21
 * Class: CPSC 5011-02
 */

package hw1;

import java.time.LocalTime;

enum PartsOfDay {MORNING, AFTERNOON, EVENING, NIGHT}

class DayPart {
    private PartsOfDay dp;

    /**
     * Constructor for user inputted locat time
     *
     * @param lt local time as indicated by user
     */
    public DayPart(LocalTime lt) {
        int hour = lt.getHour();

        if (hour >= 5 && hour < 12) {
            dp = PartsOfDay.MORNING;
        } else if (hour >= 12 && hour < 17) {
            dp = PartsOfDay.AFTERNOON;
        } else if (hour >= 17 && hour < 22) {
            dp = PartsOfDay.EVENING;
        } else {
            dp = PartsOfDay.NIGHT;
        }
    }

    /**
     * Constructor for default local time
     */
    public DayPart() {
        this(LocalTime.now());
    }

    /**
     * Method to get the string indicating the local time
     *
     * @return the enum for local time
     */
    public PartsOfDay getDayPart() {
        return dp;
    }

    /**
     * The method is overwriting the toString function so we can print the
     * words associated with the enum values
     *
     * @return a string value for the enum
     */
    @Override
    public String toString() {
        switch (dp) {
            case MORNING:
                return "morning";
            case AFTERNOON:
                return "afternoon";
            case EVENING:
                return "evening";
            case NIGHT:
                return "night";
            default:
                return "unknown";
        }
    }

}
