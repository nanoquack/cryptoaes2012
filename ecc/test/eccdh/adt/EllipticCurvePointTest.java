/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import java.math.BigInteger;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author rolf
 */
public class EllipticCurvePointTest {

    @Test
    public void testEllipticCurvePointToOctetString() {
        EllipticCurve curve = EllipticCurveFactory.newInstance(CurveConstants.EC_CURVES.secp192k1);
        //BigInteger Math.log(curve.p) / Math.log(2))).intValue();
//        int infiniteLength = 1;
//        int compressedLength = ((int) Math.ceil(Math.log(curve.q) / Math.log(2)) + 1);
        int uncompressedLength = 2 * ((int) Math.ceil(Math.log(curve.q) / Math.log(2)) + 1);

        EllipticCurvePoint[] ecval = {new EllipticCurvePoint(new BigInteger("1"), new BigInteger("2")),
            new EllipticCurvePoint(new BigInteger("7"), new BigInteger("8"))};
        String[] res = {"040000000100000002", "040000000700000010"};

        for (int i = 0; i < ecval.length; i++) {
            EllipticCurvePoint ec = ecval[i];
            BigInteger os = new BigInteger(res[i]);
            BigInteger osres = ec.toOctet();
            assertEquals("Conversion " + (i + 1) + " not correct", os, osres);
        }
    }

    @Test
    public void testOctetStringToEllipticCurvePoint() {
        String[] octval = {};
        EllipticCurvePoint[] res = {};

        for (int i = 0; i < octval.length; i++) {
            BigInteger os = new BigInteger(octval[i]);
            EllipticCurvePoint ec = res[i];
            EllipticCurvePoint ecpoint = new EllipticCurvePoint(os);
            assertEquals("Conversion " + (i + 1) + " not correct", ec, ecpoint);
        }
    }
}
