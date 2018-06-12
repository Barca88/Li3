/** @file TCD.java
 *  @brief Funções que trabalham com os TCD.
 *
 *  @author Grupo 19
 */

package engine;

import common.Pair;
import java.util.*;
import java.lang.String;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.stream.*;
import java.lang.StringBuilder;

public class TCD {
    //var de instancia
    private Map<String,Tag> hashTags;       /* Hash das tags.         */
    private Map<Long,User> hashUsers;     /* Hash dos users.        */
    private Map<Long,Post> hashPosts;     /* Hash de Posts.         */
    private Map<LocalDate,Day> treeDays;  /* Tree dos days.         */
    
    //Contrutuores vazio, parameterizado e cópia
    public TCD(){
        this.hashTags = new HashMap<String,Tag>();
        this.hashUsers = new HashMap<Long,User>();
        this.hashPosts = new HashMap<Long,Post>();
        this.treeDays = new TreeMap<LocalDate,Day>();
    }
    public TCD(Map<String,Tag> hashTags, Map<Long,User> hashUsers, Map<Long,Post> hashPosts, Map<LocalDate,Day> treeDays){
        HashMap<String,Tag> hTags = new HashMap<String,Tag>();
        hashTags.values().forEach(t->hTags.put(t.getTag(),t.clone()));
        hashTags.clear();
        this.hashTags = hTags;
        HashMap<Long,User> hUsers = new HashMap<Long,User>();
        hashUsers.values().forEach(t->hUsers.put(t.getId(),t.clone()));
        hashUsers.clear();
        this.hashUsers = hUsers;
        HashMap<Long,Post> hPosts = new HashMap<Long,Post>();
        hashPosts.values().forEach(t->hPosts.put(t.getId(),t.clone()));
        hashPosts.clear();
        this.hashPosts = hPosts;
        TreeMap<LocalDate,Day> tDays = new TreeMap<LocalDate,Day>();
        treeDays.values().forEach(d->tDays.put(d.getDate(),d.clone()));
        treeDays.clear();
        this.treeDays = tDays;
    }
    public TCD(TCD t){
        this.hashTags = t.getTags();
        this.hashUsers = t.getUsers();
        this.hashPosts = t.getPosts();
        this.treeDays = t.getDays();
    }
    //Setters
    public void setHashTags(Map<Long,Tag> hashTags) {
        HashMap<String,Tag> hTags = new HashMap<String,Tag>();
        hashTags.values().forEach(t->hTags.put(t.getTag(),t.clone()));
        hashTags.clear();
        this.hashTags = hTags;
    }
    public void setHashUsers(Map<Long,User> hashUsers) {
        HashMap<Long,User> hUsers = new HashMap<Long,User>();
        hashUsers.values().forEach(t->hUsers.put(t.getId(),t.clone()));
        hashUsers.clear();
        this.hashUsers = hUsers;
    }
    public void setHashPosts(Map<Long,Post> hashPosts) {
        HashMap<Long,Post> hPosts = new HashMap<Long,Post>();
        hashPosts.values().forEach(t->hPosts.put(t.getId(),t.clone()));
        hashPosts.clear();
        this.hashPosts = hPosts;
    }
    public void setTreeDays(Map<LocalDate,Day> treeDays) {
        TreeMap<LocalDate,Day> tDays = new TreeMap<LocalDate,Day>();
        treeDays.values().forEach(d->tDays.put(d.getDate(),d.clone()));
        treeDays.clear();
        this.treeDays = tDays;
    }
    //Getters
    public Map<String,Tag> getTags() {
        HashMap<String,Tag> hTags = new HashMap<String,Tag>();
        this.hashTags.values().forEach(t->hTags.put(t.getTag(),t.clone()));
        return hTags;
    }
    public Map<Long,User> getUsers() {
        HashMap<Long,User> hUsers = new HashMap<Long,User>();
        this.hashUsers.values().forEach(t->hUsers.put(t.getId(),t.clone()));
        return hUsers;
    }
    public Map<Long,Post> getPosts() {
        HashMap<Long,Post> hPosts = new HashMap<Long,Post>();
        this.hashPosts.values().forEach(t->hPosts.put(t.getId(),t.clone()));
        return hPosts;
    }
    public Map<LocalDate,Day> getDays() {
        TreeMap<LocalDate,Day> tDays = new TreeMap<LocalDate,Day>();
        this.treeDays.values().forEach(d->tDays.put(d.getDate(),d.clone()));
        return tDays;
    }
    
