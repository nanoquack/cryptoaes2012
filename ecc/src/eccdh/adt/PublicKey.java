/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import eccdh.adt.EllipticCurvePoint;

/**
 *
 * @author rolf
 */
public class PublicKey {

    /**
     * Der Public-Key. Dieser ist eine Punkt auf der elliptischen Kurve und wird
     * aus d * G berechnet, wobei d der Private Key ist und G der gemeinsame
     * Punkt auf der elliptischen Kurve.
     */
    private EllipticCurvePoint q;
}
