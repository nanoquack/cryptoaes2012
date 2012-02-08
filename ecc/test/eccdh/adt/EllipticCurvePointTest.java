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
    public void testEllipticCurvePointToUncompressedOctetString() {
//        int uncompressedLength = 2 * ((int) Math.ceil(Math.log(CurveConstants.secp192k_1_q) / Math.log(2)) + 1);

        EllipticCurvePoint[] ecval = {
            new EllipticCurvePoint(new BigInteger("DB4FF10E" + "C057E9AE" + "26B07D02" + "80B7F434" + "1DA5D1B1" + "EAE06C7D", 16),
            new BigInteger("9B2F2F6D" + "9C5628A7" + "844163D0" + "15BE8634" + "4082AA88" + "D95E2F9D", 16))
        };
        BigInteger[] expected = {CurveConstants.secp192k1_G};

        for (int i = 0; i < ecval.length; i++) {
            EllipticCurvePoint ec = ecval[i];
            BigInteger expRes = expected[i];
            BigInteger res = ec.toOctet();
            assertEquals("Conversion " + (i + 1) + " not correct", expRes, res);
        }
    }

    @Test
    public void testUncompressedOctetStringToEllipticCurvePoint() {
        BigInteger[] octval = {CurveConstants.secp192k1_G};
        EllipticCurvePoint[] res = {
            new EllipticCurvePoint(new BigInteger("DB4FF10E" + "C057E9AE" + "26B07D02" + "80B7F434" + "1DA5D1B1" + "EAE06C7D", 16),
            new BigInteger("9B2F2F6D" + "9C5628A7" + "844163D0" + "15BE8634" + "4082AA88" + "D95E2F9D", 16))
        };

        for (int i = 0; i < octval.length; i++) {
            EllipticCurvePoint ec = res[i];
            EllipticCurvePoint ecpoint = new EllipticCurvePoint(octval[i]);
            assertEquals("Conversion " + (i + 1) + " not correct", ec, ecpoint);
        }
    }

    @Test
    public void testPointAddition() {
        EllipticCurvePoint[] firstPoint = {
            new EllipticCurvePoint(new BigInteger("10"), new BigInteger("10"))
        };
        EllipticCurvePoint[] secondPoint = {
            new EllipticCurvePoint(new BigInteger("5"), new BigInteger("5"))
        };
        EllipticCurvePoint[] expectedPoint = {
            new EllipticCurvePoint(new BigInteger(""), new BigInteger(""))
        };
        for(int i=0;i<firstPoint.length;i++){
            EllipticCurvePoint p1 = firstPoint[i];
            EllipticCurvePoint p2 = secondPoint[i];
            EllipticCurvePoint expected = expectedPoint[i];
            EllipticCurvePoint result = p1.add(p2);
            assertEquals("Point is not the expected one", expectedPoint, result);
        }
    }
    
    @Test
    public void testPoindDoubling(){
        //(x1,y1)+(x1,y2)=(x3,y3)
        //x3=(lambda^2 - 2*x1) mod p
        //y3=(lambda*(x1-x3)-y1) mod p
        //lambda=(3*x1^2+a)/(2*y1)
                EllipticCurvePoint[] firstPoint = {
            new EllipticCurvePoint(new BigInteger("10"), new BigInteger("10"))
        };
        EllipticCurvePoint[] secondPoint = {
            new EllipticCurvePoint(new BigInteger("5"), new BigInteger("5"))
        };
        EllipticCurvePoint[] expectedPoint = {
            new EllipticCurvePoint(new BigInteger(""), new BigInteger(""))
        };
        for(int i=0;i<firstPoint.length;i++){
            EllipticCurvePoint p1 = firstPoint[i];
            EllipticCurvePoint p2 = secondPoint[i];
            EllipticCurvePoint expected = expectedPoint[i];
            EllipticCurvePoint result = p1.doub(CurveConstants.secp192k1_a, CurveConstants.secp192k1_p);
            assertEquals("Point is not the expected one", expectedPoint, result);
        }
    }

    @Test
    public void testScalarMultiplication() {
    }
}
