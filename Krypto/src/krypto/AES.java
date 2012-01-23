/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package krypto;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;

/**
 *
 * @author Alex
 */
public class AES {

    private State state;
    private Key key;
    private Mode mode;

    public AES(Key key, Mode mode) {
        this.state = new State();
        this.key = key;
        this.mode = mode;
    }

    public AES(Key key) {
        this.state = new State();
        this.key = key;
        this.mode = Mode.ECB;
    }

    public void setMode(Mode mode) {
        this.mode = mode;
    }

    public void setKey(Key key) {
        this.key = key;
    }
    
    public String decipherToString(byte[] input) {
        
        byte[] output = new byte[input.length];
               
        for (int i=0; i < input.length; i+=16) {
            state.bytes[0]=input[i];
            state.bytes[1]=input[i+1];
            state.bytes[2]=input[i+2];
            state.bytes[3]=input[i+3];
            state.bytes[4]=input[i+4];
            state.bytes[5]=input[i+5];
            state.bytes[6]=input[i+6];
            state.bytes[7]=input[i+7];
            state.bytes[8]=input[i+8];
            state.bytes[9]=input[i+9];
            state.bytes[10]=input[i+10];
            state.bytes[11]=input[i+11];
            state.bytes[12]=input[i+12];
            state.bytes[13]=input[i+13];
            state.bytes[14]=input[i+14];
            state.bytes[15]=input[i+15];
            decipher();
            output[i] = state.bytes[0];
            output[i+1] = state.bytes[1];
            output[i+2] = state.bytes[2];
            output[i+3] = state.bytes[3];
            output[i+4] = state.bytes[4];
            output[i+5] = state.bytes[5];
            output[i+6] = state.bytes[6];
            output[i+7] = state.bytes[7];
            output[i+8] = state.bytes[8];
            output[i+9] = state.bytes[9];
            output[i+10] = state.bytes[10];
            output[i+11] = state.bytes[11];
            output[i+12] = state.bytes[12];
            output[i+13] = state.bytes[13];
            output[i+14] = state.bytes[14];
            output[i+15] = state.bytes[15];
        }
         
        return new String(output);
    }
    
    public byte[] encipherFromString(String m) {
        
        if (m.length() %16 != 0) {
            StringBuilder builder = new StringBuilder(m);
            builder.setLength(m.length()+(16 - m.length()%16));
            m = builder.toString();
        }
               
        byte[] input = m.getBytes();
        byte[] output = new byte[input.length];
        
        for (int i=0; i < input.length; i+=16) {
            state.bytes[0]=input[i];
            state.bytes[1]=input[i+1];
            state.bytes[2]=input[i+2];
            state.bytes[3]=input[i+3];
            state.bytes[4]=input[i+4];
            state.bytes[5]=input[i+5];
            state.bytes[6]=input[i+6];
            state.bytes[7]=input[i+7];
            state.bytes[8]=input[i+8];
            state.bytes[9]=input[i+9];
            state.bytes[10]=input[i+10];
            state.bytes[11]=input[i+11];
            state.bytes[12]=input[i+12];
            state.bytes[13]=input[i+13];
            state.bytes[14]=input[i+14];
            state.bytes[15]=input[i+15];
            encipher();
            output[i] = state.bytes[0];
            output[i+1] = state.bytes[1];
            output[i+2] = state.bytes[2];
            output[i+3] = state.bytes[3];
            output[i+4] = state.bytes[4];
            output[i+5] = state.bytes[5];
            output[i+6] = state.bytes[6];
            output[i+7] = state.bytes[7];
            output[i+8] = state.bytes[8];
            output[i+9] = state.bytes[9];
            output[i+10] = state.bytes[10];
            output[i+11] = state.bytes[11];
            output[i+12] = state.bytes[12];
            output[i+13] = state.bytes[13];
            output[i+14] = state.bytes[14];
            output[i+15] = state.bytes[15];
        }
        
        return output;
    }

    public void decipherStream(BufferedInputStream in, BufferedOutputStream out) throws IOException {
        int i = 0;

        State tmp = new State();

        //TODO check if in.read always fills the whole byte array unless eof...
        while ((i = in.read(state.bytes)) != -1) {
            //System.out.println(i + " bytes read");
            //fill up bytes (should be called at most once at the end of the stream)
            /* for (int j = i; j < 16; j++) {
            state.bytes[j] = '\0';
            } */

            decipher();

            out.write(state.bytes);
        }
    }

    public void encipherStream(BufferedInputStream in, BufferedOutputStream out) throws IOException {
        int i = 0;
        //TODO check if in.read always fills the whole byte array unless eof...
        while ((i = in.read(state.bytes)) != -1) {
            //System.out.println(i + " bytes read, array length " + state.bytes.length);
            //fill up bytes (should be called at most once at the end of the stream)
            for (int j = i; j < 16; j++) {
                //System.out.println("Filling byte " + j);
                state.bytes[j] = '\0';
            }

            encipher();

            out.write(state.bytes);
        }
    }

