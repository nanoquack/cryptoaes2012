/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package krypto;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import static org.junit.Assert.*;
import org.junit.Test;

/**
 *
 * @author Alex
 */
public class AESTest {

    @Test
    public void testSimple128() throws BadKeyException, IOException {
        String aes128key = "2b7e151628aed2a6abf7158809cf4f3c";

        System.out.println("Test simple 128 encryption");
        Key key = new Key(aes128key);
        AES aes = new AES(key,Mode.ECB);
        
        String input = "This is a little test message.";
 
        System.out.println("Input: " + input);
        
        byte[] output = aes.encipherFromString(input);       
               
        //TODO add mechanism to retrieve appended 0bytes
        
        String result = aes.decipherToString(output);
        
        System.out.println("Decrypt: " + result);
        
        assertEquals(input, result);
    }

    @Test
    public void testSimple192() {
        String aes192key = "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b";

        
        /*
        void AesAlgorithmTest::testSimple192()
        {
        cerr << "Test: testSimple192()" << endl;
        try {
        AesEncryption aes(aes192key);
        string m("This is a little test message.");
        string iv("A part of this string will be used as IV.");
        AesEncryption::CipherMode modes[] = {AesEncryption::ECB,
        AesEncryption::CBC,
        AesEncryption::CFB,
        AesEncryption::OFB};
        for(int x = 0; x < 4; x++) {
        aes.setIvFromString(iv);
        vector<uint8_t> c = aes.encipher(m, modes[x]);
        aes.setIvFromString(iv);
        string m_ = aes.decipher(c, modes[x]);
        cerr << "m      : " << m << endl <<
        "d(e(m)): " << m_ << endl << endl;
        CPPUNIT_ASSERT(strcmp(m.c_str(), m_.c_str()) == 0);
        }
        } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
        } 
        
        
         */
    }

    @Test
    public void testSimple256() {
        String aes256key = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";        
        
        /*
        void AesAlgorithmTest::testSimple256()
        {
        cerr << "Test: testSimple256()" << endl;
        try {
        AesEncryption aes(aes256key);
        string m("This is a little test message.");
        string iv("A part of this string will be used as IV.");
        AesEncryption::CipherMode modes[] = {AesEncryption::ECB,
        AesEncryption::CBC,
        AesEncryption::CFB,
        AesEncryption::OFB};
        for(int x = 0; x < 4; x++) {
        aes.setIvFromString(iv);
        vector<uint8_t> c = aes.encipher(m, modes[x]);
        aes.setIvFromString(iv);
        string m_ = aes.decipher(c, modes[x]);
        cerr << "m      : " << m << endl <<
        "d(e(m)): " << m_ << endl << endl;
        CPPUNIT_ASSERT(strcmp(m.c_str(), m_.c_str()) == 0);
        }
        } catch(AesBadKeyException& e) {
        cerr << "Error: " << e.what() << endl;
        CPPUNIT_ASSERT(false);
        }
        
         */
    }
}
