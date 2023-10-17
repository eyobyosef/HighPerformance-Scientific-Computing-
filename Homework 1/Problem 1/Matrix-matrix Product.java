import org.apache.commons.math3.linear.*;
import org.apache.commons.math3.random.RandomDataGenerator;

public class MatrixMultiplication {

    public static void main(String[] args) {
        int n = 1000;
        RandomDataGenerator generator = new RandomDataGenerator();
        RealMatrix A = createRandomMatrix(n, n, generator);
        RealMatrix B = createRandomMatrix(n, n, generator);
        RealMatrix C = new Array2DRowRealMatrix(n, n);
        RealMatrix CC = new Array2DRowRealMatrix(n, n);

        long startTime = System.currentTimeMillis();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    C.addToEntry(i, j, A.getEntry(i, k) * B.getEntry(k, j));
                }
            }
        }
        long endTime = System.currentTimeMillis();
        double timeloop = (endTime - startTime) / 1000.0; // in seconds

        startTime = System.currentTimeMillis();
        for (int j = 0; j < n; j++) {
            CC.setColumnMatrix(j, A.multiply(B.getColumnMatrix(j)));
        }
        endTime = System.currentTimeMillis();
        double timeloopvec = (endTime - startTime) / 1000.0; // in seconds

        startTime = System.currentTimeMillis();
        RealMatrix CCC = A.multiply(B);
        endTime = System.currentTimeMillis();
        double timevec = (endTime - startTime) / 1000.0; // in seconds

        System.out.println("Time using loops: " + timeloop + " seconds");
        System.out.println("Time using loop with vectorization: " + timeloopvec + " seconds");
        System.out.println("Time using direct multiplication: " + timevec + " seconds");
        
        double normDiffCC = C.subtract(CC).getFrobeniusNorm();
        double normDiffCCC = C.subtract(CCC).getFrobeniusNorm();

        System.out.println("Norm difference between C and CC: " + normDiffCC);
        System.out.println("Norm difference between C and CCC: " + normDiffCCC);
        
        System.out.println("Speedup of loop with vectorization over loops: " + timeloop / timeloopvec);
        System.out.println("Speedup of direct multiplication over loops: " + timeloop / timevec);
        System.out.println("Speedup of direct multiplication over loop with vectorization: " + timeloopvec / timevec);
    }

    private static RealMatrix createRandomMatrix(int rows, int columns, RandomDataGenerator generator) {
        RealMatrix matrix = new Array2DRowRealMatrix(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrix.setEntry(i, j, generator.nextUniform(0.0, 1.0));
            }
        }
        return matrix;
    }
}
