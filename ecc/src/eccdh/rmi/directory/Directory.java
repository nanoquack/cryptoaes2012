/*  
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.rmi.directory;

import eccdh.rmi.directory.data.User;
import java.rmi.RemoteException;
import java.util.Hashtable;
import java.util.List;

/**
 *
 * @author Alex
 */
public class Directory implements DirectoryInterface {

    public static final String SERVICE = "DHDirectory";
    
    private Hashtable<String, User> clientTable;
    
    public Directory() {
        clientTable = new Hashtable<String, User>();
    }
    
    @Override
    public synchronized boolean registerClient(User client) throws RemoteException {
        if (!clientTable.containsKey(client.getName())) {
            System.out.println("Client " + client.getName() + " registered with " + client.getCurves().size() + " keys");
            clientTable.put(client.getName(), client);
            return true;
        } 
        
        System.out.println("Client name " + client.getName() + " already taken");
        return false;
    }

    @Override
    public synchronized boolean removeClient(String name) throws RemoteException {
        if (clientTable.contains(name)) {
            clientTable.remove(name);
            return true;
        }
        
        System.out.println("Client " + name + " does not exist");
        return false;
    }

    @Override
    public synchronized List<String> getNames() throws RemoteException {
        return (List<String>) clientTable.keySet();
    }

    @Override
    public synchronized User getClient(String name) throws RemoteException {
        return clientTable.get(name);
    }
}
