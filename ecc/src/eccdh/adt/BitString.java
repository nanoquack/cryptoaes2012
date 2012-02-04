/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

/**
 *
 * @author rolf
 */
public class BitString {

    String mValue;

    public BitString() {
    }

    public BitString(String value) {
        mValue = value;
    }

    public OctetString toOctetString() {
        String padded = padValue8(mValue);
        String m = "";
        int bitLength = padded.length();
        //we know the string is padded, so we know the length is a multiple of 8
        int octetLength = (int) (padded.length() / 8);
        for (int i = 0; i < octetLength; i++) {
            int bitIndex0 = (bitLength - 8) - 8 * (octetLength - 1 - i);
            int bitIndex1 = (bitLength - 7) - 8 * (octetLength - 1 - i);
            int bitIndex2 = (bitLength - 6) - 8 * (octetLength - 1 - i);
            int bitIndex3 = (bitLength - 5) - 8 * (octetLength - 1 - i);
            int bitIndex4 = (bitLength - 4) - 8 * (octetLength - 1 - i);
            int bitIndex5 = (bitLength - 3) - 8 * (octetLength - 1 - i);
            int bitIndex6 = (bitLength - 2) - 8 * (octetLength - 1 - i);
            int bitIndex7 = (bitLength - 1) - 8 * (octetLength - 1 - i);
            String mi = ((padded.charAt(bitIndex0) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex1) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex2) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex3) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex4) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex5) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex6) == '0') ? "0" : "1")
                    + ((padded.charAt(bitIndex7) == '0') ? "0" : "1");
            m = m+mi;
        }
        
        OctetString result = new OctetString(m);
        return result;

    }

    /**
     * Pads the value through appending 0s on the left side until it its length
     * is a multiple of 8
     *
     * @param value
     * @return
     */
    private String padValue8(String value) {
        if ((value.length() % 8) == 0) {
            return new String(value);
        } else {
            String padded = new String(value);
            int padCount = 8 - (value.length() % 8);
            for (int i = 0; i < padCount; i++) {
                padded = "0" + padded;
            }
            return padded;
        }
    }

    @Override
    public String toString() {
        return mValue;
    }

    @Override
    public boolean equals(Object b) {
        if (b instanceof BitString) {
            BitString bsB = (BitString) b;
            this.mValue.equals(bsB.mValue);
        }
        return false;
    }
}
