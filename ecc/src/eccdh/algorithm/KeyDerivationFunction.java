/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

import eccdh.adt.OctetString;

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
    public abstract OctetString execute(OctetString z, int keydatalen, OctetString sharedInfo) throws EncryptionException;
}
