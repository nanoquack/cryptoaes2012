/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.algorithm;

/**
 *
 * @author rolf
 */
public class DiffieHellman {

    public void execute(Configuration config) {
        //0. einigung auf algorithmus: einigung auf key derivation function KDF sowie ob Diffie-Hellman oder cofactor-Diffie-Hellman verwendet werden soll
        //1. finde gemeinsame Kurve und gemeinsamen Punkt auf der Kurve
        //2. berechne Private Key d und Public Key Q
        //3. Tausche die Public Keys aus
        //4. Wenn standardverfahren verwendet wird: überprüfe, ob bekommener Public Key valid ist. 
        //5. benutze Diffie Hellman welcher in Punkt 0 ausgewählt wurde, um das shared secret field z zu generieren. Siehe S 25ff. 
        //6. konvertiere z in einen octet-string
        //7. Benutze die in Punkt 0 ausgewählte Key derivation function KDF um Keyring data zu generieren. Siehe S 29ff. 
        //      Falls die Funktion invalid zurückgibt, invalid zurückgeben.
    }
}
