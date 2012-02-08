/*  
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.registry;

import eccdh.registry.data.Client;
import java.rmi.RemoteException;
import java.util.Hashtable;
import java.util.List;

/**
 *
 * @author Alex
 */
public class Registry implements RegistryInterface {

    private Hashtable<String, Client> clientTable;
    
    public Registry() {
        clientTable = new Hashtable<String, Client>();
    }
    
    @Override
    public synchronized boolean registerClient(Client client) throws RemoteException {
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
    public synchronized Client getClient(String name) throws RemoteException {
        return clientTable.get(name);
    }
}
