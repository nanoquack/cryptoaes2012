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
public class CurveConstants {

    public enum EC_CURVES {

        secp192k1
    }
    public final static BigInteger secp192k1_p = new BigInteger("FFFFFFFF" + "FFFFFFFF" + "FFFFFFFF" + "FFFFFFFF" + "FFFFFFFE" + "FFFFEE37", 16);
    public final static BigInteger secp192k1_a = new BigInteger("00000000" + "00000000" + "00000000" + "00000000" + "00000000" + "00000000", 16);
    public final static BigInteger secp192k1_b = new BigInteger("00000000" + "00000000" + "00000000" + "00000000" + "00000000" + "00000003", 16);
    public final static BigInteger secp192k1_G = new BigInteger("04" + "DB4FF10E" + "C057E9AE" + "26B07D02" + "80B7F434" + "1DA5D1B1" + "EAE06C7D" + "9B2F2F6D" + "9C5628A7" + "844163D0" + "15BE8634" + "4082AA88" + "D95E2F9D", 16);
    public final static BigInteger secp192k1_n = new BigInteger("FFFFFFFF" + "FFFFFFFF" + "FFFFFFFE" + "26F2FC17" + "0F69466A" + "74DEFD8D", 16);
    public final static BigInteger secp192k1_h = new BigInteger("01", 16);
    public final static int secp192k_1_q = 192;     //192bit
}
