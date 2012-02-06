/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.adt;

import eccdh.algorithm.EncryptionException;

/**
 *
 * @author rolf
 */
public class OctetString {
    private String mValue;
    
    public OctetString(){
        mValue = "";
    }
    
    public OctetString(int value) throws EncryptionException{
        mValue = Integer.toString(value);
    }
    
    public OctetString(String value){
        mValue = new String(value);
    }
    
    public BitString toBitString(){
        throw new UnsupportedOperationException("not yet implemented");
    }
    
    public int toInteger(){
        throw new UnsupportedOperationException("not yet implemented");
    }
    
    public EllipticCurvePoint toEllipticCurvePoint(){
        throw new UnsupportedOperationException("not yet implemented");
    }
    
    @Override
    public String toString(){
        return new String(mValue);
    }
    
    @Override
    public boolean equals(Object b){
        if(b instanceof OctetString){
            OctetString oB = (OctetString) b;
            return this.mValue.equals(oB.mValue);
        }
        return false;
    }
}
