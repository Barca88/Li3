package engine;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;

import java.io.FileReader;
import java.util.Iterator;
import javax.xml.stream.*;
import javax.xml.namespace.QName;
import javax.xml.stream.events.XMLEvent;

public class Parser{
    public void parseTags(String file) {
        XMLInputFactory xmlif = XMLInputFactory.newInstance();
        //XMLEvent e;
        int e;
        String id;
        String tagName;
        String text;
        try{
            XMLStreamReader xmlr = xmlif.createXMLStreamReader(new FileReader(file));

            while(xmlr.hasNext()) {
				e = xmlr.next();
				if(e == XMLStreamConstants.START_ELEMENT) {
					text = xmlr.getLocalName();
					if (text.equals("row")) {
						id = xmlr.getAttributeValue(null, "Id");               
						tagName = xmlr.getAttributeValue(null, "TagName");  
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
