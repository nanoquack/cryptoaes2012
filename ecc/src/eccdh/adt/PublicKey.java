/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import java.io.Serializable;

/**
 *
 * @author rolf
 */
public class PublicKey implements Serializable {
    
    /**
     * Der Public-Key. Dieser ist eine Punkt auf der elliptischen Kurve und wird
     * aus d * G berechnet, wobei d der Private Key ist und G der gemeinsame
     * Punkt auf der elliptischen Kurve.
     */
    private EllipticCurvePoint q;
    
    private CurveConstants.EC_CURVES curveId;
}