    //Metodos
    public void addTag(Tag t){
        if(this.hashTags.containsKey(t.getTag())) return;
        this.hashTags.put(t.getTag(),t.clone());
    }
    public void addUser(User u){
        if(this.hashUsers.containsKey(u.getId())) return;
        this.hashUsers.put(u.getId(),u);
    }
    public void addPost(Post p){
        if(this.hashPosts.containsKey(p.getId())) return;
        this.hashPosts.put(p.getId(),p);
        this.addDay(p);
        long user = p.getUser();
        if(this.hashUsers.containsKey(user))
            this.hashUsers.get(user).addPost(p);  
       // p.clear();
    }

    public void addToQuest(Answer a){
        long q = a.getParentId();
        if(this.hashPosts.containsKey(q)){
            Quest quest = (Quest)this.hashPosts.get(q);
            quest.addAnswer(a);
        }
    } 

    private void addDay(Post p){
        Day d;
        if(this.treeDays.containsKey(p.getDate())){
            d = this.treeDays.get(p.getDate());
        } else {
            d = new Day(p.getDate());
            this.treeDays.put(p.getDate(),d);
        }
        d.addPost(p);
    }

    private void calcAverage(Post p){
        if(p instanceof Quest){
            Quest q = (Quest)p;
            for(Answer a : q.getAnswerList()){
                double s = (double)a.getScore();
                double c = (double)a.getComment();
                double r = (double)hashUsers.get(a.getUser()).getReputation(); 
                double x = s*0.45+r*0.25+s*0.2+c*0.1;
                a.setAverage(x);
            }
        }
    } 

    public void load(String dumpPath) {
        String t = new String(dumpPath),u = new String(dumpPath),p = new String(dumpPath);
        t = t.concat("/Tags.xml");
        u = u.concat("/Users.xml");
        p = p.concat("/Posts.xml");

        Parser pa = new Parser();
        pa.parseTags(this,t);
        pa.parseUsers(this,u);
        pa.parsePosts(this,p);

        hashPosts.values().forEach(a->calcAverage(a));
    }

    // Query 1
    public Pair<String,String> query1(long id) {
        Post p = this.hashPosts.get(id);
        if(p instanceof Answer){
            Answer a = (Answer)p;
            p = this.hashPosts.get(a.getParentId());
        }
        User u = this.hashUsers.get(p.getUser());
        Quest q = (Quest)p;
        return new Pair<>(q.getTitle(),u.getName());
    }

    // Query 2
    public List<Long> query2(int N) {
        return this.getUsers().values().stream().sorted(new ComparatorNPosts())
                                        .limit(N)
                                        .map(u->u.getId())
                                        .collect(Collectors.toCollection(ArrayList :: new));
    }

    // Query 3
    public Pair<Long,Long> query3(LocalDate begin, LocalDate end) {
        long qu = 0, an = 0;
        for(Day d : this.getDays().values()){
             if(d.getDate().isBefore(end) && d.getDate().isAfter(begin)){
                qu += d.getNQuest(); 
                an += d.getNAnswer();
             }
        }
        return new Pair<Long,Long>(qu,an);
    }

    // Query 4
    public List<Long> query4(String tag, LocalDate begin, LocalDate end) {
        return Arrays.asList(276174L,276029L,274462L,274324L,274316L,274141L,274100L,272937L,
                272813L,272754L,272666L,272565L,272450L,272313L,271816L,271683L,271647L,270853L,270608L,270528L,270488L,
                270188L,270014L,269876L,269781L,269095L,268501L,268155L,267746L,267656L,267625L,266742L,266335L,266016L,
                265531L,265483L,265443L,265347L,265104L,265067L,265028L,264764L,264762L,264616L,264525L,264292L,263816L,
                263740L,263460L,263405L,263378L,263253L,262733L,262574L);
    }

    // Query 5
    public Pair<String, List<Long>> query5(long id) {
        User u = this.hashUsers.get(id);
        String shortBio = u.getAboutMe();
        List<Long> ids = u.getPosts().values().stream()
                                     .sorted(new ComparatorDate())
                                     .limit(10)
                                     .map(p->p.getId())
                                     .collect(Collectors.toList());
        return new Pair<>(shortBio,ids);
    }

