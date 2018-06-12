package engine;

import java.util.Comparator;
import java.time.LocalDate;


public class ComparatorDateDay implements Comparator<Day>{

    public int compare (Day da1, Day da2){
        LocalDate d1 = da1.getDate();
        LocalDate d2 = da2.getDate();

        if (d1.compareTo(d2) > 0) 
            return -1;
        if (d1.compareTo(d2) < 0) 
            return 1;
        return 0;
    }
}
