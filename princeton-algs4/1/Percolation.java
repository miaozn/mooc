import edu.princeton.cs.algs4.WeightedQuickUnionUF;


public class Percolation
{
	private WeightedQuickUnionUF _board;
	private int _N;
	private boolean[] _isOpened;
	private boolean[] _isBottom;
	private int _waterFrom = -1;
	private boolean _isPercolated = false;

	public Percolation(int N)
	{
		if(N <= 0) throw new java.lang.IllegalArgumentException();
		_board = new WeightedQuickUnionUF(N*N);
		_N = N;
		_isOpened = new boolean[N*N];
		_isBottom = new boolean[N*N];
		for(int i=0; i<N; ++i)
		{
			_isBottom[goto1D(N-1, i)] = true;
		}
	}

	private int goto1D(int i, int j)
	{
		return i*_N + j;
	}

	private void myUnion(int id1, int id2)
	{
		int root1 = _board.find(id1);
		int root2 = _board.find(id2);
		if(_isBottom[root1] || _isBottom[root2])
		{
			_isBottom[root1] = true;
			_isBottom[root2] = true;
			if(!_isPercolated && (isFull(id1) || isFull(id2))) _isPercolated = true;
		}
		_board.union(id1, id2);
	}

	private void check(int i, int j)
	{
		if(i <= 0 || i > _N || j <= 0 || j > _N)
		{
			throw new java.lang.IndexOutOfBoundsException();
		}
	}
	public void open(int i, int j)
	{
		check(i, j);
		--i;
		--j;
		int id = goto1D(i, j);
		if(_isOpened[id]) return;
		_isOpened[id] = true;
		if(i == 0)
		{
			if(_waterFrom == -1)
			{
				_waterFrom = j;
				if(_N == 1) _isPercolated = true;
			}
			else
			{
				myUnion(id, goto1D(0, _waterFrom));
			}
		}

		if(i != _N - 1 && isOpen(i+1+1, j+1)) 
		{
			myUnion(id, goto1D(i+1, j));
		}

		if(i != 0 && isOpen(i-1+1, j+1))
		{
			myUnion(id, goto1D(i-1, j));
		}

		if(j != _N - 1 && isOpen(i+1, j+1+1))
		{
			myUnion(id, goto1D(i, j+1));
		}

		if(j != 0 && isOpen(i+1, j-1+1))
		{
			myUnion(id, goto1D(i, j-1));
		}

	}

	public boolean isOpen(int i, int j)
	{
		check(i, j);
		--i;
		--j;
		return _isOpened[goto1D(i, j)];
	}


	private boolean isFull(int id)
	{
		return _waterFrom != -1 && _isOpened[id] 
			&& _board.connected(id, goto1D(0, _waterFrom));
	}

	public boolean isFull(int i, int j)
	{
		check(i, j);
		return isFull(goto1D(i-1, j-1));
	}

	public boolean percolates()
	{
		return _isPercolated;
	}
}