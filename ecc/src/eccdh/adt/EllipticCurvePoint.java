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
    
    public EllipticCurvePoint(OctetString octet){
        throw new UnsupportedOperationException("not yet implemented");
    }
    
    public EllipticCurvePoint(BigInteger x, BigInteger y){
        this.x = x;
        this.y = y;
    }
    
    public OctetString toOctetString(){
        throw new UnsupportedOperationException("not yet implemented");
    }
    
    @Override
    public String toString(){
        throw new UnsupportedOperationException("not yet implemented");
    }
    
    @Override
    public boolean equals(Object b){
        throw new UnsupportedOperationException("not yet implemented");
    }
}
