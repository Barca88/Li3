/** @file Tag.java
 *  @brief Funções que trabalham com as Tag.
 *
 *  @author Grupo 19
 */

package engine;
import java.lang.StringBuilder;
public class Tag {
    //var. de instancia
    private long id;    /* Id da tag. */
	private String tag; /* Tag pretendida. */
    private int n_used; /* Numero de vezes utilizada */
    //Construtores
    public Tag(long id){
        this.id = id;
        this.tag = "";
        this.n_used = 0;
    }
    public Tag(long id, String tag, int n_used) {
        this.id = id;
        this.tag = tag;
        this.n_used = n_used;
    }
    public Tag(Tag t){
        this.id = t.getId();
        this.tag = t.getTag();
        this.n_used = t.getN_used();
    }
    //Setters
    public void setId(long id) {
        this.id = id;
    }
    public void setTag(String tag) {
        this.tag = tag;
    }
    public void setN_used(int n_used) {
        this.n_used = n_used;
    }
    //Getters
    public long getId() {
        return id;
    }
    public String getTag() {
        return tag;
    }
    public int getN_used() {
        return n_used;
    }
    //Metodos
    public Tag clone(){
        Tag r = new Tag(this);
        return r;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Tag object = (Tag) o;

        if (id != object.id) return false;
        if (tag != null ? !tag.equals(object.tag) : object.tag != null) return false;
        return !(n_used != object.n_used);
    }

    public String toString() {
        final StringBuilder sb = new StringBuilder("Tag{");
        sb.append("id = ").append(getId());
        sb.append(", tag = ").append(getTag());
        sb.append(", n_used = ").append(getN_used());
        return sb.append("}").toString();
    }
}

