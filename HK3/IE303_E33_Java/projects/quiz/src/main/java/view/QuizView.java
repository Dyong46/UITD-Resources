package view;

import model.Question;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class QuizView extends JFrame {
    private JPanel cardPanel;
    private CardLayout cardLayout;
    private List<Question> questions;
    private JButton btnFirst;
    private JButton btnPrev;
    private JButton btnNext;
    private JButton btnLast;
    private int currentIndex = 0;

    public QuizView() {
        setTitle("Test Quiz - Java Swing");
        setSize(700, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        createUIComponents();
    }

    private void createUIComponents() {
        questions = createSampleQuestions();

        setLayout(new BorderLayout());

        cardLayout = new CardLayout();
        cardPanel = new JPanel(cardLayout);
        cardPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));

        for (int i = 0; i < questions.size(); i++) {
            cardPanel.add(createQuestionPanel(questions.get(i), i), "Card" + i);
        }

        JPanel rightPanel = new JPanel(new GridLayout(0, 3, 10, 10));
        rightPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        JButton[] questionButtons = new JButton[questions.size()];

        for (int i = 0; i < questions.size(); i++) {
            final int index = i;
            questionButtons[i] = new JButton(String.valueOf(i + 1));
            questionButtons[i].setPreferredSize(new Dimension(50, 30));
            questionButtons[i].addActionListener(e -> {
                cardLayout.show(cardPanel, "Card" + index);
                currentIndex = index;
                updateNavigationButtons();
            });
            rightPanel.add(questionButtons[i]);
        }

        JPanel footerPanel = getFooterPanel();

        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(cardPanel, BorderLayout.CENTER);
        mainPanel.add(rightPanel, BorderLayout.EAST);

        add(mainPanel, BorderLayout.CENTER);
        add(footerPanel, BorderLayout.SOUTH);

        updateNavigationButtons();
    }

    private JPanel getFooterPanel() {
        JPanel footerPanel = new JPanel();
        btnFirst = new JButton("First");
        btnPrev = new JButton("<-");
        btnNext = new JButton("->");
        btnLast = new JButton("Last");

        btnFirst.addActionListener(e -> {
            currentIndex = 0;
            cardLayout.first(cardPanel);
            updateNavigationButtons();
        });

        btnPrev.addActionListener(e -> {
            if (currentIndex > 0) {
                currentIndex--;
                cardLayout.show(cardPanel, "Card" + currentIndex);
                updateNavigationButtons();
            }
        });

        btnNext.addActionListener(e -> {
            if (currentIndex < questions.size() - 1) {
                currentIndex++;
                cardLayout.show(cardPanel, "Card" + currentIndex);
                updateNavigationButtons();
            }
        });

        btnLast.addActionListener(e -> {
            currentIndex = questions.size() - 1;
            cardLayout.last(cardPanel);
            updateNavigationButtons();
        });

        footerPanel.add(btnFirst);
        footerPanel.add(btnPrev);
        footerPanel.add(btnNext);
        footerPanel.add(btnLast);
        return footerPanel;
    }

    private JPanel createQuestionPanel(Question q, int index) {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        String text = "<html><body style='width:300px'>Câu " + (index + 1) + ": " + q.getContent() + "</body></html>";
        JLabel lblQuestion = new JLabel(text);
        lblQuestion.setFont(new Font("Arial", Font.BOLD, 16));

        panel.add(lblQuestion);
        panel.add(Box.createRigidArea(new Dimension(0, 10)));

        ButtonGroup group = new ButtonGroup();
        String[] labels = {"A", "B", "C", "D"};

        for (int i = 0; i < q.getOptions().length; i++) {
            JRadioButton rb = getRadioAnswer(q, labels, i);

            group.add(rb);
            panel.add(rb);
        }

        panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        return panel;
    }

    private JRadioButton getRadioAnswer(Question q, String[] labels, int i) {
        String optionLabel = labels[i];
        String optionText = q.getOptions()[i];
        JRadioButton rb = new JRadioButton(optionLabel + ". " + optionText);

        rb.addActionListener(e -> {
            if (optionLabel.equals(q.getCorrectAnswer())) {
                JOptionPane.showMessageDialog(this, "Correct!", "Result :", JOptionPane.INFORMATION_MESSAGE);
            } else {
                JOptionPane.showMessageDialog(this, "Wrong!\nCorrect answer: " + q.getCorrectAnswer(), "Result", JOptionPane.ERROR_MESSAGE);
            }
        });
        return rb;
    }

    private void updateNavigationButtons() {
        btnFirst.setEnabled(currentIndex > 0);
        btnPrev.setEnabled(currentIndex > 0);
        btnNext.setEnabled(currentIndex < questions.size() - 1);
        btnLast.setEnabled(currentIndex < questions.size() - 1);
    }

    // Sample data
    private List<Question> createSampleQuestions() {
        List<Question> questions = new ArrayList<>();
        questions.add(new Question(
                "Which planet is known as the Red Planet?",
                new String[]{"Venus", "Mars", "Jupiter", "Mercury"},
                "B"
        ));
        questions.add(new Question(
                "What is the largest ocean on Earth?",
                new String[]{"Atlantic Ocean", "Indian Ocean", "Arctic Ocean", "Pacific Ocean"},
                "D"
        ));
        questions.add(new Question(
                "Who painted the Mona Lisa?",
                new String[]{"Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Michelangelo"},
                "C"
        ));
        questions.add(new Question(
                "What is the smallest prime number?",
                new String[]{"1", "2", "3", "5"},
                "B"
        ));
        questions.add(new Question(
                "Which gas do plants absorb from the atmosphere?",
                new String[]{"Oxygen", "Nitrogen", "Carbon Dioxide", "Hydrogen"},
                "C"
        ));
        questions.add(new Question(
                "Which country is home to the kangaroo?",
                new String[]{"Australia", "India", "Canada", "Brazil"},
                "A"
        ));
        questions.add(new Question(
                "What is the boiling point of water at sea level?",
                new String[]{"90°C", "100°C", "110°C", "120°C"},
                "B"
        ));
        questions.add(new Question(
                "Which element has the chemical symbol 'O'?",
                new String[]{"Gold", "Oxygen", "Osmium", "Ozone"},
                "B"
        ));
        questions.add(new Question(
                "Who wrote 'Romeo and Juliet'?",
                new String[]{"Charles Dickens", "William Shakespeare", "Mark Twain", "Jane Austen"},
                "B"
        ));
        questions.add(new Question(
                "Which language has the most native speakers worldwide?",
                new String[]{"English", "Spanish", "Mandarin Chinese", "Hindi"},
                "C"
        ));
        return questions;
    }
}
