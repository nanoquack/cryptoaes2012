/*  
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.registry;

import eccdh.adt.EllipticCurveFactory.EC_CURVES;
import eccdh.adt.PublicKey;
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
            clientTable.put(client.getName(), client);
            return true;
        } 
        
        return false;
    }

    @Override
    public synchronized boolean removeClient(String name) throws RemoteException {
        if (clientTable.contains(name)) {
            clientTable.remove(name);
            return true;
        }
        
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
