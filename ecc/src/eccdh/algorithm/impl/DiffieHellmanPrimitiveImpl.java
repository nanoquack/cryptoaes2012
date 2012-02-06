/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm.impl;

import eccdh.adt.EllipticCurve;
import eccdh.adt.PrivateKey;
import eccdh.adt.PublicKey;
import eccdh.algorithm.DiffieHellmanPrimitive;
import eccdh.algorithm.EncryptionException;

/**
 *
 * @author rolf
 */
public class DiffieHellmanPrimitiveImpl extends DiffieHellmanPrimitive{

    @Override
    public int execute(EllipticCurve curve, PrivateKey privkey, PublicKey pubkey) throws EncryptionException{
        throw new UnsupportedOperationException("Not supported yet.");
    }
    
}
