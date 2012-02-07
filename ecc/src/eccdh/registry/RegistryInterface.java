/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.registry;

import eccdh.adt.EllipticCurveFactory.EC_CURVES;
import eccdh.adt.PublicKey;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

/**
 *
 * @author Alex
 */
public interface RegistryInterface extends Remote {
    /**
     * register the public key of the client to the registry
     * 
     * @param key the public key of the client
     * @param curve the curve for which the key has been created
     * @param name the name of the client
     * @return true if the key has been registered, false otherwise (i.e. if the name is already taken)
     * @throws RemoteException 
     */
    public boolean registerPublicKey(PublicKey key, EC_CURVES curve, String name) throws RemoteException;
    
    /**
     * remove the public key of the client from the registry
     * 
     * @param name the name of the client
     * @param curve the curve for which the key should be removed
     * @return true if the key was removed, false otherwise (i.e. if the key or person does not exist)
     * @throws RemoteException 
     */
    public boolean removePublicKey(String name, EC_CURVES curve) throws RemoteException;
       
    /**
     * retrieve a list of all registered names
     * 
     * @return a list of all registered names
     * @throws RemoteException 
     */
    public List<String> getNames() throws RemoteException;
    
    /**
     * retrieve a list of all curves for the given name
     * 
     * @param name the username
     * @return a list of all registered curves for the name
     * @throws RemoteException 
     */
    public List<EC_CURVES> getCurves(String name) throws RemoteException;
    
    /**
     * get the public key for the registered name and given curve
     * 
     * @param name the username
     * @param curve the curve
     * @return the public key for the username and curve
     * @throws RemoteException 
     */
    public PublicKey getKey(String name, EC_CURVES curve) throws RemoteException;
}
