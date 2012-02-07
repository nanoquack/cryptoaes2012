/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.registry;

import eccdh.adt.EllipticCurveFactory;
import eccdh.adt.PublicKey;
import java.rmi.Remote;
import java.rmi.RemoteException;

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
    public boolean registerPublicKey(PublicKey key, EllipticCurveFactory.EC_CURVES curve, String name) throws RemoteException;
    
    /**
     * remove the public key of the client from the registry
     * 
     * @param name the name of the client
     * @param curve the curve for which the key should be removed
     * @return true if the key was removed, false otherwise (i.e. if the key or person does not exist)
     * @throws RemoteException 
     */
    public boolean removePublicKey(String name, EllipticCurveFactory.EC_CURVES curve) throws RemoteException;
    
    /**
     * change the persons status to online
     * 
     * @param name the username
     * @return true if the person exists and the status is online
     * @throws RemoteException 
     */
    public boolean login(String name) throws RemoteException;
    
    /**
     * change the persons status to offline
     * 
     * @param name the username
     * @return true if the person exists and is offline now
     * @throws RemoteException 
     */
    public boolean logout(String name) throws RemoteException;
}