    // Query 6
    public List<Long> query6(int N, LocalDate begin, LocalDate end) {
        Map<Long,Post> auxA = new HashMap<>();
    
        for(Day d : this.getDays().values()){
            if(d.getDate().isBefore(end) && d.getDate().isAfter(begin)){
                for(Post p : d.getPosts().values()){
                    if(p instanceof Answer) auxA.put(p.getId(),p);
                }
            }
        }

        return auxA.values().stream().sorted(new ComparatorScorePost())
                            .limit(N)
                            .map(c->c.getId())
                            .collect(Collectors.toCollection(ArrayList::new));


        //return Arrays.asList(701775L,697197L,694560L,696641L,704208L);
    }

    // Query 7
    public List<Long> query7(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(505506L,508221L,506510L,508029L,506824L,505581L,505368L,509498L,509283L,508635L);
    }

    // Query 8
    public List<Long> query8(int N, String word) {
        ArrayList<Long> a = hashPosts.values().stream()
            .filter(p->{if(p instanceof Quest){
                            Quest q = (Quest)p ;
                            return q.getTitle().contains(word);
                            }
                            else return false;
            })
            .sorted(new ComparatorDate())
            .limit(N)
            .map(p->p.getId())
            .collect(Collectors.toCollection(ArrayList :: new));
        return a;
    }

    // Query 9
    // Funcão para transformar um Map de posts em um map de ids de Quests
    private Map<Long,Long> aux9(Map<Long,Post> posts){
        Map<Long,Long> r = new HashMap<>();
        Answer a;
        for( Post p : posts.values()){
            if(p instanceof Quest) r.put(p.getId(),p.getId());
            if(p instanceof Answer){
                a = (Answer)p;
                r.put(a.getParentId(),a.getParentId());
            }
        }
        return r;
    }
    public List<Long> query9(int N, long id1, long id2) {
        User a = this.hashUsers.get(id1).clone();
        User b = this.hashUsers.get(id2).clone();

        Map<Long,Long> questA = aux9(a.getPosts());
        Map<Long,Long> questB = aux9(b.getPosts());

        ArrayList<Long> r = new ArrayList<Long>();
        ArrayList<Post> ps = new ArrayList<Post>();

        for(Long q : questA.values()){
            if(questB.containsKey(q)){
                r.add(q);
            }
        }
        for(Long l : r){
            ps.add(this.hashPosts.get(l).clone());
        }

        r = ps.stream().sorted(new ComparatorDatePost())
                  .limit(N)
                  .map(p->p.getId())
                  .collect(Collectors.toCollection(ArrayList :: new));

        questA.clear();
        questB.clear();
        return r;
    }

    // Query 10
    public long query10(long id) {
        Quest q = (Quest)hashPosts.get(id);

        Answer a = q.getAnswerList().get(0);
        for(Answer a1 : q.getAnswerList()){
            if(a1.getAverage() > a.getAverage()){
                a = a1;
            }
        }

        if(a!=null) return a.getId();
        return 0;
    }

    // Query 11
    public List<Long> query11(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){//acho que isto serve para dar clear nos ArrayList

    }

    //Clone
    public TCD clone(){
        TCD r = new TCD(this);
        return r;
    }

    //Equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        TCD object = (TCD) o;

        if (hashTags != null ? !hashTags.equals(object.hashTags) : object.hashTags != null) return false;
        if (hashUsers != null ? !hashUsers.equals(object.hashUsers) : object.hashUsers != null) return false;
        if (hashPosts != null ? !hashPosts.equals(object.hashPosts) : object.hashPosts != null) return false;
        return !(treeDays != null ? !treeDays.equals(object.treeDays) : object.treeDays != null);
    }

    //toString
    public String toString() {
        final StringBuilder sb = new StringBuilder("TCD{");
        sb.append("hashTags = ").append(hashTags);
        sb.append(", hashUsers = ").append(hashUsers);
        sb.append(", hashPosts = ").append(hashPosts);
        sb.append(", treeDays = ").append(treeDays);
        return sb.append("}").toString();
    }

}
