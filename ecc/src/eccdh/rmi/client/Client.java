/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.rmi.client;

import eccdh.gui.GUI;
import java.rmi.RemoteException;

/**
 *
 * @author Alex
 */
public class Client implements ClientInterface {

    private GUI gui;
    
    public Client(GUI gui) {
        this.gui = gui;
    }
    
    @Override
    public void receiveMessage(String text, String from) throws RemoteException {
        
    }
}
