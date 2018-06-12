/** @file User.java
 *  @brief Funções que trabalham com os User.
 *
 *  @author Grupo 19
 */

package engine;

import java.util.HashMap;
import java.lang.StringBuilder;

public class User {
    //var. de instancia
    private long id;               /* Id do user. */
    private String name;           /* DisplayName de um user. */
    private String aboutMe;        /* Short bio de um user. */
    private long reputation;       /* Reputação de um user. */
    private int Nposts;            /* Nº de posts de um user. */
    private HashMap<Long,Post> posts; /* Lista dos posts que um user fez. */
    //Contrutores
    public User(long id){
        this.id = id;
        this.name = "";
        this.aboutMe = "";
        this.reputation = 0;
        this.Nposts = 0;
        this.posts = new HashMap<Long,Post>();
    }
    public User(long id, String name, String aboutMe, long reputation, int Nposts, HashMap<Long,Post> posts) {
        this.id = id;
        this.name = name;
        this.aboutMe = aboutMe;
        this.reputation = reputation;
        this.Nposts = Nposts;
        HashMap<Long,Post> l = new HashMap<Long,Post>();
        posts.values().forEach(c->l.put(c.getId(),c.clone()));
        posts.clear();
        this.posts = l;
    }
    public User(User u){
        this.id = u.getId();
        this.name = u.getName();
        this.aboutMe = u.getAboutMe();
        this.reputation = u.getReputation();
        this.Nposts = u.getNposts();
        this.posts = u.getPosts();
    }
    //Setters
    public void setId(long id) {
        this.id = id;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setAboutMe(String aboutMe) {
        this.aboutMe = aboutMe;
    }
    public void setReputation(long reputation) {
        this.reputation = reputation;
    }
    public void setNposts(int Nposts) {
        this.Nposts = Nposts;
    }
    public void setPosts(HashMap<Long,Post> p) {
        HashMap<Long,Post> l = new HashMap<Long,Post>();
        p.values().forEach(c->l.put(c.getId(),c.clone()));
        p.clear();
        this.posts.clear();
        this.posts = l;
    }
    //Getters
    public long getId() {
        return id;
    }
    public String getName() {
        return name;
    }
    public String getAboutMe() {
        return aboutMe;
    }
    public long getReputation() {
        return reputation;
    }
    public int getNposts() {
        return Nposts;
    }
    public HashMap<Long,Post> getPosts() {
        HashMap<Long,Post> l = new HashMap<Long,Post>();
        this.posts.forEach((k,c)->l.put(c.getId(),c.clone()));
        return l;
    }
    //Metodos
    public void addPost(Post p){
        this.Nposts += 1;
        this.posts.put(p.getId(),p.clone());
    }

    public User clone(){
        User r = new User(this);
        return r;
    }

    public String toString() {
        final StringBuilder sb = new StringBuilder("User{");
        sb.append("id = ").append(getId());
        sb.append(", name = ").append(getName());
        sb.append(", aboutMe = ").append(getAboutMe());
        sb.append(", reputation = ").append(getReputation());
        sb.append(", Nposts = ").append(getNposts());
        sb.append(", posts = ").append(getPosts());
        return sb.append("}").toString();
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        User object = (User) o;

        if (id != object.id) return false;
        if (name != null ? !name.equals(object.name) : object.name != null) return false;
        if (aboutMe != null ? !aboutMe.equals(object.aboutMe) : object.aboutMe != null) return false;
        if (reputation != object.reputation) return false;
        if (Nposts != object.Nposts) return false;
        return !(posts != null ? !posts.equals(object.posts) : object.posts != null);
    }
}


