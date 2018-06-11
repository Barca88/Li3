package engine;
import engine.TCD;
import engine.Tag;
import engine.User;
import engine.Post;
import engine.Quest;
import engine.Answer;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;

import java.io.FileReader;
import java.util.Iterator;
import javax.xml.stream.*;
import javax.xml.namespace.QName;
import javax.xml.stream.events.XMLEvent;

public class Parser{
    public void parseTags(TCD d,String file) {
        XMLInputFactory xmlif = XMLInputFactory.newInstance();
        int e;
        String id;
        String tagName;
        String text;
        try{
            XMLStreamReader xmlr = xmlif.createXMLStreamReader(new FileReader(file));
            Tag t;
            while(xmlr.hasNext()) {
				e = xmlr.next();
				if(e == XMLStreamConstants.START_ELEMENT) {
					text = xmlr.getLocalName();
					if (text.equals("row")) {
						id = xmlr.getAttributeValue(null, "Id");               
						tagName = xmlr.getAttributeValue(null, "TagName");  
                        t = new Tag(Long.parseLong(id),tagName,0);
                        data.addTag(t);
                    }
				}
            }
        } catch (FileNotFoundException eis) {
            eis.printStackTrace();
        } catch (XMLStreamException eis) {
            eis.printStackTrace();
        }
   }
   public void parseUsers(TCD d,String file) {
        XMLInputFactory xmlif = XMLInputFactory.newInstance();
        int e;
        String id;
        String name;
        String aboutMe;
        String reputation;
        try{
            XMLStreamReader xmlr = xmlif.createXMLStreamReader(new FileReader(file));
            User u; 
            while(xmlr.hasNext()) {
				e = xmlr.next();
				if(e == XMLStreamConstants.START_ELEMENT) {
					text = xmlr.getLocalName();
					if (text.equals("row")) {
						id = xmlr.getAttributeValue(null, "Id");               
						reputation = xmlr.getAttributeValue(null, "Reputation");  
						name = xmlr.getAttributeValue(null, "DisplayName");  
						aboutMe = xmlr.getAttributeValue(null, "AboutMe");  

                        u = new User(Long.parseLong(id),name,aboutMe,Long.parseLong(reputation),0,new ArryList<Posts>());
                        data.addUser(u);
                    }
				}
            }
        } catch (FileNotFoundException eis) {
            eis.printStackTrace();
        } catch (XMLStreamException eis) {
            eis.printStackTrace();
        }
    }
    public void parsePost(TCD d,String file) {
        XMLInputFactory xmlif = XMLInputFactory.newInstance();
        int e;
        String id;
        String date;
        String score;
        String userId;
        String nComment;
        String pId;
        String title;
        String tags;
        String nAnswer;
        try{
            XMLStreamReader xmlr = xmlif.createXMLStreamReader(new FileReader(file));
            Quest q;
            Answer a;
            while(xmlr.hasNext()) {
				e = xmlr.next();
				if(e == XMLStreamConstants.START_ELEMENT) {
					text = xmlr.getLocalName();
					if (text.equals("row")) {
                        id = xmlr.getAttributeValue(null, "Id");
                        date = xmlr.getAttributeValue(null, "CreationDate");               
                        score = xmlr.getAttributeValue(null, "Score");
                        userId = xmlr.getAttributeValue(null, "OwnerUserId");
                        nComment = xmlr.getAttributeValue(null, "CommentCount");
                        String[] s = date.split("T");

                        if(xmlr.getAttributeValue(null,"PostTypeId") == "1"){
                            title = xmlr.getAttributeValue(null, "Title");
                            tags = xmlr.getAttributeValue(null, "Tags");
                            nAnswer = xmlr.getAttributeValue(null, "AnswerCount");

                            q = new Quest(Long.parseLong(id), LocalDate.parse(s[0]), Integer.parseInt(score), 
                                        Long.parseLong(userId), Integer.parseInt(nComment), 
                                        title, tags, Integer.parseInt(nAnswer));
                            data.addPost(q);
                        } else if(xmlr.getAttributeValue(null,"PostTypeId") == "2"){
                            pId = xmlr.getAttributeValue(null,"ParentId");
                            a = new Answer(Long.parseLong(id),LocalDate.parse(s[0]), Integer.parseInt(score),
                                        Long.parseLong(userId), Integer.parseInt(nComment),Long.parseLong(pId));
                            data.addPost(a);
                        }
                    }
				}
            }
        } catch (FileNotFoundException eis) {
            eis.printStackTrace();
        } catch (XMLStreamException eis) {
            eis.printStackTrace();
        }
   }
}
