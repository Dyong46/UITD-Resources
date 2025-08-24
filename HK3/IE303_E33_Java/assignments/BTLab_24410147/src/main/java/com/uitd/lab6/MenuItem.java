package com.uitd.lab6;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MenuItem extends JFrame implements ActionListener {
    private JMenuBar menuBar;
    JMenu fileMenu, editMenu, helpMenu;
    JMenuItem cutMenuItem, copyMenuItem, pasteMenuItem, selectAllMenuItem;
    JTextArea textArea;

    MenuItem() {
        setTitle("Menu Item");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(null);

        initUI();
    }

    private void initUI() {
        cutMenuItem = new JMenuItem("Cut");
        copyMenuItem = new JMenuItem("Copy");
        pasteMenuItem = new JMenuItem("Paste");
        selectAllMenuItem = new JMenuItem("Select All");

        cutMenuItem.addActionListener(this);
        copyMenuItem.addActionListener(this);
        pasteMenuItem.addActionListener(this);
        selectAllMenuItem.addActionListener(this);

        menuBar = new JMenuBar();
        fileMenu = new JMenu("File");
        editMenu = new JMenu("Edit");
        helpMenu = new JMenu("Help");

        editMenu.add(cutMenuItem);
        editMenu.add(copyMenuItem);
        editMenu.add(pasteMenuItem);
        editMenu.add(selectAllMenuItem);

        menuBar.add(fileMenu);
        menuBar.add(editMenu);
        menuBar.add(helpMenu);
        this.add(menuBar);
        this.setJMenuBar(menuBar);

        textArea = new JTextArea();
        textArea.setBounds(5, 5, 360, 320);
        this.add(textArea);


    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == cutMenuItem) {
            textArea.setText("Welcome to the Cut");
        }
        if (e.getSource() == copyMenuItem) {
            textArea.setText("Welcome to the Copy");
        }
        if (e.getSource() == pasteMenuItem) {
            textArea.setText("Welcome to the Paste");
            gssgg
        }
        if (e.getSource() == selectAllMenuItem) {
            textArea.setText("Welcome to the Select All");
        }
        textArea.setText(null);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new MenuItem().setVisible(true));
    }
}
