import view.QuizView;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            QuizView app = new QuizView();
            app.setVisible(true);
        });
    }
}
