/** @file Quest.java
 *  @brief Funções que trabalham com as Quest.
 *
 *  @author Grupo 19
 */

package engine;
import java.util.ArrayList;
import java.time.LocalDate;
import java.lang.StringBuilder;

public class Quest extends Post{
    //var. de instancia
    private String title; /* Título da pergunta. */
    private String tags; /* Tag da pergunta. */
    private int answer_c; /* Nº de answer. */
    private ArrayList<Long> answerList; /* Lista das answer de uma quest. */
    //Construtores
    public Quest(long id){
        super(id,LocalDate.now(),0,-2,0);
        this.title = "";
        this.tags = "";
        this.answer_c = 0;
        this.answerList = new ArrayList<Long>();
    }
    public Quest(long id, LocalDate date, int score, long ownerUserId, int comment_c, String title, String tags, int answer_c){
        super(id,date,score,ownerUserId,comment_c);
        this.title = title;
        this.tags = tags;
        this.answer_c = answer_c;
        this.answerList = new ArrayList<Long>(); 
    }
    public Quest(Quest q){
        super(q);
        this.title = q.getTitle();
        this.tags = q.getTags();
        this.answer_c = q.getAnswer_c();
        this.answerList = q.getAnswerList();
    }
    //Setters
    public void setTitle(String title) {
        this.title = title;
    }
    public void setTags(String tags) {
        this.tags = tags;
    }
    public void setAnswer_c(int answer_c) {
        this.answer_c = answer_c;
    }
    public void setAnswerList(ArrayList<Long> answerList) {
        ArrayList<Long> l = new ArrayList<Long>();
        answerList.forEach(c->l.add(c));
        answerList.clear();
        this.answerList = l;
    }

    //Getters
    public String getTitle() {
        return title;
    }
    public String getTags() {
        return tags;
    }
    public int getAnswer_c() {
        return answer_c;
    }
    public ArrayList<Long> getAnswerList() {
        ArrayList<Long> l = new ArrayList<Long>();
        this.answerList.forEach(c->l.add(c));
        return l;
    }
    //Metodos
    public Quest clone(){
        Quest q = new Quest(this);
        return q;
    }

    //Equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Quest object = (Quest) o;

        if (title != null ? !title.equals(object.title) : object.title != null) return false;
        if (tags != null ? !tags.equals(object.tags) : object.tags != null) return false;
        if (answer_c != object.answer_c) return false;
        if (!super.equals(object)) return false;
        return !(answerList != null ? !answerList.equals(object.answerList) : object.answerList != null);
    }

    //toString
    public String toString() {
        final StringBuilder sb = new StringBuilder("Quest{");
        sb.append("title = ").append(getTitle());
        sb.append(", tags = ").append(getTags());
        sb.append(", answer_c = ").append(getAnswer_c());
        sb.append(", answerList = ").append(getAnswerList());
        return sb.append("}").toString();
    }
}
