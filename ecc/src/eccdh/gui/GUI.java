/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package eccdh.gui;

/**
 *
 * @author Alex
 */
public class GUI extends javax.swing.JFrame {

    /**
     * Creates new form GUI
     */
    public GUI() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form. WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        tabPanel = new javax.swing.JTabbedPane();
        tabConn = new javax.swing.JPanel();
        tfRegistry = new javax.swing.JTextField();
        lbRegistry = new javax.swing.JLabel();
        btConnect = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        keyList = new javax.swing.JList();
        lbStatus = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Diffie Hellmann Chat");

        tfRegistry.setText("localhost");
        tfRegistry.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tfRegistryActionPerformed(evt);
            }
        });

        lbRegistry.setLabelFor(tfRegistry);
        lbRegistry.setText("Registry Hostname or IP");

        btConnect.setText("Connect");

        keyList.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        keyList.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        jScrollPane1.setViewportView(keyList);

        lbStatus.setText("Status");

        javax.swing.GroupLayout tabConnLayout = new javax.swing.GroupLayout(tabConn);
        tabConn.setLayout(tabConnLayout);
        tabConnLayout.setHorizontalGroup(
            tabConnLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(tabConnLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(tabConnLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(tabConnLayout.createSequentialGroup()
                        .addComponent(lbRegistry)
                        .addGap(18, 18, 18)
                        .addComponent(tfRegistry, javax.swing.GroupLayout.DEFAULT_SIZE, 296, Short.MAX_VALUE)
                        .addGap(18, 18, 18)
                        .addComponent(btConnect))
                    .addComponent(jScrollPane1)
                    .addComponent(lbStatus, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap())
        );
        tabConnLayout.setVerticalGroup(
            tabConnLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(tabConnLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(tabConnLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(tfRegistry, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(lbRegistry)
                    .addComponent(btConnect))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(lbStatus)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 294, Short.MAX_VALUE)
                .addContainerGap())
        );

        tabPanel.addTab("Registry", tabConn);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(tabPanel)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(tabPanel)
                .addContainerGap())
        );

        tabPanel.getAccessibleContext().setAccessibleName("Connections");

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void tfRegistryActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tfRegistryActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_tfRegistryActionPerformed

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btConnect;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JList keyList;
    private javax.swing.JLabel lbRegistry;
    private javax.swing.JLabel lbStatus;
    private javax.swing.JPanel tabConn;
    private javax.swing.JTabbedPane tabPanel;
    private javax.swing.JTextField tfRegistry;
    // End of variables declaration//GEN-END:variables
}