/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.registry;

import eccdh.adt.EllipticCurveFactory.EC_CURVES;
import eccdh.adt.PublicKey;
import java.io.Serializable;
import java.util.Hashtable;
import java.util.List;

/**
 *
 * @author Alex
 */
public class Client implements Serializable {
    private String name;
        
    private Hashtable<EC_CURVES, PublicKey> keyTable;
    
    public Client(String name, EC_CURVES curve, PublicKey key) {
        this.name = name;
        keyTable = new Hashtable<EC_CURVES, PublicKey>();
        keyTable.put(curve, key);
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
