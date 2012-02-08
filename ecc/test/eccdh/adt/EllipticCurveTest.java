/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import eccdh.algorithm.EncryptionException;
import java.math.BigInteger;
import org.junit.*;
import static org.junit.Assert.*;

/**
 *
 * @author rolf
 */
public class EllipticCurveTest {

    public EllipticCurveTest() {
    }

    @Test
    public void testCurveFormula() throws EncryptionException {
        EllipticCurve curve = EllipticCurveFactory.newInstance(CurveConstants.EC_CURVES.secp192k1);
        BigInteger[] x = {
            new BigInteger("0")};
        BigInteger[] y = {
            new BigInteger("0")};
        for (int i = 0; i < x.length; i++) {
//            BigInteger resY = curve.func(x[i]);
//            assertEquals("Calculated Point does not match expected", y, resY);
        }
    }
}
