/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.registry;

import eccdh.adt.EllipticCurveFactory.EC_CURVES;
import eccdh.adt.PublicKey;
import java.rmi.RemoteException;

/**
 *
 * @author Alex
 */
public class Registry implements RegistryInterface {

    @Override
    public boolean registerPublicKey(PublicKey key, EC_CURVES curve, String name) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public boolean removePublicKey(String name, EC_CURVES curve) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public boolean login(String name) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public boolean logout(String name) throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
