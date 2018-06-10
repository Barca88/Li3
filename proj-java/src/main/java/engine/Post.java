import java.time.LocalDate;
import java.lang.StringBuilder;

public abstract class Post{
    //variaveis de instancia
    private long id;
    private LocalDate creationDate;
    private int score;
    private long ownerUserId;
    private int comment_c;

    public Post(long id){
        this.id = id;
        this.creationDate = LocalDate.now();
        this.score = 0;
        this.ownerUserId = -2;
        this.comment_c =0;
    }
    //unico metodo de criação necessario
    public Post(long id,LocalDate creationDate, int score, long ownerUserId, int comment_c){
        this.id = id;
        this.creationDate = creationDate.clone();
        this.score = score;
        this.ownerUserId = ownerUserId;
        this.comment_c = comment_c;
    }
    public Post(Post p){
        this.id = p.getId();
        this.creationDate = p.getDate();
        this.score = p.getScore();
        this.ownerUserId = p.getUser();
        this.comment_c = p.getComment();
    }
    //Setters
    public void setId(long id) {
        this.id = id;
    }
    public void setCreationDate(LocalDate creationDate) {
        this.creationDate = creationDate;
    }
    public void setScore(int score) {
        this.score = score;
    }
    public void setOwnerUserId(long ownerUserId) {
        this.ownerUserId = ownerUserId;
    }
    public void setComment_c(int comment_c) {
        this.comment_c = comment_c;
    }

    //getters
    public long getId(){
        return id;
    }
    public LocalDate getDate(){
        return creationDate.clone();
    }
    public int getScore(){
        return score;
    }
    public long getUser(){
        return ownerUserId;
    }
    public int getComment(){
        return comment_c;
    }
    //clone
    public abstract Post clone();

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Post object = (Post) o;

        if (id != object.id) return false;
        if (creationDate != null ? !creationDate.equals(object.creationDate) : object.creationDate != null) return false;
        if (score != object.score) return false;
        if (ownerUserId != object.ownerUserId) return false;
        return !(comment_c != object.comment_c);
    }

    public String toString() {
        final StringBuilder sb = new StringBuilder("Post{");
        sb.append("id = ").append(id);
        sb.append(", creationDate = ").append(creationDate);
        sb.append(", score = ").append(score);
        sb.append(", ownerUserId = ").append(ownerUserId);
        sb.append(", comment_c = ").append(comment_c);
        return sb.append("}").toString();
    }

}
