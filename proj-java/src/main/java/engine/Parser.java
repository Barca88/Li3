package engine;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;

import javax.xml.stream.XMLInputFactory;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.File;
import java.util.Iterator;
import javax.xml.stream.*;
import javax.xml.namespace.QName;
import javax.xml.stream.events.XMLEvent;

public class Parser{
    public void parseTags(String file) {
        int ev;
        String text,Id,TagName = "nnnn";
        try{
            XMLInputFactory xmlif = XMLInputFactory.newInstance();
            xmlif.setProperty(XMLInputFactory.IS_COALESCING,true);
            XMLStreamReader xmlr = xmlif.createXMLStreamReader(new FileInputStream(new File(file)));

            while(xmlr.hasNext()) {
				ev = xmlr.next();
				if(ev == XMLStreamConstants.START_ELEMENT) {
					text = xmlr.getLocalName();
					if (text.equals("row")) {
						Id = xmlr.getAttributeValue(null, "Id");               
                        System.out.println("Id:" + Id);
						TagName = xmlr.getAttributeValue(null, "TagName");  
                        System.out.println("Nome:" + TagName);
                    }
				}
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (XMLStreamException e) {
            e.printStackTrace();
        }
   }
}
