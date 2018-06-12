/** @file ComparatorDate.java
 *  @brief Funções que trabalham com os Day e Post.
 *
 *  @author Grupo 19
 */

package engine;

import java.util.Comparator;
import java.time.LocalDate;

public class ComparatorDate implements Comparator<Post>{

	public int compare (Post p1, Post p2){
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
