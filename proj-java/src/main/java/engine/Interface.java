/** @file Interface.java
 *  @brief Funções que trabalham com o Interface.
 *
 *  @author Grupo 19
 */

package engine;
import common.Pair;
import common.MyLog;
import li3.TADCommunity;
import engine.TCD;

import java.util.List;
import java.time.LocalDate;
import java.lang.StringBuilder;
public class Interface implements TADCommunity {
    private TCD tcd;

    public Interface(){
        this.tcd = new TCD();
    }
    public Interface(TCD t){
        this.tcd = t.clone();
    }
    public Interface(Interface i){
        this.tcd = i.getTcd();
    }
    //Setters
    public void setTcd(TCD tcd) {
        this.tcd = tcd.clone();
        //tcd.clear()  --TODO
    }
    //Getters
    public TCD getTcd() {
        return tcd.clone();
    }
    //Load
    public void load(String file){
        this.tcd.load(file);
    }
    // Query 1
    public Pair<String,String> infoFromPost(long id){
        return this.tcd.query1(id);
    }
    // Query 2
    public List<Long> topMostActive(int N) {
        return this.tcd.query2(N);
    }
    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        return this.tcd.query3(begin,end);
    }
    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        return this.tcd.query4(tag,begin,end);
    }
    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        return this.tcd.query5(id);
    }
    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return this.tcd.query6(N,begin,end);
    }
    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return this.tcd.query7(N,begin,end);
    }
    // Query 8
    public List<Long> containsWord(int N, String word) {
        return this.tcd.query8(N,word);
    }
    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return this.tcd.query9(N,id1,id2);
    }
    // Query 10
    public long betterAnswer(long id) {
        return this.tcd.query10(id);
    }
    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return this.tcd.query11(N,begin,end);
    }
    //Clear
    public void clear(){
    }
    //Clone
    public Interface clone(){
        Interface r = new Interface(this);
        return r;
    }
    //Equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Interface object = (Interface) o;

        return !(tcd != null ? !tcd.equals(object.tcd) : object.tcd != null);
    }
    //toString
    public String toString() {
        final StringBuilder sb = new StringBuilder("Interface{");
        sb.append(", tcd = ").append(getTcd());
        return sb.append("}").toString();
    }
}
