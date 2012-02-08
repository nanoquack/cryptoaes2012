/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import eccdh.algorithm.EncryptionException;
import java.math.BigInteger;

/*
 * Elliptic curve: y^2 = x^3 + a*x^2 + b a und b müssen 4*a^3+27*b^2 != 0
 * erfüllen, sonst kann es Singularitäten geben. @author: rolf
 */
public class EllipticCurve {
    /*
     * Pimzahl, die das finite Feld bestimmt.
     */

    public final BigInteger p;
    /**
     * a und b legen die zu verwendende elliptische Kurve über die Gleicung y^2
     * = x^3 + a*x^2 + b fest.
     */
    public final BigInteger a, b;
    /**
     * Der gemeinsame Basepoint G auf der durch a und b definierten Kurve.
     */
    public final EllipticCurvePoint g;
    /**
     * O-Text: a prime n which is the order of G siehe S. 25
     */
    public final BigInteger n;
    /**
     * O-Text: an integer h which is the cofactor siehe S. 25
     */
    public final BigInteger h;
    /**
     * The bit-length
     */
    public final int q;

    public EllipticCurve(BigInteger p, BigInteger a, BigInteger b, EllipticCurvePoint g, BigInteger n, BigInteger h, int q) {
        this.p = p;
        this.a = a;
        this.b = b;
        this.g = g;
        this.n = n;
        this.h = h;
        this.q = q;
    }
    
    public BigInteger func(BigInteger x) throws EncryptionException{
        
        
        BigInteger y = new BigInteger("0");
        return y;
    }
}
