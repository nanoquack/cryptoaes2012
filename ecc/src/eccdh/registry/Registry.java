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
    public synchronized boolean registerPublicKey(PublicKey key, EC_CURVES curve, String name) throws RemoteException {
        if (!clientTable.containsKey(name)) {
            clientTable.put(name, new Client(name, curve, key));
            return true;
        } else {
            Client client = clientTable.get(name);
            return client.addKey(curve, key);
        }
    }

    @Override
    public synchronized boolean removePublicKey(String name, EC_CURVES curve) throws RemoteException {
        if (clientTable.contains(name)) {
            Client client = clientTable.get(name);
            return client.removeKey(curve);
        }
        
        return false;
    }

    @Override
    public synchronized List<String> getNames() throws RemoteException {
        return (List<String>) clientTable.keySet();
    }

    @Override
    public synchronized List<EC_CURVES> getCurves(String name) throws RemoteException {
        if (clientTable.contains(name)) {
            Client client = clientTable.get(name);
            return client.getCurves();
        }
        
        return null;
    }

    @Override
    public synchronized PublicKey getKey(String name, EC_CURVES curve) throws RemoteException {
        if (clientTable.contains(name)) {
            Client client = clientTable.get(name);
            return client.getKey(curve);
        }
        
        return null;
    }
}
