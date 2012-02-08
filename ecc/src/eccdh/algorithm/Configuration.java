/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

import eccdh.adt.EllipticCurve;

/**
 *
 * @author rolf
 */
public class Configuration {
    //Key derivation function
    //Hash function for Key derivation function
    //Diffie Hellman privitive
    public final EllipticCurve curve;
    
    public Configuration(EllipticCurve curve){
        this.curve = curve;
    }
}
