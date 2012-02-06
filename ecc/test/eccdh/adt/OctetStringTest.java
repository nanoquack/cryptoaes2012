/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

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
        String[] octval = {"0", "1", "200", "377", "400"};
        String[] res = {"0", "1", "10000000", "11111111", "100000000"};

        for (int i = 0; i < octval.length; i++) {
            OctetString os = new OctetString(octval[i]);
            BitString bs = new BitString(res[i]);
            BitString bitres = os.toBitString();
            assertEquals("Conversion " + (i + 1) + " not correct", bs, bitres);
        }
    }
}