    private void encipher() {
        switch (mode) {
            case ECB:
                encipherState();
                break;
            case CBC:
                /*
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                encipherState(state);
                iv.w[0] = state.w[0];
                iv.w[1] = state.w[1];
                iv.w[2] = state.w[2];
                iv.w[3] = state.w[3];
                 */
                break;
            case CFB:
                /*
                encipherState(iv);
                iv.w[0] ^= state.w[0];
                iv.w[1] ^= state.w[1];
                iv.w[2] ^= state.w[2];
                iv.w[3] ^= state.w[3];
                state.w[0] = iv.w[0];
                state.w[1] = iv.w[1];
                state.w[2] = iv.w[2];
                state.w[3] = iv.w[3];
                 */
                break;
            case OFB:
                /*
                encipherState(iv);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                 */
                break;
        }
    }

    private void decipher() {
        switch (mode) {
            case ECB:
                decipherState();
                break;
            case CBC:
                /*
                tmp.w[0] = state.w[0];
                tmp.w[1] = state.w[1];
                tmp.w[2] = state.w[2];
                tmp.w[3] = state.w[3];
                decipherState(state);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                iv.w[0] = tmp.w[0];
                iv.w[1] = tmp.w[1];
                iv.w[2] = tmp.w[2];
                iv.w[3] = tmp.w[3];
                 */
                break;
            case CFB:
                /*
                encipherState(iv);
                tmp.w[0] = state.w[0];
                tmp.w[1] = state.w[1];
                tmp.w[2] = state.w[2];
                tmp.w[3] = state.w[3];
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                iv.w[0] = tmp.w[0];
                iv.w[1] = tmp.w[1];
                iv.w[2] = tmp.w[2];
                iv.w[3] = tmp.w[3];
                 */
                break;
            case OFB:
                /*
                encipherState(iv);
                state.w[0] ^= iv.w[0];
                state.w[1] ^= iv.w[1];
                state.w[2] ^= iv.w[2];
                state.w[3] ^= iv.w[3];
                 */
                break;
        }
    }

    private void encipherState() {
        addRoundKey(0);
        for (int r = 1; r < key.rnum; r++) {
            subBytes();
            shiftRows();
            mixColumns();
            addRoundKey(r);

        }
        subBytes();
        shiftRows();
        addRoundKey(key.rnum);
    }

    private void decipherState() {        
        addRoundKey(key.rnum);
        for (int r = key.rnum - 1; r > 0; r--) {
            invShiftRows();
            invSubBytes();
            addRoundKey(r);
            invMixColumns();
        }
        invShiftRows();
        invSubBytes();
        addRoundKey(0);
    }

    public void subBytes() {
        for (int n = 0; n < 16; n++) {
            state.bytes[n] = SBox.subByte(state.bytes[n]);
        }
    }

    public void invSubBytes() {
        for (int n = 0; n < 16; n++) {
            state.bytes[n] = SBox.invSubByte(state.bytes[n]);
        }
    }

    private void shiftRows() {
        byte tmp;
        //row 1
        //shifting not necessary
        //row 2
        tmp = state.bytes[1];
        state.bytes[1] = state.bytes[5];
        state.bytes[5] = state.bytes[9];
        state.bytes[9] = state.bytes[13];
        state.bytes[13] = tmp;
        //row 3
        tmp = state.bytes[2];
        state.bytes[2] = state.bytes[10];
        state.bytes[10] = tmp;
        tmp = state.bytes[6];
        state.bytes[6] = state.bytes[14];
        state.bytes[14] = tmp;
        //row 4
        tmp = state.bytes[3];
        state.bytes[3] = state.bytes[15];
        state.bytes[15] = state.bytes[11];
        state.bytes[11] = state.bytes[7];
        state.bytes[7] = tmp;
    }

    private void invShiftRows() {
        byte tmp;
        //row 1
        //shifting not necessary
        //row 2
        tmp = state.bytes[1];
        state.bytes[1] = state.bytes[13];
        state.bytes[13] = state.bytes[9];
        state.bytes[9] = state.bytes[5];
        state.bytes[5] = tmp;
        //row 3
        tmp = state.bytes[2];
        state.bytes[2] = state.bytes[10];
        state.bytes[10] = tmp;
        tmp = state.bytes[6];
        state.bytes[6] = state.bytes[14];
        state.bytes[14] = tmp;
        //row 4
        tmp = state.bytes[3];
        state.bytes[3] = state.bytes[7];
        state.bytes[7] = state.bytes[11];
        state.bytes[11] = state.bytes[15];
        state.bytes[15] = tmp;
    }

