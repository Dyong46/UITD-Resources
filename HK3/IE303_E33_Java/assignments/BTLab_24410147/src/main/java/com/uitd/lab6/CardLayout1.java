package com.uitd.lab6;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CardLayout1 extends JFrame implements ActionListener {
    private CardLayout cardLayout;

    private JButton btn1, btn2, btn3;
    private Container pane;

    public CardLayout1() {
        setTitle("Card Layout");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 500);
        setLocationRelativeTo(null);
        setLayout(new CardLayout());

        initUI();
    }

    private void initUI() {
        pane = getContentPane();
        cardLayout = new CardLayout();
        pane.setLayout(cardLayout);

        btn1 = new JButton("Apple");
        btn2 = new JButton("Boy");
        btn3 = new JButton("Cat");

        btn1.addActionListener(this);
        btn2.addActionListener(this);
        btn3.addActionListener(this);

        pane.add("a", btn1);
        pane.add("b", btn2);
        pane.add("c", btn3);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        cardLayout.next(pane);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new CardLayout1().setVisible(true));
    }

}

