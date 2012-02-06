/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

import eccdh.adt.EllipticCurve;
import eccdh.adt.PrivateKey;
import eccdh.adt.PublicKey;

/**
 *
 * @author rolf
 */
public abstract class DiffieHellmanPrimitive {

    /**
     * Führt die Diffie-Hellman Primitive aus. 
     *
     * @param curve Die gemeinsame Elliptische Kurve
     * @param privkey Der zu verwendende Private Key
     * @param pubkey Der zu verwendende Public Key 
     * @return
     */
    public abstract int execute(EllipticCurve curve, PrivateKey privkey, PublicKey pubkey) throws EncryptionException;
}
