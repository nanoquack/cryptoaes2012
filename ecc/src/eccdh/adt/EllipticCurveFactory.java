/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import eccdh.adt.CurveConstants.EC_CURVES;

/**
 *
 * @author rolf
 */
public class EllipticCurveFactory {

    public static EllipticCurve newInstance(EC_CURVES type) {
        EllipticCurve curve = null;

        if (type == EC_CURVES.secp192k1) {
            EllipticCurvePoint g = new EllipticCurvePoint(CurveConstants.secp192k1_G);
            curve = new EllipticCurve(CurveConstants.secp192k1_p, CurveConstants.secp192k1_a, CurveConstants.secp192k1_b, g, CurveConstants.secp192k1_n, CurveConstants.secp192k1_h, CurveConstants.secp192k_1_q);
        }

        return curve;
    }
}
