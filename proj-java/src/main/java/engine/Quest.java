import java.util.ArrayList;

public class Quest extends Post{
    private String title;
    private ArrayList<String> tags;
    private int answer_c;
    private ArrayList answerList;

    public Quest(long id, LocalDate creationDate, int score, long ownerUserId, int comment_c, String title, ArrayList<String> tags, int answer_c, Arraylist<long> answerList){
        super(id,creationDate,score,ownerUserId,comment_c);
        this.title = title;
        this.tags = tags;
        this.answer_c = answer_c;
        this.answerList = answerList;
    }

