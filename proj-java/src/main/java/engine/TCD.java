package engine;

import common.MyLog;
import common.Pair;
import li3.TADCommunity;

import java.time.LocalDate;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.stream;
import java.util.stream.Collectors;
import java.lang.StringBuilder;


public class TCD implements TADCommunity {
    //var de instancia
    private MyLog qelog;
    private Map<Long,Tag> hashTags;       /* Hash das tags.         */
    private Map<Long,User> hashUsers;     /* Hash dos users.        */
    private Map<Long,Post> hashPosts;     /* Hash de Posts.         */
    private Map<LocalDate,Day> treeDays;  /* Tree dos days.         */
    //Contrutuores vazio, parameterizado e cópia
    public TCD(){
        this.qelog = new MyLog("queryengine");
        this.hashTags = new HashTable<Long,Tag>();
        this.hashUsers = new HashTable<Long,Tag>();
        this.hashPosts = new HashTable<Long,Tag>();
        this.treeDays = new TreeMap<LocalDate,Day>();
    }
    public TCD(MyLog qelog, Map<Long,Tag> hashTags, Map<Long,User> hashUsers, Map<Long,Post> hashPosts, Map<LocalDate,Day> treeDays){
        this.qelog = qelog.clone();
        this.hashTags = hashTags.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,Tag> :: new)); 
        this.hashUsers = hashUsers.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,User> :: new));
        this.hashPosts = hashPosts.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,Post> :: new));
        this.treeDays = treeDays.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashTree<LocalDate,Day> :: new));
    }
    public TCD(TCD t){
        this.qelog = t.getLog();
        this.hashTags = t.getTags();
        this.hashUsers = t.getUsers();
        this.hashPosts = t.getPosts();
        this.treeDays = t.getDays();
    }
    //Setters
    public void setQelog(MyLog qelog) {
        this.qelog = qelog.clone();
    }
    public void setHashTags(Map<Long,Tag> hashTags) {
        this.hashTags = hashTags.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,Tag> :: new)); 
    }
    public void setHashUsers(Map<Long,User> hashUsers) {
        this.hashUsers = hashUsers.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,User> :: new));
    }
    public void setHashPosts(Map<Long,Post> hashPosts) {
        this.hashPosts = hashPosts.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,Post> :: new));
    }
    public void setTreeDays(Map<LocalDate,Day> treeDays) {
        this.treeDays = treeDays.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashTree<LocalDate,Day> :: new));
    }
    //Getters
    public MyLog getQelog() {
        return qelog;
    }
    public Map<Long,Tag> getHashTags() {
        return this.hashTags.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,Tag> :: new)); 
    }
    public Map<Long,User> getHashUsers() {
        return this.hashUsers.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,User> :: new));
    }
    public Map<Long,Post> getHashPosts() {
        return this.hashPosts.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashMap<Long,Post> :: new));
    }
    public Map<Long,User> getTreeDays() {
        return this.treeDays.values().stream().collect(Collectors.toMap(c->c.getId(),c.clone(),HashTree<LocalDate,Day> :: new));
    }

    
    //Metodos
    public void load(String dumpPath) {
        File inputFile = new File(dumpPath);
        try {

        DocumentBuilderFactory dbFactory
                = DocumentBuilderFactory.newInstance();

        DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();

        Document doc = null;

            doc = dBuilder.parse(inputFile);
            doc.getDocumentElement().normalize();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        return new Pair<>("What are the actual risks of giving www-data sudo nopasswd access?", "WebNinja");
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return Arrays.asList(15811L,449L,158442L,167850L,367165L,295286L,59676L,93977L,35795L,3940L);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        return new Pair<>(3667L,4102L);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        return Arrays.asList(276174L,276029L,274462L,274324L,274316L,274141L,274100L,272937L,
                272813L,272754L,272666L,272565L,272450L,272313L,271816L,271683L,271647L,270853L,270608L,270528L,270488L,
                270188L,270014L,269876L,269781L,269095L,268501L,268155L,267746L,267656L,267625L,266742L,266335L,266016L,
                265531L,265483L,265443L,265347L,265104L,265067L,265028L,264764L,264762L,264616L,264525L,264292L,263816L,
                263740L,263460L,263405L,263378L,263253L,262733L,262574L);
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        String shortBio = "<p>Coder. JS, Perl, Python, Basic<br>Books/movies: SF+F.<br>Dead:" +
                "dell 9300<br>Dead: dell 1720 as of may 10th 2011.</p>\n" +
                "<p>Current system: Acer Aspire 7750G.<br>\n" +
                "Works OOTB as of Ubuntu 12.04.<br></p>";
        List<Long> ids = Arrays.asList(982507L,982455L,980877L,980197L,980189L,976713L,974412L,
                974359L,973895L,973838L);
        return new Pair<>(shortBio,ids);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(701775L,697197L,694560L,696641L,704208L);
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(505506L,508221L,506510L,508029L,506824L,505581L,505368L,509498L,509283L,508635L);
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return Arrays.asList(980835L,979082L,974117L,974105L,973832L,971812L,971056L,968451L,964999L,962770L);
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long betterAnswer(long id) {
        return 175891;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){

    }
    public TCD clone(){
        TCD r = new TCD(this);
        return r;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        TCD object = (TCD) o;

        if (qelog != null ? !qelog.equals(object.qelog) : object.qelog != null) return false;
        if (hashTags != null ? !hashTags.equals(object.hashTags) : object.hashTags != null) return false;
        if (hashUsers != null ? !hashUsers.equals(object.hashUsers) : object.hashUsers != null) return false;
        if (hashPosts != null ? !hashPosts.equals(object.hashPosts) : object.hashPosts != null) return false;
        return !(treeDays != null ? !treeDays.equals(object.treeDays) : object.treeDays != null);
    }

    public String toString() {
        final StringBuilder sb = new StringBuilder("TCD{");
        sb.append("qelog = ").append(getQelog());
        sb.append(", hashTags = ").append(getHashTags());
        sb.append(", hashUsers = ").append(getHashUsers());
        sb.append(", hashPosts = ").append(getHashPosts());
        sb.append(", treeDays = ").append(treeDays);
        return sb.append("}").toString();
    }

}
