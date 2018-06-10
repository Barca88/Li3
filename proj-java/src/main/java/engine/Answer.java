import java.time.LocalDate;
import java.lang.StringBuilder;

public class Answer extends Post{
    //var. de instancia
    private long parentId; /* Id da quest à qual esta answer responde. */
    private float average; /* variavel que define a qualidade da resposta */

    public Answer(long id, LocalDate data, int score, long ownerUserId, int comment_c, long parentId) {
        super(id,data,score,ownerUserId,comment_c);        
        this.parentId = parentId;
        this.average = 0;
    }
    public Answer(Answer a){
        super(a);
        this.parentId = g.getParentId();
        this.average = g.getAverage();
    }
    //Setters
    public void setParentId(long parentId) {
        this.parentId = parentId;
    }
    public void setAverage(float average) {
        this.average = average;
    }
    //Getters
    public float getAverage() {
        return average;
    }
    public long getParentId() {
        return parentId;
    }

    //Metodos
    public Answer clone(){
        Answer r = new Answer(this);
        return r;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Answer object = (Answer) o;

        if (parentId != object.parentId) return false;
        if (!super.equals(object)) return false;
        return !(Float.compare(average, object.average) != 0);
    }

    public String toString() {
        final StringBuilder sb = new StringBuilder("Answer{");
        sb.append("parentId = ").append(getParentId());
        sb.append(", average = ").append(getAverage());
        return sb.append("}").toString();
    }

}
