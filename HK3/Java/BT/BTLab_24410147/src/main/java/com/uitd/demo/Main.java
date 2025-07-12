package com.uitd.demo;


import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.util.Objects;

public class Main extends JFrame implements ActionListener{
    private double result;
    private final JTextField tf1;
    private final JTextField tf2;
    private final JTextField tf3;

    public Main(String s) {
        JPanel panel1, panel2;
        Container container;
        JButton btn1, btn2, btn3, btn4;
        super(s);
        container = this.getContentPane();
        this.setSize(400, 400);
        this.setLayout(new GridLayout(3, 1));

        JLabel num1 = new JLabel("First number: ", JLabel.RIGHT);
        tf1 = new JTextField();
        JLabel num2 = new JLabel("Second number: ", JLabel.RIGHT);
        tf2 = new JTextField();
        JLabel result = new JLabel("Result: ", JLabel.RIGHT);
        result.setSize(350, 100);
        tf3 = new JTextField();

        tf3.setEditable(false);

        panel1 = new JPanel();
        panel1.setLayout(new GridLayout(3,2));
        /*Đặt các thành phần vào panel 1*/
        panel1.add(num1);
        panel1.add(tf1);
        panel1.add(num2);
        panel1.add(tf2);
        panel1.add(result);
        panel1.add(tf3);

        btn1 = new JButton("+");
        btn2= new JButton("-");
        btn3 = new JButton("*");
        btn4 = new JButton(":");

        panel2 = new JPanel();
        panel2.add(btn1);
        panel2.add(btn2);
        panel2.add(btn3);
        panel2.add(btn4);

        container.add(panel1);
        container.add(panel2,"South");

        btn1.addActionListener(this);
        btn2.addActionListener(this);
        btn3.addActionListener(this);
        btn4.addActionListener(this);

        this.setSize(350, 200);
        this.setVisible(true);
        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
    }

    public void Add()
    {
        result = Double.parseDouble(tf1.getText()) + Double.parseDouble(tf2.getText());
        tf3.setText(String.valueOf(result));
    }
    public void Minus()
    {
        result = Double.parseDouble(tf1.getText()) - Double.parseDouble(tf2.getText());
        tf3.setText(String.valueOf(result));
    }
    public void Multi()
    {
        result = Double.parseDouble(tf1.getText()) * Double.parseDouble(tf2.getText());
        tf3.setText(String.valueOf(result));
    }
    public void Div()
    {
        result = Double.parseDouble(tf1.getText()) / Double.parseDouble(tf2.getText());
        tf3.setText(String.valueOf(result));
    }

    public void actionPerformed(ActionEvent e)
    {
        if (Objects.equals(e.getActionCommand(), "+")) {
            if(tf1.getText().isEmpty() || tf2.getText().isEmpty()) {
                JOptionPane.showMessageDialog(this, "You haven't entered enough data");
            }else {
                Add();
            }
        }

        if (Objects.equals(e.getActionCommand(), "-")) {
            if(tf1.getText().isEmpty() || tf2.getText().isEmpty()) {
                JOptionPane.showMessageDialog(this, "You haven't entered enough data");
            }else {
                Minus();
            }
        }
        if (Objects.equals(e.getActionCommand(), "*")){
            if(tf1.getText().isEmpty()|| tf2.getText().isEmpty()) {
                JOptionPane.showMessageDialog(this, "You haven't entered enough data");
            }else {
                Multi();
            }
        }
        if (Objects.equals(e.getActionCommand(), ":")) {
            if(tf1.getText().isEmpty()|| tf2.getText().isEmpty()) {
                JOptionPane.showMessageDialog(this, "You haven't entered enough data");
            }else {
                Div();
            }
        }
    }

    public static void main(String[] args) {
        Main cal = new Main("SimpleCalculator");
        cal.setLocationRelativeTo(null);
    }
}
