/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

import eccdh.adt.CurveConstants;
import eccdh.adt.EllipticCurve;
import eccdh.adt.EllipticCurveFactory;
import eccdh.adt.PublicKey;
import eccdh.algorithm.impl.DiffieHellmanImpl;
import org.junit.*;
import static org.junit.Assert.*;

/**
 *
 * @author rolf
 */
public class DiffieHellmanTest {
    
    public DiffieHellmanTest() {
    }
    
    @Test
    public void testGenerateKeys() throws EncryptionException{
        EllipticCurve curve = EllipticCurveFactory.newInstance(CurveConstants.EC_CURVES.secp192k1);
        Configuration config = new  Configuration(curve);
        DiffieHellman dh = new DiffieHellmanImpl(config);
        
        PublicKey pubKey = dh.generateKeys();
        assertNotNull("Generated Public Key is null", pubKey);
    }
    
    @Test
    public void testStringEncryption(){
        
    }
    
    @Test
    public void testStringDecryption(){
        
    }
    
       @Test
    public void testByteEncryption(){
        
    }
    
    @Test
    public void testByteDecryption(){
        
    } 
}
