import java.util.*;

public class Board
{

    private int[][] _block;
    private int _manhattanDist;
    private int _hammingDist;
    private char _blankX;
    private char _blankY;

    public Board(int[][] blocks)
    {
        _manhattanDist = 0;
        _hammingDist = 0;
        _blankX = 200;
        _blankY = 200;
        int n = blocks.length;
        _block = new int[n][n];
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                // copy
                _block[i][j] = blocks[i][j];
                
                if(blocks[i][j] != 0)
                {
                    // hamming
                    int ref = i * n + j + 1;
                    if(blocks[i][j] != ref) ++_hammingDist;
                    
                    // manhattan
                    ref = blocks[i][j];
                    int ref_i = (ref - 1) / n;
                    int ref_j = (ref - 1) % n;
                    _manhattanDist += (Math.abs(ref_i - i) + Math.abs(ref_j - j));
                }
                else
                {
                    _blankX = (char)i;
                    _blankY = (char)j;
                }
            }
        }
        
    }
    
    public int dimension()
    {
        return _block.length;
    }
    
    public int hamming()
    {
        return _hammingDist;
    }
    
    public int manhattan()
    {
        return _manhattanDist;
    }
    
    
    public boolean isGoal()
    {
        return _hammingDist == 0;
    }
    
    public Board twin()
    {
        Board result = null;
        if(_block[0][0] == 0 || _block[0][1] == 0)
        {
            swap(1, 0, 1, 1);
            result = new Board(_block);
            swap(1, 0, 1, 1);
        }
        else
        {
            swap(0, 0, 0, 1);
            result = new Board(_block);
            swap(0, 0, 0, 1);
        }
        
        return result;
    }
    
    private void swap(int i1, int j1, int i2, int j2)
    {
        int t = _block[i1][j1];
        _block[i1][j1] = _block[i2][j2];
        _block[i2][j2] = t;
    }
    
    public boolean equals(Object y)
    {
        if(this == y) return true;
        if(y == null) return false;
        if(!(y instanceof Board)) return false;
        
        Board that = (Board) y;
        int n = dimension();
        if(n != that.dimension()) return false;
        
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<n; ++j)
            {
                if(_block[i][j] != that._block[i][j]) return false;
            }
        }

        return true;
    }
    
    public Iterable<Board> neighbors()
    {
        int i = (int) _blankX;
        int j = (int) _blankY;
        List<Board> result = new ArrayList();
        int n = _block.length;
        
        //up
        if(i != 0)
        {
            swap(i, j, i - 1, j);
            result.add(new Board(_block));
            swap(i, j, i - 1, j);
        }
        
        //down
        if(i != n - 1)
        {
            swap(i, j, i + 1, j);
            result.add(new Board(_block));
            swap(i, j, i + 1, j);
        }
        
        //left
        if(j != 0)
        {
            swap(i, j, i, j - 1);
            result.add(new Board(_block));
            swap(i, j, i, j - 1);
        }
        
        //right
        if(j != n - 1)
        {
            swap(i, j, i, j + 1);
            result.add(new Board(_block));
            swap(i, j, i, j + 1);
        }
        
        return result;
        
    }

    
    public String toString()
    {

        StringBuilder s = new StringBuilder();
        int n = _block.length;
        s.append(n + "\n");
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                s.append(String.format("%2d ", _block[i][j]));
            }
            s.append("\n");
        }
        return s.toString();
    }
    
    

    
    public static void main(String[] args)
    {
        // implements..
    }
    
}