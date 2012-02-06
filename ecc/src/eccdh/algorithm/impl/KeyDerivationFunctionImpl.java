/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm.impl;

import eccdh.adt.OctetString;
import eccdh.algorithm.EncryptionException;
import eccdh.algorithm.KeyDerivationFunction;

/**
 *
 * @author rolf
 */
public class KeyDerivationFunctionImpl extends KeyDerivationFunction{

    @Override
    public OctetString execute(OctetString z, int keydatalen, OctetString sharedInfo) throws EncryptionException{
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
