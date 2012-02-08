/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import java.io.Serializable;

/**
 * Der Public-Key. Dieser ist eine Punkt auf der elliptischen Kurve und wird aus
 * d * G berechnet, wobei d der Private Key ist und G der gemeinsame Punkt auf
 * der elliptischen Kurve.
 *
 * @author rolf
 */
public class PublicKey implements Serializable {

    public final EllipticCurvePoint q;
    public final CurveConstants.EC_CURVES curveId;

    public PublicKey(CurveConstants.EC_CURVES curveId, EllipticCurvePoint q) {
        this.q = q;
        this.curveId = curveId;
    }
}
