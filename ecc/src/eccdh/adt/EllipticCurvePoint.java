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
    public final BigInteger x;
    public final BigInteger y;
    
    public EllipticCurvePoint(BigInteger octet){
        String value = octet.toString(16);
        value = value.substring(1, value.length());
        String xValue = value.substring(0,(int)(value.length()/2));
        String yValue = value.substring((int)(value.length()/2), value.length());
        this.x = new BigInteger(xValue, 16);
        this.y = new BigInteger(yValue, 16);
    }
    
    public EllipticCurvePoint(BigInteger x, BigInteger y){
        this.x = x;
        this.y = y;
    }
    
    public BigInteger toOctet(){
        String value = "04";
        value = value.concat(this.x.toString(16));
        value = value.concat(this.y.toString(16));
        
        BigInteger octet = new BigInteger(value, 16);
        return octet;
    }
    
    @Override
    public boolean equals(Object b){
        if(b instanceof EllipticCurvePoint){
            EllipticCurvePoint pointB = (EllipticCurvePoint)b;
            if((this.x.equals(pointB.x)) && (this.y.equals(pointB.y))){
                return true;
            }
        }
        return false;
    }
}
