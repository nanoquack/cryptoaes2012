/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package krypto;

/**
 *
 * @author Alex
 */
public class Key {

    //rcon value for key expansion
    private static int[] rcon = {
        0x00000001, 0x00000002, 0x00000004, 0x00000008,
        0x00000010, 0x00000020, 0x00000040, 0x00000080,
        0x0000001b, 0x00000036, 0x0000006c, 0x000000d8,
        0x000000ab, 0x0000004d, 0x0000009a
    };
    public int knum;
    public int rnum;
    public Word[] key;

    public Key(String keyString) throws BadKeyException {
        switch (keyString.length()) {
            case 32:
                knum = 4;
                rnum = 10;
                break;
            case 48:
                knum = 6;
                rnum = 12;
                break;
            case 64:
                knum = 8;
                rnum = 14;
                break;
            default:
                throw new BadKeyException("Length must be 32, 48 or 64 characters, but is " + keyString.length());
        }

        key = new Word[(rnum + 1) * 4];

        keyHex2Arr(keyString);
        expandKey();
    }

    public Key(byte[] keyArray) throws BadKeyException {
        switch (keyArray.length) {
            case 16:
            case 24:
            case 32:
                knum = keyArray.length / 4;
                rnum = knum + 6;
                break;
            default:
                throw new BadKeyException("Invalid key length. Must be 16, 24 or 32");
        }

        key = new Word[(rnum + 1) * 4];

        for (int n = 0, m = 0; m < keyArray.length; n++, m += 4) {
            key[n].b0 = keyArray[m];
            key[n].b1 = keyArray[m + 1];
            key[n].b2 = keyArray[m + 2];
            key[n].b3 = keyArray[m + 3];
        }

        expandKey();
    }

    private void expandKey() {
        for (int i = knum; i < (rnum + 1) * 4; i++) {
            Word tmp = new Word(key[i - 1]);
            if (i % knum == 0) {

                int shift = tmp.getInteger();
                
                //do shifting with unsigned int
                //important because if signed bit is set, then rightshift inserts 1s instead of 0s
                shift = (int)((0xffffffffl & shift) << 24) | (int)((0xffffffffl & shift) >> 8);
                
                tmp.setInteger(shift);

                tmp.b0 = SBox.subByte(tmp.b0);
                tmp.b1 = SBox.subByte(tmp.b1);
                tmp.b2 = SBox.subByte(tmp.b2);
                tmp.b3 = SBox.subByte(tmp.b3);

                //tmp.w ^= rcon[i / knum - 1];
                tmp.setInteger(tmp.getInteger() ^ rcon[i / knum - 1]);
            } else if (knum > 6 && i % knum == 4) {
                tmp.b0 = SBox.subByte(tmp.b0);
                tmp.b1 = SBox.subByte(tmp.b1);
                tmp.b2 = SBox.subByte(tmp.b2);
                tmp.b3 = SBox.subByte(tmp.b3);
            }

            //key[i].w = key[i - knum].w ^ tmp.w;
            key[i] = new Word((key[i - knum].getInteger() ^ tmp.getInteger()));
            
            //System.out.println(i + ": " + (0xFF & key[i].b3) + " " + (0xFF & key[i].b2) + " " + (0xFF & key[i].b1) + " " + (0xFF & key[i].b0));
        }
    }

    private void keyHex2Arr(String keyString) throws BadKeyException {
        int x;
        char[] str = keyString.toCharArray();

        if (keyString.length() % 8 != 0) {
            throw new BadKeyException("Invalid key length: " + keyString.length());
        }

        for (int n = 0, m = 0; n < keyString.length(); n++) {
            if (str[n] >= '0' && str[n] <= '9') {
                x = (((byte) str[n] - '0') << 4);
            } else if (str[n] >= 'a' && str[n] <= 'f') {
                x = (((byte) str[n] - 'a' + 10) << 4);
            } else if (str[n] >= 'A' && str[n] <= 'F') {
                x = (((byte) str[n] - 'A' + 10) << 4);
            } else {
                throw new BadKeyException("Invalid character " + str[n]);
            }

            n++;
            if (str[n] >= '0' && str[n] <= '9') {
                x += str[n] - '0';
            } else if (str[n] >= 'a' && str[n] <= 'f') {
                x += str[n] - 'a' + 10;
            } else if (str[n] >= 'A' && str[n] <= 'F') {
                x += str[n] - 'A' + 10;
            } else {
                throw new BadKeyException("Invalid character " + str[n]);
            }

            int sh = ((n - 1) / 2) % 4;
            switch (sh) {
                case 0:
                    //key[m].w = x;
                    key[m] = new Word(x);
                    break;
                case 3:
                    x <<= sh * 8;
                    //key[m].w += x;
                    key[m] = new Word(key[m].getInteger()+x);
                    m++;
                    break;
                default:
                    x <<= sh * 8;
                    //key[m].w += x;
                    key[m] = new Word(key[m].getInteger()+x);
            }
        }

        //System.out.println(getExpandedKeyAsHexString());
        //System.out.println(getExpandedKeyAsIntString());
    }

    public String getExpandedKeyAsHexString() {
        String hex = "";

        for (int i = 0; i < key.length; i++) {

            if (key[i] != null) {
                
                String b0 = Integer.toHexString(0xff & key[i].b0);
                String b1 = Integer.toHexString(0xff & key[i].b1);
                String b2 = Integer.toHexString(0xff & key[i].b2);
                String b3 = Integer.toHexString(0xff & key[i].b3);
                
                if (b0.length() == 1) {
                    b0 = "0" + b0;
                }
                
                if (b1.length() == 1) {
                    b1 = "0" + b1;
                }
                
                if (b2.length() == 1) {
                    b2 = "0" + b2;
                }
                
                if (b3.length() == 1) {
                    b3 = "0" + b3;
                }                
                
                hex = hex + b0 + b1 + b2 + b3;
            }
        
        }

        return hex;
    }
    
    public String getExpandedKeyAsIntString() {
        String bin = "";

        for (int i = 0; i < key.length; i++) {

            if (key[i] != null) {
                bin = bin + (0xff & key[i].b3) + " " + (0xff & key[i].b2) + " " + (0xff & key[i].b1) + " " + (0xff & key[i].b0) + " ";            
            }
        }

        return bin;
    }
}
