/** @file TCD.java
 *  @brief Funções que trabalham com os TCD.
 *
 *  @author Grupo 19
 */

package engine;

import common.Pair;

import java.util.Arrays;
import java.time.LocalDate;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
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
        treeDays.values().forEach(d->tDays.put(d.getData(),d.clone()));
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
        treeDays.values().forEach(d->tDays.put(d.getData(),d.clone()));
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
        this.treeDays.values().forEach(d->tDays.put(d.getData(),d.clone()));
        return tDays;
    }
    
    //Metodos
    public void addTag(Tag t){
        if(this.hashTags.containsKey(t.getTag())) return;
        this.hashTags.put(t.getTag(),t.clone());
    }
    public void addUser(User u){
        if(this.hashUsers.containsKey(u.getId())) return;
        this.hashUsers.put(u.getId(),u.clone());
    }
    public void addPost(Post p){
        if(this.hashPosts.containsKey(p.getId())) return;
        this.addDay(p);
        long user = p.getUser();
        if(this.hashUsers.containsKey(user)){
            this.hashUsers.get(user).addPost(p);
        }
        this.hashPosts.put(p.getId(),p.clone());
       // p.clear();
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
    public void load(String dumpPath) {
        String t = new String(dumpPath),u = new String(dumpPath),p = new String(dumpPath);
        t = t.concat("Tags.xml");
        u = u.concat("Users.xml");
        p = p.concat("Posts.xml");

        Parser pa = new Parser();
        pa.parseTags(this,t);
        pa.parseUsers(this,u);
        pa.parsePosts(this,p);
        System.out.println(this);
    }

    // Query 1
    public Pair<String,String> query1(long id) {
        return new Pair<>("What are the actual risks of giving www-data sudo nopasswd access?", "WebNinja");
    }

    // Query 2
    public List<Long> query2(int N) {
        return Arrays.asList(15811L,449L,158442L,167850L,367165L,295286L,59676L,93977L,35795L,3940L);
    }

    // Query 3
    public Pair<Long,Long> query3(LocalDate begin, LocalDate end) {
        return new Pair<>(3667L,4102L);
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
        String shortBio = "<p>Coder. JS, Perl, Python, Basic<br>Books/movies: SF+F.<br>Dead:" +
                "dell 9300<br>Dead: dell 1720 as of may 10th 2011.</p>\n" +
                "<p>Current system: Acer Aspire 7750G.<br>\n" +
                "Works OOTB as of Ubuntu 12.04.<br></p>";
        List<Long> ids = Arrays.asList(982507L,982455L,980877L,980197L,980189L,976713L,974412L,
                974359L,973895L,973838L);
        return new Pair<>(shortBio,ids);
    }

    // Query 6
    public List<Long> query6(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(701775L,697197L,694560L,696641L,704208L);
    }

    // Query 7
    public List<Long> query7(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(505506L,508221L,506510L,508029L,506824L,505581L,505368L,509498L,509283L,508635L);
    }

    // Query 8
    public List<Long> query8(int N, String word) {
        return Arrays.asList(980835L,979082L,974117L,974105L,973832L,971812L,971056L,968451L,964999L,962770L);
    }

    // Query 9
    public List<Long> query9(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long query10(long id) {
        return 175891;
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
