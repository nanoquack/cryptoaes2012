/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.rmi.client;

import eccdh.rmi.directory.data.User;
import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author Alex
 */
public interface ClientInterface extends Remote {
    
    /**
     * receive a message from a user
     * 
     * @param text the message
     * @param from the username from the sender
     * @throws RemoteException 
     */
    public void receiveMessage(String text, String from) throws RemoteException;
    //public void sendBytes(byte[] bytes) throws RemoteException;
}
