/** @file Day.java
 *  @brief Funções que trabalham com os Days.
 *
 *  @author Grupo 19
 */

package engine;

import engine.Post;

import java.time.LocalDate;
import java.util.Map;
import java.util.HashMap;
import java.lang.StringBuilder;

public class Day{
    //var. de inststancia
    private LocalDate data; /* Data de um dia. */
    private Map<Long,Post> posts; /* Lista de posts. */
    private int nQuest; /* Nº de quest num dia. */
    private int nAnswer; /* Nº de answer num dia. */
    //Construtores
    public Day(){
        this.data = LocalDate.now();
        this.posts = new HashMap<Long,Post>();
        this.nQuest = 0;
        this.nAnswer = 0;
    }
    public Day(LocalDate date,Map<Long,Post> map,int nQuest,int nAnswer){
        this.data = date;
        HashMap<Long,Post> m = new HashMap<Long,Post>();
        map.values().forEach(p->m.put(p.getId(),p.clone()));
        this.posts = m;
        this.nQuest = nQuest;
        this.nAnswer = nAnswer;
    }
    public Day(Day d){
        this.data = d.getData();
        this.posts = d.getPosts();
        this.nQuest = d.getNQuest();
        this.nAnswer = d.getNAnswer();
    }
    //Setters
    public void setData(LocalDate data) {
        this.data = data;
    }
    public void setPosts(Map<Long,Post> posts) {
        HashMap<Long,Post> m = new HashMap<Long,Post>();
        posts.values().forEach(p->m.put(p.getId(),p.clone()));
        posts.clear();
        this.posts = m;
    }
    public void setNQuest(int nQuest) {
        this.nQuest = nQuest;
    }
    public void setNAnswer(int nAnswer) {
        this.nAnswer = nAnswer;
    }
    //Gettrs
    public LocalDate getData() {
        return data;
    }
    public Map<Long,Post> getPosts() {
        HashMap<Long,Post> m = new HashMap<Long,Post>();
        this.posts.values().forEach(p->m.put(p.getId(),p.clone()));
        return m;
    }
    public int getNQuest() {
        return nQuest;
    }
    public int getNAnswer() {
        return nAnswer;
    }
    //Clone
    public Day clone(){
        Day r = new Day(this);
        return r;
    }
    //Equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Day object = (Day) o;

        if (data != null ? !data.equals(object.data) : object.data != null) return false;
        if (posts != null ? !posts.equals(object.posts) : object.posts != null) return false;
        if (nQuest != object.nQuest) return false;
return !(nAnswer != object.nAnswer);
    }
    //toString
    public String toString() {
        final StringBuilder sb = new StringBuilder("Day{");
        sb.append("data = ").append(getData());
        sb.append(", posts = ").append(getPosts());
        sb.append(", nQuest = ").append(getNQuest());
        sb.append(", nAnswer = ").append(getNAnswer());
        return sb.append("}").toString();
    }
}
