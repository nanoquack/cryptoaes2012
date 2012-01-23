/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package krypto;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author Alex
 */
public class WordTest {

    @Test
    public void testGetInteger() {
        Word w = new Word();
        w.b3 = (byte)0x1A;
        w.b2 = (byte)0x2B;
        w.b1 = (byte)0x3C;
        w.b0 = (byte)0x4D;
        
        int i = w.getInteger();
        
        assertEquals(0x1A2B3C4D, i);
    }
    
    @Test
    public void testSetInteger() {
        Word w = new Word();
        
        int i = 0x1A2B3C4D;       
        w.setInteger(i);
        
        assertEquals(0x1A, w.b3);
        assertEquals(0x2B, w.b2);
        assertEquals(0x3C, w.b1);
        assertEquals(0x4D, w.b0);
        
        i = 0x2B4D;
        w.setInteger(i);
        
        assertEquals(0x00, w.b3);
        assertEquals(0x00, w.b2);
        assertEquals(0x2B, w.b1);
        assertEquals(0x4D, w.b0);
    }
    
    @Test
    public void testWord() {
        Word w = new Word(0x1A2B3C4D);
        
        assertEquals(0x1A, w.b3);
        assertEquals(0x2B, w.b2);
        assertEquals(0x3C, w.b1);
        assertEquals(0x4D, w.b0);
        
        w = new Word(0x2B4D);
        
        assertEquals(0x00, w.b3);
        assertEquals(0x00, w.b2);
        assertEquals(0x2B, w.b1);
        assertEquals(0x4D, w.b0);
    }
    
}
