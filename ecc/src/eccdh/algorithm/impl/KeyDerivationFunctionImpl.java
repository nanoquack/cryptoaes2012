/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm.impl;

import eccdh.algorithm.EncryptionException;
import eccdh.algorithm.KeyDerivationFunction;
import java.math.BigInteger;

/**
 *
 * @author rolf
 */
public class KeyDerivationFunctionImpl extends KeyDerivationFunction{

    @Override
    public BigInteger execute(BigInteger z, int keydatalen, BigInteger sharedInfo) throws EncryptionException{
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
