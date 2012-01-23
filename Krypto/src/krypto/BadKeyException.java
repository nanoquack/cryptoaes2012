/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package krypto;

/**
 *
 * @author Alex
 */
public class BadKeyException extends Exception {

    /**
     * Creates a new instance of <code>BadKeyException</code> without detail message.
     */
    public BadKeyException() {
    }

    /**
     * Constructs an instance of <code>BadKeyException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public BadKeyException(String msg) {
        super(msg);
    }
}
