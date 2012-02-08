/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

/**
 *
 * @author Alex
 */
public class DHRegistry {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.getRegistry();
        } catch (RemoteException ex) {
            ex.printStackTrace();
        }
    }
}
