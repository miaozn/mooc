import java.util.*;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.MinPQ;

public class Solver
{
    
    private MinPQ<Node> _Q;
    private MinPQ<Node> _tQ;
    private Node _result;

    public Solver(Board initial)
    {
        if(initial == null) throw new java.lang.NullPointerException();
        _Q = new MinPQ(new ManhattanOrder());
        _Q.insert(new Node(initial, 0, null));
        _tQ = new MinPQ(new ManhattanOrder());
        _tQ.insert(new Node(initial.twin(), 0, null));
        
        
        Node cur = null;
        _result = null;
        while(true)
        {
            cur = _Q.delMin();
            if(cur.board.isGoal())
            {
                _result = cur;
                break;
            }
            
            for(Board b : cur.board.neighbors())
            {
                if(cur.prev != null && b.equals(cur.prev.board)) continue;
                _Q.insert(new Node(b, 1 + cur.nMoves, cur));
            }
            
            cur = _tQ.delMin();
            if(cur.board.isGoal())
            {
                break;
            }
            
            for(Board b : cur.board.neighbors())
            {
                if(cur.prev != null && b.equals(cur.prev.board)) continue;
                _tQ.insert(new Node(b, 1 + cur.nMoves, cur));
            }
            
        }
    }
    
    public boolean isSolvable()
    {
        return _result != null;
    }
    
    public int moves()
    {
        if(_result == null) return -1;
        return _result.nMoves;
    }
    
    public Iterable<Board> solution()
    {
        if(_result == null) return null;
        List<Board> path = new ArrayList();
        Node node = _result;
        while(node != null)
        {
            path.add(node.board);
            node = node.prev;
        }
        Collections.reverse(path);
        return path;
    }


    private class Node
    {
        public Board board;
        public int nMoves;
        public Node prev;
        public Node(Board b, int n, Node p)
        {
            board = b;
            nMoves = n;
            prev = p;
        }
    }
    
    private class ManhattanOrder implements Comparator<Node>
    {
        @Override
        public int compare(Node n1, Node n2)
        {
            int d1 = n1.board.manhattan();
            int d2 = n2.board.manhattan();
            int m1 = n1.nMoves;
            int m2 = n2.nMoves;
            if(d1 + m1 < d2 + m2) return -1;
            if(d1 + m1 > d2 + m2) return 1;
            int h1 = n1.board.hamming();
            int h2 = n2.board.hamming();
            if(h1 + m1 < h2 + m2) return -1;
            if(h1 + m1 > h2 + m2) return 1;
            return 0;
        }
    }



    public static void main(String[] args)
    {

        // create initial board from file
        In in = new In(args[0]);
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) blocks[i][j] = in.readInt();
        }
        Board initial = new Board(blocks);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable()) StdOut.println("No solution possible");
        else 
        {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution()) StdOut.println(board);
        }

        
    }
    
}