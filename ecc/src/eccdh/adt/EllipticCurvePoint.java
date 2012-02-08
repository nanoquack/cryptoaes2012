/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import java.math.BigInteger;

/**
 *
 * @author rolf
 */
public class EllipticCurvePoint {

    public final EllipticCurve curve;
    public final BigInteger x;
    public final BigInteger y;

    public EllipticCurvePoint(BigInteger octet) {
        String value = octet.toString(16);
        value = value.substring(1, value.length());
        String xValue = value.substring(0, (int) (value.length() / 2));
        String yValue = value.substring((int) (value.length() / 2), value.length());
        this.x = new BigInteger(xValue, 16);
        this.y = new BigInteger(yValue, 16);
        this.curve = curve;
    }

    public EllipticCurvePoint(BigInteger x, BigInteger y) {
        this.x = x;
        this.y = y;
        this.curve = curve;
    }

    public BigInteger toOctet() {
        String value = "04";
        value = value.concat(this.x.toString(16));
        value = value.concat(this.y.toString(16));

        BigInteger octet = new BigInteger(value, 16);
        return octet;
    }

    @Override
    public boolean equals(Object b) {
        if (b instanceof EllipticCurvePoint) {
            EllipticCurvePoint pointB = (EllipticCurvePoint) b;
            if ((this.x.equals(pointB.x)) && (this.y.equals(pointB.y))) {
                return true;
            }
        }
        return false;
    }

    public EllipticCurvePoint add(EllipticCurvePoint b) {

        throw new UnsupportedOperationException("Not yet implemented");
    }

    public EllipticCurvePoint doub(BigInteger a, BigInteger p) {
        //(x1,y1)+(x1,y1)=(x3,y3)

        //lambda=(3*x1^2+a)/(2*y1)
        BigInteger lambda = x.pow(2).multiply(new BigInteger("3")).add(a);
        lambda = lambda.divide(y.multiply(new BigInteger("2")));
        lambda = lambda.mod(p);

        //x3=(lambda^2 - 2*x1) mod p
        BigInteger xValue = lambda.pow(2).subtract(x.multiply(new BigInteger("2)")));
        xValue = xValue.mod(p);

        //y3=(lambda*(x1-x3)-y1) mod p
        BigInteger yValue = lambda.multiply((x.subtract(xValue).subtract(y)));
        yValue = yValue.mod(p);

        EllipticCurvePoint result = new EllipticCurvePoint(xValue, yValue);
        return result;
    }

    public EllipticCurvePoint scalarMul(BigInteger k, BigInteger a, BigInteger p) {
        return scalarMulImpl(new EllipticCurvePoint(this.x, this.y), k, a, p);
    }
    
    private EllipticCurvePoint scalarMulImpl(EllipticCurvePoint point, BigInteger k, BigInteger a, BigInteger p){
                //f(P, n) is
        //   if n = 0 then return 0           # computation complete
        //   else if n mod 2 = 1 then
        //      P + f(P, n-1)                 # addition when n is odd
        //   else
        //      f(2P, n/2)                    # doubling when n is even
        
        if(k.equals(BigInteger.ZERO)){
            return new EllipticCurvePoint(BigInteger.ZERO, BigInteger.ZERO);
        }
        else{
            if (k.mod(new BigInteger("2")).equals(BigInteger.ONE)) {
                return point.add(scalarMulImpl(point, k.subtract(BigInteger.ONE), a, p));
            }
            else{
                return scalarMulImpl(point.doub(a, p), k.divide(new BigInteger("2")), a, p);
            }
        }
    }
}
