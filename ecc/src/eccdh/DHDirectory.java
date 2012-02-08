/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh;

import eccdh.directory.Directory;
import eccdh.directory.DirectoryInterface;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

/**
 *
 * @author Alex
 */
public class DHDirectory {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            System.out.println("Starting directory service");
            DirectoryInterface directory = (DirectoryInterface)UnicastRemoteObject.exportObject(new Directory(), 0); 
            System.out.println("Directory service created");
            Registry registry = LocateRegistry.createRegistry(1099);
            System.out.println("Initializing registry");
            registry.rebind(Directory.SERVICE, directory);
            System.out.println("Binding directory service");
        } catch (RemoteException ex) {
            System.err.println(ex.getMessage());
        }
    }
}
