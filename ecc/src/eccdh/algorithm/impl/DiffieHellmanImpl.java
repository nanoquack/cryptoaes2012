/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm.impl;

import eccdh.adt.CurveConstants;
import eccdh.adt.EllipticCurve;
import eccdh.adt.PrivateKey;
import eccdh.adt.PublicKey;
import eccdh.algorithm.Configuration;
import eccdh.algorithm.DiffieHellman;
import eccdh.algorithm.EncryptionException;
import java.math.BigInteger;
import java.util.Random;

/**
 *
 * @author rolf
 */
public class DiffieHellmanImpl extends DiffieHellman {

    protected PublicKey pubKey;
    protected PrivateKey prvKey;

    public DiffieHellmanImpl(Configuration config) {
        super(config);
    }

    @Override
    public PublicKey generateKeys() throws EncryptionException {

        //Randomly or pseudorandomly select an integer d in the interval [1;n-1]
        //Calculate Q = dG
        //Output (d;Q)
        generatePrivateKey();
        generatePublicKey();
        return this.pubKey;
    }

    private void generatePrivateKey() {
        BigInteger n = new BigInteger(curve.n.bitLength() - 1, new Random());
        this.prvKey = new PrivateKey(n);
    }
    
    private void generatePublicKey(){
        if(this.prvKey!=null){
            
        }
    }

    @Override
    public PublicKey getPublicKey() throws EncryptionException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public String encrypt(String plaintText) throws EncryptionException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public String decrypt(String cypherText) throws EncryptionException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Byte[] encrypt(Byte[] plainBytes) throws EncryptionException {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public Byte[] decrypt(Byte[] plainBytes) throws EncryptionException {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
