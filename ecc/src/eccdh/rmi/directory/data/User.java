/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.rmi.directory.data;

import eccdh.adt.CurveConstants.EC_CURVES;
import eccdh.adt.PublicKey;
import java.io.Serializable;
import java.util.Hashtable;
import java.util.List;

/**
 *
 * @author Alex
 */
public class User implements Serializable {
    private String name;
    
    private Hashtable<EC_CURVES, PublicKey> keyTable;
    
    public User(String name) {
        this.name = name;
        keyTable = new Hashtable<EC_CURVES, PublicKey>();
    }
    
    public String getName() {
        return name;
    }
       
    public boolean hasKey(EC_CURVES curve) {
        return keyTable.containsKey(curve);
    }
    
    public boolean removeKey(EC_CURVES curve) {
        if (keyTable.remove(curve) != null) {
            return true;
        }
        
        return false;
    }
    
    
    public boolean addKey(EC_CURVES curve, PublicKey key) {
        if (!hasKey(curve)) {
            keyTable.put(curve, key);
            return true;
        }
        
        return false;
    }
    
    public PublicKey getKey(EC_CURVES curve) {
        return keyTable.get(curve);
    }
    
    public List<EC_CURVES> getCurves() {
        return (List<EC_CURVES>) keyTable.keySet();
    }
}
