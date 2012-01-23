/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package krypto;

/**
 *
 * @author Alex
 */
public class Word {
    
    public byte b0;
    public byte b1;
    public byte b2;
    public byte b3;
    
    public Word() {};
    
    public Word(int i) {
        convertInt2Bytes(i);
    }
    
    public Word(Word word) {
        b0 = word.b0;
        b1 = word.b1;
        b2 = word.b2;
        b3 = word.b3;
    }
    
    public int getInteger() {
        return ((0xFF & b3) << 24) | ((0xFF & b2) << 16) | ((0xFF & b1) << 8) | (0xFF & b0);
    }
    
    public void setInteger(int i) {
        convertInt2Bytes(i);
    }
    
    private void convertInt2Bytes(int i) {
        b0 = (byte)i;
        i = i >> 8;
        b1 = (byte)i;
        i = i >> 8;
        b2 = (byte)i;
        i = i >> 8;
        b3 = (byte)i;        
    }
}