    private void mixColumns() {
        for (int n = 0; n < 4; n++) {
            mixColumn(n);
        }
    }

    private void mixColumn(int n) {
        byte t0, t1, t2, t3;

        n = n * 4; //use word offset;

        t0 = state.bytes[n];
        t1 = state.bytes[n + 1];
        t2 = state.bytes[n + 2];
        t3 = state.bytes[n + 3];

        state.bytes[n] = (byte) (gmul(t0, (byte) 2) ^ gmul(t1, (byte) 3) ^ t2 ^ t3);
        state.bytes[n + 1] = (byte) (t0 ^ gmul(t1, (byte) 2) ^ gmul(t2, (byte) 3) ^ t3);
        state.bytes[n + 2] = (byte) (t0 ^ t1 ^ gmul(t2, (byte) 2) ^ gmul(t3, (byte) 3));
        state.bytes[n + 3] = (byte) (gmul(t0, (byte) 3) ^ t1 ^ t2 ^ gmul(t3, (byte) 2));

    }

    private void invMixColumns() {
        for (int n = 0; n < 4; n++) {
            invMixColumn(n);
        }

    }

    private void invMixColumn(int n) {
        byte t0, t1, t2, t3;

        n = n * 4; //use word offset;

        t0 = state.bytes[n];
        t1 = state.bytes[n + 1];
        t2 = state.bytes[n + 2];
        t3 = state.bytes[n + 3];
        state.bytes[n] = (byte) (gmul(t0, (byte) 0x0e) ^ gmul(t1, (byte) 0x0b) ^ gmul(t2, (byte) 0x0d) ^ gmul(t3, (byte) 0x09));
        state.bytes[n + 1] = (byte) (gmul(t0, (byte) 0x09) ^ gmul(t1, (byte) 0x0e) ^ gmul(t2, (byte) 0x0b) ^ gmul(t3, (byte) 0x0d));
        state.bytes[n + 2] = (byte) (gmul(t0, (byte) 0x0d) ^ gmul(t1, (byte) 0x09) ^ gmul(t2, (byte) 0x0e) ^ gmul(t3, (byte) 0x0b));
        state.bytes[n + 3] = (byte) (gmul(t0, (byte) 0x0b) ^ gmul(t1, (byte) 0x0d) ^ gmul(t2, (byte) 0x09) ^ gmul(t3, (byte) 0x0e));
    }

    private int gmul(int p, int q) {
        
        p = p & 0xFF;
        q = q & 0xFF;
        
        int r = 0;
        for (int i = 0; i < 8; i++) {
            if ((q & 0x01) != 0) {
                r ^= p;
            }
            if ((p & 0x80) != 0) {
                p <<= 1;
                p ^= 0x1b;
            } else {
                p <<= 1;
            }
            q >>= 1;
        }
        return r;
    } 

    /*
    //Multiplication in GF(256)
    private byte gmul(byte p, byte q) {
        byte r = 0;
        for (byte i = 0; i < 8; i++) {
            if ((q & 0x01) != 0) {
                r ^= p;
            }
            if ((p & 0x80) != 0) {
                p <<= 1;
                p ^= 0x1b;
            } else {
                p <<= 1;
            }
            q >>= 1;
        }
        return r;
    }*/

    private void addRoundKey(int round) {

        state.bytes[0] ^= key.key[round * 4].b0;
        state.bytes[1] ^= key.key[round * 4].b1;
        state.bytes[2] ^= key.key[round * 4].b2;
        state.bytes[3] ^= key.key[round * 4].b3;

        state.bytes[4] ^= key.key[round * 4 + 1].b0;
        state.bytes[5] ^= key.key[round * 4 + 1].b1;
        state.bytes[6] ^= key.key[round * 4 + 1].b2;
        state.bytes[7] ^= key.key[round * 4 + 1].b3;

        state.bytes[8] ^= key.key[round * 4 + 2].b0;
        state.bytes[9] ^= key.key[round * 4 + 2].b1;
        state.bytes[10] ^= key.key[round * 4 + 2].b2;
        state.bytes[11] ^= key.key[round * 4 + 2].b3;

        state.bytes[12] ^= key.key[round * 4 + 3].b0;
        state.bytes[13] ^= key.key[round * 4 + 3].b1;
        state.bytes[14] ^= key.key[round * 4 + 3].b2;
        state.bytes[15] ^= key.key[round * 4 + 3].b3;

        /*
        state.w[0] ^= key[round * 4].w;
        state.w[1] ^= key[round * 4 + 1].w;
        state.w[2] ^= key[round * 4 + 2].w;
        state.w[3] ^= key[round * 4 + 3].w;
         */
    }
}
