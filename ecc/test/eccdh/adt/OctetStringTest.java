/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import eccdh.algorithm.EncryptionException;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author rolf
 */
public class OctetStringTest {

    @Test
    public void testBitStringConversion() {
        String[] octval = {"0", "1", "200", "377", "400"};
        String[] res = {"0", "1", "10000000", "11111111", "100000000"};

        for (int i = 0; i < octval.length; i++) {
            OctetString os = new OctetString(octval[i]);
            BitString bs = new BitString(res[i]);
            BitString bitres = os.toBitString();
            assertEquals("Conversion " + (i + 1) + " not correct", bs, bitres);
        }
    }

    @Test
    public void testIntToOctetString() {
        Integer negative = -1;
        EncryptionException exception=null;
        try{
            OctetString negativeTest = new OctetString(negative);
        }
        catch(EncryptionException e){
            exception = e;
        }
        assertNotNull("Negative integer should raise exception", exception);
        
        int[] intval = {};
        String[] res = {};

        for (int i = 0; i < intval.length; i++) {
            Integer is = new Integer(intval[i]);
            OctetString os = new OctetString(res[i]);
            OctetString osres = new OctetString(is);
            assertEquals("Conversion " + (i + 1) + " not correct", os, osres);
        }
    }

    @Test
    public void testOctetStringToInt() {
        String[] octval = {};
        String[] res = {};

        for (int i = 0; i < octval.length; i++) {
            OctetString os = new OctetString(octval[i]);
            BitString bs = new BitString(res[i]);
            BitString bitres = os.toBitString();
            assertEquals("Conversion " + (i + 1) + " not correct", bs, bitres);
        }
    }
}
