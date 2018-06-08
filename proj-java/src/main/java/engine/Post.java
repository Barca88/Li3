import java.time.LocalDate;

public abstract class Post{
    //variaveis de instancia
    private long id;
    private LocalDate creationDate;
    private int score;
    private long ownerUserId;
    private int comment_c;

    //unico metodo de criação necessario
    public Post(long id,LocalDate creationDate, int score, long ownerUserId, int comment_c){
        this.id = id;
        this.creationDate = creationDate.clone();
        this.score = score;
        this.ownerUserId = ownerUserId;
        this.comment_c = comment_c;
    }
    //getters
    public get_id(){
        return id;
    }
    public get_date(){
        return creationDate.clone();
    }
    public get_score(){
        return score;
    }
    public get_owner_id(){
        return ownerUserId;
    }
    public get_comment_c(){
        return comment_c;
    }
    //clone
    public abstract Post clone();
    //equals
    public boolean equals(Object obj){
        if(obj == this)
            return true;
        if(obj == null || obj.getClass() != this.getClass())
            return false;
        Post p = (Post) obj;
        return p.get_id() == this.id &&
               p.get_date().equals(this.creationDate) &&
               p.get_score() == this.score &&
               p.get_owner_id() == this.ownerUserId &&
               p.get_comment_c == this.comment_c;
    }
}
