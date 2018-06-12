
package engine;

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorAverage implements Comparator<Answer>{

	public int compare (Answer p1, Answer p2){
        double a1 = p1.getAverage();
        double a2 = p2.getAverage();
        if (a1 > a2)
            return 1;
        if (a1 < a2)
            return -1;
        return 0;
    }
}

