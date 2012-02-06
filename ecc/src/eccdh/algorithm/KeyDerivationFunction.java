/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

import java.math.BigInteger;

/**
 *
 * @author rolf
 */
public abstract class KeyDerivationFunction {
    /**
     * Führt die KDF aus. 
     * @param z die shared secret value
     * @param keydatalen Länge der zu erzeugenden keyring data
     * @param sharedInfo zu sharende daten
     * @return 
     */
    public abstract BigInteger execute(BigInteger z, int keydatalen, BigInteger sharedInfo) throws EncryptionException;
}
