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
    public void testOctetStringConversion() {
        String[] bsval = {"0", "1", "00000000", "00000001", "10000000", "11111111", "000000000", "100000000"};
        String[] res = {"0", "1", "0", "1", "200", "377", "0", "400"};

        for (int i = 0; i < bsval.length; i++) {
            OctetString os = new OctetString(bsval[i]);
            BitString bs = new BitString(res[i]);
            BitString bitres = os.toBitString();
            assertEquals("Conversion " + (i + 1) + " not correct", bs, bitres);
        }
    }
}
