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
    private LocalDate date; /* Data de um dia. */
    private Map<Long,Post> posts; /* Lista de posts. */
    private int nQuest; /* Nº de quest num dia. */
    private int nAnswer; /* Nº de answer num dia. */
    //Construtores
    public Day(LocalDate d){
        this.date = d;
        this.posts = new HashMap<Long,Post>();
        this.nQuest = 0;
        this.nAnswer = 0;
    }
    public Day(LocalDate date,Map<Long,Post> map,int nQuest,int nAnswer){
        this.date = date;
        HashMap<Long,Post> m = new HashMap<Long,Post>();
        map.values().forEach(p->m.put(p.getId(),p.clone()));
        this.posts = m;
        this.nQuest = nQuest;
        this.nAnswer = nAnswer;
    }
    public Day(Day d){
        this.date = d.getDate();
        this.posts = d.getPosts();
        this.nQuest = d.getNQuest();
        this.nAnswer = d.getNAnswer();
    }
    //Setters
    public void setData(LocalDate data) {
        this.date = data;
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
    public LocalDate getDate() {
        return date;
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
    public void addPost(Post p){
        if(p instanceof Quest){
            this.nQuest += 1;
        }else {
            this.nAnswer += 1;
        }
        this.posts.put(p.getId(),p.clone());
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

        if (date != null ? !date.equals(object.date) : object.date != null) return false;
        if (posts != null ? !posts.equals(object.posts) : object.posts != null) return false;
        if (nQuest != object.nQuest) return false;
return !(nAnswer != object.nAnswer);
    }
    //toString
    public String toString() {
        final StringBuilder sb = new StringBuilder("Day{");
        sb.append("data = ").append(getDate());
        sb.append(", posts = ").append(getPosts());
        sb.append(", nQuest = ").append(getNQuest());
        sb.append(", nAnswer = ").append(getNAnswer());
        return sb.append("}").toString();
    }
}
