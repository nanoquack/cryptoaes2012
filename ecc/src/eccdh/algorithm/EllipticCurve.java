/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

import eccdh.adt.EllipticCurvePoint;

/*
 * Elliptic curve: y^2 = x^3 + a*x^2 + b
 * a und b müssen 4*a^3+27*b^2 != 0
 * erfüllen, sonst kann es Singularitäten geben. @author: rolf
 */
public class EllipticCurve {
    /*
     * Pimzahl, die das finite Feld bestimmt. 
     */
    private int p;
    
    /**
     * a und b legen die zu verwendende elliptische Kurve über die Gleicung y^2 = x^3 + a*x^2 + b fest. 
     */
    private int a, b;
    
    /**
     * Der gemeinsame Basepoint G auf der durch a und b definierten Kurve. 
     */
    private EllipticCurvePoint G;
    
    /**
     * O-Text: a prime n which is the order of G
     * siehe S. 25
     */
    private int n;
    
    /**
     * O-Text: an integer h which is the cofactor
     * siehe S. 25
     */
    private int h;
}
