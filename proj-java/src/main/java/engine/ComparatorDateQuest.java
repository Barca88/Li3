package engine;

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorDateQuest implements Comparator<Quest>{

	public int compare (Quest p1, Quest p2){
        LocalDate d1 = p1.getDate();
        LocalDate d2 = p2.getDate();
        if (d1.compareTo(d2) > 0)
            return -1;
        if (d1.compareTo(d2) < 0)
            return 1;
        if(p1.getId() < p2.getId())
            return 1;
        if(p1.getId() > p2.getId())
            return -1;
        return 0;
    }
}
