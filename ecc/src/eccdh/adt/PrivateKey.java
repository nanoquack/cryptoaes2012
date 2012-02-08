/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import java.math.BigInteger;

/**
 *
 * @author rolf
 */
public class PrivateKey {
    /**
     * Der Private Key zu einer elliptischen Kurve und einem gemeinsamen Punkt. 
     */
    public final BigInteger d;
    
    public PrivateKey(BigInteger d){
        this.d = d;
    }
}
