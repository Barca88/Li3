package engine;

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorScorePost implements Comparator<Post>{

	public int compare (Post p1, Post p2){
        int o = p1.getScore() - p2.getScore();
        if (o > 0)
            return -1;
        if (o < 0)
            return 1;
        if(p1.getId() < p2.getId())
            return 1;
        if(p1.getId() > p2.getId())
            return -1;
        return 0;
    }
}
