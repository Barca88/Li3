package engine;
import engine.User;

import java.util.Comparator;
import java.time.LocalDate;


public class ComparatorNPosts implements Comparator<User>{
    public int compare(User a, User b){

        int o = a.getNposts()-b.getNposts();
        if(o > 0) return -1;
        if(o < 0) return 1;
        if(a.getId() < b.getId()) return -1;
        return 1;

	}
}
